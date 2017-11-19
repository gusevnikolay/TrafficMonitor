Public Interface IDevice
    Property DeviceId As String
    Property DeviceTime As String
    Property BaseTableName As String
    Function GetQueryСondition() As String
End Interface
