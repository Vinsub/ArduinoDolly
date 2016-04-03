#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
const int buttonPin = A0;    // the number of the pushbutton pin

// Button value and menù value:
const int valueButtonMenuMeno[] = {720,785};
const int valueButtonMenuPiu[] = {620,680};
const int valueButtonNoMeno[] = {445,485};
const int valueButtonSiPiu[] = {345,385};
const int valueButtonStart[] = {90,145};
const int valueButtonStop[] = {15,50};
char* menuPrincipale[4] = {"Andata e ritorno","Tempo corsa     ","Controllo       ","Reset           "};
char* menuPrincipaleSecondaRiga[4] = {"Si/No > ","000            ","3                ","4                "};
int voceMenu = 0;
int buttonState;             // the current reading from the input pin
int lastButtonState = 0;   // the previous reading from the input pin
int giro = 0;
// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
int lastDebounceTime = 0;  // the last time the output pin was toggled
int debounceDelay = 25;    // the debounce time; increase if the output flickers

int debounceDelayPush = 150;
int c = 0;
int startTimePush = 0;
int pushingTime = 0;

int andataRitorno = 0;
int tempoCorsa = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(buttonPin, INPUT);
 
  lcd.setCursor(0,0);
  lcd.print("Ciao");
  lcd.setCursor(0,1);
  lcd.print("Antonio");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(menuPrincipale[voceMenu]);
  lcd.setCursor(0,1);
  lcd.print(menuPrincipaleSecondaRiga[voceMenu]);
}
//int buttonRead() {
  //return analogRead(buttonPin);
//}
// Da usare per il debounce
int buttonRead() {
  int reading = analogRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  } 
  if ((millis() - lastDebounceTime) > debounceDelay) {
      if (reading != buttonState) {
        buttonState = reading;
      }
  }
  lastButtonState = reading;
  return buttonState;
}

int buttonValue(){
  int value = buttonRead();
  if (value == 0) {
    return 0;
  }

  if ((valueButtonMenuMeno[0] < value)&&(value < valueButtonMenuMeno[1])) {
    return 1;
  }
  else if ((valueButtonMenuPiu[0] < value)&&(value < valueButtonMenuPiu[1])) {
    return 2;
  }
  else if ((valueButtonNoMeno[0] < value)&&(value < valueButtonNoMeno[1])) {
    return 3;
  }
  else if ((valueButtonSiPiu[0] < value)&&(value < valueButtonSiPiu[1])) {
    return 4;
  }
  else if ((valueButtonStart[0] < value)&&(value < valueButtonStart[1])) {
    return 5;
  }
  else if ((valueButtonStop[0] < value)&&(value < valueButtonStop[1])) {
    return 6;
  }
}

void lcdPrintMenu() {
  lcd.setCursor(0,0);
  lcd.print(menuPrincipale[voceMenu]);
  lcd.setCursor(0,1);
  lcd.print(menuPrincipaleSecondaRiga[voceMenu]);
}
void loop() {
  
  int button = buttonValue();
  if (button == 0) { c = 0;}
  if (giro == 0) {
    if (button == 1) {
      if (c == 0) { 
        startTimePush = millis();
        c = 1;
      }
      else if (c == 1) {
        pushingTime = millis();
        if (pushingTime > (startTimePush + debounceDelayPush)) {
          voceMenu--;
          if (voceMenu < 0) {
            voceMenu = 3;
           }
          lcdPrintMenu();
          c = 0;
         }
       }
    }
    else if (button == 2) {
      if (c == 0) { 
        startTimePush = millis();
        c = 1;
      }
      else if (c == 1) {
        pushingTime = millis();
        if (pushingTime > (startTimePush + debounceDelayPush)) {
          voceMenu++;
          if (voceMenu > 3) {
            voceMenu = 0;
            }
          lcdPrintMenu();
          c = 0;
         }
       }
    }
  }
  if (voceMenu == 0) {
    if (button == 3) {
      if (c == 0) { 
        startTimePush = millis();
        c = 1;
      }
      else if (c == 1) {
        pushingTime = millis();
        if (pushingTime > (startTimePush + debounceDelayPush)) {
          
          lcd.print("No    ");
          c = 0;
          andataRitorno = 1;
         }
       }
    }
    if (button == 4) {
      if (c == 0) { 
        startTimePush = millis();
        c = 1;
      }
      else if (c == 1) {
        pushingTime = millis();
        if (pushingTime > (startTimePush + debounceDelayPush)) {
          c = 0;
          andataRitorno = 2;
         }
       }
    }
    if (andataRitorno == 1) {
      lcd.setCursor(9,1);
      lcd.print("No        ");
    }
    if (andataRitorno == 2) {
      lcd.setCursor(9,1);
      lcd.print("Si        ");
    } 
  }
  else if (voceMenu == 1) {
    if (button == 3) {
      if (c == 0) { 
        startTimePush = millis();
        c = 1;
      }
      else if (c == 1) {
        pushingTime = millis();
        if (pushingTime > (startTimePush + debounceDelayPush)) {
          tempoCorsa--;
          c = 0;
        }
      }
    }
    else if (button == 4) {
      if (c == 0) { 
        startTimePush = millis();
        c = 1;
      }
      else if (c == 1) {
        pushingTime = millis();
        if (pushingTime > (startTimePush + debounceDelayPush)) {
          tempoCorsa++;
          c = 0;
        }
      }
    }
    if (tempoCorsa < 0) { tempoCorsa = 0; }
    if (tempoCorsa > 999) { tempoCorsa = 999; }
    if (tempoCorsa < 10) {
      lcd.setCursor(0,1);
      lcd.print("00");
      lcd.setCursor(2,1);
     }
    if (tempoCorsa > 9 && tempoCorsa < 100) {
      lcd.setCursor(0,1);
      lcd.print("0");
      lcd.setCursor(1,1);
     }
    if (tempoCorsa > 99) {
      lcd.setCursor(0,1);
     }
    lcd.print(tempoCorsa);
   }



  Serial.println(buttonRead());
  Serial.println(button);
  Serial.print("menu: ");
  Serial.println(voceMenu);
}
