/* This example says "Hello World!" in Morse Code by flashing the 
 *  onboard LED on pin 13.  It also sends the text over the USB
 *  to the serial monitor on the Arduino IDE.  We will make a 
 *  function for dots and one for dashes and call them as needed
 *  to flash our message.  For timing purposes, each dot is 50 ms, 
 *  and each dash is 150 ms.  Intra-letter pauses are the same as a 
 *  dot and inter-letter pauses are the same as a dash.  The pause 
 *  between words is seven dots long.  
 *  
 *  LETTERS:
 *  H = . . . .     
 *  E = .     
 *  L = . - . .     
 *  O = - - -     
 *  W = . - -     
 *  R = . - .     
 *  D = - . .     
 *  ! = - . - . - -
 */

//define constants for timing.  The letter and word timing is short by
//one dot length since the dash and dot functions include a dot delay
//at the end.
const int dotDelay = 50;    //define the constant delay in milliseconds for dot
const int dashDelay = 150;  //define the constant delay in milliseconds for dash
const int letterDelay = 100;//define the constant delay between letters
const int wordDelay = 300;  //define the constant delay between words

// the setup() function runs only once when the board is powered up or reset.
void setup()
{
  // initialize pin 13 as an output. This pin has the LED connected to it.
  pinMode(13, OUTPUT);

  //initialize serial port to communicate with serial monitor at 9600 baud.
  Serial.begin(9600);
}  //end setup


// the loop function loops indefinitely
void loop() 
{
  Serial.println("Hello World!"); //send text to the Serial Monitor

  //Time for the morse code starting with
  //H = . . . .
  dot();
  dot();
  dot();
  dot();
  delay(letterDelay); //delay for the next letter

  //E = . 
  dot();
  delay(letterDelay); //delay for the next letter

  //L = . - . .
  dot();
  dash();
  dot();
  dot();
  dot();
  delay(letterDelay); //delay for the next letter
  
  //L = . - . .
  dot();
  dash();
  dot();
  dot();
  dot();
  delay(letterDelay); //delay for the next letter

  //O = - - -
  dash();
  dash();
  dash();
  
  delay(wordDelay); //delay for the next word

  //W = . - -
  dot();
  dash();
  dash();
  delay(letterDelay); //delay for the next letter

  //O = - - -
  dash();
  dash();
  dash();
  delay(letterDelay); //delay for the next letter

  //R = . - . 
  dot();
  dash();
  dot();
  delay(letterDelay); //delay for the next letter

  //L = . - . .
  dot();
  dash();
  dot();
  dot();
  dot();
  delay(letterDelay); //delay for the next letter 

  //D = - . 
  dash();
  dot();
  dot();
  delay(letterDelay); //delay for the next letter

  //! = - . - . - -
  dash();
  dot();
  dash();
  dot();
  dash();
  dash();

  delay (2000); //wait 2 seconds before starting all over  
}  //end loop

//create a function for a dot
void dot()
{
  digitalWrite(13, HIGH);   // turn the LED on
  delay(dotDelay);          // leave on for duration of a dot
  digitalWrite(13, LOW);    // turn the LED off
  delay(dotDelay);          // wait for intra-letter duration, same as dot
}  //end dot

//create a function for a dash
void dash()
{
  digitalWrite(13, HIGH);   // turn the LED on
  delay(dashDelay);          // leave on for duration of a dash
  digitalWrite(13, LOW);    // turn the LED off
  delay(dotDelay);          // wait for intra-letter duration, same as dot
}  //end dash

