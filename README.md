项目名称：可持续改善的智能无线控制小车
目前所处阶段：-----step1-----


step1：基于蓝牙连接的无线控制小车

项目主要硬件模块：
  控制端：STM32F103ZET6型号MCU开发板
  受控端：STM32F103C8T6型号MCU开发板
  蓝牙模块：HC-05（控制端） & HC-06（受控端）
  六轴陀螺仪：MPU6050
  超声波测距模块：HC-SR04
  OLED屏幕：0.96寸
  温度传感器：DS18B20
  
  主要功能：
    1、使用控制端按键实现对小车前后左右的无线控制
    2、使用陀螺仪实现对小车前后左右的无线控制
    3、OLED实时显示小车当前运动状态、接收并显示控制端温度信息、超声波测距结果
    4、倒车时小于安全距离时，停止后退动作、控制端蜂鸣器报警
    
step2：实时路况显示

   增加硬件：控制端图像显示LCD屏幕、  受控端图像采集摄像头模块：OV2640
   
   主要功能：
    1、小车采集前方图像无线发送到控制端并在屏幕显示
    
step3：手机端微信小程序通过蓝牙控制小车动作、显示图像

step4:数据传输使用NB-IoT

