/*
||  Simple Password Entry Using Matrix Keypad
||  4/5/2012 Updates Nathan Sobieck: Nathan@Sobisource.com
||  MODIFIED BY CHANDRAGUPTA  
*/


//* is to validate password   
//# is to reset password attempt

/////////////////////////////////////////////////////////////////
#include <Servo.h> 
#include <LiquidCrystal.h>
#include <Password.h> //http://www.arduino.cc/playground/uploads/Code/Password.zip
#include <Keypad.h> //http://www.arduino.cc/playground/uploads/Code/Keypad.zip
Servo myservo;  
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Password password = Password( "9835" );
int pos = 0;
const byte ROWS = 4; // Four rows
const byte COLS = 4; //  columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {53,52,49,48};// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte colPins[COLS] = {A0,A1,A2, A3};// Connect keypad COL0, COL1 and COL2 to these Arduino pins.


// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  myservo.attach(9);
  myservo.write(pos);
    lcd.begin(16, 2);
 pinMode(13,OUTPUT);
  pinMode(11,OUTPUT);
  Serial.begin(9600);
   lcd.print("ENTER PASSWORD");

  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
}

void loop(){
  keypad.getKey();

  if(keypad.getKey()=='A')
          {
          for(pos;pos>0;pos-=1)
              { myservo.write(pos);
              delay(10);
              }
          }
}

//take care of some special events
void keypadEvent(KeypadEvent eKey){
int i;
  switch (keypad.getState()){
    case PRESSED:
 // lcd.print(eKey);
 Serial.println(eKey);
	 lcd.print(Serial.read());
	//Serial.print("Pressed: ");

	switch (eKey){
	  case '*': checkPassword(); break;
	  case '#': password.reset(); break;
	  default: password.append(eKey);
     }
  }
}

void checkPassword()
{
  if (password.evaluate()){
            lcd.print("Success");
            digitalWrite(13,HIGH);
            if (pos!=180)
                  {
                    for(pos = 0; pos < 180; pos += 1)
                    {
                       myservo.write(pos);
                       delay(15);
                    }
                  }
      //else if(pos==180)
                 {
                  // for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
                    {                                
                      // myservo.write(pos);              // tell servo to go to position in variable 'pos' 
                     //  delay(15);
                    }  
                  } 
 delay(5000);
 digitalWrite(13,LOW);
 
 //Add code to run if it works
  }
  else{
    lcd.print("Wrong");
    digitalWrite(11,HIGH);
     
    delay(5000);
     
    
      digitalWrite(11,LOW);
    //add code to run if it did not work

  }
}


