Imports Bwl.Framework
Imports SmartCity.Server

Public Class App
    Inherits FormAppBase
    Private _sqlBase As New StringSetting(_storage, "SQL Base name", "database")
    Private _sqlUser As New StringSetting(_storage, "SQL User", "user")
    Private _sqlPassword As New StringSetting(_storage, "SQL Password", "password")
    Private _tcpPort As New IntegerSetting(_storage, "TCP port", 8520)

    Private _app As ApplicationMonitor

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        _app = New ApplicationMonitor(_logger)
        _app.SetSqlSetting(_sqlBase.Value, _sqlUser.Value, _sqlPassword.Value)
        _app.SetServerSetting(_tcpPort.Value)
        _app.Run()
    End Sub

    Private Sub bUpdateAccessPointsList_Click(sender As Object, e As EventArgs) Handles bUpdateAccessPointsList.Click
        listAccessPoints.Items.Clear()
        Dim list = _app.GetAccessPoints
        For Each id In list
            listAccessPoints.Items.Add(id)
        Next
    End Sub

    Private Sub timer_Tick(sender As Object, e As EventArgs) Handles timer.Tick
        listAccessPoints.Items.Clear()
        Dim list = _app.GetAccessPoints
        For Each id In list
            listAccessPoints.Items.Add(id)
        Next
    End Sub
End Class
