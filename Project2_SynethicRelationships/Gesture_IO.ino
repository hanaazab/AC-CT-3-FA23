#include "config.h"
#include <Wire.h>
#include "PAJ7620U2.h"
//#define GESTURE_SENSOR_INT_PIN 4
//unsigned long myTime;

int LED = 13;   //  The on-board Esp32 LED

 

AdafruitIO_Feed *gesture = io.feed("gesture_sensor");

// the Adafruit IO username of whomever owns the feed
#define FEED_OWNER "vilmaheee"

// set up the `sharedFeed`
AdafruitIO_Feed *sharedFeed = io.feed("pulse_sensor", FEED_OWNER);

unsigned short  Gesture_Data;

void handleMessage(AdafruitIO_Data *data) {

  Serial.print("received <-  ");
  Serial.println(data->toInt());

//Print BPM to Serial so the values sent to TD are simple
    int bpm = data->toInt();
    Serial.println(bpm);

 // LED Test  
  //digitalWrite(LED, HIGH);  // Turn on the LED
  //delay(1000);  // Keep the LED on for 1 second
  //digitalWrite(LED, LOW);  // Turn off the LED
  
}

void setup() {
    uint8_t i;
    Serial.begin(115200);
    pinMode(LED, OUTPUT);

    while(! Serial);
    // connect to io.adafruit.com
    Serial.print("Connecting to Adafruit IO");
     
    io.connect(); 

    sharedFeed->onMessage(handleMessage);    

    // wait for a connection
    while(io.status() < AIO_CONNECTED) {
      Serial.println(io.statusText());
      sharedFeed->get();
      }

    pinMode(LED,OUTPUT);
    //pinMode(pulsePin, INPUT); // Sets the trigPin as an Output
    // start the serial connection
    Serial.print("\nGesture Sensor Test Program ...\n");
    delayMicroseconds(200);
    Wire.begin();
    delayMicroseconds(10);
    while(!PAJ7620U2_init())
    { Serial.print("\nGesture Sensor Error\n");
      delay(500);
    }
    Serial.print("\nGesture Sensor OK\n");
    I2C_writeByte(PAJ_BANK_SELECT, 0);//Select Bank 0
    for (i = 0; i < Gesture_Array_SIZE; i++)
    {
      I2C_writeByte(Init_Gesture_Array[i][0], Init_Gesture_Array[i][1]);//Gesture register initializes
    }

   // attachInterrupt(digitalPinToInterrupt(GESTURE_SENSOR_INT_PIN), ISR_Gesture, CHANGE);
}

void loop() {
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
  delay(1000);

  io.run();

  Gesture_Data = I2C_readU16(PAJ_INT_FLAG1);
    if (Gesture_Data)
    {
      switch (Gesture_Data)
      {
        case PAJ_FORWARD:              
        Serial.print("Forward\r\n");    
        gesture->save("Forward");   
        break;

        case PAJ_BACKWARD:             
        Serial.print("Backward\r\n");    
        gesture->save("Backward");    
        break;
        //case PAJ_CLOCKWISE:            Serial.print("Clockwise\r\n");     break;
        //case PAJ_COUNT_CLOCKWISE:      Serial.print("AntiClockwise\r\n"); break;
        
        case PAJ_WAVE:                 
        Serial.print("Wave\r\n");
        gesture->save("Wave");          
        break;
        
        default: 
        break;
      }
      Gesture_Data=0;
    }

    //Serial.println(beatTimes);
    delay(10);
}

// this function is called whenever an 'sharedFeed' feed message
// is received from Adafruit IO. it was attached to
// the 'digital' feed in the setup() function above.

