Imports SmartCity.Server

Public Class AccessPointController
    Private _deviceController As DeviceController

    Sub New()

    End Sub

    Public Sub New(_deviceController As DeviceController)
        Me._deviceController = _deviceController
    End Sub

    Friend Function SetMessage(accessPointData() As Byte) As Object
        Throw New NotImplementedException()
    End Function
End Class
