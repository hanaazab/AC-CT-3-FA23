#define IO_USERNAME  "hanaazab"
#define IO_KEY       "aio_Csyl66mH6hWUi3w6K7wY9HYKomcH"
//Adafruit IO username and key

#define WIFI_SSID "ACCD"
#define WIFI_PASS "tink1930"

#include "AdafruitIO_WiFi.h"
// header file that enables wifi functionallity

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
// this line instantiates a class using username, key, name and pass for wifi network
//example of object oriented programing