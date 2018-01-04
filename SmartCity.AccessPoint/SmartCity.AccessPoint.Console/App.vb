Imports SmartCity.AccessPoint

Module App
    Private _ap As AccessPoint = Nothing
    Sub Main()
        _ap = New AccessPoint("127.0.0.1", 8520, "0000000001")
        _ap.Run()
        While (True)
            Threading.Thread.Sleep(1000)
        End While
    End Sub

End Module
