Public Interface IDeviceDriver
    Function IsDeviceSupported(data As Byte(), baseStation As String) As IDevice
    Function GetTableName() As String
    Function GetQueryCreatTable() As String
End Interface