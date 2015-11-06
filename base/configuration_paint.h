/*
 * configuration.h
 *
 *  Created on: 2015��10��9��
 *      Author: Dark
 */
#include <avr/pgmspace.h>

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

//
//������
#define MACHINE_NAME "PAINTING_ONE"
#define FIRMWARE_URL "none"
//IICͨѶ��������
//���ڲ�������
#define SERIAL_RATE 115200

//��������Ӧ�ĽǱ�
//#define NUM_AXIS  4

#define SLIDE_MOTOR 0
#define LIFT_MOTOR 1
#define WALK_MOTOR 2
#define TURN_MOTOR 3 //�����ת������������

//ʹ��PAINT��е����7�ᣬ����һ��
//#define PAINT
/******************************
 *��е��������
 */

//PI Բ����
#define MATH_PI 3.1415926

//���������������
#define STEP_PULSE_WIDTH 1

//�������ߵ���������ֵĲ���
#define WALK_DRIVER_TEETH 18.0
#define WALK_DRIVEN_TEETH 64.0
#define WALK_DRIVE_TATIO (WALK_DRIVEN_TEETH/WALK_DRIVER_TEETH) // ������
#define WALK_MOTOR_SUBDIVIDE 16.0//8.0//16.0
#define WALK_BELT_MOFULES 2.032 //mm
#define WALK_MOTOR_STEPS_PER_CYCLE 400.0 //������� ����һȦ�Ĳ���

#define WALK_WHEEL_DIAMETER  50.0 //mm ��ֱ��
#define WALK_WHEEL_PERIMETER (WALK_WHEEL_DIAMETER*MATH_PI) //�ܳ�

#define WALK_DRIVER_PULSES_PER_CYCLR  (WALK_MOTOR_SUBDIVIDE*WALK_MOTOR_STEPS_PER_CYCLE) //һȦ��������
#define WALK_PULSES_PER_UNIT_BELT (WALK_DRIVER_PULSES_PER_CYCLR/(WALK_DRIVER_TEETH*WALK_BELT_MOFULES))
#define WALK_PULSES_PER_UNIT_WHEEL (WALK_PULSES_PER_UNIT_BELT/(WALK_WHEEL_PERIMETER/(WALK_DRIVEN_TEETH*WALK_BELT_MOFULES)))

//����ת��������
#define TURN_DRIVER_TEETH 18.0//20.0//18.0
#define TURN_DRIVEN_TEETH 96.0
#define TURN_DRIVE_TATIO (TURN_DRIVEN_TEETH/TURN_DRIVER_TEETH) // ������
#define TURN_MOTOR_SUBDIVIDE 16.0//32.0//2.0 //32.0
#define TURN_BELT_MOFULES 2.032 //mm
#define TURN_MOTOR_STEPS_PER_CYCLE 400.0//200.0 //������� ����һȦ�Ĳ���

#define TURN_WHEEL_PULSES_PER_CYCLR  (TURN_MOTOR_SUBDIVIDE*TURN_MOTOR_STEPS_PER_CYCLE) //һȦ��������
#define TURN_BELT_PULSE_PER_UNIT (TURN_WHEEL_PULSES_PER_CYCLR/(TURN_DRIVER_TEETH*TURN_BELT_MOFULES))
#define TURN_PULSES_PER_ANGLE_BELT (TURN_WHEEL_PULSES_PER_CYCLR*TURN_DRIVE_TATIO/360)

//���廬�ݵ������
#define SLIDE_DRIVER_TEETH 20.0
#define SLIDE_MOTOR_SUBDIVDE 16.0
#define SLIDE_BELT_MOFULES 2.032 //mm
#define SLIDE_MOTOR_STEPS_PER_CYCLE 200.0//������� ����һȦ�Ĳ���
#define SLIDE_WHEEL_PULSES_PER_CYCLR (SLIDE_MOTOR_SUBDIVDE*SLIDE_MOTOR_STEPS_PER_CYCLE)
#define SLIDE_PULSES_PER_UNIT ((SLIDE_WHEEL_PULSES_PER_CYCLR)/(SLIDE_DRIVER_TEETH*SLIDE_BELT_MOFULES))

//���廬���������
#define LIFT_DRIVER_TEETH 20.0
#define LIFT_MOTOR_SUBDIVDE 16.0
#define LIFT_BELT_MOFULES 2.032 //mm
#define LIFT_MOTOR_STEPS_PER_CYCLE 200.0//������� ����һȦ�Ĳ���
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

//ʹ�����μ���
//�������ã�
//�Ƅ� 1 mm �� step ��
//#ifdef PAINT
//#define DEFAULT_AXIS_STEPS_PER_UNIT {SLIDE_PULSES_PER_UNIT,LIFT_PULSES_PER_UNIT, \
//	WALK_PULSES_PER_UNIT_WHEEL,TURN_PULSES_PER_ANGLE_BELT}
//#endif //define /**

//#define DEFAULT_MAX_FEEDRATE {500,500,500,500}//�����S����� nominal speed mm/sec
//#define DEFAULT_MAX_ACCELERATION {5000,5000,5000,5000}//�����S�������ٶ�mm/sec^2
//#define DEFAULT_ACCELERATION {300,300,300,300}// �A�O�ļ��ٶ�ֵ ����ͬλ�õ�λ�õĵ��Ҫ�в�ͬ�ļ��ٶ�mm/sec^2

//#define HOMING_FEEDRATE {50*60, 50*60, 50*60, 0}  // set the homing speeds (mm/min)

//#define AXIS_RELATIVE_MODES {false, false, false, false}

//#define DEFAULT_ACCELERATION          500    // X, Y, Z and E max acceleration in mm/s^2 for printing moves
//#define DEFAULT_ACCELERATION          3000    // X, Y, Z and E max acceleration in mm/s^2 for printing moves
//#define DEFAULT_RETRACT_ACCELERATION  3000   // X, Y, Z and E max acceleration in mm/s^2 for retracts
//#define DEFAULT_MINIMUMFEEDRATE       0.0     // minimum feedrate
//#define DEFAULT_MINTRAVELFEEDRATE     0.0
//���ٶ����ã�
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

//��е�ߴ����
#define SLIDE_MAX_POSITION 6000 //mm //��ȷ��

//Ҏ���ɗl·�����B���ٶȕr���������ٶ���Ӌ��

//default stepper release if idle //�����������ʱ����
//#define DEFAULT_STEPPER_DEACTIVE_TIME 60

//����������������
#define US_DEFAULT_MAX_DISTANCE 4500 //mm
#define US_DEFAULT_MIN_DISTANCE 40 //mm

/***************************************
 *�����ô��룬ע�ⲻҪ�� ��pins.h����configuration.h��
 *�е����ó�ͻ
 */
//�����ã�����ʹ������㷨
#define INTERRUPTTIME 1
//�㷨���� ��ǰ����
#define SPEED_UP_STEPS_SPEED_DOWN_STEPS 8
//������
//�����õĶ˿�,���������
#define TEST_MOTOR_STEP_PIN 51
#define TEST_MOTOR_ENABLE_PIN 52
#define TEST_MOTOR_DIR_PIN 53
//***************************************

//����������
////������ȫ�ֱ���
//#define DEFAULT_MIN_SPEED_FACTOR 30 //min speed = DEFAULT_MIN_SPEED_FACTOR X **MOTOR_SUBDIVIDE

#endif /* CONFIGURATION_H_ */
