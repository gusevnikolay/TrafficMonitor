Imports bwl.Hardware.SimplSerial

Public Class GenericAccessPoint
    Private _ss As New SimplSerialBus()
    Private _logger As Logger
    Private _processor As MessageProcess

    Sub New(ss As SimplSerialBus, log As Logger)
        _logger = log
        _ss = ss
        Dim th = New Threading.Thread(AddressOf WorkThread)
        th.Start()
    End Sub

    Sub WorkThread()
        While True
            If _ss.IsConnected Then
                Dim response = _ss.Request(0, 1, {})
                If response.ResponseState <> ResponseState.ok Then
                    _logger.AddWarning("Communication problem")
                Else
                    _logger.AddMessage("Incoming data: " + response.Data.Length.ToString + " bytes")
                    _processor.PutMessage(response.Data)
                End If
            End If
        End While
    End Sub
End Class
