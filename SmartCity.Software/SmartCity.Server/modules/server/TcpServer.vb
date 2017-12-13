Imports System.Net
Imports System.Net.Sockets
Imports bwl.Framework

Public Class TcpServer
    Private _logger As Logger
    Private _port As Integer
    Private _tcpClients As Dictionary(Of String, ClientProcessor) = New Dictionary(Of String, ClientProcessor)

    Event onDevicePacketEvent(packet As DevicePacket)

    Sub New(logger As Logger, tcpPort As Integer)
        _port = tcpPort
        _logger = logger
        Dim th = New Threading.Thread(AddressOf ListenProcess)
        th.IsBackground = True
        th.Start()
    End Sub

    Private Sub ListenProcess()
        Dim localAddr As IPAddress = Dns.GetHostEntry(Dns.GetHostName()).AddressList(0)
        Dim _server = New TcpListener(localAddr, _port)
        _server.Start()
        _logger.AddMessage("TCP server created on " + _port.ToString + " port")
        While True
            Try
                Dim client As TcpClient = _server.AcceptTcpClient()
                Dim cleintProcessor = New ClientProcessor(client)
                AddHandler cleintProcessor.onPacketReceived, AddressOf PacketHandler
                AddHandler cleintProcessor.onClinetDisconnectedEvent, AddressOf onClientDisconnectedHandelr
            Catch ex As Exception
                _logger.AddError(ex.Message)
            End Try
        End While
    End Sub

    Private Sub PacketHandler(packet As DevicePacket)
        _logger.AddMessage("TCP received data from: " + packet.AccessPointId)
        RaiseEvent onDevicePacketEvent(packet)
        If Not _tcpClients.ContainsKey(packet.AccessPointId) Then
            _tcpClients.Add(packet.AccessPointId, packet.Client)
        End If
    End Sub

    Public Function GetTcpClientsActivity() As List(Of String)
        Dim list As New List(Of String)
        Dim keySet = _tcpClients.Keys.ToArray
        For Each key In keySet
            list.Add("#" + key + "      " + _tcpClients(key).LastTime.ToString("dd\/MM\/yy hh:mm:ss"))
        Next
        Return list
    End Function

    Public Sub onClientDisconnectedHandelr(client As ClientProcessor)
        Dim keySet = _tcpClients.Keys.ToArray
        For Each key In keySet
            If client Is _tcpClients(key) Then
                _tcpClients.Remove(key)
            End If
        Next
    End Sub
End Class
