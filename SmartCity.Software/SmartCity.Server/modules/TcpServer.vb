Imports System.Net
Imports System.Net.Sockets
Imports bwl.Framework

Public Class TcpServer
    Private _logger As Logger
    Private _controller As DeviceController
    Private _port As Integer
    Private _apProcessor As AccessPointController
    Sub New(logger As Logger, controller As DeviceController, tcpPort As Integer, apProcessor As AccessPointController)
        _port = tcpPort
        _logger = logger
        _controller = controller
        _apProcessor = apProcessor
        Dim th = New Threading.Thread(AddressOf ListenProcess)
        th.IsBackground = True
        th.Start()
    End Sub

    Private Sub ListenProcess()
        Dim localAddr As IPAddress = Dns.GetHostEntry(Dns.GetHostName()).AddressList(0)
        Dim _server = New TcpListener(localAddr, _port)
        _server.Start()
        _logger.AddMessage("TCP server  -> started on " + localAddr.ToString + ":" + _port.ToString)
        While True
            Try
                Dim client As TcpClient = _server.AcceptTcpClient()
                _logger.AddMessage("TCP server -> connection from " + client.Client.RemoteEndPoint.ToString)
                Dim proc = New ClientProcessor(client, _controller, _apProcessor)
            Catch ex As Exception
                _logger.AddError("TCP server -> " + ex.Message)
            End Try
        End While
    End Sub
End Class
