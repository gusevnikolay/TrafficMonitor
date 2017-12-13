Imports Bwl.Framework
Imports MySql.Data.MySqlClient

Public Class DataBase
    Private _user As String = ""
    Private _password As String = ""
    Private _base As String = ""
    Private _logger As Logger
    Private _con As MySqlConnection

    Sub New(user As String, password As String, base As String)
        _user = user
        _password = password
        _base = base
    End Sub

    Public Sub SetRootLogger(logger As Logger)
        _logger = logger
    End Sub

    Public Sub Open()
        _con = New MySqlConnection()
        Dim setting = "server=city.spacekennel.ru;uid=" + _user + ";pwd=" & _password & ";database=" + _base
        _con.ConnectionString = setting
        Try
            _con.Open()
            _logger.AddMessage("MySQL connected")
        Catch ex As MySqlException
            _logger.AddMessage(ex.Message)
        End Try
    End Sub

    Public Sub Execute(sql As String)
        Dim cmd = New MySqlCommand(sql, _con)
        Try
            cmd.ExecuteNonQuery()
        Catch ex As Exception
            _logger.AddMessage(ex.Message)
        End Try
    End Sub
End Class
