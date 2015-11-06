/*
 * configuration.h
 *
 *  Created on: 2015年10月9日
 *      Author: Dark
 */
#include <avr/pgmspace.h>

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

//
//主机名
#define MACHINE_NAME "PAINTING_ONE"
#define FIRMWARE_URL "none"
//IIC通讯参数设置
//串口参数设置
#define SERIAL_RATE 115200

//定义各轴对应的角标
//#define NUM_AXIS  4

#define SLIDE_MOTOR 0
#define LIFT_MOTOR 1
#define WALK_MOTOR 2
#define TURN_MOTOR 3 //程序对转向做单独处理

//使用PAINT机械参数7轴，冗余一轴
//#define PAINT
/******************************
 *机械参数计算
 */

//PI 圆周率
#define MATH_PI 3.1415926

//步进电机的脉冲宽度
#define STEP_PULSE_WIDTH 1

//定义行走电机及行走轮的参数
#define WALK_DRIVER_TEETH 18.0
#define WALK_DRIVEN_TEETH 64.0
#define WALK_DRIVE_TATIO (WALK_DRIVEN_TEETH/WALK_DRIVER_TEETH) // 传动比
#define WALK_MOTOR_SUBDIVIDE 16.0//8.0//16.0
#define WALK_BELT_MOFULES 2.032 //mm
#define WALK_MOTOR_STEPS_PER_CYCLE 400.0 //步进电机 步进一圈的步数

#define WALK_WHEEL_DIAMETER  50.0 //mm 轮直径
#define WALK_WHEEL_PERIMETER (WALK_WHEEL_DIAMETER*MATH_PI) //周长

#define WALK_DRIVER_PULSES_PER_CYCLR  (WALK_MOTOR_SUBDIVIDE*WALK_MOTOR_STEPS_PER_CYCLE) //一圈的脉冲数
#define WALK_PULSES_PER_UNIT_BELT (WALK_DRIVER_PULSES_PER_CYCLR/(WALK_DRIVER_TEETH*WALK_BELT_MOFULES))
#define WALK_PULSES_PER_UNIT_WHEEL (WALK_PULSES_PER_UNIT_BELT/(WALK_WHEEL_PERIMETER/(WALK_DRIVEN_TEETH*WALK_BELT_MOFULES)))

//定义转向电机参数
#define TURN_DRIVER_TEETH 18.0//20.0//18.0
#define TURN_DRIVEN_TEETH 96.0
#define TURN_DRIVE_TATIO (TURN_DRIVEN_TEETH/TURN_DRIVER_TEETH) // 传动比
#define TURN_MOTOR_SUBDIVIDE 16.0//32.0//2.0 //32.0
#define TURN_BELT_MOFULES 2.032 //mm
#define TURN_MOTOR_STEPS_PER_CYCLE 400.0//200.0 //步进电机 步进一圈的步数

#define TURN_WHEEL_PULSES_PER_CYCLR  (TURN_MOTOR_SUBDIVIDE*TURN_MOTOR_STEPS_PER_CYCLE) //一圈的脉冲数
#define TURN_BELT_PULSE_PER_UNIT (TURN_WHEEL_PULSES_PER_CYCLR/(TURN_DRIVER_TEETH*TURN_BELT_MOFULES))
#define TURN_PULSES_PER_ANGLE_BELT (TURN_WHEEL_PULSES_PER_CYCLR*TURN_DRIVE_TATIO/360)

//定义滑梯电机参数
#define SLIDE_DRIVER_TEETH 20.0
#define SLIDE_MOTOR_SUBDIVDE 16.0
#define SLIDE_BELT_MOFULES 2.032 //mm
#define SLIDE_MOTOR_STEPS_PER_CYCLE 200.0//步进电机 步进一圈的步数
#define SLIDE_WHEEL_PULSES_PER_CYCLR (SLIDE_MOTOR_SUBDIVDE*SLIDE_MOTOR_STEPS_PER_CYCLE)
#define SLIDE_PULSES_PER_UNIT ((SLIDE_WHEEL_PULSES_PER_CYCLR)/(SLIDE_DRIVER_TEETH*SLIDE_BELT_MOFULES))

//定义滑车电机参数
#define LIFT_DRIVER_TEETH 20.0
#define LIFT_MOTOR_SUBDIVDE 16.0
#define LIFT_BELT_MOFULES 2.032 //mm
#define LIFT_MOTOR_STEPS_PER_CYCLE 200.0//步进电机 步进一圈的步数
#define LIFT_WHEEL_PULSES_PER_CYCLR (SLIDE_MOTOR_SUBDIVDE*SLIDE_MOTOR_STEPS_PER_CYCLE)
#define LIFT_PULSES_PER_UNIT ((SLIDE_WHEEL_PULSES_PER_CYCLR)/(SLIDE_DRIVER_TEETH*SLIDE_BELT_MOFULES))

/*
 * Paint use configuration only
 */
#define PAINT_ADD_HOME {2.4,0,0} //mm
#define PAINT_RETURN_DISTANCE 10 //mm
#define PAINT_HOME_RATE 10 // mm/s
#define PAINT_DIVE_DISTANCE -1

#define INVERT_WALK_DIR true //all walk motor

#define INVERT_LEFT_WALK_DIR false
#define INVERT_RIGHT_WALK_DIR false
#define INVERT_TURN_WALK_DIR false

#define TURN_ENDSTOP_INVERTING false

//使用梯形加速
//参数设置：
//移動 1 mm 的 step 數
//#ifdef PAINT
//#define DEFAULT_AXIS_STEPS_PER_UNIT {SLIDE_PULSES_PER_UNIT,LIFT_PULSES_PER_UNIT, \
//	WALK_PULSES_PER_UNIT_WHEEL,TURN_PULSES_PER_ANGLE_BELT}
//#endif //define /**

//#define DEFAULT_MAX_FEEDRATE {500,500,500,500}//可容許的最大 nominal speed mm/sec
//#define DEFAULT_MAX_ACCELERATION {5000,5000,5000,5000}//可容許的最大加速度mm/sec^2
//#define DEFAULT_ACCELERATION {300,300,300,300}// 預設的加速度值 ，不同位置的位置的电机要有不同的加速度mm/sec^2

//#define HOMING_FEEDRATE {50*60, 50*60, 50*60, 0}  // set the homing speeds (mm/min)

//#define AXIS_RELATIVE_MODES {false, false, false, false}

//#define DEFAULT_ACCELERATION          500    // X, Y, Z and E max acceleration in mm/s^2 for printing moves
//#define DEFAULT_ACCELERATION          3000    // X, Y, Z and E max acceleration in mm/s^2 for printing moves
//#define DEFAULT_RETRACT_ACCELERATION  3000   // X, Y, Z and E max acceleration in mm/s^2 for retracts
//#define DEFAULT_MINIMUMFEEDRATE       0.0     // minimum feedrate
//#define DEFAULT_MINTRAVELFEEDRATE     0.0
//初速度设置：
//#define DEFAULT_X_JERK 5.0 // mm/sec
//#define DEFAULT_Y_JERK 5.0 // mm/sec
//#define DEFAULT_Zlift_JERK 5.0// mm/sec
//#define DEFAULT_Zroll_JERK 5.0 // mm/sec

// The speed change that does not require acceleration (i.e. the software might assume it can be done instantaneously)
//#define DEFAULT_XYJERK                20.0    // (mm/sec)
//#define DEFAULT_ZJERK                 20.0    // (mm/sec)
//#define DEFAULT_EJERK                 20.0   // (mm/sec)

// minimum time in microseconds that a movement needs to take if the buffer is emptied.
//#define DEFAULT_MINSEGMENTTIME        20000

//机械尺寸参数
#define SLIDE_MAX_POSITION 6000 //mm //待确认

//規畫兩條路徑的連接速度時，會對初速度做計算

//default stepper release if idle //保护电机，暂时不用
//#define DEFAULT_STEPPER_DEACTIVE_TIME 60

//超声波传感器参数
#define US_DEFAULT_MAX_DISTANCE 4500 //mm
#define US_DEFAULT_MIN_DISTANCE 40 //mm

/***************************************
 *测试用代码，注意不要与 “pins.h”或“configuration.h”
 *中的设置冲突
 */
//已弃用，不再使用这个算法
#define INTERRUPTTIME 1
//算法修正 提前减速
#define SPEED_UP_STEPS_SPEED_DOWN_STEPS 8
//已启用
//测试用的端口,电机测试用
#define TEST_MOTOR_STEP_PIN 51
#define TEST_MOTOR_ENABLE_PIN 52
#define TEST_MOTOR_DIR_PIN 53
//***************************************

//已启用设置
////定义电机全局变量
//#define DEFAULT_MIN_SPEED_FACTOR 30 //min speed = DEFAULT_MIN_SPEED_FACTOR X **MOTOR_SUBDIVIDE

#endif /* CONFIGURATION_H_ */
