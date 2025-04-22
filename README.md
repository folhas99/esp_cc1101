ESPHome with CC1001 transceiver library

Based on:

https://github.com/dbuezas/esphome-cc1101

https://github.com/nopnop2002/esp-idf-cc1101/blob/main/README.md

# Wirering

|CC1101||ESP32|ESP32-S2/S3|ESP32-C2/C3/C6|
|:-:|:-:|:-:|:-:|:-:|
|MISO|--|GPIO19|GPIO37|GPIO4|
|SCK|--|GPIO18|GPIO36|GPIO3|
|MOSI|--|GPIO23|GPIO35|GPIO2|
|CSN|--|GPIO5|GPIO34|GPIO1|
|GDO0|--|GPIO15|GPIO33|GPIO0|
|GDO2|--|N/C|N/C|N/C|
|GND|--|GND|GND|GND|
|VCC|--|3.3V|3.3V|3.3V|
