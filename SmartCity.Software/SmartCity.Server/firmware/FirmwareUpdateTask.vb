Imports System.Windows.Forms

Public Class FirmwareUpdateTask
    Private _ap As ClientProcessor = Nothing
    Public Property DeviceId As String = ""
    Private _hexFile As String = ""
    Private _hexPath As String = ""
    Private _status As String = "Wait queue"
    Private _bootMode As Boolean = False
    Private _currentFlashAddress As UInt16 = 0
    Private _flashedAddress As UInt16 = 0
    Private _flashAddressShift As UInt16 = 0
    Private _subTaskProcess As Boolean = False
    Private _hashId As String = ""
    Sub New(deviceId As String, ap As ClientProcessor, hexPath As String)
        _ap = ap
        _hexPath = hexPath
        Me.DeviceId = deviceId
        _hashId = Tool.GenerateRandomString(30)
    End Sub

    Public Function GetTaskHash() As String
        Return _hashId
    End Function

    Private Sub LoadHex()
        Try
            Using sr As IO.StreamReader = New IO.StreamReader(_hexPath)
                _hexFile = sr.ReadToEnd()
            End Using
        Catch e As Exception
        End Try
    End Sub

    Public Sub EnterBootModeRequest()
        _status = "Wait bootloader"
        While (_bootMode = False)
            Dim data(2) As Byte
            data(0) = 38
            data(1) = 1
            data(2) = 245
            _subTaskProcess = False
            _ap.Send(DeviceId, data)
            Threading.Thread.Sleep(1000)
        End While
    End Sub

    Private Function DecodeHexData(hex As String) As Byte()
        Dim data(hex.Length / 2 - 1) As Byte
        For i = 0 To data.Length - 1
            data(i) = Convert.ToInt16(hex.Substring(i * 2, 2), 16)
        Next
        Return data
    End Function

    Public Sub Run()
        LoadHex()
        AddHandler _ap.onPacketReceived, AddressOf PacketHandler
        _bootMode = False
        EnterBootModeRequest()
        Dim lines = _hexFile.Split(Environment.NewLine)
        For i = 0 To lines.Length - 1
            Dim hexLine = lines(i)
            If hexLine.Contains(":") Then
                Dim hexData = hexLine.Split(":")(1)
                If (hexData.Length > 8) Then
                    Dim dataLength As UInt16 = Convert.ToInt16(hexData.Substring(0, 2), 16)
                    Dim address As UInt16 = Convert.ToInt16(hexData.Substring(2, 4), 16)
                    Dim hexType As UInt16 = Convert.ToInt16(hexData.Substring(6, 2), 16)
                    If hexType = 0 Then
                        Dim flashData = DecodeHexData(hexData.Substring(8, dataLength * 2))
                        Threading.Thread.Sleep(100)
                        SendHex(address, flashData)
                        _status = "Loading: " + Math.Round(i * 100 / lines.Count, 1).ToString
                    End If

                    If hexType = 2 Then
                        Dim sh = Tool.StringToByteArray(hexLine.Substring(8, 4))
                        SetAddressShift(sh(0) * 256 + sh(1))
                    End If

                    If hexType = 1 Then
                        StartMainApplication()
                    End If
                End If
            End If
        Next
    End Sub

    Public Function GetAccessPointProccess() As ClientProcessor
        Return _ap
    End Function

    Private Sub SendHex(address As UInt16, prog As Byte())
        Dim data(prog.Length + 6) As Byte
        data(0) = 76
        data(1) = 74
        data(2) = 98
        data(3) = CByte(address >> 8)
        data(4) = CByte(address Mod 256)
        Dim crc As UInt16 = 0
        For Each b In prog
            crc += b
        Next
        data(5) = CByte(prog.Length)
        data(6) = CByte(crc Mod 256)
        Array.Copy(prog, 0, data, 7, prog.Length)
        _currentFlashAddress = address
        _subTaskProcess = False
        While _subTaskProcess <> True
            _ap.Send(DeviceId, data)
            Threading.Thread.Sleep(1000)
        End While
    End Sub

    Private Sub SetAddressShift(shift As UInt16)
        Dim data(4) As Byte
        data(0) = 26
        data(1) = 126
        data(2) = 76
        data(3) = CByte(shift >> 8)
        data(4) = CByte(shift Mod 256)
        _flashAddressShift = shift
        _subTaskProcess = False
        _ap.Send(DeviceId, data)
        While _subTaskProcess <> True
            Threading.Thread.Sleep(100)
        End While
    End Sub

    Private Sub StartMainApplication()
        Dim data(2) As Byte
        data(0) = 1
        data(1) = 241
        data(2) = 38
        _subTaskProcess = False
        _ap.Send(DeviceId, data)
        While _subTaskProcess <> True
            Threading.Thread.Sleep(100)
        End While
    End Sub


    Private Sub PacketHandler(pack As DevicePacket)
        If pack.DeviceId = DeviceId Then
            Try
                If pack.Data(0) = 48 And pack.Data(1) = 85 And pack.Data(2) = 127 Then
                    _bootMode = True
                End If

                If pack.Data(0) = 148 And pack.Data(1) = 185 And pack.Data(2) = 27 Then
                    If _flashAddressShift = (pack.Data(3) * 256 + pack.Data(4)) Then
                        _subTaskProcess = True
                    End If
                End If

                If pack.Data(0) = 24 And pack.Data(1) = 42 And pack.Data(2) = 64 Then
                    If _currentFlashAddress = (pack.Data(3) * 256 + pack.Data(4)) Then
                        _subTaskProcess = True
                    End If
                End If

                If pack.Data(0) = 87 And pack.Data(1) = 24 And pack.Data(2) = 73 Then
                    _subTaskProcess = True
                End If
            Catch ex As Exception
                _status = ex.Message
            End Try
        End If
    End Sub

    Public Function GetInfo() As String
        Return DeviceId + ": " + _status
    End Function
End Class
