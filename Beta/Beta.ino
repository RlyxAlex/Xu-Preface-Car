#define IR_USE_AVR_TIMER1
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Car.h"

bool flag=false;
bool     overtaking = Disable;
uint32_t overtakeAt = 0;
uint32_t lastSense  = 0;
uint32_t lastLcd    = 0;
float    dist       = -1;

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
  //OverTake Mode
  if (overtaking && millis() - overtakeAt >= 5000) {
    overtaking = false;
    straight(150);
  }
  //避障
  if (millis() - lastSense >= 150) {
    lastSense = millis();
    dist = Ultrasound_front();
    if (dist > 0 && dist < 30) {
      BrakeActivated = Enabled;
      brake();
      delay(600);
      if(flag && BrakeActivated==Disable){
        straight(150);
      }
    }
    else{
      BrakeActivated = Disable;
    }
  }
  if (IrReceiver.decode()){
    IrReceiver.resume();
    switch (IrReceiver.decodedIRData.command) {
      case 0x40:
        flag=true;
        BrakeActivated=Disable;
        overtaking = false;
        ReverseActivation = Disable;
        straight(150);
        break;
      case 0x44:
        flag=false;
        overtaking = false;
        Reversing(150);
        break;
      case 0x43:
        flag=false;
        ReverseActivation = Disable;
        overtaking = false;
        brake();
        break;
      case 0x16:
        digitalWrite(A0,HIGH);
        delay(300);
        digitalWrite(A0,LOW);
        break;
      case 0x9:
        ReverseActivation = Disable;
        if(flag=true){
          overtakeAt = millis();
          straight(255);
        }
        break;
      case 0x46:
        overtaking = false;
        if(ReverseActivation!=Enabled){
          flag=true;
          straight(100);
        }
        else {
          flag=false;
          Reversing(100);
        }
        break;
      case 0x45:
        car_arc_left(150);
        break;
      case 0x47:
        car_arc_right(150);
        break;
      case 0x19:
        car_drive(128,150);
        break;
      case 0xD:
        car_drive(150,128);
        break;
      default:
        break;
    }
  }
  Display();
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