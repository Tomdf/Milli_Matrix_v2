#define SMILE { \
    {0, 0, 1, 1, 1, 1, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {1, 0, 1, 0, 0, 1, 0, 1}, \
    {1, 0, 0, 0, 0, 0, 0, 1}, \
    {1, 0, 1, 0, 0, 1, 0, 1}, \
    {1, 0, 0, 1, 1, 0, 0, 1}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 0, 1, 1, 1, 1, 0, 0}  \
}

#define MRSKULL1 { \
    {0, 0, 1, 1, 1, 1, 1, 0}, \
    {0, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 0, 0, 1, 0, 0, 1, 1}, \
    {1, 0, 0, 1, 0, 0, 1, 1}, \
    {0, 1, 1, 0, 1, 1, 1, 0}, \
    {0, 0, 0, 1, 1, 1, 0, 0}, \
    {0, 0, 0, 1, 0, 1, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}  \
}

#define MRSKULL2 { \
    {0, 0, 1, 1, 1, 1, 1, 0}, \
    {0, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 0, 0, 1, 0, 0, 1, 1}, \
    {0, 1, 1, 0, 1, 1, 1, 0}, \
    {0, 0, 0, 1, 1, 1, 0, 0}, \
    {0, 0, 0, 1, 0, 1, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}  \
}

#define MRSKULL3 { \
    {0, 0, 1, 1, 1, 1, 1, 0}, \
    {0, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 0, 1, 1, 1, 0, 1, 1}, \
    {1, 0, 0, 1, 0, 0, 1, 1}, \
    {0, 1, 1, 0, 1, 1, 1, 0}, \
    {0, 0, 0, 1, 1, 1, 0, 0}, \
    {0, 0, 0, 1, 1, 1, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}  \
}

// pin[xx] on led matrix connected to nn on Arduino (-1 is dummy to make array start at pos 1)
int pins[17]= {-1, 7, 17, 15, 16, 14, 11, 3, 2, 4, 12, 6, 8, 9, 10, 5, 13};

// col[xx] of leds = pin yy on led matrix
int cols[8] = {pins[13], pins[3], pins[4], pins[10], pins[06], pins[11], pins[15], pins[16]};

// row[xx] of leds = pin yy on led matrix
int rows[8] = {pins[9], pins[14], pins[8], pins[12], pins[1], pins[7], pins[2], pins[5]};

int frameCount = 0;
int patternCount = 0;

byte col = 0;
byte row = 0;
byte pattern[2][8][8] = {MRSKULL1, MRSKULL3};
byte randBlink;

void setup() {
  // sets the pins as output
  for (int i = 1; i <= 16; i++) {
    pinMode(pins[i], OUTPUT);
  }  
  // set up cols and rows
  for (int i = 1; i <= 8; i++) {
    digitalWrite(cols[i - 1], LOW);
  }
  for (int i = 1; i <= 8; i++) {
    digitalWrite(rows[i - 1], HIGH);
  }
  // seed the random number with noise on an unconnected pin
  randomSeed(analogRead(0));
}

void loop(){
  ++frameCount;
  randBlink = random(100);
  if (frameCount == 2000) {
    if (randBlink <= 66) {
      patternCount++;
    }
    else {
      frameCount = 0;
    }
  }
  else if (frameCount == 2200) {
    patternCount = 0;
    frameCount = 0;
  }
    
  for (int i = 0; i < 8; i++) {      // loop to scan thru columns
    digitalWrite(cols[i], HIGH);     // enable column 'i'
    for (int j = 0; j < 8; j++) {    // loop to scan thru rows
      if (pattern[patternCount][i][j] == 1) {    // reference the predefined pattern
        digitalWrite(rows[j], LOW);    // enable row 'j'. turn on the LED at column 'i' and row 'j'
        delayMicroseconds(10);         // leave the LED on for 10 microseconds
        digitalWrite(rows[j], HIGH);   // turn the LED off
      } 
      else {
        delayMicroseconds(10);
      }
    }
    digitalWrite(cols[i], LOW);
  }
}

