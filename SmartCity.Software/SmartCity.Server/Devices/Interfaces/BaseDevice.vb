Imports SmartCity.Server

Public MustInherit Class BaseDevice
    Implements IDevice
    Private _id As String
    Private _deviceString As String
    Private _tableName As String
    Private _deviceTime As String

    Public Property DeviceId As String Implements IDevice.DeviceId
        Get
            Return _id
        End Get
        Set(value As String)
            _id = value
        End Set
    End Property

    Public Property DeviceTime As String Implements IDevice.DeviceTime
        Get
            Return _deviceTime
        End Get
        Set(value As String)
            _deviceTime = value
        End Set
    End Property

    Public Property BaseTableName As String Implements IDevice.BaseTableName
        Get
            Return _tableName
        End Get
        Set(value As String)
            _tableName = value
        End Set
    End Property

    Public Function GetHexString(data As Byte(), startIndex As Integer, length As Integer) As String
        Dim hex = BitConverter.ToString(data)
        Return hex.Replace("-", "").Substring(startIndex * 2, length * 2)
    End Function

    Public MustOverride Function GetQueryСondition() As String Implements IDevice.GetQueryСondition
End Class
