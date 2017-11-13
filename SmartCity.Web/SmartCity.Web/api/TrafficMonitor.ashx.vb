Imports System.Web
Imports System.Web.Services
Imports MySql.Data.MySqlClient

Public Class TrafficMonitor
    Implements System.Web.IHttpHandler

    Sub ProcessRequest(ByVal context As HttpContext) Implements IHttpHandler.ProcessRequest
        Dim _con As New MySqlConnection()
        _con = New MySqlConnection()
        _con.ConnectionString = "server=localhost;User id=appender;password=appender;database=smart_city"
        _con.Open()
        Dim cmd As New MySqlCommand
        cmd.Connection = _con
        cmd.CommandText = "SELECT * from traffic_monitor;"
        Dim reader As MySqlDataReader
        reader = cmd.ExecuteReader()
        Dim tables As List(Of String) = New List(Of String)
        While reader.Read()
            context.Response.Write("<br>" + reader.VisibleFieldCount.ToString + "      " + reader.GetValue(0).ToString)
        End While
        reader.Close()
        cmd.Dispose()
    End Sub

    ReadOnly Property IsReusable() As Boolean Implements IHttpHandler.IsReusable
        Get
            Return False
        End Get
    End Property

End Class