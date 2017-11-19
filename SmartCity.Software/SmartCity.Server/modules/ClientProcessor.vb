Imports System.Net.Sockets

Public Class ClientProcessor
    Private _tcp As TcpClient = Nothing
    Private _stream As NetworkStream

    Private _clientDescription As String = ""
    Private _dataBuffer(300) As Byte
    Private _cursor As Integer = 0
    Private _base As DeviceController
    Private _apProcessor As AccessPointController

    Sub New(client As TcpClient, base As DeviceController, apProcessor As AccessPointController)
        _apProcessor = apProcessor
        _base = base
        _tcp = client
        _stream = _tcp.GetStream
        Dim th = New Threading.Thread(AddressOf ClientHandler)
        th.Start()
    End Sub

    Private Sub ClientHandler()
        While _tcp.Connected
            Try
                Dim accessPointDataLength = _stream.ReadByte * 256 + _stream.ReadByte
                Dim accessPointData(accessPointDataLength) As Byte
                _stream.Read(accessPointData, 0, accessPointDataLength)
                Dim deviceDataLength = _stream.ReadByte
                Dim deviceData(deviceDataLength - 1) As Byte
                _stream.Read(deviceData, 0, deviceDataLength)
                _base.DevicePacketHandler(deviceData, Text.Encoding.ASCII.GetString(accessPointData).Substring(0, 20))
                Dim response = _apProcessor.SetMessage(accessPointData)
                If (response IsNot Nothing) Then
                    _stream.Write({CByte(response.Length)}, 0, 1)
                    _stream.Write(response, 0, response.Length)
                    _stream.Flush()
                End If
                _stream.Close()
                _tcp.Close()
            Catch ex As Exception
                _cursor = 0
                For ii = 0 To _dataBuffer.Length - 1
                    _dataBuffer(ii) = 0
                Next
            End Try
        End While
    End Sub

    Private Sub AppendBytes(data As Byte())
        Array.Copy(data, 0, _dataBuffer, _cursor, data.Length)
        _cursor += data.Length
        Dim pointer As Integer = -1
        For i = 0 To _dataBuffer.Length - 16
            If _dataBuffer(i) = 0 And _dataBuffer(i + 1) = 14 And _dataBuffer(i + 2) = 62 And _dataBuffer(i + 3) = 54 And _dataBuffer(i + 4) = 2 And _dataBuffer(i + 5) = 104 And _dataBuffer(i + 6) = 254 And _dataBuffer(i + 7) = 80 Then
                pointer = i + 8
            End If
            If pointer <> -1 And _dataBuffer(i + 7) = 0 And _dataBuffer(i + 6) = 14 And _dataBuffer(i + 5) = 62 And _dataBuffer(i + 4) = 54 And _dataBuffer(i + 3) = 2 And _dataBuffer(i + 2) = 104 And _dataBuffer(i + 1) = 254 And _dataBuffer(i) = 80 Then
                _cursor = 0
                Dim message(i - pointer - 1) As Byte
                Array.Copy(_dataBuffer, pointer, message, 0, message.Length)

                For ii = 0 To _dataBuffer.Length
                    _dataBuffer(ii) = 0
                Next
            End If
        Next
    End Sub
End Class
