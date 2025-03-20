#include "car.hpp"
#include <Arduino.h>

void CarController::setup()
{
  pinMode(left_forward_pin, OUTPUT);
  pinMode(right_forward_pin, OUTPUT);
  pinMode(left_speed_pin, OUTPUT);
  pinMode(right_speed_pin, OUTPUT);
}

void CarController::start()
{
  // 初始化转向
  digitalWrite(left_forward_pin, LOW);
  digitalWrite(right_forward_pin, LOW);

  // 初始化转速
  analogWrite(left_speed_pin, 180);
  analogWrite(right_speed_pin, 255);
}

void CarController::turn_left()
{
  start(); // 先重置参数再停转
  analogWrite(left_speed_pin, 0);
}

void CarController::turn_right()
{
  start();
  analogWrite(right_speed_pin, 0);
}

void CarController::stop()
{
  // 初始化转速
  analogWrite(left_speed_pin, 0);
  analogWrite(right_speed_pin, 0);
}
