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
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-beta.2/css/bootstrap.min.css" integrity="sha384-PsH8R72JQ3SOdhVi3uxftmaW6Vc51MKb0q5P2rRUpPvrszuE4W1povHYgTpBfshb" crossorigin="anonymous"/>
</head>
<body>
      <header style="margin-bottom:80px;">
      <nav class="navbar navbar-expand-md navbar-dark fixed-top bg-dark">
        <a class="navbar-brand" href="#">Панель управления</a>
        <button class="navbar-toggler d-lg-none" type="button" data-toggle="collapse" data-target="#navbarsExampleDefault" aria-controls="navbarsExampleDefault" aria-expanded="false" aria-label="Toggle navigation">
          <span class="navbar-toggler-icon"></span>
        </button>

        <div class="collapse navbar-collapse" id="navbarsExampleDefault">
          <ul class="navbar-nav mr-auto">
            <li class="nav-item active">
              <a class="nav-link" href="#">Базовые станции<span class="sr-only">(current)</span></a>
            </li>
            <li class="nav-item">
              <a class="nav-link" href="#">База данных</a>
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
              <a class="nav-link active" href="#">Overview <span class="sr-only">(current)</span></a>
            </li>
            <li class="nav-item">
              <a class="nav-link" href="#">Reports</a>
            </li>
            <li class="nav-item">
              <a class="nav-link" href="#">Analytics</a>
            </li>
            <li class="nav-item">
              <a class="nav-link" href="#">Export</a>
            </li>
          </ul>



          <ul class="nav nav-pills flex-column">
            <li class="nav-item">
              <a class="nav-link" href="#">Nav item again</a>
            </li>
            <li class="nav-item">
              <a class="nav-link" href="#">One more nav</a>
            </li>
            <li class="nav-item">
              <a class="nav-link" href="#">Another nav item</a>
            </li>
          </ul>
        </nav>

        <main role="main" class="col-sm-9 ml-sm-auto col-md-10 pt-3">
          <h1>Датчики потока автомобилей</h1>
          <div class="table-responsive">
            <table class="table table-striped">
              <thead>
                <tr>
                  <th>#ID</th>
                  <th>Скорость</th>
                  <th>Широта</th>
                  <th>Долгота</th>
                  <th>Время</th>
                  <th>Питание</th>
                  <th>Аккумулятор</th>
                </tr>
              </thead>
              <tbody>
                <tr>
                  <td>#010000000000</td>
                  <td>36.7</td>
                  <td>51.2458</td>
                  <td>52.054</td>
                  <td>18:20:14</td>
                  <td>11.2</td>
                  <td>3.98</td>
                </tr>
                  <tr>
                  <td>#010000000000</td>
                  <td>36.7</td>
                  <td>51.2458</td>
                  <td>52.054</td>
                  <td>18:20:14</td>
                  <td>11.2</td>
                  <td>3.98</td>
                </tr>
                <tr>
                  <td>#010000000000</td>
                  <td>36.7</td>
                  <td>51.2458</td>
                  <td>52.054</td>
                  <td>18:20:14</td>
                  <td>11.2</td>
                  <td>3.98</td>
                </tr>
              </tbody>
            </table>
          </div>
        </main>
      </div>
    </div>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.0/jquery.min.js"></script>
    <script src="https://code.jquery.com/jquery-3.2.1.slim.min.js" integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.3/umd/popper.min.js" integrity="sha384-vFJXuSJphROIrBnz7yo7oB41mKfc8JzQZiCq4NCceLEaO4IHwicKwpJf9c9IpFgh" crossorigin="anonymous"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-beta.2/js/bootstrap.min.js" integrity="sha384-alpBpkh1PFOepccYVYDB4do5UnbKysX5WZXm3XxPqe5iKTfUKjNkCk9SaVuEZflJ" crossorigin="anonymous"></script>   
</body>
</html>

