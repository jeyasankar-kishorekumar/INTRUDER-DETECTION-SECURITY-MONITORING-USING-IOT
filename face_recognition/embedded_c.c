// include the library code:
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(6, 7); // RX, TX

const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
void gsm_send();
void gsm_send1();
void make_call();
const String PHONE = "+919787857769"; //use your number with country code

void setup() {
  myservo.attach(3);
  
  Serial.begin(9600);
 mySerial.begin(9600);
  pinMode(4,INPUT);
   pinMode(6,OUTPUT);
   pinMode(5,INPUT);
     lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("  WELCOME   ");
  digitalWrite(6,LOW);
}

void loop() 
{
 int a=digitalRead(4);
 int b=digitalRead(5);
 if(a==0)
 {
   myservo.write(180);   
   lcd.setCursor(0,0);
lcd.print("left IR detected"); 
 }
     if(b==0)
 {
   myservo.write(0);  
    lcd.setCursor(0,0);
lcd.print("Right IR Detected");   
 }       

if (Serial.available() > 0) {
    int c = Serial.read();
    if(c=='1')
    {
digitalWrite(6,HIGH);
        make_call();
delay(2000);delay(2000);
 
  gsm_send();

  
delay(2000);
digitalWrite(6,LOW);

gsm_send1();
delay(2000);

}
 }  
 

  }
  
 void gsm_send()
{  
lcd.clear();
lcd.setCursor(0,0);
lcd.print("sending sms1........................");
delay(500);
Serial.print("AT");         // SIM CARD READY CHECK
delay(100);  delay(100);
Serial.write(13);           // ENTER
delay(1000);
Serial.write(10);           // NEW LINE
delay(1000);
Serial.print("AT+CMGF=1");         // SIM CARD READY CHECK
delay(100);  delay(100);
Serial.write(13);           // ENTER
delay(1000);
Serial.write(10);           // NEW LINE
delay(1000);
Serial.print("AT+CNMI=2,2,2,0");         // SIM CARD READY CHECK
delay(100);  delay(100);
Serial.write(13);           // ENTER
delay(1000);
Serial.write(10);           // NEW LINE
delay(1000);
Serial.print("AT+CMGS=");   // SMS SEND FUNCTION
delay(100);  delay(100);
Serial.print('"');
delay(100);  delay(100);
Serial.print("9787857769");
delay(100);  delay(100);
Serial.print('"');   
delay(100);  delay(100);    
Serial.write(13);
delay(1000);
Serial.print("Intruder alert ");
delay(100);  delay(100);
Serial.write(13);           // ENTER
delay(1000);
Serial.write(10);           // NEW LINE
delay(1000);

Serial.write(26);        // CTRL+Z
delay(100);  delay(100);
lcd.setCursor(0,0);
delay(600);   
lcd.print("   COMPLETED     ");
}
void gsm_send1()
{  
lcd.clear();
lcd.setCursor(0,0);
lcd.print("sending sms1........................");
delay(500);
Serial.print("AT");         // SIM CARD READY CHECK
delay(100);  delay(100);
Serial.write(13);           // ENTER
delay(1000);
Serial.write(10);           // NEW LINE
delay(1000);
Serial.print("AT+CMGF=1");         // SIM CARD READY CHECK
delay(100);  delay(100);
Serial.write(13);           // ENTER
delay(1000);
Serial.write(10);           // NEW LINE
delay(1000);
Serial.print("AT+CNMI=2,2,2,0");         // SIM CARD READY CHECK
delay(100);  delay(100);
Serial.write(13);           // ENTER
delay(1000);
Serial.write(10);           // NEW LINE
delay(1000);
Serial.print("AT+CMGS=");   // SMS SEND FUNCTION
delay(100);  delay(100);
Serial.print('"');
delay(100);  delay(100);
Serial.print("8072592779");
delay(100);  delay(100);
Serial.print('"');   
delay(100);  delay(100);    
Serial.write(13);
delay(1000);
Serial.print("Intruder alert ");
delay(100);  delay(100);
Serial.write(13);           // ENTER
delay(1000);
Serial.write(10);           // NEW LINE
delay(1000);

Serial.write(26);        // CTRL+Z
delay(100);  delay(100);
lcd.setCursor(0,0);
delay(600);   
lcd.print("   COMPLETED     ");
}
//*************************************************************************************************************************************************************
// call_funtion
//*************************************************************************************************************************************************************               
void make_call()
{
  lcd.clear();
lcd.setCursor(0,0);
lcd.print("calling....");
    Serial.println("calling....");
     Serial.println("ATD9787857769;");
    delay(20000); //20 sec delay
     Serial.println("ATH");
    delay(1000); //1 sec delay
}