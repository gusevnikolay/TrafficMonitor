﻿Imports Bwl.Hardware.SimplSerial

Public Class LoraController
    Private _bus As SimplSerialBus
    Private _lock As Object
    Private _deviceId As String = "Lora"
    Event onRxLoraPacket(packet As LoraPacket)
    Event onServicePacket(packet As LoraPacket)
    Event OnTxComplite()
    Dim _deviceFounded As Boolean = False

    Event Logger(type As String, msg As String)

    Sub New(ss As SimplSerialBus)
        _bus = ss
        _deviceFounded = True
    End Sub

    Sub New()
        _deviceFounded = False
    End Sub

    Public Sub Start()
        Dim th = New Threading.Thread(AddressOf RadioPolling)
        th.IsBackground = True
        th.Start()
    End Sub

    Public Function ReadReg(addr As Byte) As Byte
        Try
            Dim response = _bus.Request(0, 3, {addr})
            Return response.Data(0)
        Catch ex As Exception
            RaiseEvent Logger("ERR", ex.Message)
        End Try
        Return 0
    End Function

    Public Sub WriteReg(addr As Byte, val As Byte)
        Try
            Dim response = _bus.Request(0, 4, {addr, val})
        Catch ex As Exception
            RaiseEvent Logger("ERR", ex.Message)
        End Try
    End Sub


    Private Sub RadioPolling()

        While True
            If _deviceFounded Then
                Try
                    Dim response As SSResponse
                    response = _bus.Request(0, 1, {})
                    If response.ResponseState = ResponseState.ok Then
                        Dim packet As New LoraPacket
                        Dim irq As New LoraIrqFlags
                        Dim modemStatus As New LoraModemStatus
                        modemStatus.RxCodingRateTwo = If(response.Data(0) And &H80, 1, 0)
                        modemStatus.RxCodingRateOne = If(response.Data(0) And &H40, 1, 0)
                        modemStatus.RxCodingRateZero = If(response.Data(0) And &H20, 1, 0)
                        modemStatus.ModemClear = If(response.Data(0) And &H10, 1, 0)
                        modemStatus.HeaderInfoValid = If(response.Data(0) And &H8, 1, 0)
                        modemStatus.RxOnGoin = If(response.Data(0) And &H4, 1, 0)
                        modemStatus.SignalSynchronized = If(response.Data(0) And &H2, 1, 0)
                        modemStatus.SignalDetected = If(response.Data(0) And &H1, 1, 0)

                        irq.RxTimeout = If(response.Data(1) And &H80, 1, 0)
                        irq.RxDone = If(response.Data(1) And &H40, 1, 0)
                        irq.PayloadCrcError = If(response.Data(1) And &H20, 1, 0)
                        irq.ValidHeader = If(response.Data(1) And &H10, 1, 0)
                        irq.TxDone = If(response.Data(1) And &H8, 1, 0)
                        irq.CadDone = If(response.Data(1) And &H4, 1, 0)
                        irq.FhssChangeChannel = If(response.Data(1) And &H2, 1, 0)
                        irq.CadDetected = If(response.Data(1) And &H1, 1, 0)
                        packet.IrqFlags = irq
                        packet.ModemStatus = modemStatus
                        If irq.TxDone Then RaiseEvent OnTxComplite()

                        If irq.RxDone And irq.PayloadCrcError = False Then
                            If response.Data.Length > 3 Then
                                packet.RxOnGoingRSSI = response.Data(2) - 137
                                packet.PacketRSSI = response.Data(3) - 137
                                Dim Data(response.Data.Length - 5) As Byte
                                Array.Copy(response.Data, 4, Data, 0, Data.Length)
                                packet.Data = Data
                                RaiseEvent onRxLoraPacket(packet)
                            End If
                        Else
                            RaiseEvent onServicePacket(packet)
                        End If
                    End If
                Catch ex As Exception
                    RaiseEvent Logger("ERR", ex.Message)
                End Try
                Threading.Thread.Sleep(10)
            Else
                Dim ports = IO.Ports.SerialPort.GetPortNames
                For Each port In ports
                    Try
                        Dim test = New SimplSerialBus(port)
                        test.SerialDevice.DeviceSpeed = 115200
                        test.Connect()
                        If (test.RequestDeviceInfo(0).DeviceName.ToLower.Contains(_deviceId.ToLower)) Then
                            test.Disconnect()
                            _bus = New SimplSerialBus(port)
                            _bus.SerialDevice.DeviceSpeed = 115200
                            _bus.Connect()
                            _deviceFounded = True
                        End If
                    Catch ex As Exception
                    End Try
                Next
            End If
        End While
    End Sub

    Public Sub RadioWrite(data As Byte())
        _bus.Request(0, 2, data)
    End Sub
End Class
