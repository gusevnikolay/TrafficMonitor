Imports Bwl.Framework

Public Class ApplicationMonitor
    Private _sqlBase As String = "default"
    Private _sqlUser As String = "default"
    Private _sqlPassword As String = "default"
    Private _tcpPort As Integer = 8000

    Private _server As TcpServer
    Private _logger As Logger
    Private _deviceManager As DeviceManager
    Private _base As DataBase
    Sub New(logger As Logger)
        _logger = logger
    End Sub

    Public Sub SetSqlSetting(base As String, user As String, password As String)
        _sqlBase = base
        _sqlPassword = password
        _sqlUser = user
    End Sub

    Public Sub SetServerSetting(port As Integer)
        _tcpPort = port
    End Sub

    Public Sub Run()
        _server = New TcpServer(_logger, _tcpPort)
        _base = New DataBase(_sqlUser, _sqlPassword, _sqlBase)
        _base.SetRootLogger(_logger)
        _base.Open()
        _deviceManager = New DeviceManager(_base)
        AddHandler _server.onDevicePacketEvent, AddressOf _deviceManager.DevicePacketHandler
    End Sub

    Public Function GetAccessPoints() As List(Of String)
        Return _server.GetTcpClientsActivity
    End Function
End Class
