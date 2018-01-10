Imports System.Windows.Forms
Imports Bwl.Framework

Public Class BootloaderTasksMonitor

    Private _db As DataBase = Nothing
    Private _tcpServer As TcpServer = Nothing
    Private _deviceManager As DeviceManager = Nothing
    Private _tasks As List(Of FirmwareUpdateTask) = New List(Of FirmwareUpdateTask)
    Private _logger As Logger
    Sub New(db As DataBase, tcpServer As TcpServer, deviceManager As DeviceManager, logger As Logger)
        _db = db
        _tcpServer = tcpServer
        _deviceManager = deviceManager
    End Sub

    Public Sub AddTask(deviceId As String, hexPath As String)
        Dim baseId = GetAccessPoint(deviceId)
        Dim ap = _tcpServer.EjectProcess(baseId)
        Dim newTask = New FirmwareUpdateTask(deviceId, ap, hexPath)
        _tasks.Add(newTask)
        _db.Execute("INSERT INTO firmware_tasks (device_id, base_station, hex_file, hash, state, time) VALUES('" + deviceId + "', '" + baseId + "', '" + IO.Path.GetFileName(hexPath) + "', '" + newTask.GetTaskHash + "', 'In queue', NOW());")
    End Sub

    Private Function GetAccessPoint(deviceId As String) As String
        Dim sql = "select base_station from traffic_monitor where device_id='" + deviceId + "' ORDER BY rssi_packet ASC LIMIT 1;"
        Dim sqlResult = _db.GetData(sql)
        If sqlResult.Count > 0 Then
            Return _db.GetData(sql).ElementAt(0).Values.ElementAt(0)
        End If
        Throw New Exception(deviceId + " not found in database.")
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
                    Dim task = _tasks.First()
                    _db.Execute("UPDATE firmware_tasks SET state = 'In process' WHERE device_id='" + task.DeviceId + "' and hash='" + task.GetTaskHash + "'")
                    task.Run()
                    '_tcpServer.InsertProcess(task.GetAccessPointProccess)
                    _tasks.Remove(task)
                    _db.Execute("UPDATE firmware_tasks SET state = 'Complete' WHERE device_id='" + task.DeviceId + "' and hash='" + task.GetTaskHash + "'")
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
            list.Add(task.GetInfo)
        Next
        Return list.ToArray()
    End Function
End Class

