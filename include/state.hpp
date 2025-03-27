#ifndef STATE_HPP

#define STATE_HPP

/**
 * 应用程序状态
 */
enum AppState
{
  /**
   * 初始状态
   */
  INIT,

  /**
   * 左转
   */
  TURN_LEFT,
  
  /**
   * 右转
   */
  TURN_RIGHT,
  
  /**
   * 直行
   */
  MAIN,
  
  /**
   * 停车
   */
  STOP
};

#endif