Imports System.Net.Sockets
Imports Bwl.Hardware.SimplSerial

Public Class Bootloader

    Public Event onBootEvent(desc As String, progress As Integer)
    Private _serverIp As String = ""
    Private _serverPort As Integer = 0
    Private _client As TcpClient = Nothing
    Private _destinationDeviceId As String = ""
    Public Property IsConnected As Boolean = False

    Sub New(ip As String, port As Integer)
        _serverIp = ip
        _serverPort = port
        Dim th = New Threading.Thread(AddressOf Connect)
        th.IsBackground = True
        th.Start()
    End Sub

    Public Sub SetDestinationDeviceId(id As String)
        _destinationDeviceId = id
    End Sub

    Private Sub Connect()
        While True
            If _client Is Nothing Then
                Try
                    _client = New TcpClient()
                    _client.Connect(_serverIp, _serverPort)
                    IsConnected = True
                Catch ex As Exception
                    _client = Nothing
                End Try
            End If
            Threading.Thread.Sleep(1000)
        End While
    End Sub

    Private Function SendDataRequest() As Byte()
        Return Nothing
    End Function

    Private Function decodeData(hex As String) As Byte()
        Dim data(hex.Length / 2 - 1) As Byte
        For i = 0 To data.Length - 1
            data(i) = Convert.ToInt16(hex.Substring(i * 2, 2), 16)
        Next
        Return data
    End Function

    Public Sub Upload(hexPath As String)
        If (IsConnected = False) Then Throw New Exception("Server not connected")
        Try
            Using sr As IO.StreamReader = New IO.StreamReader(hexPath)
                Dim lines As String() = (sr.ReadToEnd()).Split(Environment.NewLine)
                For i = 0 To lines.Length - 1
                    Dim hexLine = lines(i)
                    If hexLine.Contains(":") Then
                        Dim hexData = hexLine.Split(":")(1)
                        If (hexData.Length > 8) Then
                            Dim dataLength As UInt16 = Convert.ToInt16(hexData.Substring(0, 2), 16)
                            Dim address As UInt16 = Convert.ToInt16(hexData.Substring(2, 4), 16)
                            Dim hexType As UInt16 = Convert.ToInt16(hexData.Substring(6, 2), 16)
                            If hexType = 0 Then
                                Dim flashData = decodeData(hexData.Substring(8, dataLength * 2))
                                Dim data(dataLength + 2) As Byte
                                data(0) = CByte(address >> 8)
                                data(1) = CByte(address Mod 256)
                                data(2) = Convert.ToInt16(hexData.Substring(8 + dataLength * 2, 2), 16)
                                Array.Copy(flashData, 0, data, 3, flashData.Length)
                            End If
                        End If
                    End If
                Next
            End Using
        Catch e As Exception

        End Try
    End Sub
End Class
