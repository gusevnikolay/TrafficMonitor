Imports bwl.Framework

Module App
    Private _app As New AppBase
    Private _logger As Logger = _app.RootLogger
    Private _messageProcessor As MessageProcess
    Private _accessPointId As String = ""
    Dim rnd As New Random()
    Sub Main()
        _accessPointId = Command()
        _logger.ConnectWriter(New ConsoleLogWriter)
        _messageProcessor = New MessageProcess(_accessPointId, "city.spacekennel.ru", 9874, _logger)
        While True
            Dim data As Byte() = {1, rnd.Next(255), rnd.Next(255), rnd.Next(255), rnd.Next(255), rnd.Next(255), 18, 45, 52, 2, 45, 0, 112, 0, 39, 52, 56, 48, 55, 46, 48, 51, 56, 48, 49, 49, 51, 49, 46, 48, 48, 48}
            Threading.Thread.Sleep(5000)
            _messageProcessor.PutMessage(data)
            _logger.AddMessage("Sending")
        End While
    End Sub

End Module
