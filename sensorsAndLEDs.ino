#include <Wire.h>  
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

//#define statements
#define echoPin 3
#define trigPin 2
#define ledPin1 4
#define ledPin2 5
#define ledPin3 6

//Variables for the sensor
int duration, cm;

//Variables for the LCD/LED's
int val1, val2, val3;

void setup()   
{
  Serial.begin(9600);  // Used to type in characters
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin1, INPUT);
  pinMode(ledPin2, INPUT);
  pinMode(ledPin3, INPUT);
  lcd.begin(16,2);  
 
// ------- Quick 3 blinks of backlight  -------------
  for(int i = 0; i< 3; i++)
  {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  
  lcd.backlight(); // finish with backlight on  

  lcd.setCursor(0,0); 
  lcd.print("Welcome!");
  lcd.setCursor(0,1);
  lcd.print("Pressa' switch!");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
}

void loop()  
{
 val1 = digitalRead(ledPin1);
 val2 = digitalRead(ledPin2);
 val3 = digitalRead(ledPin3);
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration= pulseIn(echoPin,HIGH);
  cm=(duration*0.034)/2; //This is the distance away from the sensor in cm
  Serial.print("Distance: ");
  Serial.println(cm);
  delay(100);

//Option 1: One thing enters the garbage sorter
 if(val1 == HIGH){
  lcd.setCursor(0,0); 
  lcd.print("Option #1");
  lcd.setCursor(0,1);
  lcd.print("Bin #1");
  delay(1000);
  lcd.clear();
 }

//Option 2: A large garbage bag enters
 else if(val2 == HIGH){
  lcd.setCursor(0,0); 
  lcd.print("Option #2");
  lcd.setCursor(0,1);
  lcd.print("Bin #2");
  delay(1000);
  lcd.clear();
 }

 //Option 3: Shot basketball!
 else if(val3 == HIGH){
  lcd.setCursor(0,0); 
  lcd.print("Option #3");
  lcd.setCursor(0,1);
  lcd.print("BASKETBALL GAME!");
  delay(2000);
  lcd.clear();

  int score = 0;
  //START COUNTING SCORE HERE
  while(score != 5){
  
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration= pulseIn(echoPin,HIGH);
    cm=(duration*0.034)/2; //This is the distance away from the sensor in cm
    Serial.print("Distance: ");
    Serial.println(cm);
    delay(100);
    
    
    if(cm <= 5)
    { 
    score++;
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("SCORE!");
    lcd.setCursor(0,1);
    lcd.print("Points: ");
    lcd.print(score); 
    delay(1000);
    } 
 }


  //END COUNTING SCORE HERE
 }


 else{
  lcd.clear();

 }
 
 
 

}


