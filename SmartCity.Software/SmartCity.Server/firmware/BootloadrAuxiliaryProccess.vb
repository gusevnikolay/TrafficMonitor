﻿''' <summary>
''' Вспомогательный класс для работы загрузчика. Проверяет и детектирует выполнение текущих задач прошивки конкретного устройства
''' </summary>
Public Class BootloadrAuxiliaryProccess

    Private _bootMode As Boolean = False
    Private _currentFlashAddress As UInt16 = 0
    Private _flashAddressShift As UInt16 = 0
    Private _deviceId As String = ""
    Private _mainAppIsRunned As Boolean = False

    Sub New(deviceId As String)
        _deviceId = deviceId
    End Sub

    Public Function IsBootMode() As Boolean
        Return _bootMode
    End Function

    Public Function FlashWriteIsComplete(addr As UInt16) As Boolean
        Return _currentFlashAddress = addr
    End Function

    Public Function FlashShiftIsComplete(addr As UInt16) As Boolean
        Return _flashAddressShift = addr
    End Function

    Public Function MainAppIsRunned() As Boolean
        Return _mainAppIsRunned
    End Function

    Public Sub PacketHandler(pack As DevicePacket)
        If pack.DeviceId = _deviceId Then
            If pack.Data(0) = 48 And pack.Data(1) = 85 And pack.Data(2) = 127 Then
                _bootMode = True
            End If
            If pack.Data(0) = 148 And pack.Data(1) = 185 And pack.Data(2) = 27 Then
                _flashAddressShift = (pack.Data(3) * 256 + pack.Data(4))
            End If
            If pack.Data(0) = 24 And pack.Data(1) = 42 And pack.Data(2) = 64 Then
                _currentFlashAddress = (pack.Data(3) * 256 + pack.Data(4))
            End If
            If pack.Data(0) = 87 And pack.Data(1) = 24 And pack.Data(2) = 73 Then
                _mainAppIsRunned = True
            End If
        End If
    End Sub
End Class