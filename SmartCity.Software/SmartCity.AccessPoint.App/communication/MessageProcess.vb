Imports System.Net.Sockets
Imports bwl.Framework

Public Class MessageProcess
    Private _server As String
    Private _port As Integer
    Private _logger As Logger
    Private _deviceDescriptor As String
    Sub New(deviceDescriptor As String, server As String, port As Integer, logger As Logger)
        _deviceDescriptor = deviceDescriptor
        _server = server
        _port = port
        _logger = logger
    End Sub

    Sub PutMessage(msg As Byte())
        Try
            Dim _con = New TcpClient(_server, _port)
            Dim _stream = _con.GetStream()
            _stream.Write({CByte(_deviceDescriptor.Length >> 8), CByte(_deviceDescriptor.Length And &HFF)}, 0, 2)
            _stream.Write(Text.Encoding.ASCII.GetBytes(_deviceDescriptor), 0, _deviceDescriptor.Length)
            _stream.Write({CByte(msg.Length)}, 0, 1)
            _stream.Write(msg, 0, msg.Length)
            _stream.Flush()
            Dim responseLenght = _stream.ReadByte()
            If responseLenght > 0 Then
                Dim buffer(responseLenght) As Byte
                _stream.Read(buffer, 0, responseLenght)
                ResponseHandler(buffer)
            End If
            _stream.Close()
            _con.Close()
        Catch ex As Exception
            _logger.AddMessage("Sending: " + ex.Message)

        End Try
    End Sub

    Private Sub ResponseHandler(data As Byte())
        _logger.AddMessage("Received from server: " + data.Length.ToString + " bytes")
    End Sub
End Class
