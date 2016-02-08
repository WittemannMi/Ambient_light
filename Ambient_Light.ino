/*
 **********************************
 *** Program by M. Wittemann*******
 ****Projekt started February 2016*
 **********************************
 *
--------------------------------------------------------------------------------------
  Pinout & Description
--------------------------------------------------------------------------------------
                                      +-----+
         +----[PWR]-------------------| USB |--+
         |                            +-----+  |
         |         GND/RST2  [ ][ ]            |
         |       MOSI2/SCK2  [ ][ ]  A5/SCL[ ] |   C5 
         |          5V/MISO2 [ ][ ]  A4/SDA[ ] |   C4 
         |                             AREF[ ] |
         |                              GND[ ] |
         | [ ]N/C                    SCK/13[ ] |   B5
         | [ ]v.ref                 MISO/12[ ] |   .
         | [ ]RST                   MOSI/11[ ]~|   .
         | [ ]3V3    +---+               10[ ]~|   .
         | [ ]5v     | A |                9[ ]~|   .
         | [ ]GND   -| R |-               8[ ] |   B0
         | [ ]GND   -| D |-                    |
         | [ ]Vin   -| U |-               7[ ] |   D7
         |          -| I |-               6[ ]~|   .
         | [ ]A0    -| N |-               5[ ]~|   .
         | [ ]A1    -| O |-               4[ ] |   .
         | [ ]A2     +---+           INT1/3[ ]~|   .
         | [ ]A3                     INT0/2[ ] |   .
         | [ ]A4/SDA  RST SCK MISO     TX>1[ ] |   .
         | [ ]A5/SCL  [ ] [ ] [ ]      RX<0[ ] |   D0
         |            [ ] [ ] [ ]              |
         |  UNO_R3    GND MOSI 5V  ____________/
          \_______________________/

Pin description:

 --digital Pins--:
 0: 
 1: 
 2: 
 3: LEDpin (PWM)
 4: 
 5: 
 6: 
 7: 
 8:  
 9: 
10: HC-SR04-1 Echo
11: HC-SR04-1 Trig
12: HC-SR04-2 Echo
13: HC-SR04-2 Trig

 --analog pins--:
 A0: Light Sensor Output
 A1: 
 A2:
 A3:
 A4:
 A5:

 

/*--------------------------------------------------------------------------------------
  Includes
--------------------------------------------------------------------------------------*/
#include <NewPing.h>    //NewPing sonar(trigger_pin, echo_pin [, max_cm_distance]);

/*--------------------------------------------------------------------------------------
  Init the LCD library with the LCD pins to be used, DHT sesor and serial
--------------------------------------------------------------------------------------*/
NewPing sonar1(11, 10, 300);

/*--------------------------------------------------------------------------------------
  Defines
--------------------------------------------------------------------------------------*/
//PINS:

#define LIGHT_ADC_PIN            A0  // A0 is the Light Sensor ADC input

#define ECHO1_PIN                10  // HC-SR04-1 Echo pin
#define TRIG1_PIN                11  // HC-SR04-1 Trig pin

#define ECHO2_PIN                12  // HC-SR04-2 Echo pin
#define TRIG2_PIN                13  // HC-SR04-2 Trig pin

#define LED_PIN                  3  // HC-SR04-2 Trig pin

/*--------------------------------------------------------------------------------------
  global Variables
--------------------------------------------------------------------------------------*/
int lightValue;

long Sensor1detect, Sensor2detect;

/*--------------------------------------------------------------------------------------
  Functions
--------------------------------------------------------------------------------------*/

void LEDon()
{
 digitalWrite(LED_PIN, HIGH);   // turn on LED with full intensity
 delay(30000);                  // stay on with full intensity for 30 seconds
 for(int i=150; i>=0;i--)       // dim the LEDs for 150 seconds
 {
  analogWrite(LED_PIN, i); 
  delay(1000);
 }
 digitalWrite(LED_PIN, LOW);   // turn off LEDs after 180 seconds total
}

void setup()
{
 Serial.begin(9600);   // Setup the serial debug connection

 //pinMode(ECHO1_PIN, INPUT);
 //pinMode(TRIG1_PIN, OUTPUT);

// pinMode(ECHO2_PIN, INPUT);
// pinMode(TRIG2_PIN, OUTPUT); 
}

void loop() 
{
 
 lightValue = analogRead(LIGHT_ADC_PIN);
 Sensor1detect = sonar1.ping_cm();  // read sensor 1 value
 
 if(lightValue >= 700)   // Only turn on the lights if the room is dark (900)
 {
  if(Sensor1detect <=10)    // only if there is a value below 100cm someone is getting out of bed (for tests set to 10)
  {
   LEDon(); 
  }
 }
 
  Serial.print(Sensor1detect);
  Serial.println("cm");
  delay(200);
  Serial.print("Light:");
  Serial.println(lightValue);
  delay(200);

}
