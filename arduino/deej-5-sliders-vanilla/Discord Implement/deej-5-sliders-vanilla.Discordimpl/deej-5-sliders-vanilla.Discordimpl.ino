

#include <Wire.h>
#include <mpr121.h>
//Digital port 2 for IRQ,SDA second to top, SCL top
const int NUM_SLIDERS = 1;
const int analogInputs[NUM_SLIDERS] = {A0};// , A1, A2, A3, A4, A5, A6, A7};
int analogSliderValues[NUM_SLIDERS];
int key = 0;
void setup() { 
  for (int i = 0; i < NUM_SLIDERS; i++) {
    pinMode(analogInputs[i], INPUT);
    
  }

  Wire.begin();
  CapaTouch.begin();

  Serial.begin(9600);
}

void loop() {
  updateSliderValues();
  getKeypadInput();
  sendSliderValues(); // Actually send data (all the time)
  sendKeypadVals();
  printSliderValues(); // For debug
  //delay(10);
}

void getKeypadInput() {
  
}

void updateSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
     analogSliderValues[i] = analogRead(analogInputs[i]);
  }
}

void sendSliderValues() {
  String builtString = String("");

  for (int i = 0; i < NUM_SLIDERS; i++) {
    builtString += String((int)analogSliderValues[i]);

    if (i < NUM_SLIDERS - 1) {
      builtString += String("|");
    }
  }
  
  Serial.println(builtString);
}
void sendKeypadVals(){
  key=CapaTouch.keyPad();
  if (key>=0){
    String keyStr = String("K")+String(key);
    Serial.write(keyStr.c_str());
    Serial.write("\n");
  }
  
 
  
}

void printSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    String printedString = String("Slider #") + String(i + 1) + String(": ") + String(analogSliderValues[i]) + String(" mV");
    Serial.write(printedString.c_str());

    if (i < NUM_SLIDERS - 1) {
      Serial.write(" | ");
    } else {
      Serial.write("\n");
      
    }
    
  }
  
}
