// color swirl! connect an RGB LED to the PWM pins as indicated
// in the #defines
// public domain, enjoy!
 
#define REDPIN 3
#define GREENPIN 5
#define BLUEPIN 6
#define SOUNDPIN 0
#define FADESPEED 5     // make this higher to slow down
const int sampleWindow = 50;
const int fadeFrequency = 30000;
const int fadeSpeed = 500;
unsigned int sample;
unsigned long previousMillisInitFade = 0;
unsigned long previousMillisFade = 0;
int brightness = 0;
int rValue = 0;
int gValue = 0;
int bValue = 0;
int rValueTarget = 0;
int gValueTarget = 0;
int bValueTarget = 0;

void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(SOUNDPIN, INPUT);
  Serial.begin(9600);
}
 
void setRGB(int r, int g, int b, int brightness){
  analogWrite(REDPIN,r + brightness);
  analogWrite(GREENPIN, g + brightness);
  analogWrite(BLUEPIN,b + brightness);
}

void loop() {

  unsigned long startMillis = millis();
  unsigned int peakToPeak = 0;

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(SOUNDPIN);
    if (sample < 1024)
    {
      if (sample > signalMax)
      {
        signalMax = sample;
      }
      else if (sample < signalMin)
      {
        signalMin = sample;
      }
    }
  }
  peakToPeak = signalMax - signalMin;
  brightness = (constrain(peakToPeak,0,192));
  setRGB(rValue,gValue,bValue,brightness);

  if (startMillis - previousMillisInitFade >= fadeFrequency){
    previousMillisInitFade = startMillis;
    Serial.println("Fading");
    rValueTarget = random(0,64);
    gValueTarget = random(0,64);
    bValueTarget = random(0,64);

  Serial.print("Writing red: "); Serial.println(rValueTarget);
  Serial.print("Writing green:" ); Serial.println(gValueTarget);
  Serial.print("Writing blue: "); Serial.println(bValueTarget);
  }

  if (startMillis - previousMillisFade >= fadeSpeed){
    previousMillisFade = startMillis;
    if(rValue < rValueTarget){
      rValue++;
    }
    if(rValue > rValueTarget){
      rValue--;
    }
    if(gValue < gValueTarget){
      gValue++;
    }
    if(gValue > gValueTarget){
      gValue--;
    }
    if(bValue < bValueTarget){
      bValue++;
    }
    if(bValue > bValueTarget){
      bValue--;
    }
  }




}
