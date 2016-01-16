// color swirl! connect an RGB LED to the PWM pins as indicated
// in the #defines
// public domain, enjoy!
 
#define REDPIN 3
#define GREENPIN 5
#define BLUEPIN 6
#define SOUNDPIN 0
#define FADESPEED 5     // make this higher to slow down
const int sampleWindow = 50;
unsigned int fadeFrequency = 60000;
int fadeSpeed = 20;
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
int fadeFrequencyPotPin = A1;
int fadeSpeedPotPin = A2;

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

  fadeFrequency = analogRead(fadeFrequencyPotPin) * 120;
//  fadeSpeed = analogRead(fadeSpeedPotPin) / 2;
  
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
  brightness = (constrain(peakToPeak,0,64));
  setRGB(rValue,gValue,bValue,brightness);


  if (startMillis - previousMillisInitFade >= fadeFrequency){
    if (fadeFrequency != 0){
      previousMillisInitFade = startMillis;
      Serial.println("Fading");
      Serial.println(fadeFrequency);
      Serial.println(analogRead(fadeFrequencyPotPin));
      rValueTarget = random(0,192);
      gValueTarget = random(0,192);
      bValueTarget = random(0,192);
    }
  }

  if (startMillis - previousMillisFade >= fadeSpeed){
    previousMillisFade = startMillis;
    
    if(rValue < rValueTarget){
      rValue++;
      Serial.print("Red: ");Serial.println(rValue);
    }
    if(rValue > rValueTarget){
      rValue--;
      Serial.print("Red: ");Serial.println(rValue);
    }
    if(gValue < gValueTarget){
      gValue++;
      Serial.print("Green: ");Serial.println(gValue);
    }
    if(gValue > gValueTarget){
      gValue--;
      Serial.print("Green: ");Serial.println(gValue);
    }
    if(bValue < bValueTarget){
      bValue++;
      Serial.print("Blue: ");Serial.println(bValue);
    }
    if(bValue > bValueTarget){
      bValue--;
      Serial.print("Blue: ");Serial.println(bValue);
    }
  }




}
