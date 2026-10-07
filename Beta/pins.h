#pragma once
#include <Arduino.h>

enum Pins : uint8_t {
    // ---- 电机 L298N：左轮 ----
  MOTOR_L_IN1 = 5,     // 方向脚 1
  MOTOR_L_IN2 = 7,     // 方向脚 2
  MOTOR_L_EN  = 6,     // 调速脚（PWM，Timer0）

  // ---- 电机 L298N：右轮 ----
  MOTOR_R_IN1 = 8,     // 方向脚 1
  MOTOR_R_IN2 = 10,     // 方向脚 2
  MOTOR_R_EN  = 11,    // 调速脚（PWM，Timer2）
  
  // ---- 超声波（车头） HC-SR04 ----
  ULTRA_TRIG_Front = 13, 
  ULTRA_ECHO_Front = 12,

};