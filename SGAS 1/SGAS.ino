// board info :-node mcu 1.0 (ESP12E module)
// lcd module
    //scl d1 and sda for d2 for lcd 
    //lcd vcc is for 5v
// rfid module
    //sda d9 rx
    //sck d5
    //mosi d7
    //miso d6
    //rst d3
    //voltage 3.3v 
//alchohol data pin D0  if alchohol data is 1 then no alochol -- if alchohol present data is o
//v1 for alerts v2 for responce v3 and v4 for display custom msges
//sos botton as ir sensor  d8  
//led buzzer d4 
//mq 135 tx d10

#define BLYNK_TEMPLATE_ID "TMPL3lCyR9C5r"
#define BLYNK_TEMPLATE_NAME "senior guard alert system"
#define BLYNK_AUTH_TOKEN "weyv5CTCdCjL_VPQoKHdHCxS-zs8Zncl"
#define BLYNK_PRINT Serial


#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <BlynkSimpleEsp8266.h>


const char *ssid     = "SANKARAM";
const char *password = "00000000";
char auth[]=BLYNK_AUTH_TOKEN;


String time1="09:00:00";
String time2="09:02:30";

String time3="12:00:00";
String time4="12:02:30";

String time5="21:00:00";
String time6="21:02:30";




// time
WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "in.pool.ntp.org", 19800, 60000);
//
// rfid
constexpr uint8_t RST_PIN = D3;   
constexpr uint8_t SS_PIN = D9;
MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
//

// flags
String tag;
int clearflag=0;
int sosflag=0;
int pushflag=0;
int buzzflag=0;
int ledflag=0;
int notification=1;
int flag=0;
int gasflag=0;


LiquidCrystal_I2C lcd(0x27, 16, 2);



//these are for terminal
int custom_msg=0;
String textIn = "";
bool text = false;
int x = 0;


WidgetLED notifications(V0);
WidgetLED alcohol(V1);
WidgetLED sos(V6);
WidgetLED notresponding(V2);
WidgetLED gas(V7);



BLYNK_WRITE(V3)
{
  textIn = param.asStr();
  if (textIn) // working for text Input Widget
  { 
    lcd.clear();
    text = true;
    x = 0;
   // Serial2.print(String("!") + textIn + String("\r\n"));
    Serial.print(String("!") + textIn + String("\r\n"));
    text = false;
    //Serial2.flush();
  }
}
BLYNK_WRITE(V4) 
{ 
  custom_msg=param.asInt(); 
} 
//end for terminal code
void setup()
{
      Serial.begin(9600);
      //Serial2.begin(115200, SERIAL_8N1, 16, 17);
      SPI.begin(); 
      rfid.PCD_Init();   
      lcd.init();
      lcd.clear();
      lcd.backlight();
      lcd.setCursor(0, 0);
      lcd.print("SENIOR GUARD");
      lcd.setCursor(0, 1);
      lcd.print("ALERT SYSTEM");
      WiFi.begin(ssid, password);
      while ( WiFi.status() != WL_CONNECTED )
      {
           lcd.clear();
           lcd.setCursor(0, 0);
           lcd.print("CONNECTING");
           delay ( 500 );
           Serial.print ( "." );
           lcd.clear();
       }
       
       lcd.clear();
       Blynk.begin(auth,ssid,password);
       timeClient.begin();
       notresponding.off();
       alcohol.off();
       sos.off();
       gas.off();
       pinMode(D8,INPUT);       //sos data
       delay(2000); 
       pinMode(D4,OUTPUT); //led
       pinMode(D10,INPUT);//mq-135
              
}

void loop() 
{  
    if(digitalRead(D10)==0)
    {
      gasflag=1;
     }
    if(gasflag==1)
    {
      gas.on();
      }
    if(gasflag==0)
    {
      gas.off();
      }
    if(ledflag==1)
    {
      digitalWrite(D4,HIGH);
    }
    if(ledflag==0)
    {
      digitalWrite(D4,LOW);
    }
    if(ledflag==0)
    {
      if(digitalRead(D8)==1)
      {
        sosflag=1;
      }
      if(sosflag==1)
      {
      
        sos.on();
      }
    }
    String tag = readRFID();
    timeClient.update();
    //Serial.println(timeClient.getFormattedTime());
    Serial.println(tag);
    int alchldata=digitalRead(D0);
    Serial.println(alchldata);
    if(alchldata==0)
    {
      //alchol present
      alcohol.on();
    }
    if(tag=="13118174252")
    {
      notification=0;
    }
    if(tag=="195221115205")
    {
       notification=0;
       
    }
    if ( notification==1) 
    {
       lcd.setCursor(0, 1);
       lcd.print("alerts on");
       notifications.off();
    }
    if(notification==0)
    {
       lcd.setCursor(0, 1);
       lcd.print("alerts off");
       notifications.on();
    }
    
    if(flag==0)
    {
     lcd.setCursor(0, 0);
     lcd.print(timeClient.getFormattedTime());
    }
    if(flag==1)
    {
      lcd.setCursor(0, 0);
      lcd.print("press-button");
     }
      Blynk.run();
     if(custom_msg==1)
      {

         lcd.clear();
         lcd. setCursor (0, 0);
         lcd. print ( " SVEC SGAS " );
         lcd. setCursor (0, 1);
         lcd.print(String("!") + textIn + String("\r\n"));
         lcd.scrollDisplayLeft();
         delay(300);
         clearflag=0;
        } 
       if(clearflag=0)
       {
        lcd.clear();
        clearflag=1;
       } 

        
        if( notification==1)
        {
          if(timeClient.getFormattedTime()==time1)
          {
            pushflag=0;



            
            flag=1;
            ledflag=1;
            
           }
            if(digitalRead(D8)==1)
            {
               pushflag=1;
               flag=0;
               ledflag=0;
               lcd.clear();
            }
            if(timeClient.getFormattedTime()==time2)
            {
               if(pushflag==0)
               {
                 notresponding.on();
               }
            }

           if(timeClient.getFormattedTime()==time3)
          {
            pushflag=0;
            flag=1;
            ledflag=1;
            
           }
            if(digitalRead(D8)==1)
            {
               pushflag=1;
               flag=0;
               ledflag=0;
               lcd.clear();
            }
            if(timeClient.getFormattedTime()==time4)
            {
               if(pushflag==0)
               {
                 notresponding.on();
               }
            }

            if(timeClient.getFormattedTime()==time5)
          {
            pushflag=0;
            flag=1;
            ledflag=1;
            
           }
            if(digitalRead(D8)==1)
            {
               pushflag=1;
               flag=0;
               ledflag=0;
               lcd.clear();
            }
            if(timeClient.getFormattedTime()==time6)
            {
               if(pushflag==0)
               {
                 notresponding.on();
               }
            }
        }
      
}

String readRFID() {
  String tag;
  
  if (!rfid.PICC_IsNewCardPresent())
  
    return tag;

  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
  return tag;
}
