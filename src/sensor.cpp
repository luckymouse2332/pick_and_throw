#include "sensor.hpp"
#include "Arduino.h"

void SensorController::setup() {
  pinMode(right, INPUT);
  pinMode(left, INPUT);
  pinMode(left_edge, INPUT);
  pinMode(right_edge, INPUT);
  pinMode(middle, INPUT);
}

bool SensorController::crossed()
{
  static bool line_flag = false;

  int state = digitalRead(middle);

  // 统计路口
  if (state && left_state() && right_state() && left_edge_state() && right_edge_state())
  {
    Serial.println("Online...");
    line_flag = true;
  }

  if ((!left_edge_state()) && (!right_edge_state()) && line_flag) // 走出了黑线
  {
    Serial.println("Operated!");
    line_flag = false;
    return true;
  }
  return false;
}

bool SensorController::right_state() {
  return digitalRead(right) == 1;
}

bool SensorController::left_state() {
  return digitalRead(left) == 1;
}

bool SensorController::right_edge_state() {
  return digitalRead(right_edge) == 1;
}

bool SensorController::left_edge_state() {
  return digitalRead(left_edge) == 1;
}

bool SensorController::middle_state() {
  return digitalRead(middle) == 1;
}