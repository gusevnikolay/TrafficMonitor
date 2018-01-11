Imports System.Windows.Forms

Public Class FirmwareUpdateTask
    Private _accessPoint As AccessPointProcessor = Nothing
    Public Property DeviceId As String = ""
    Public Property Status As String = "Wait queue"
    Private _helper As BootloadrAuxiliaryProccess
    Private _task As BootloaderTasksMonitor.BootloaderTask

    Sub New(ap As AccessPointProcessor, task As BootloaderTasksMonitor.BootloaderTask)
        _accessPoint = ap
        _task = task
        _helper = New BootloadrAuxiliaryProccess(task.DeviceId)
    End Sub

    ''' <summary>
    ''' Проверка завершения работы загрузчика
    ''' </summary>
    ''' <returns></returns>
    Public Function isComplete() As Boolean
        Return _helper.MainAppIsRunned
    End Function
    ''' <summary>
    ''' Вводим устройство в режим загрузчика, отправляя ключевую пследоавтельность раз в секунду
    ''' </summary>
    Private Sub EnterBootMode()
        Status = "Waiting for bootloader mode"
        While (_helper.IsBootMode = False)
            Dim data(2) As Byte
            data(0) = 38
            data(1) = 1
            data(2) = 245
            _accessPoint.Send(DeviceId, data)
            Threading.Thread.Sleep(1000)
        End While
    End Sub

    Public Sub Start()
        Dim th = New Threading.Thread(AddressOf Run)
        th.IsBackground = True
        th.Start()
    End Sub

    Private Sub Run()
        Dim hexFile = ""
        Using sr As IO.StreamReader = New IO.StreamReader(_task.HexPath)
            hexFile = sr.ReadToEnd()
        End Using
        Me.DeviceId = _task.DeviceId
        AddHandler _accessPoint.onPacketReceived, AddressOf _helper.PacketHandler
        EnterBootMode()
        Dim lines = hexFile.Split(Environment.NewLine)
        For i = 0 To lines.Length - 1
            Dim hexLine = lines(i)
            If hexLine.Contains(":") Then
                Dim hexData = hexLine.Split(":")(1)
                If (hexData.Length > 8) Then

                    Dim dataLength As UInt16 = Convert.ToInt16(hexData.Substring(0, 2), 16)
                    Dim address As UInt16 = Convert.ToInt16(hexData.Substring(2, 4), 16)
                    Dim hexType As UInt16 = Convert.ToInt16(hexData.Substring(6, 2), 16)

                    If hexType = 0 Then
                        Dim flashData = Tool.DecodeHexData(hexData.Substring(8, dataLength * 2))
                        SendHexToDevice(address, flashData)
                        Status = "Download firmware: " + Math.Round(i * 100 / lines.Count, 1).ToString + "%"
                    End If

                    If hexType = 2 Then
                        Dim memoryShift = Tool.StringToByteArray(hexLine.Substring(8, 4))
                        SetDeviceAddressShift(memoryShift(0) * 256 + memoryShift(1))
                    End If

                    If hexType = 1 Then
                        StartMainApplication()
                    End If
                End If
            End If
        Next
        RemoveHandler _accessPoint.onPacketReceived, AddressOf _helper.PacketHandler
    End Sub

    ''' <summary>
    ''' Прошивает память
    ''' </summary>
    ''' <param name="address">Целевой адрес памяти</param>
    ''' <param name="prog">Данные для записи в память</param>
    Private Sub SendHexToDevice(address As UInt16, prog As Byte())
        Dim data(prog.Length + 6) As Byte
        data(0) = 76
        data(1) = 74
        data(2) = 98
        data(3) = CByte(address >> 8)
        data(4) = CByte(address Mod 256)
        Dim crc As UInt16 = 0
        For Each b In prog
            crc += b
        Next
        data(5) = CByte(prog.Length)
        data(6) = CByte(crc Mod 256)
        Array.Copy(prog, 0, data, 7, prog.Length)
        While _helper.FlashWriteIsComplete(address) <> True
            _accessPoint.Send(DeviceId, data)
            Threading.Thread.Sleep(2000)
        End While
    End Sub

    ''' <summary>
    ''' Устанавливаем смещение адреса прошивки
    ''' </summary>
    ''' <param name="shift">Смещение</param>
    Private Sub SetDeviceAddressShift(shift As UInt16)
        Dim data(4) As Byte
        data(0) = 26
        data(1) = 126
        data(2) = 76
        data(3) = CByte(shift >> 8)
        data(4) = CByte(shift Mod 256)
        While _helper.FlashShiftIsComplete(shift) <> True
            _accessPoint.Send(DeviceId, data)
            Threading.Thread.Sleep(100)
        End While
    End Sub

    ''' <summary>
    ''' Запускаем основной код
    ''' </summary>
    Private Sub StartMainApplication()
        Dim data(2) As Byte
        data(0) = 1
        data(1) = 241
        data(2) = 38
        While _helper.MainAppIsRunned <> True
            _accessPoint.Send(DeviceId, data)
            Threading.Thread.Sleep(100)
        End While
    End Sub
End Class
