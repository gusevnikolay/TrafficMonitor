Imports bwl.Framework
Imports MySql.Data.MySqlClient

Public Class DeviceController
    Private _con As MySqlConnection
    Private _sqlServer As String = ""
    Private _sqlUser As String = ""
    Private _sqlPassword As String = ""
    Private _sqlBaseName As String = ""
    Private _logger As Logger
    Private _connected As Boolean = False

    Private DriverList As List(Of IDeviceDriver) = New List(Of IDeviceDriver)

    Sub New(logger As Logger)
        _logger = logger
        DriverList.Add(New TrafficMonitorDriver())
    End Sub

    Public Sub Open(sqlServer As String, sqlUser As String, sqlPassword As String, sqlBaseName As String)
        _sqlBaseName = sqlBaseName
        _sqlServer = sqlServer
        _sqlPassword = sqlPassword
        _sqlUser = sqlUser
        _con = New MySqlConnection()
        _con.ConnectionString = "server=" + _sqlServer + ";User id=" + _sqlUser + ";password=" + _sqlPassword + ";database=" + _sqlBaseName
        _logger.AddMessage("Base parameters: " + _con.ConnectionString)
        Dim th = New Threading.Thread(AddressOf OpenProcess)
        th.IsBackground = True
        th.Start()
    End Sub

    Private Sub OpenProcess()
        While True
            If (_connected = False) Then
                Try
                    _con.Open()
                    _connected = True
                    _logger.AddError("MySQL connected")
                    CheckTable()
                Catch ex As Exception
                    _logger.AddError("MySQL: " + ex.Message)
                End Try
            End If
            Threading.Thread.Sleep(3000)
        End While
    End Sub

    Private Sub CheckTable()
        Dim cmd As New MySqlCommand
        cmd.Connection = _con
        cmd.CommandText = "SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_TYPE = 'BASE TABLE' AND TABLE_SCHEMA='" + _sqlBaseName + "'"
        Dim reader As MySqlDataReader
        reader = cmd.ExecuteReader()
        Dim tables As List(Of String) = New List(Of String)
        While reader.Read()
            tables.Add(reader.GetValue(0).ToString)
        End While
        reader.Close()
        cmd.Dispose()
        For i = 0 To DriverList.Count - 1
            Dim deviceName = DriverList(i).GetTableName
            Dim tablePresent = False
            For ii = 0 To tables.Count - 1
                If (tables(ii).ToLower.Contains(deviceName.ToLower)) Then
                    tablePresent = True
                End If
            Next
            If Not tablePresent Then
                cmd = New MySqlCommand
                cmd.Connection = _con
                cmd.CommandText = DriverList(i).GetQueryCreatTable
                Try
                    cmd.ExecuteNonQuery()
                    cmd.Dispose()
                Catch ex As Exception
                    _logger.AddError(ex.Message)
                End Try

            End If
        Next
    End Sub


    Public Sub DevicePacketHandler(data As Byte(), baseStation As String)
        For i = 0 To DriverList.Count - 1
            Dim device = DriverList(i).IsDeviceSupported(data, baseStation)
            If device IsNot Nothing Then
                Dim cmd As New MySqlCommand
                cmd.Connection = _con
                _logger.AddDebug(device.GetQueryСondition)
                cmd.CommandText = device.GetQueryСondition
                Try
                    cmd.ExecuteNonQuery()
                Catch ex As Exception
                End Try
                _logger.AddMessage("MSG from " + device.DeviceId.ToString)
                Return
            End If
        Next
    End Sub
End Class
