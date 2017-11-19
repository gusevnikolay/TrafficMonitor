Imports System.IO.Ports

Public Class Flasher

    Private _serial As SerialPort
    Sub New(serial As SerialPort, hexFile As String)
        _serial = serial
    End Sub

    Public Sub WriteFirmware()

    End Sub
End Class
