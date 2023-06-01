#define BLYNK_PRINT Serial

#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "9gLYLPFlCmzgrBBHMjh3vB8eIbRBETVq";
                 // You should get Auth Token in the Blynk App.  
                 
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";

int btnPin = V3;
int emrPin = V4;
WidgetLCD lcd(V1);
WidgetLED led3(V2);
BlynkTimer timer;
#define startButton 0
#define sensor 2
#define led 5
#define red 14
#define yellow 12
#define green 13

   BLYNK_WRITE(V4)
       {
        emrPin = param.asInt();

        
       }
  BLYNK_WRITE(V3)
  {
     btnPin = param.asInt();

   
}
       
  // Read button
  //boolean isPressed = (digitalRead(btnPin) == LOW);
  //boolean isPressed = (digitalRead(emrPin) == LOW);
  // If state has changed...


void setup()
{
  // Debug console
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  Serial.println("Connected");
  //timer.setInterval(500L, BlynkWidgetWrite);
  pinMode(startButton, INPUT);
  pinMode(sensor, INPUT);
  pinMode(led, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(0, 0, "Press Button"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  lcd.print(1, 1, "To Start");
  // Please use timed events when LCD printintg in void loop to avoid sending too many commands
  // It will cause a FLOOD Error, and connection will be dropped
}

void loop()
{
  Blynk.run();
  timer.run();
  // for physical
    if ( digitalRead(startButton) == LOW && digitalRead(sensor) == LOW)
    {
   for (int y = 3; y > 0; y--)
    {
      Blynk.notify("Sterlization Starts in 3 seconds");
      Serial.println("Sterlization Starts in:");
      Serial.println(y);
      lcd.print(0, 0, "Sterlization Starts in:");
      lcd.print(1, 1, y);
      y = y;
      delay(1000);
    }
    
    for (int t = 0; t < 180; t++)
    {
        if (digitalRead(sensor) == LOW)
        {
        digitalWrite(led, HIGH);
        led3.on();
        Serial.print("Sterlizing");
        Serial.print(t);
        lcd.clear();
        lcd.print(0, 0, "Sterlizing");
        lcd.print(1, 1, t);
        digitalWrite(yellow, HIGH);
        digitalWrite(green, LOW);
        digitalWrite(red, LOW);
        t = t;
        delay(1000);
        }
        else
        {
          digitalWrite(led, LOW);
          digitalWrite(red, HIGH);
          digitalWrite(yellow, LOW);
        digitalWrite(green, LOW);
        
        lcd.clear();
        lcd.print(1,1,"Emergency stopped");
        Blynk.notify("Emergency stopped");
        Serial.println("Emergency stopped");
        delay(6000);   
        }
        }
      
      
    
    
      
    led3.off();
    digitalWrite(led, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
    Serial.println("Done Sterlizing");
    lcd.clear();
    lcd.print(0, 0, "Done Sterlizing");
    Blynk.notify("Done Sterlizing");
    delay(1000);
    return;
  }
 
  else
  {
    delay(200);
    led3.off();
    digitalWrite(yellow, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
    Serial.println("press start");
    lcd.clear();
    lcd.print(1,1,"Press Start");
    delay(1000);
  }
}