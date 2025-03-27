#include <Arduino.h>
#include "car.hpp"
#include "sensor.hpp"
#include "constants.hpp"
#include "state.hpp"

CarController cct(m1, m2, e1, e2);

SensorController sct(right_edge_sensor, left_edge_sensor, right_sensor, left_sensor, middle_sensor);

AppState state = AppState::INIT;

/**
 * 统计经过的路口数
 * 
 * TODO:干掉这个状态
 */
int intersections_count = 0;

void setup()
{
  Serial.begin(9600);

  cct.setup();
  sct.setup();

  cct.start();
  state = AppState::MAIN;
}

void loop()
{
  switch (state)
  {
  case AppState::MAIN:
    cct.start();
    if (!sct.middle_state())
    {
      if (sct.left_state())
      {
        // 向右偏，应该向左转
        state = AppState::TURN_LEFT;
      }
      else if (sct.right_state())
      { // 向左偏，应该向右转
        state = AppState::TURN_RIGHT;
      }
    }
    
    if (sct.crossed())
    {
      intersections_count++;
      if (intersections_count == 2)
      {
        state = AppState::STOP;
      }
    }
    break;

  case AppState::TURN_LEFT:
    cct.turn_left();
    if (!sct.left_state())
    {
      state = AppState::MAIN;
    }
    break;

  case AppState::TURN_RIGHT:
    cct.turn_right();
    if (!sct.right_state())
    {
      state = AppState::MAIN;
    }
    break;

  case AppState::STOP:
    cct.stop();
    intersections_count = 0; // 重置统计
    break;
  
  case AppState::INIT:
    init();
    break;
  }

  // if (sct.crossing())
  // {
  //   cct.turn_left();
  //   delay(200);
  //   do
  //   {
  //     cct.turn_left();
  //   } while (!sct.middle_state());
  //   cct.start();
  // }
}