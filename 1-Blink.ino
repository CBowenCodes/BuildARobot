// the setup() function runs only once when the board is powered up or reset.
void setup()
{
  // initialize pin 13 as an output. This pin has the LED connected to it.
  pinMode(13, OUTPUT);
}

// the loop function loops indefinitely
void loop() 
{
  digitalWrite(13, HIGH);   // turn the LED on (send 5 volts to pin 13)
  delay(1000);              // wait for a second (1000 milliseconds)
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
}

