CREATE TABLE traffic_monitor (
	ID int PRIMARY KEY AUTO_INCREMENT,
    device_id varchar(20) NOT NULL,
    base_station varchar(20) NOT NULL,
    device_time varchar(10),
    latitude varchar(10),
    longitude varchar(10),
    mean_speed INT,
    min_speed INT,
    max_speed INT,
    rssi_packet INT,
    rssi INT,
    time TIMESTAMP,
    battery_voltage DOUBLE(10,2)
);