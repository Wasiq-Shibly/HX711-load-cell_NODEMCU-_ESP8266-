

#include <HX711_ADC.h>
HX711_ADC LoadCell(D3, D0);
long t;

void setup() {
  
  float calValue; // calibration value
  calValue = 696.0; // uncomment this if you want to set this value in the sketch 
  #if defined(ESP8266) 
 
  #endif
  Serial.begin(9600); 
  
  delay(10);
  Serial.println();
  Serial.println("Starting...");
  LoadCell.begin();
  long stabilisingtime = 2000; // tare preciscion can be improved by adding a few seconds of stabilising time
  LoadCell.start(stabilisingtime);
  if(LoadCell.getTareTimeoutFlag()) {
    Serial.println("Tare timeout, check MCU>HX711 wiring and pin designations");
  }
  else {
    LoadCell.setCalFactor(calValue); // set calibration value (float)
    Serial.println("Startup + tare is complete");
  }
}

void loop() {

  LoadCell.update();


  if (millis() > t + 250) {
    float i = LoadCell.getData();
    Serial.print("Load_cell output val: ");
    Serial.println(i);
    t = millis();
  }


}
