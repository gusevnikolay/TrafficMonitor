Imports System.IO.Ports
Imports Bwl.Hardware.SimplSerial

Public Class App
    Private _ss As SimplSerialBus = New SimplSerialBus
    Private _radio As LoraController

    Private Sub App_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Try
            _radio = New LoraController()
            _radio.Start()
            AddHandler _radio.onRxLoraPacket, AddressOf onPacketHandler
            AddHandler _radio.OnTxComplite, AddressOf onTxHandler
            AddHandler _radio.onServicePacket, AddressOf onServiceRadioPacketHandler
            _logger.AddMessage("Finded: " + _ss.SerialDevice.DeviceAddress)
            _logger.CollectLogs(_ss)
        Catch ex As Exception
            _logger.AddError(ex.Message)
        End Try
    End Sub

    Public Sub onServiceRadioPacketHandler(packet As LoraPacket)
        Try
            Me.Invoke(Sub()
                          checkRxCodingRate2.CheckState = If(packet.ModemStatus.RxCodingRateTwo, 1, 0)
                          checkRxCodingRate1.CheckState = If(packet.ModemStatus.RxCodingRateOne, 1, 0)
                          checkRxCodingRate0.CheckState = If(packet.ModemStatus.RxCodingRateZero, 1, 0)
                          checkModemClear.CheckState = If(packet.ModemStatus.ModemClear, 1, 0)
                          checkHeaderValid.CheckState = If(packet.ModemStatus.HeaderInfoValid, 1, 0)
                          checkRXonGoing.CheckState = If(packet.ModemStatus.RxOnGoin, 1, 0)
                          checkSynchronized.CheckState = If(packet.ModemStatus.SignalSynchronized, 1, 0)
                          checkSignalDetected.CheckState = If(packet.ModemStatus.SignalDetected, 1, 0)
                          checkRxTimeout.CheckState = If(packet.IrqFlags.RxTimeout, 1, 0)
                          checkRxDone.CheckState = If(packet.IrqFlags.RxDone, 1, 0)
                          checkPayloadCrcError.CheckState = If(packet.IrqFlags.PayloadCrcError, 1, 0)
                          checkValidHeader.CheckState = If(packet.IrqFlags.ValidHeader, 1, 0)
                          checkTxDone.CheckState = If(packet.IrqFlags.TxDone, 1, 0)
                          checkCadDone.CheckState = If(packet.IrqFlags.CadDone, 1, 0)
                          checkFhssChangeChannel.CheckState = If(packet.IrqFlags.FhssChangeChannel, 1, 0)
                          checkCadDetected.CheckState = If(packet.IrqFlags.CadDetected, 1, 0)
                      End Sub)
        Catch ex As Exception
        End Try
    End Sub

    Public Sub onPacketHandler(packet As LoraPacket)
        Try
            Me.Invoke(Sub()
                          checkRxCodingRate2.CheckState = If(packet.ModemStatus.RxCodingRateTwo, 1, 0)
                          checkRxCodingRate1.CheckState = If(packet.ModemStatus.RxCodingRateOne, 1, 0)
                          checkRxCodingRate0.CheckState = If(packet.ModemStatus.RxCodingRateZero, 1, 0)
                          checkModemClear.CheckState = If(packet.ModemStatus.ModemClear, 1, 0)
                          checkHeaderValid.CheckState = If(packet.ModemStatus.HeaderInfoValid, 1, 0)
                          checkRXonGoing.CheckState = If(packet.ModemStatus.RxOnGoin, 1, 0)
                          checkSynchronized.CheckState = If(packet.ModemStatus.SignalSynchronized, 1, 0)
                          checkSignalDetected.CheckState = If(packet.ModemStatus.SignalDetected, 1, 0)
                          checkRxTimeout.CheckState = If(packet.IrqFlags.RxTimeout, 1, 0)
                          checkRxDone.CheckState = If(packet.IrqFlags.RxDone, 1, 0)
                          checkPayloadCrcError.CheckState = If(packet.IrqFlags.PayloadCrcError, 1, 0)
                          checkValidHeader.CheckState = If(packet.IrqFlags.ValidHeader, 1, 0)
                          checkTxDone.CheckState = If(packet.IrqFlags.TxDone, 1, 0)
                          checkCadDone.CheckState = If(packet.IrqFlags.CadDone, 1, 0)
                          checkFhssChangeChannel.CheckState = If(packet.IrqFlags.FhssChangeChannel, 1, 0)
                          checkCadDetected.CheckState = If(packet.IrqFlags.CadDetected, 1, 0)
                          ListLoraReceived.Items.Add(Now.ToString("HH:mm:ss") + "      " + ByteArrayToString(packet.Data))
                          _logger.AddMessage("RxRssi: " + packet.PacketRSSI.ToString + " OnGoRssi:" + packet.RxOnGoingRSSI.ToString)
                      End Sub)
        Catch ex As Exception
            _logger.AddError(ex.Message)
        End Try
    End Sub

    Public Shared Function StringToByteArray(ByVal hex As String) As Byte()
        Return Enumerable.Range(0, hex.Length).Where(Function(x) x Mod 2 = 0).[Select](Function(x) Convert.ToByte(hex.Substring(x, 2), 16)).ToArray()
    End Function

    Public Shared Function ByteArrayToString(ByVal ba As Byte()) As String
        Dim hex As String = BitConverter.ToString(ba)
        Return hex.Replace("-", " ")
    End Function

    Private Sub bReadReg_Click(sender As Object, e As EventArgs) Handles bReadReg.Click
        Try
            Dim addr = Convert.ToByte(textRegister.Text, 16)
            textRegValue.Text = (_radio.ReadReg(addr)).ToString()
            _logger.AddMessage("Reading ok")
        Catch ex As Exception
            _logger.AddError(ex.Message)
        End Try
    End Sub

    Private Sub onTxHandler()
        _logger.AddMessage("Lora Tx Done!")
    End Sub

    Private Sub bWriteReg_Click(sender As Object, e As EventArgs) Handles bWriteReg.Click
        Try
            Dim addr = Convert.ToByte(textRegister.Text, 16)
            Dim value = Convert.ToByte(textRegValue.Text, 16)
            _radio.WriteReg(addr, value)
            _logger.AddMessage("Writing ok")
        Catch ex As Exception
            _logger.AddError(ex.Message)
        End Try

    End Sub

    Private Sub bSendLora_Click(sender As Object, e As EventArgs) Handles bSendLora.Click
        Dim bytes = StringToByteArray(textSendToLora.Text.Replace(" ", ""))
        _radio.RadioWrite(bytes)
    End Sub
End Class
