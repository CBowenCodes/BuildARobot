/*  This is a basic example to print Hello World! to a 16x2 LCD display.
 *  Once printed, it then scrolls the message off the screen one character
 *  at a time.  It uses the LiquidCrystal.h library for displays compatible
 *  with the Hitachi HD44780 driver. 
 * LCD RS pin to pin 8
 * LCD Enable pin to pin 9
 * LCD D4 pin to  pin 10
 * LCD D5 pin to pin 11
 * LCD D6 pin to digital pin 12
 * LCD D7 pin to digital pin 13
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * each end goes to 5V and ground
 * 10k potentiometer to LCD VO pin (pin 12) 
 */

//include LCD library to use the display
#include <LiquidCrystal.h>

//define LCD pins and initialize LCD library
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);  //display connected to pins 8,9,10,11,12,and 13.

int scrollDelay = 150;                    //scrollDelay governs the speed of the scrolling

//code that runs once at startup.
void setup() 
{
  //initialize lcd with 16 columns and 2 rows
  lcd.begin(16,2);          

  //initialize serial port to communicate with serial monitor at 9600 baud.
  Serial.begin(9600);
}

//code that runs on a constant loop
void loop() 
{
  clearScreen();                    //call the clearScreen function to clear the display
  Serial.println("Hello World!");   //Print message to the Arduino IDE serial monitor
  sayHello();                       //scroll message across the display
  delay(1000);
  
}

//define function to clear the screen
void clearScreen()
{
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("                ");
}


//define function to scroll Hello World! across the display
void sayHello()
{
  //print the message starting at the upper left corner.
  lcd.setCursor(0,0);
  lcd.print("Hello World!");
  
  //create a for loop to shift left to drive the message off the display
  for (int shift = 0; shift < 16; shift ++) // the ++ just increments the shift variable by 1.
  {
    lcd.scrollDisplayLeft();
    delay(scrollDelay);
  }  
}

