
#include<Servo.h> 

Servo shoulderServo;
Servo armServo; 
Servo clawServo;

const int SW_pin = 8;
const int X1_pin = A0;
const int SW2_pin = 2;
const int X2_pin = A1;
int x1,x2;
int servo1Pin=9;
int pos1=0;
int servo2Pin=10; 
int pos2=0; 
int servo3Pin=11; 
int i=5;
int j=20;

int buttonPrev = LOW;
int buttonState;            
bool servoClamped = false;
unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 10;    
unsigned long lastPressed = millis();


void setup() 
{ 
  
  buttonPrev = digitalRead(SW_pin);
shoulderServo.attach(servo1Pin);   
armServo.attach(servo2Pin);
clawServo.attach(servo3Pin);
pinMode(SW_pin, INPUT);
digitalWrite(SW_pin, HIGH);
shoulderServo.write(15);
armServo.write(20);
clawServo.write(50);
Serial.begin(9600);
} 

void loop() 
{ 
  

x1 = analogRead(X1_pin);
x2 = analogRead(X2_pin);

Serial.println(x1);
Serial.println(x2);

int reading = digitalRead(SW_pin);
if (reading != buttonPrev) {
   
    lastDebounceTime = millis();
  }

if ((millis() - lastDebounceTime) > debounceDelay) {
   
    if (reading != buttonState) {
      buttonState = reading;

      
      if (buttonState == LOW ) {
          /////
          Serial.println("triggered");
          if(!servoClamped){
           
            clawServo.write(100);
            Serial.println("Opening");
            servoClamped = true;
            delay(500);
            //lastPressed = millis();
          }
          else{
            
            clawServo.write(50);
            Serial.println("Closing");
            servoClamped = false;
            delay(500);
            //lastPressed = millis();
          }
      }
    }
  }
  buttonPrev = reading;





if(x1<250 && i>5)
{
    shoulderServo.write(i--);  
    delay(15);
}
else if(x1>700 && i<80)
{
  shoulderServo.write(i++);  
  delay(15);
}

if(x2<250 && j>20)
{
    armServo.write(j--);  
    delay(10);
}
else if(x2>700 && j<120)
{
  armServo.write(j++);  
  delay(10);
}


 
}
