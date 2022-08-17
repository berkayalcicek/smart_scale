#include "HX711.h" 
  HX711 scale; 
    uint8_t dataPin = 6; //define pins
      uint8_t clockPin = 7;

#include "EasyNextionLibrary.h" 
  EasyNex myNex(Serial);

#include <GSMSimHTTP.h>
    #define RESET_PIN 10 
  static volatile int num = 0;
GSMSimHTTP http(Serial, RESET_PIN);
  
void setup() {
myNex.begin(9600);  
  Serial.begin(115200);
    scale.begin(dataPin, clockPin);

  while(Serial) {
    ; // wait for module for connect.
  }

Serial.print("UNITS: ");
  Serial.println(scale.get_units(10));

  Serial.println("\nEmpty the scale, press a key to continue");
  while(!Serial.available());
  while(Serial.available()) Serial.read();

  scale.tare();
  Serial.print("UNITS: ");
  Serial.println(scale.get_units(10));


  Serial.println("\nPut 1000 gr in the scale, press a key to continue");
  while(!Serial.available());
  while(Serial.available()) Serial.read();

  scale.calibrate_scale(1000, 5);
  Serial.print("UNITS: ");
  Serial.println(scale.get_units(10));

  Serial.println("\nScale is calibrated, press a key to continue");
  while(!Serial.available());
  while(Serial.available()) Serial.read();
  // scale.set_unit_price(0.031415); // this part for pricing the scaled grocery
  
  delay(500);        // Wait for Nextion to start
  
  Serial.print("Set Phone Function... ");
  Serial.println(http.setPhoneFunc(1));
  //delay(1000);

  Serial.print("is Module Registered to Network?... ");
  Serial.println(http.isRegistered());
  //delay(1000);

  Serial.print("Signal Quality... ");
  Serial.println(http.signalQuality());
  //delay(1000);

  Serial.print("Operator Name... ");
  Serial.println(http.operatorNameFromSim());
  //delay(1000);

  Serial.print("Connect GPRS... ");
  Serial.println(http.connect());
  //delay(1000);

  Serial.print("Get IP Address... ");
  Serial.println(http.getIP());
  delay(1000);
  
  Serial.print("Post... "); // test line
  Serial.println(http.post("test.com/test.php", "test", "weight"));
  delay(1000);


  Serial.print("Close GPRS... ");
  Serial.println(http.closeConn());
  //delay(1000);
  
  
  

}

void loop() {
 
  
  Serial.print("UNITS: "); 
    Serial.print(scale.get_units(5)); //prints to serial monitor measured weight
  
  myNex.writeStr("t0.txt","UNITS: "); 
    myNex.writeNum("n1.val",scale.get_units(5)); //sends measured weight to nextion display 
    
  //Serial.print("\t\tPRICE: "); // price func. is optional
  //Serial.println(scale.get_price(5)); // price func. is optional
  
  delay(10000); // waits for the display

    Serial.println(http.post("test.com/test.php",String(scale.get_units(5)), "weight")); // sends measured weight to server
  
  delay(1000);

}
