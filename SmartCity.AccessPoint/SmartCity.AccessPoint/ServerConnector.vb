Public Class ServerConnector
    Private _url As String = ""
    Private _keyId As String = ""
    Event onReceiveHandler(data As Byte())

    Sub New(url As String, serverKey As String)
        _url = url
    End Sub

    Public Sub Send(data As Byte())

    End Sub

End Class
