<%@ Page Language="vb" AutoEventWireup="false" CodeBehind="index.aspx.vb" Inherits="SmartCity.Web.TrafficMonitor" %>
<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <title>Умный город</title>
    <script src="/libs/jquery-1.11.3.js"></script>
    <link href="/content/css/style.css" rel="stylesheet"/>
</head>

<body>
   <table style="width:100%; ">
       <tr>
           <td colspan="2">
               <div class="header">
                   Панель управления
               </div>
           </td>
       </tr>
       <tr>
           <td style="width:250px;">
               <div class="menu_left">
                   <div class="header">Базовые единицы</div>
                   <div class="item">Датчики пробок</div>
                   <div class="item">Светофоры</div>
                   <div class="item">Освещение</div>
                   <div class="item">Транспорт</div>
               </div>
           </td>
           <td>
               <div class="content">
                    Контент
               </div>           
           </td>
       </tr>
        <tr>
           <td colspan="2">
               <div class="footer">
                  
               </div>
           </td>
       </tr>
   </table>
</body>
</html>
