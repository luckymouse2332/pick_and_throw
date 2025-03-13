#include <Arduino.h>
#include "car.hpp"

/**
 * 控制转速
 */
const int e1 = 9;
const int e2 = 10;

/**
 * 控制转向
 */
const int m1 = 7;
const int m2 = 8;

CarController cct(m1, m2, e1, e2);

/**
 * 光电传感器
 *
 * 1: 在线上
 * 0: 不在线上
 */
const int middle_sensor = 4;
const int right_sensor = 3;
const int left_sensor = 5;
const int right_edge_sensor = 2;
const int left_edge_sensor = 6;

/**
 * 统计经过的路口数
 */
int intersections_count = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(middle_sensor, INPUT);

  cct.init();
  cct.start();
}

void loop()
{
  // 判断在不在线上
  int state = digitalRead(middle_sensor);
  int left_state = digitalRead(left_sensor);
  int right_state = digitalRead(right_sensor);
  int right_edge_state = digitalRead(right_edge_sensor);
  int left_edge_state = digitalRead(left_edge_sensor);

  // 统计路口
  // TODO：等到走出黑线的时候计数
  if (state && left_state && right_state && left_edge_state && right_edge_state)
  {
    intersections_count++;
  }

  if (intersections_count == 4)
  {
    cct.stop();
    intersections_count = 0; // 重置统计
  }

  if (!state) // 寻线修正
  {
    if (left_state)
    { // 向右偏，应该向左转
      while (digitalRead(left_sensor))
      {
        cct.turn_left();
        Serial.println("turning left...");
      }
      // 重置
      cct.start();
    }
    else if (right_state)
    { // 向左偏，应该向右转
      while (digitalRead(right_state))
      {
        cct.turn_right();
        Serial.println("turning right...");
      }
      cct.start();
    }
    else
    {
      Serial.println("error");
    }
  }
}