#define RPIN 3
#define YPIN 4
#define GPIN 5
#define RPIN2 8
#define YPIN2 9
#define GPIN2 10
#define BTN1 12
#define BTN2 13

void setup() {

  //Set all LED and push button Modes
  pinMode(RPIN, OUTPUT);
  pinMode(YPIN, OUTPUT);
  pinMode(GPIN, OUTPUT);
  pinMode(RPIN2, OUTPUT);
  pinMode(YPIN2, OUTPUT);
  pinMode(GPIN2, OUTPUT);

  // push buttons
  pinMode(BTN1, INPUT);
  pinMode(BTN2, INPUT);


  // set all LEDs to LOW ie off
  digitalWrite(RPIN, LOW);
  digitalWrite(YPIN, LOW);
  digitalWrite(GPIN, LOW);
  digitalWrite(RPIN2, LOW);
  digitalWrite(YPIN2, LOW);
  digitalWrite(GPIN2, LOW);





}



void loop() {

  digitalWrite(GPIN, HIGH);   // green1 ON
  digitalWrite(RPIN2, HIGH);  // red2 ON
  unsigned long redTime2 = millis(); // start time for the red light

  checkForButtonOnRedLight(BTN2, GPIN, YPIN, redTime2);


  digitalWrite(YPIN, LOW);  // yellow1 OFF


  digitalWrite(RPIN2, LOW);   //red2 OFF
  digitalWrite(GPIN2, HIGH);  //green2 ON


  digitalWrite(RPIN, HIGH);   //red1 ON
  unsigned long redTime1 = millis();

  checkForButtonOnRedLight(BTN1, GPIN2, YPIN2, redTime1);



  digitalWrite(YPIN2, LOW);  //yellow2 OFF
  digitalWrite(RPIN, LOW);  // red1 OFF
}

void checkForButtonOnRedLight(int btnPin, int oppositeGreenPin, int oppositeYellowPin, unsigned long redStartTime) {
  // for loop to both delay and check periodically for a button press
  //if no button is pressed 15 second delay
  for (int i = 0; i < 150; i++) {
    // after 13 seconds change the lights of the other junction to sync up with the red change at 15 seconds
    if (i == 130) {
      digitalWrite(oppositeGreenPin, LOW);   //green OFF
      digitalWrite(oppositeYellowPin, HIGH);  //yellow ON
    }

    unsigned long currentTime = millis();
    // button pressed and red has not been on for more than 10 seconds
    if (digitalRead(btnPin) && currentTime - redStartTime <= 10000) {
      delay(2000);
      digitalWrite(oppositeGreenPin, LOW);   //green OFF
      digitalWrite(oppositeYellowPin, HIGH);  //yellow ON
      break;
    } else {
      delay(100);
    }
  }

  delay(2000); // delay 2 seconds before turning red off and opposite Yellow off
}

