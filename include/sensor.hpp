#ifndef SENSOR_HPP

#define SENSOR_HPP

/**
 * 本注释中所有的“左”、“右”方向均是从车后面往前看
 */
class SensorController {
public:

  SensorController(int rgt_e, int lft_e, int rgt, int lft, int md) 
    : right_edge(rgt_e), left_edge(lft_e), right(rgt), left(lft), middle(md) {}

  void setup();

  /**
   * 穿过了线
   */
  bool crossed();

  /**
   * 中心传感器左侧的传感器是否在线上
   */
  bool left_state();

  /**
   * 中心传感器右侧的传感器是否在线上
   */
  bool right_state();

  /**
   * 最左侧的传感器是否线上
   */
  bool left_edge_state();

  /**
   * 最右侧的传感器是否在线上
   */
  bool right_edge_state();

  /**
   * 最中心的传感器是否在线上
   */
  bool middle_state();
private:
  int right_edge;
  int left_edge;

  int right;
  int left;

  int middle;
};

#endif