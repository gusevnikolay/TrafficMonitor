Public Class Message
    Public ReadOnly Property ID As Byte()
    Public ReadOnly Property Data As Byte()
    Public ReadOnly Property Time As DateTime

    Sub New(data As Byte())
        Array.Copy(data, 0, ID, 0, 6)
        Array.Copy(data, 7, ID, 0, data.Length - 7)
        Time = Now
    End Sub
End Class
