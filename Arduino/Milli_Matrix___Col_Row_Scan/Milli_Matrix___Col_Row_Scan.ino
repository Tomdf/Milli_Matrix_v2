
const int modeButton = 0;

int refreshSpeed = 10;

// pin[xx] on led matrix connected to nn on Arduino (-1 is dummy to make array start at pos 1)
int pins[17]= {-1, 7, 17, 15, 16, 14, 11, 3, 2, 4, 12, 6, 8, 9, 10, 5, 13};

// col[xx] of leds = pin yy on led matrix
int cols[8] = {pins[13], pins[3], pins[4], pins[10], pins[06], pins[11], pins[15], pins[16]};

// row[xx] of leds = pin yy on led matrix
int rows[8] = {pins[9], pins[14], pins[8], pins[12], pins[1], pins[7], pins[2], pins[5]};

void setup() {
  // set the mode select button pin as an input
  pinMode(modeButton, INPUT);
  
  // sets the pins attached to the matrix as output
  for (int i = 1; i <= 16; i++) {
    pinMode(pins[i], OUTPUT);
  }
  
  // sets the cols low and the rows high
  for (int i = 1; i <= 8; i++) {
    digitalWrite(cols[i - 1], LOW);
  }
  for (int i = 1; i <= 8; i++) {
    digitalWrite(rows[i - 1], HIGH);
  }
}

void loop(){
  for (int i = 0; i < 8; i++) {
    digitalWrite(cols[i], HIGH); // Turn whole column on at once
    for (int j = 0; j < 8; j++) {
      if (digitalRead(modeButton) == HIGH) {
        refreshSpeed += 1000;
        if (refreshSpeed >= 15010) {
          refreshSpeed = 10;
        }
        delay(50);
      }
      digitalWrite(rows[j], LOW);
      delayMicroseconds(refreshSpeed);
      digitalWrite(rows[j], HIGH);
    }
    digitalWrite(cols[i], LOW);
  }
}
