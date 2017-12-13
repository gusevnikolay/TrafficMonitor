<%@ Page Language="vb" AutoEventWireup="false" CodeBehind="Main.aspx.vb" Inherits="SmartCity.Web.Main" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <title>Server state</title>
    <meta charset="utf-8"/>
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no"/>
    <meta name="description" content=""/>
    <meta name="author" content=""/>
    <meta charset="utf-8"/>
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no"/>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
    <script src="content/bootstrap.js"></script>
    <script src="content/bootstrap.min.js"></script>
    <script src="content/npm.js"></script>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-beta.2/css/bootstrap.min.css" integrity="sha384-PsH8R72JQ3SOdhVi3uxftmaW6Vc51MKb0q5P2rRUpPvrszuE4W1povHYgTpBfshb" crossorigin="anonymous"/>
</head>
<body>
      <script src="/content/script.js"></script>  
      <header style="margin-bottom:80px;">
      <nav class="navbar navbar-expand-md navbar-dark fixed-top bg-dark">
        <a class="navbar-brand" href="#">Панель управления</a>
        <button class="navbar-toggler d-lg-none" type="button" data-toggle="collapse" data-target="#navbarsExampleDefault" aria-controls="navbarsExampleDefault" aria-expanded="false" aria-label="Toggle navigation">
          <span class="navbar-toggler-icon"></span>
        </button>

        <div class="collapse navbar-collapse" id="navbarsExampleDefault">
          <ul class="navbar-nav mr-auto">
            <li class="nav-item active">
              <a class="nav-link" href="#">Конечные устройства<span class="sr-only">(current)</span></a>
            </li>
            <li class="nav-item">
              <a class="nav-link" href="#">Базовые станции</a>
            </li>
            <li class="nav-item">
              <a class="nav-link" href="#">Статистика</a>
            </li>
            <li class="nav-item">
              <a class="nav-link" href="#">Логирование</a>
            </li>
          </ul>
        </div>
      </nav>
    </header>

    <div class="container-fluid">
      <div class="row">
        <nav class="col-sm-3 col-md-2 d-none d-sm-block bg-light sidebar">

          <ul class="nav nav-pills flex-column">
            <li class="nav-item">
              <a class="nav-link active" href="#">Транспортные потоки<span class="sr-only">(current)</span></a>
            </li>

            <li class="nav-item">
              <a class="nav-link" href="#">Светофоры</a>
            </li>

            <li class="nav-item">
              <a class="nav-link" href="#">Спецтранспорт</a>
            </li>

            <li class="nav-item">
              <a class="nav-link" href="#">ЖКХ</a>
            </li>

            <li class="nav-item">
              <a class="nav-link" href="#">Освещение</a>
            </li>

            <li class="nav-item">
              <a class="nav-link" href="#">Датчик среды</a>
            </li>
          </ul>
        </nav>   
        <main role="main" class="col-sm-9 ml-sm-auto col-md-10 pt-3">
          <h1>Датчики транспортного потока</h1>
           <div class="form-row">                
                <div class="col-sm-2">
                    <input type="id_filter" class="form-control" id="id_filter" placeholder="ID">
                </div>
                <button id="button_clear_traffic_monitor_base" type="button" class="btn btn-danger" style>Очистить базу данных</button>
          </div>          
          <div class="table-responsive">
            <table class="table table-striped" id="traffic_monitor_table">
              <thead>
                <tr id="traffic_monitor_row">
                  <th>#ID</th>
                  <th>Адрес</th>
                  <th>Скорость</th>
                  <th>Широта</th>
                  <th>Долгота</th>
                  <th>Время</th>
                  <th>Питание</th>
                  <th>Аккумулятор</th>
                  <th>RX RSSI</th>
                  <th>RXP RSSI</th>
                </tr>
              </thead>
              <tbody>              
              </tbody>
            </table>
          </div>
        </main>
      </div>
    </div>  
</div>      
</body>
</html>

