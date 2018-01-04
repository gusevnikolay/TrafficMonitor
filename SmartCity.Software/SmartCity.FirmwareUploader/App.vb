Imports Bwl.Framework

Public Class App
    Private _ipSetting As New StringSetting(_storage, "Server IP", "127.0.0.1")
    Private _portSetting As New StringSetting(_storage, "Server port", "8520")
    Private _pathSetting As New StringSetting(_storage, "Hex path", "")
    Private _bootloader As Bootloader = Nothing

    Private Sub App_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        textServerIp.Text = _ipSetting.Value
        textServerPort.Text = _portSetting.Value
        textHexPath.Text = _pathSetting.Value
        bServerConnect.BackColor = Color.LightPink
    End Sub

    Private Sub bUpload_Click(sender As Object, e As EventArgs) Handles bUpload.Click
        If _bootloader Is Nothing Then
            _logger.AddError("Server not connected")
        Else
            _bootloader.SetDestinationDeviceId(textDeviceId.Text)
            _bootloader.Upload(textHexPath.Text)
        End If
    End Sub

    Private Sub bServerConnect_Click(sender As Object, e As EventArgs) Handles bServerConnect.Click
        _bootloader = New Bootloader(textServerPort.Text, CInt(textServerPort.Text))
        _logger.AddMessage("Attempt to connect")
        timer.Start()
    End Sub

    Private Sub timer_Tick(sender As Object, e As EventArgs) Handles timer.Tick
        If _bootloader.IsConnected Then
            bServerConnect.BackColor = Color.LightGreen
        Else
            bServerConnect.BackColor = Color.LightPink
        End If
    End Sub
End Class
