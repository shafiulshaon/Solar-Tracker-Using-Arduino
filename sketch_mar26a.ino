const float referenceVolts = 5.0; // the default reference on a 5-volt board
const int batteryPin = 5;         // battery is connected to analog pin 0

#include <Servo.h>
//defining Servos
Servo servohori;
int servoh = 160;
int servohLimitHigh = 160;
int servohLimitLow = 20;

Servo servoverti; 
int servov = 160; 
int servovLimitHigh = 160;
int servovLimitLow = 20;
//Assigning LDRs
int ldrtopl = A2; //top left LDR green
int ldrtopr = A1; //top right LDR yellow
int ldrbotl = A0; // bottom left LDR blue
int ldrbotr = A3; // bottom right LDR orange

 void setup () 
 {
  servohori.attach(10);
  servohori.write(80);
  servoverti.attach(9);
  servoverti.write(50);
  pinMode(ldrtopl, INPUT);
   pinMode(ldrtopr, INPUT);
    pinMode(ldrbotl, INPUT);
     pinMode(ldrbotr, INPUT);
  Serial.begin(9600);
 
 }




void loop()
{
  servoh = servohori.read();
  servov = servoverti.read();
  //capturing analog values of each LDR
  int topl = analogRead(ldrtopl);
  int topr = analogRead(ldrtopr);
  int botl = analogRead(ldrbotl);
  int botr = analogRead(ldrbotr);
  // calculating average
  int avgtop = (topl + topr) / 2; //average of top LDRs
  int avgbot = (botl + botr) / 2; //average of bottom LDRs
  int avgleft = (topl + botl) / 2; //average of left LDRs
  int avgright = (topr + botr) / 2; //average of right LDRs

   Serial.println("----LDR Read----");
    Serial.print("Top Left");
    Serial.println(topl);
     Serial.print("Top Right");
    Serial.println(topr);
     Serial.print("Bottom Left");
    Serial.println(botl);
     Serial.print("Bottom right");
    Serial.println(botr);
    Serial.println("---Solar Voltage---");
    int solarPin = A5;
    int val 
    = analogRead(solarPin); // read the value from the sensor 
    float volts = (val / 1023.0) * referenceVolts; // calculate the ratio
    Serial.println(volts); // print the value in volts
    delay(10);
 ;
  if (avgtop < avgbot)
  { 
    servoverti.write(servov +2);
    Serial.print("Avarage Top: ");
    Serial.print(avgtop);
    Serial.print("< Avarage Bottom: ");
    Serial.print(avgbot);
    Serial.println("----servo moving vertical up----");
      if (servov > servovLimitHigh) 
     { 
      servov = servovLimitHigh;
     }
    

  }
  else if (avgbot < avgtop)
  {
    servoverti.write(servov -2);
    Serial.print("Avarage Bottom: ");
    Serial.print(avgbot);
    Serial.print("< Avarage Top: ");
    Serial.print(avgtop);
    Serial.println("----servo moving vertical down----");
    if (servov < servovLimitLow)
  {
    servov = servovLimitLow;
  }
    delay(10);
  }
  else 
  {
    servoverti.write(servov);
  }
  
  if (avgleft > avgright)
  {
    servohori.write(servoh +2);
    Serial.print("Avarage Left: ");
    Serial.print(avgleft);
    Serial.print("> Avarage Right: ");
    Serial.print(avgright);
    Serial.println("----servo moving Horizontal left----");;
    if (servoh > servohLimitHigh)
    {
    servoh = servohLimitHigh;
    }
    delay(10);
  }
  else if (avgright > avgleft)
  {
    servohori.write(servoh -2);
    Serial.print("Avarage avgright: ");
    Serial.print(avgleft);
    Serial.print("> Avarage avgleft: ");
    Serial.print(avgright);
    Serial.println("----servo moving horizontal right----");
    if (servoh < servohLimitLow)
     { 
     servoh = servohLimitLow;
     }
    delay(10);
  }
  else 
  {
    servohori.write(servoh);
  }
   delay(10);
}
