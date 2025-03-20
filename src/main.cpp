#include <Arduino.h>
#include "car.hpp"
#include "sensor.hpp"
#include "constants.hpp"

CarController cct(m1, m2, e1, e2);

SensorController sct(right_edge_sensor, left_edge_sensor, right_sensor, left_sensor, middle_sensor);

/**
 * 统计经过的路口数
 */
int intersections_count = 0;

bool line_flag = false;

void setup()
{
  Serial.begin(9600);

  cct.setup();
  sct.setup();

  cct.start();
}

void loop()
{
  if (sct.crossed())
  {
    intersections_count++;
  }

  if (intersections_count == 2)
  {
    Serial.println("Stopped!");
    cct.stop();
    intersections_count = 0; // 重置统计
  }

  if (!sct.middle_state())
  {
    if (sct.left_state())
    {
      while (sct.left_state()) // 向右偏，应该向左转
      {
        cct.turn_left();
        Serial.println("turning left...");
      }
      // 重置
      cct.start();
    }
    else if (sct.right_state())
    { // 向左偏，应该向右转
      while (sct.right_state())
      {
        cct.turn_right();
        Serial.println("turning right...");
      }
      cct.start();
    }
  }
}