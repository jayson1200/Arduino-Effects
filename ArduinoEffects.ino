  /*These are like the import statements in java except instead 
  * of holding the actual implementation of the code they hold the declerations in C++ header files which we can access for our own uses.
  * It litteraly dumps all the code from the other class we want
  * Ex. We could litteraly does this: 
  * int i = 
  *         #include <valueofpi.h>
  *         ;
  * In the acutal valueofpi.h file we can litteraly just have 3.14 by itself.
  * This shows how it is litteraly just copying and pasting the code into our file
  * 
  * If we have written it ourselves instead of  <> we use ""
  * Ex. #include "SoftwareSerial.h"
  * 
  * The include directive always has to be on its own line
 */
 #include <SoftwareSerial.h> //This is part of the Arduino library
 #include <BlynkSimpleStream.h> 
 #include <stdlib.h>


 
SoftwareSerial SerialDebugger(2,3);


 // You should get Auth Token in the Blynk App.
 // Go to the Project Settings (nut icon).
 char auth[] = "fKN7KAuYKjf0OTN3Yy1YyWcxC2HbqUn_";

 int currentEffect = 0;
 char response = 0;
 int mSpeed = 1;

 bool staticColorChange = false;
 bool smoothRainbow = false;

 int fadeRed;
 int fadeGreen;
 int fadeBlue;

 int fadeRedTarget = 255;
 int fadeGreenTarget = 255;
 int fadeBlueTarget = 255;



 void setup()
 {

   // Blynk will work through Serial
   Serial.begin(9600);
   SerialDebugger.begin(9600);

   pinMode(2, INPUT);
   pinMode(3, OUTPUT);

   Blynk.begin(Serial ,auth);
 }

 void loop()
 {
     Blynk.run();

      while(staticColorChange)
      {
        if(millis() % (5000/mSpeed) == 0)
        {
          analogWrite(9 , rand() % 256);
          analogWrite(10 , rand() % 256);
          analogWrite(11 , rand() % 256);
        }
         Blynk.run();
      }

      while(smoothRainbow)
      {
        if(millis() % (100/mSpeed) == 0)
        {
          changeRGBVals();
          
          analogWrite(9 , fadeBlue);
          analogWrite(10 , fadeRed);
          analogWrite(11 , fadeGreen);

          Serial.println(fadeRed);
          Serial.println(fadeBlue);
          Serial.println(fadeGreen);
        }
         Blynk.run();
      }
 }

//This is for the Color Picker
 BLYNK_WRITE(V0)
 {
    staticColorChange = false;
    smoothRainbow = false;
    analogWrite(9 ,param[2].asInt());
    analogWrite(10 ,param[0].asInt());
    analogWrite(11 ,param[1].asInt());
 }

//This is for the Effect Picker
 BLYNK_WRITE(V1)
 {
  if(param.asInt() == 2)
  {
    smoothRainbow = false;
    staticColorChange = true;
  }
  else if(param.asInt() == 3)
  {
     staticColorChange = false;
     smoothRainbow = true;

     fadeRedTarget = rand() % 256;
     fadeGreenTarget = rand() % 256;
     fadeBlueTarget = rand() % 256;
  }
 }

//This is for the speed adjuster
 BLYNK_WRITE(V2)
 {
    if(mSpeed == 0)
    {
      mSpeed = 1;
    }
    else if(mSpeed == 51)
    {
      mSpeed = 50;
    }

    mSpeed += param.asInt();
 }

 
//This changes the RGB values for the smootheRainbow Effect
void changeRGBVals()
{
  if(fadeRed > fadeRedTarget)
  {
    fadeRed--;
  }
  else if(fadeRed < fadeRedTarget)
  {
    fadeRed++;
  }

  if(fadeGreen > fadeGreenTarget)
  {
    fadeGreen--;
  }
  else if(fadeGreen < fadeGreenTarget)
  {
    fadeGreen++;
  }

  if(fadeBlue > fadeBlueTarget)
  {
    fadeBlue--;
  }
  else if(fadeBlue < fadeBlueTarget)
  {
    fadeBlue++;
  }

  if(fadeRed == fadeRedTarget)
  {
    fadeRedTarget = rand() % 256;
  }

  if(fadeGreen == fadeGreenTarget)
  {
    fadeGreenTarget = rand() % 256;
  }

  if(fadeBlue == fadeBlueTarget)
  {
    fadeBlueTarget = rand() % 256;
  }
 
}

 


 
