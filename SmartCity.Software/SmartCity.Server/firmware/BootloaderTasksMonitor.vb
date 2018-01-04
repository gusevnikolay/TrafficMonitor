Public Class BootloaderTasksMonitor

    Private _db As DataBase = Nothing
    Private _tcpServer As TcpServer = Nothing
    Private _deviceManager As DeviceManager = Nothing
    Private _tasks As List(Of Task) = New List(Of Task)

    Sub New(db As DataBase, tcpServer As TcpServer, deviceManager As DeviceManager)
        _db = db
        _tcpServer = tcpServer
        _deviceManager = deviceManager
    End Sub

    Public Sub AddTask(deviceId As String, hexPath As String)
        Dim task As New Task
        task.DeviceId = deviceId
        task.HexPath = hexPath
        _tasks.Add(Task)
    End Sub

    Private Function GetAccessPoint(deviceId As String) As String
        Dim sql = "select base_station from traffic_monitor where device_id='" + deviceId + "' ORDER BY rssi_packet ASC LIMIT 1;"
        Return _db.GetData(sql).ElementAt(0).Values.ElementAt(0)
    End Function

    Public Sub Run()
        Dim th = New Threading.Thread(AddressOf WorkProcess)
        th.IsBackground = True
        th.Start()
    End Sub

    Private Sub WorkProcess()
        While True
            If _tasks.Count > 0 Then
                Try
                    Dim task = _tasks.ElementAt(0)
                    Dim taskProccess = New FirmwareUpdateTask(task.DeviceId, _tcpServer.EjectProcess(""))
                    taskProccess.LoadHex(task.HexPath)
                    taskProccess.Run()
                    _tasks.RemoveAt(0)
                    _tcpServer.InsertProcess(taskProccess.GetAccessPointProccess)
                Catch ex As Exception
                End Try
            Else
                Threading.Thread.Sleep(1000)
            End If
        End While
    End Sub

    Public Function GetStates() As String()
        Dim list = New List(Of String)
        For Each task In _tasks
            list.Add(task.DeviceId + ": " + task.HexPath)
        Next
        Return list.ToArray()
    End Function
End Class

Public Class Task
    Public Property DeviceId As String = ""
    Public Property HexPath As String = ""
End Class
