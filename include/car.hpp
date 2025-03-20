#ifndef CAR_HPP
#define CAR_HPP

class CarController
{
public:
  CarController(int lf_pin, int rf_pin, int ls_pin, int rs_pin)
      : left_forward_pin(lf_pin), right_forward_pin(rf_pin), left_speed_pin(ls_pin), right_speed_pin(rs_pin) {}

  /**
   * 初始化端口
   */
  void setup();

  /**
   * 启动
   */
  void start();

  /**
   * 左转
   */
  void turn_left();

  /**
   * 右转
   */
  void turn_right();

  /**
   * 停车
   */
  void stop();

private:
  /**
   * 左轮电机转向控制端口
   */
  int left_forward_pin;

  /**
   * 右轮电机转向控制端口
   */
  int right_forward_pin;

  /**
   * 左轮转速控制端口
   */
  int left_speed_pin;

  /**
   * 右轮转速控制端口
   */
  int right_speed_pin;
};
#endif