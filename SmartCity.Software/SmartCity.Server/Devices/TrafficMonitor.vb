Imports SmartCity.Server

Public Class TrafficMonitor
    Inherits BaseDevice
    Public Property RoadFlowSpeed As Single
    Public Property Latitude As String
    Public Property Longitude As String
    Public Property InputVoltage As Single
    Public Property BatteryVoltage As Single
    Public Property BaseStationAddress As String
    Sub New(data As Byte(), baseStation As String)
        DeviceId = GetHexString(data, 0, 6)
        DeviceTime = data(6).ToString + ":" + data(7).ToString + ":" + data(8).ToString
        RoadFlowSpeed = (data(9) * 256 + data(10)) * 0.1
        InputVoltage = (data(11) * 256 + data(12)) * 0.1
        BatteryVoltage = (data(13) * 256 + data(14)) * 0.1
        Latitude = System.Text.Encoding.ASCII.GetString(data).Substring(15, 8)
        Longitude = System.Text.Encoding.ASCII.GetString(data).Substring(23, 9)
        BaseStationAddress = baseStation
    End Sub

    Public Overrides Function GetQueryСondition() As String
        Return "INSERT INTO traffic_monitor (device_id, base_station, device_time, latitude, longitude, flow_speed, input_voltage, time, battery_voltage) VALUES('" + DeviceId + "', '" + BaseStationAddress + "', '" + DeviceTime + "', '" + Latitude + "', '" + Longitude + "', " + RoadFlowSpeed.ToString.Replace(",", ".") + ", " + InputVoltage.ToString.Replace(",", ".") + ", NOW(), " + BatteryVoltage.ToString.Replace(",", ".") + ");"
    End Function
End Class

Public Class TrafficMonitorDriver
    Implements IDeviceDriver
    Sub New()

    End Sub

    Public Function GetQueryCreatTable() As String Implements IDeviceDriver.GetQueryCreatTable
        Dim query = "CREATE TABLE traffic_monitor(
        id INT NOT NULL AUTO_INCREMENT,
        PRIMARY KEY(id), 
        device_id       VARCHAR(16) NOT NULL, 
        base_station    VARCHAR(16),
        device_time     VARCHAR(16), 
        latitude        VARCHAR(16),         
        longitude       VARCHAR(16), 
        flow_speed      VARCHAR(16), 
        input_voltage   decimal(5,2), 
        time            TIMESTAMP,
        battery_voltage decimal(5,2));"
        Return query
    End Function

    Public Function GetTableName() As String Implements IDeviceDriver.GetTableName
        Return "traffic_monitor"
    End Function

    Public Function IsDeviceSupported(data As Byte(), baseStation As String) As IDevice Implements IDeviceDriver.IsDeviceSupported
        If (data(0) = 1) Then
            Return New TrafficMonitor(data, baseStation)
        End If
        Return Nothing
    End Function
End Class

