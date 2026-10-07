#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Car.h"

enum Status : bool {
  Disable = false,
  Enabled = true
};

LiquidCrystal_I2C lcd_tail(0x27,16,2);

Status BrakeActivated = Enabled;
Status ReverseActivation = Disable;
Status OverTake = Disable;

//Ultrasound_front函数 ：超声波测距,Trig:13,Echo:12
float Ultrasound_front(){
  digitalWrite(ULTRA_TRIG_Front,LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRA_TRIG_Front,HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRA_TRIG_Front,LOW);
  float distance = pulseIn(ULTRA_ECHO_Front,HIGH) / 58.00;
  delay(10);
  return distance;
}

void Display(){
  lcd_tail.clear();
  lcd_tail.setCursor(0, 0);
  lcd_tail.print(String(Ultrasound_front()) + String("cm"));
  delay(500);
}

void straight(){
  // if (BrakeActivated==Disable) {
    car_forward(150);
  // }
  // else{
    // return;
  // }
}

void Reversing(){
  // ReverseActivation=Enabled;
  car_backward(150);
}

void brake(){
  // if(ReverseActivation!=Enabled){
    car_stop();
  // }
}

void setup(){
  lcd_tail.init();
  lcd_tail.backlight();
  Pin_setup();
  car_setup();
  car_stop();
  Serial.begin(9600);
  IrReceiver.begin(A3, DISABLE_LED_FEEDBACK);
}
void loop(){
  if (!IrReceiver.decode()) return;
  IrReceiver.resume();
  uint16_t cmd = IrReceiver.decodedIRData.command; 
  Display();
  switch (cmd) {
    case 0x40:
      straight();
      OverTake=Enabled;
      break;
    case 0x44:
      Reversing();
      OverTake=Disable;
      break;
    case 0x43:
      brake();
      OverTake=Disable;
      break;
    case 0x16:
      digitalWrite(A0,HIGH);
      delay(1000);
      digitalWrite(A0,LOW);
      break;
    case 0x9:
      if(OverTake==Enabled){
        car_forward(255);
        delay(5000);
      }
      OverTake=Disable;
      straight();
      break;
    case 0x46:
      OverTake=Disable;
      car_forward(100);
      break;
    default:
      break;
  }
}
  // Serial.flush();
  // if(Ultrasound_front() <= 30){
  //   Display();
  //   brake();
  //   delay(1000);
  //   Reversing();
  //   BrakeActivated=Enabled;
  // }
  // else{
  //   ReverseActivation=Disable;
  //   BrakeActivated=Disable;
  // }
  // straight();
// }