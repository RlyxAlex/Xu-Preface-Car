#pragma once

#include <Arduino.h>
#include "pins.h"
#include <IRremote.h>

static inline void motor(int dirpin1, int dirpin2, int speedpin, int speed) {
  speed = constrain(speed, -255, 255);

  if (speed > 0) {            // 前进
    digitalWrite(dirpin1, HIGH);
    digitalWrite(dirpin2, LOW);
  } else if (speed < 0) {     // 后退
    digitalWrite(dirpin1, LOW);
    digitalWrite(dirpin2, HIGH);
  } else {                    // 停：两脚都低（滑行）
    digitalWrite(dirpin1, LOW);
    digitalWrite(dirpin2, LOW);
  }

  analogWrite(speedpin, abs(speed));
}

//单轮控制
static inline void car_wheel_left(int speed) {
  motor(MOTOR_L_IN1, MOTOR_L_IN2, MOTOR_L_EN, speed);
}
static inline void car_wheel_right(int speed) {
  motor(MOTOR_R_IN1, MOTOR_R_IN2, MOTOR_R_EN, speed);
}

//两轮组合动作
static inline void car_drive(int left, int right) {
  car_wheel_left(left);
  car_wheel_right(right);
}

static inline void car_forward(int speed = 255)      { car_drive(speed,  speed); }
static inline void car_backward(int speed = 255)     { car_drive(-speed, -speed); }
static inline void car_stop()                        { car_drive(0, 0); }

//两轮反转
static inline void car_pivot_left(int speed = 200)   { car_drive( speed, -speed); }
static inline void car_pivot_right(int speed = 200)  { car_drive(-speed,  speed); }

// 弧线转向
static inline void car_arc_left(int speed = 150)     { car_drive( speed, 0); }
static inline void car_arc_right(int speed = 150)    { car_drive(0,  speed); }

static inline void car_setup() {
  pinMode(MOTOR_L_IN1, OUTPUT);
  pinMode(MOTOR_L_IN2, OUTPUT);
  pinMode(MOTOR_L_EN,  OUTPUT);
  pinMode(MOTOR_R_IN1, OUTPUT);
  pinMode(MOTOR_R_IN2, OUTPUT);
  pinMode(MOTOR_R_EN,  OUTPUT);

  car_stop();
}
const char* protoName(decode_type_t p) {
  switch (p) {
    case NEC:       return "NEC";
    case NEC2:      return "NEC2";
    case SAMSUNG:   return "SAMSUNG";
    case SAMSUNGLG: return "SAMSUNGLG";
    case SONY:      return "SONY";
    case RC5:       return "RC5";
    case RC6:       return "RC6";
    case LG:        return "LG";
    case PANASONIC: return "PANASONIC";
    case KASEIKYO:  return "KASEIKYO";
    case UNKNOWN:   return "UNKNOWN";
    default:        return "OTHER";
  }
}
//引脚初始化
static inline void Pin_setup() {
  pinMode(MOTOR_L_IN1, OUTPUT);
  pinMode(MOTOR_L_IN2, OUTPUT);
  digitalWrite(MOTOR_L_IN1, LOW);
  digitalWrite(MOTOR_L_IN2, LOW);
  pinMode(MOTOR_R_IN1, OUTPUT);
  pinMode(MOTOR_R_IN2, OUTPUT);
  digitalWrite(MOTOR_R_IN1, LOW);
  digitalWrite(MOTOR_R_IN2, LOW);
  pinMode(ULTRA_TRIG_Front, OUTPUT);
  pinMode(ULTRA_ECHO_Front, INPUT);
  pinMode(A0, OUTPUT);
}