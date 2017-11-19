Imports bwl.Framework

Module App
    Private _app As New AppBase
    Private _logger As Logger = _app.RootLogger
    Private _deviceController As DeviceController
    Private _server As TcpServer
    Private _apProcessor As AccessPointController
    Sub Main()
        _logger.ConnectWriter(New ConsoleLogWriter)
        Dim cmd = Command().Split(" ")
        Dim baseName As String = "none"
        Dim baseUser As String = "none"
        Dim basePassword As String = "none"
        Dim baseServer As String = "none"
        Dim port As Integer = 9874
        For Each cmdItem In cmd
            Dim parts = cmdItem.Split(":")
            If parts.Length = 2 Then
                Select Case parts(0)
                    Case "base"
                        baseName = parts(1)
                    Case "user"
                        baseUser = parts(1)
                    Case "password"
                        basePassword = parts(1)
                    Case "server"
                        baseServer = parts(1)
                    Case "port"
                        port = CInt(parts(1))
                End Select
            End If
        Next
        _deviceController = New DeviceController(_logger)
        _deviceController.Open(baseServer, baseUser, basePassword, baseName)
        _apProcessor = New AccessPointController(_deviceController)
        _server = New TcpServer(_logger, _deviceController, port, _apProcessor)
        Do
            Threading.Thread.Sleep(100)
        Loop
    End Sub

End Module
