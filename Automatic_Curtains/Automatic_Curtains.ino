#include "7segment.h"

//(numbers closer to 1024 are darker) 
int light_sensor = A1; //light sensor analog input
int sw = 2; //switch input
int current = A3; //current sensor input
int cw = 6; //clockwise output
int ccw = 7; //counterclockwise output
int button1 = A4;
int button2 = A5;

// when ambient light is > max light, curtains open
// when ambient light is below min light, curtains close
int MAX_LIGHT = 450;
int MIN_LIGHT = 300;
int timer = 0; // time till curtains open in hours
bool timerOpen = false;

bool isClosed = false;
bool isOpen = false;

void setup() {
  
  Serial.begin(9600);  

  setupDisplay(); //import from 7segment.h
  
  pinMode(ccw, OUTPUT);
  pinMode(cw, OUTPUT);
  pinMode(sw, INPUT);
  pinMode(light_sensor, INPUT);
  pinMode(current, INPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);

}

void loop() {
  while (digitalRead(sw) == HIGH) {
    interruptFunction();
  } 

  timeFunction();
  
}

void interruptFunction() {
  printChar(' ');
  alternate();
}

// opens or closes curtains with passthrough strings "open" or "close"
void moveCurtains(String str) {
  int pin = 0;
  
  if (str.equals("open")) {
    pin = cw;
  } else {
    pin = ccw;
  }
  
  Serial.println(str);
  
  digitalWrite(pin, HIGH);
  delay(500);
  while (analogRead(current) < 450) {
    
  }
  digitalWrite(pin, LOW);
  delay(1000);
}

void alternate() {
  if (readLightSensor() > MAX_LIGHT && !isOpen) {
    moveCurtains("open");
    isClosed = false;
    isOpen = true;
  } else if (readLightSensor() < MIN_LIGHT && !isClosed) {
    moveCurtains("close");
    isOpen = false;
    isClosed = true;
  }
}

void setMode() {
  blinkChar('D', 3);
  bool modeSet = false;
  while (!modeSet) {
    if (timerOpen) {
      printChar('O');
    } else {
      printChar('C');
    }

    if (digitalRead(button1) == 0) {
      if (timerOpen) {
        timerOpen = false;
      } else {
        timerOpen = true;
      }
      while(digitalRead(button1) == 0) {
      }
      delay(100);
    }

    if (digitalRead(button2) == 0) {
      while(digitalRead(button2) == 0) {
      }
      modeSet = true;
    }
  }
}

void setTime(char c) {
  blinkChar(c, 3);
  int t = 0;
  bool timeSet = false;
  while (!timeSet) {
    
    printChar(t + '0');
    if (digitalRead(button1) == 0) {
      t++;
      if (t > 9) {
        t = 0;
      }
      while(digitalRead(button1) == 0) {
      }
      delay(100);
    }
    if (digitalRead(button2) == 0) {
      while(digitalRead(button2) == 0) { 
        }
        timeSet = true;
      }
    }

  timer = t;
  
}

void timeFunction() {
  timer = 0;
  setMode();
  setTime('H');

  if (timerOpen) {
    printWord("OPEN");
  } else {
    printWord("CLOSE");
  }
  printChar(' ');
  delay(500);
  printChar(timer + '0');
  delay(1000);
  printWord("HOURS");

  long startTime = millis();
  printChar('.');

  while((millis() - startTime)/60000 < timer*60) {
    if (digitalRead(sw) == HIGH) {
      return;
    }
  }
  if (timerOpen) {
    moveCurtains("open");
    isOpen = true;
  } else {
    moveCurtains("close");
    isClosed = false;
  }
}

// returns "reversed" light sensor values so lower numbers are darker
int readLightSensor() {
  return 1024 - analogRead(light_sensor);
}
