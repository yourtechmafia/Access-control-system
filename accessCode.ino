//  Include all necessary libraries
#include <Keypad.h> //  Keypad module library
#include <LiquidCrystal.h>  //  LCD module library & config
//  Libraries constants for initialization
const char keys[4][3] = { //  Keypad layout
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
const byte rowPins[4] = {0, 1, 2, 3}; //connect to the row pinouts of the keypad
const byte colPins[3] = {4, 5, 6}; //connect to the column pinouts of the keypad
//  Initialize all libraries
Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 3 );
LiquidCrystal lcd(8, 9, 10, 11, 12 , 13);  //  LCD module pins on board - RS,EN,D4,D5,D6,D7
//  Variables declaration
const char code[] = "2014"; //Your Passcode (constant)
char str1[4]; //  Array to store key input
int n = 0;  //  Key counter

void setup() {
  pinMode(7, OUTPUT); pinMode(A5, OUTPUT);  pinMode(A3, OUTPUT);  //  Configure board pins
  lcd.begin(16, 2);  lcd.clear();  //  Initialize LCD and clear screen
}

void loop() {
  lcd.print(" Enter Passcode ");
  char key = myKeypad.getKey();
  if (isdigit(key)) { //  If the key entered is a digit (0 - 9)
    lcd.setCursor(4 + n, 1);  lcd.write('*');
    str1[n] = key;  //  Store key into array
    n++;  //  Increase key counter
  } else if (key == '*') {  //  If key '*' is pressed
    strncpy(str1, "", 4); //  Empty the key array
    n = 0;  //  Reset key counter
    lcd.clear();  //  Clear screen
  } else if (key == '#') {  //  If key '#' is pressed
    if ((strncmp(str1, code, 4) == 0) && (n <= 4)) {  //  If the correct code is entered
      lcd.clear();  
      lcd.print(" Access Granted ");
      digitalWrite(A5, 1); //  Trigger a pin high
      delay(1000);
      digitalWrite(A5, 0);  //  Trigger it back to low  
      lcd.clear();
      strncpy(str1, "", 4);  // Clear the key array for another input later
      n = 0;
    } else  { //  Incorrect code is entered
      lcd.clear();    
      lcd.print(" Access Denied  ");
      digitalWrite(A3, HIGH); 
      delay(200);
      digitalWrite(A3, LOW); 
      delay(200);
      digitalWrite(A3, HIGH); 
      delay(200);
      digitalWrite(A3, LOW); 
      lcd.clear();
      strncpy(str1, "", 4);  
      n = 0; 
    }
  }
}
