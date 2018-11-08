/*
 * This example is based on a WAV file player sample for the Adafruit Waveshield.  It has been modified 
 * for the InYourFaceBot 2600 and controls the sound portion of the robot.  It gets data through a 
 * software serial port from the other controller so it knows what type of sound to play.
 */
#include <WaveHC.h>
#include <WaveUtil.h>
#include <SoftwareSerial.h> //this is to use two pins as a software serial port

SoftwareSerial mySerial(6, 7); // RX, TX pins
SdReader card;    // This object holds the information for the card
FatVolume vol;    // This holds the information for the partition on the card
FatReader root;   // This holds the information for the volumes root directory
FatReader file;   // This object represent the WAV file 
WaveHC wave;      // This is the only wave (audio) object, since we will only play one at a time

uint8_t dirLevel; // indent level for file/dir names    (for prettyprinting)
dir_t dirBuf;     // buffer for directory reads


/*
 * Define macro to put error messages in flash memory
 */
#define error(msg) error_P(PSTR(msg))

// Function definitions (we define them here, but the code is below)
void play(FatReader &dir);

//////////////////////////////////// SETUP
void setup() {
      
  Serial.begin(9600);           // set up Serial library at 9600 bps for debugging
    
  mySerial.begin(4800); // set the data rate for the SoftwareSerial port
  Serial.println("mySerial started"); 
  
  randomSeed(analogRead(0));  // start random seed generator
  putstring_nl("\nWave test!");  // say we woke up!
  
  putstring("Free RAM: ");       // This can help with debugging, running out of RAM is bad
  Serial.println(FreeRam());

  //  if (!card.init(true)) { //play with 4 MHz spi if 8MHz isn't working for you
  if (!card.init()) {         //play with 8 MHz spi (default faster!)  
    error("Card init. failed!");  // Something went wrong, lets print out why
  }
  
  // enable optimize read - some cards may timeout. Disable if you're having problems
  card.partialBlockRead(true);
  
  // Now we will look for a FAT partition!
  uint8_t part;
  for (part = 0; part < 5; part++) {   // we have up to 5 slots to look in
    if (vol.init(card, part)) 
      break;                           // we found one, lets bail
  }
  if (part == 5) {                     // if we ended up not finding one  :(
    error("No valid FAT partition!");  // Something went wrong, lets print out why
  }
  
  // Lets tell the user about what we found
  putstring("Using partition ");
  Serial.print(part, DEC);
  putstring(", type is FAT");
  Serial.println(vol.fatType(), DEC);     // FAT16 or FAT32?
  
  // Try to open the root directory
  if (!root.openRoot(vol)) {
    error("Can't open root dir!");      // Something went wrong,
  }
  
  // Whew! We got past the tough parts.
  putstring_nl("Files found (* = fragmented):");

  // Print out all of the files in all the directories.
  root.ls(LS_R | LS_FLAG_FRAGMENTED);
}

//////////////////////////////////// LOOP
void loop() {
   if (mySerial.available()) {  //when something comes across digital serial
   char c = mySerial.read();
   Serial.println(c);
   if(c=='1')
  {
    Serial.println("Greet");
    greet();
  }
  else if (c=='2')
  {
    Serial.println("Fart");
    fart();
  }
  else if (c=='3')
  {
    Serial.println("Exclaim");
    exclaim();
  }
  }
}

/////////////////////////////////// Functions



/*
 * print error message and halt
 */
void error_P(const char *str) {
  PgmPrint("Error: ");
  SerialPrint_P(str);
  sdErrorCheck();
  while(1);
}
/*
 * print error message and halt if SD I/O error, great for debugging!
 */
void sdErrorCheck(void) {
  if (!card.errorCode()) return;
  PgmPrint("\r\nSD I/O error: ");
  Serial.print(card.errorCode(), HEX);
  PgmPrint(", ");
  Serial.println(card.errorData(), HEX);
  while(1);
}


/*
 * Open and start playing a WAV file
 */
void playfile(char *name) {
  while (wave.isplaying) {// already playing something, so stop it!
    delay(100);
  }
  if (!file.open(root, name)) {
    PgmPrint("Couldn't open file ");
    Serial.print(name); 
    return;
  }
  if (!wave.create(file)) {
    PgmPrintln("Not a valid WAV");
    return;
  }
  // ok time to play!
  wave.play();
}

/*
 * Play a random fart file.  Fart noises were saved on SD card as F##.WAV
 */
void fart() {
  long randFart;
  randFart = random(7)+1;  //choose a random number between 1 and 7;
  Serial.println(randFart);
  if (randFart == 1){
    playfile("F01.WAV");
  }
  else if (randFart == 2){
    playfile("F02.WAV");
  }
  else if (randFart == 3){
    playfile("F03.WAV");
  }
  else if (randFart == 4){
    playfile("F04.WAV");
  }
  else if (randFart == 5){
    playfile("F05.WAV");
  }
  else if (randFart == 6){
    playfile("F06.WAV");
  }
  else if (randFart == 7){
    playfile("F07.WAV");
  }
}

/*
 * Play a random greeting.  Greeting files were saved on SD card as G##.WAV
 */
void greet() {
  long randFart;
  randFart = random(10)+1;  //choose a random number between 1 and 10;
  Serial.println(randFart);
  if (randFart == 1){
    playfile("G01.WAV");
  }
  else if (randFart == 2){
    playfile("G02.WAV");
  }
  else if (randFart == 3){
    playfile("G03.WAV");
  }
  else if (randFart == 4){
    playfile("G04.WAV");
  }
  else if (randFart == 5){
    playfile("G05.WAV");
  }
  else if (randFart == 6){  //in case more are added later
    playfile("G06.WAV");
  }
  else if (randFart == 7){  //in case more are added later
    playfile("G07.WAV");
  }
  else if (randFart == 8){  //in case more are added later
    playfile("G08.WAV");
  }
  else if (randFart == 9){  //in case more are added later
    playfile("G09.WAV");
  }
  else if (randFart == 10){  //in case more are added later
    playfile("G10.WAV");
  }

}

/*
 * Play a random exclamation.  Exclamation WAV files were saved on SD card as E##.WAV
 */
void exclaim() {
  long randFart;
  randFart = random(17)+1;  //choose a random number between 1 and 12;
  Serial.println(randFart);
  if (randFart == 1){
    playfile("E01.WAV");
  }
  else if (randFart == 2){
    playfile("E02.WAV");
  }
  else if (randFart == 3){
    playfile("E03.WAV");
  }
  else if (randFart == 4){
    playfile("E04.WAV");
  }
  else if (randFart == 5){
    playfile("E05.WAV");
  }
  else if (randFart == 6){
    playfile("E06.WAV");
  }
  else if (randFart == 7){
    playfile("E07.WAV");
  }
  else if (randFart == 8){
    playfile("E08.WAV");
  }
  else if (randFart == 9){
    playfile("E09.WAV");
  }
  else if (randFart == 10){
    playfile("E10.WAV");
  }
  else if (randFart == 11){
    playfile("E11.WAV");
  }
  else if (randFart == 12){
    playfile("E12.WAV");
  }
  else if (randFart == 13){
    playfile("E13.WAV");
  }
  else if (randFart == 14){
    playfile("E14.WAV");
  }
  else if (randFart == 15){
    playfile("E15.WAV");
  }
  else if (randFart == 16){
    playfile("E16.WAV");
  }
  else if (randFart == 17){
    playfile("E17.WAV");
  }
  
}
