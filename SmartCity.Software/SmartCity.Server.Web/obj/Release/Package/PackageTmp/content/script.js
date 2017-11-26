var _lastid = 0;
var _trafficUrl = "/api/TrafficMonitor.ashx";

$(document).ready(function () {

});

$(function () {
    traffic_monitor_update();
    $("#button_clear_traffic_monitor_base").click(function () {
        $.get(_trafficUrl + "?act=clear_base", function (data, status) {
            var table_header = $("traffic_monitor_row").clone();
            $("#traffic_monitor_table").empty();
            table_header.prependTo("traffic_monitor_table");
        });
    });
    setInterval(traffic_monitor_update, 2000);
});

function traffic_monitor_show_map(obj)
{
    alert(obj);
    $('#message_modal').modal('show');
    $("#message_modal").css("z-index", "1500");
}

function traffic_monitor_update() {
    $.get(_trafficUrl+"?last_id=" + _lastid, function (data, status) {
        var json = JSON.parse(data);
        var data_count = json.result.length;
        for (var i = 0; i < data_count; i++) {
            if (_lastid < parseInt(json.result[i].id)) _lastid = parseInt(json.result[i].id);
            $("#traffic_monitor_table").prepend("<tr onclick='traffic_monitor_show_map(this)'><td>" + json.result[i].id+"</td><td>"+json.result[i].device_id + "</td><td>" + json.result[i].flow_speed + "</td><td>" + json.result[i].latitude + "</td><td>" + json.result[i].longitude + "</td><td>" + json.result[i].device_time + "</td><td>" + json.result[i].input_voltage + "</td><td>" + json.result[i].battery_voltage + "</td></tr>");
        }
    });
}