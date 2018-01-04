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
        Dim _server = New TcpListener(IPAddress.Parse("127.0.0.1"), _port)
        _server.Start()
        _logger.AddMessage("TCP server created on " + _port.ToString + " port")
        While True
            Try
                Dim client As TcpClient = _server.AcceptTcpClient()
                Dim cleintProcessor = New ClientProcessor(client)
                InsertProcess(cleintProcessor)
            Catch ex As Exception
                _logger.AddError(ex.Message)
            End Try
        End While
    End Sub

    Private Sub PacketHandler(packet As DevicePacket)
        _logger.AddMessage("TCP received data from: " + packet.AccessPointId)
        If Not _tcpClients.ContainsKey(packet.AccessPointId) Then
            _tcpClients.Add(packet.AccessPointId, packet.Client)
        End If
        RaiseEvent onDevicePacketEvent(packet)
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

    Public Function ClientExist(apId As String) As Boolean
        Return _tcpClients.ContainsKey(apId)
    End Function

    Public Function EjectProcess(apId As String) As ClientProcessor
        apId = _tcpClients.Keys.ElementAt(0)
        If _tcpClients.ContainsKey(apId) Then
            Dim client = _tcpClients(apId)
            RemoveHandler client.onPacketReceived, AddressOf PacketHandler
            Return client
        End If
        Throw New Exception("Device ID not found")
    End Function

    Public Sub InsertProcess(proc As ClientProcessor)
        AddHandler proc.onPacketReceived, AddressOf PacketHandler
        AddHandler proc.onClinetDisconnectedEvent, AddressOf onClientDisconnectedHandelr
    End Sub
End Class
