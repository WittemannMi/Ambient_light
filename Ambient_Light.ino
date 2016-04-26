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
//#include <NewPing.h>    //NewPing sonar(trigger_pin, echo_pin [, max_cm_distance]);

/*--------------------------------------------------------------------------------------
  Init the LCD library with the LCD pins to be used, DHT sesor and serial
--------------------------------------------------------------------------------------*/
//NewPing sonar1(11, 10, 600);

/*--------------------------------------------------------------------------------------
  Defines
--------------------------------------------------------------------------------------*/
//PINS:

#define LIGHT_ADC_PIN            A0  // A0 is the Light Sensor ADC input

#define ECHO1_PIN                10  // HC-SR04-1 Echo pin
#define TRIG1_PIN                11  // HC-SR04-1 Trig pin

#define ECHO2_PIN                12  // HC-SR04-2 Echo pin
#define TRIG2_PIN                13  // HC-SR04-2 Trig pin

#define LED_PIN                  3  // FET-GATE LED

/*--------------------------------------------------------------------------------------
  global Variables
--------------------------------------------------------------------------------------*/
int lightValue;

long Sensor1detect, Sensor2detect, duration1, duration2;

/*--------------------------------------------------------------------------------------
  Functions
--------------------------------------------------------------------------------------*/

void LEDon()
{
 digitalWrite(LED_PIN, HIGH);   // turn on LED with full intensity, check brightnes with the actual LEDS
 delay(30000);                  // stay on with full intensity for 30 seconds
 for(int i=150; i>=0;i--)       // dim the LEDs for 150 seconds
 {
  analogWrite(LED_PIN, i); 
  delay(1000);
 }
 digitalWrite(LED_PIN, LOW);   // turn off LEDs after 180 seconds total
}

void READsensor1()
{
 digitalWrite(TRIG1_PIN, LOW);
 delayMicroseconds(5);
 digitalWrite(TRIG1_PIN, HIGH);
 delayMicroseconds(10);
 digitalWrite(TRIG1_PIN, LOW);

 duration1 = pulseIn(ECHO1_PIN,HIGH); 
 Sensor1detect = (duration1/2) / 29.1; 

 if(duration1 == 0 && digitalRead(ECHO1_PIN) == HIGH)    // Unlock sensor if it gets stuck, because of timeout problem
 {
  pinMode(ECHO1_PIN, OUTPUT);
  digitalWrite(ECHO1_PIN, LOW);
  delay(100);
  pinMode(ECHO1_PIN, INPUT);
  Serial.print("RESET SENSOR1");
  Sensor1detect = 100; // set to a value that does not turn on the LED
 }
}

void READsensor2()
{
 digitalWrite(TRIG2_PIN, LOW);
 delayMicroseconds(5);
 digitalWrite(TRIG2_PIN, HIGH);
 delayMicroseconds(10);
 digitalWrite(TRIG2_PIN, LOW);

 duration2 = pulseIn(ECHO2_PIN,HIGH); 
 Sensor2detect = (duration2/2) / 29.1; 

 if(duration2 == 0 && digitalRead(ECHO2_PIN) == HIGH)   // Unlock sensor if it gets stuck, because of timeout problem
 {
  pinMode(ECHO2_PIN, OUTPUT);
  digitalWrite(ECHO2_PIN, LOW);
  delay(100);
  pinMode(ECHO2_PIN, INPUT);
  Serial.print("RESET SENSOR2");
 }
}

void setup()
{
 Serial.begin(9600);   // Setup the serial debug connection

 pinMode(ECHO1_PIN, INPUT);
 pinMode(TRIG1_PIN, OUTPUT);

 pinMode(ECHO2_PIN, INPUT);
 pinMode(TRIG2_PIN, OUTPUT); 
}

void loop() 
{
 
 lightValue = analogRead(LIGHT_ADC_PIN);
 delay(50); 
 //Sensor1detect = sonar1.ping_cm();  // read sensor 1 value
 //Read Sensor without library
 READsensor1();           // Read Sensor 1 distance
 //READsensor2();         // read Sensor 2 distance

 if(lightValue >= 700)   // Only turn on the lights if the room is dark (900)
 {
  if((Sensor1detect <=10) || (Sensor2detect <0))    // only if there is a value below 50cm on either side of the bed someone is getting out of bed (for tests set to 10)
  {
   LEDon();   // turn on the LEDS if someone is getting out of bed
  }
 }
 
  Serial.print(Sensor1detect);
  Serial.println("cm");
  delay(200);
  Serial.print("Light:");
  Serial.println(lightValue);
  delay(200);

}
