// Do not remove the include below
#include "Marlin.h"
#include "base.h"
#include "pins.h"
#include "stepper.h"
#include "configuration_paint.h"
#include "watchdog.h"
#include "ConfigurationStore.h"
#include "fastio.h"
#include "planner.h"

//���붨ʱ��
#include "TimerOne.h"

#include "FlexiTimer2.h"

//marlin����
//in "marlin_main.cpp"
float homing_feedrate[] = HOMING_FEEDRATE;
bool axis_relative_modes[] = AXIS_RELATIVE_MODES;

#ifndef MARLIN
#define MARLIN
		int fanSpeed = 0;
		int feedmultiply=100; //100->1 200->2
		int saved_feedmultiply;
		int extrudemultiply = 100;//100->1 200->2
		uint8_t active_extruder = 0;
#endif

//functions
//in "marlin_main.cpp"
//��ֹ�ظ�����

		float volumetric_multiplier[EXTRUDERS] = {1.0
#if EXTRUDERS > 1
		, 1.0
#if EXTRUDERS > 2
		, 1.0
#endif
#endif
	};

	float current_position[NUM_AXIS] = {0.0, 0.0, 0.0, 0.0};
	float add_homeing[3]= {0,0,0};

#ifdef SCARA
		int scara_segments_per_second = 200;
#endif

//#ifdef PAINT
		int paint_segments_per_second = 200;
//#endif

//		float min_pos[3] = {X_MIN_POS, Y_MIN_POS, Z_MIN_POS};
//		float max_pos[3] = {X_MAX_POS, Y_MAX_POS, Z_MAX_POS};
		bool axis_known_position[3] = {true, true, true};

//===========================================================================
//=============================Private Variables=============================
//===========================================================================
		const char axis_codes[NUM_AXIS] = {'X', 'Y', 'Z', 'E'};
		static float destination[NUM_AXIS] = {0.0, 0.0, 0.0, 0.0};

#ifndef DELTA
		static float delta[3] = {0.0, 0.0, 0.0};
#endif

		static float offset[3] = {0.0, 0.0, 0.0}; //����λ��У׼ //δʹ�øù���
		static bool home_all_axis = true;
		static float feedrate = 1500.0,
next_feedrate, saved_feedrate;
static long gcode_N, gcode_LastN, Stopped_gcode_LastN = 0;

static bool relative_mode = false; //Determines Absolute or Relative Coordinates

static char cmdbuffer[BUFSIZE][MAX_CMD_SIZE];
static bool fromsd[BUFSIZE];
static int bufindr = 0;
static int bufindw = 0;
static int buflen = 0; //����������ĸ���

static char serial_char;
static int serial_count = 0;
static boolean comment_mode = false;
static char *strchr_pointer; // just a pointer to find chars in the command string like X, Y, Z, E, etc
//const int sensitive_pins[] = SENSITIVE_PINS; // Sensitive pin list for M42

//Inactivity shutdown variables
static unsigned long previous_millis_cmd = 0;
static unsigned long max_inactive_time = 0;
static unsigned long stepper_inactive_time = DEFAULT_STEPPER_DEACTIVE_TIME
		* 1000l;

unsigned long starttime = 0;
unsigned long stoptime = 0;
//�����ǲ�����ͣ��״̬
bool Stopped = false;

void initialPins() {
	//��ʼ������
	//*****************************************
	//����������ų�ʼ��
	pinMode(LFFT_WALK_MOTOR_STEP_PIN, OUTPUT);
	pinMode(LFFT_WALK_MOTOR_ENABLE_PIN, OUTPUT);
	pinMode(LFFT_WALK_MOTOR_DIR_PIN, OUTPUT);

	pinMode(RIGHT_WALK_MOTOR_STEP_PIN, OUTPUT);
	pinMode(RIGHT_WALK_MOTOR_ENABLE_PIN, OUTPUT);
	pinMode(RIGHT_WALK_MOTOR_DIR_PIN, OUTPUT);

	pinMode(TURN_MOTOR_STEP_PIN, OUTPUT);
	pinMode(TURN_MOTOR_ENABLE_PIN, OUTPUT);
	pinMode(TURN_MOTOR_DIR_PIN, OUTPUT);

	pinMode(SLIDE_STEP_PIN, OUTPUT);
	pinMode(SLIDE_DIR_PIN, OUTPUT);
	pinMode(SLIDE_ENABLE_PIN, OUTPUT);

	pinMode(LIFT_STEP_PIN, OUTPUT);
	pinMode(LIFT_DIR_PIN, OUTPUT);
	pinMode(LIFT_ENABLE_PIN, OUTPUT);
	//***************************************

	//***************************************
	//�������ų�ʼ��
	//���ÿ��ض˿ڵ�ģʽ
	pinMode(FRONT_RIGHT_STOP, INPUT);
	pinMode(FRONT_LEFT_STOP, INPUT);
	pinMode(LEFT_STOP, INPUT);
	pinMode(RIGHT_STOP, INPUT);
	pinMode(BACK_STOP, INPUT);

	pinMode(ANGLE_CALIBRATION_STOP, INPUT);

	pinMode(SLIDE_TOP_ENDSTOP, INPUT);
	pinMode(SLIDE_TRIGER_ENDSTOP, INPUT);
	pinMode(SLIDE_BOTTOM_ENDSTOP, INPUT);

	pinMode(LIFT_TOP_ENDSTOP, INPUT);
	pinMode(LIFT_BOTTOM_ENDSTOP, INPUT);

	//����������
	digitalWrite(FRONT_RIGHT_STOP, HIGH);
	digitalWrite(FRONT_LEFT_STOP, HIGH);
	digitalWrite(LEFT_STOP, HIGH);
	digitalWrite(RIGHT_STOP, HIGH);
	digitalWrite(BACK_STOP, HIGH);

	digitalWrite(ANGLE_CALIBRATION_STOP, HIGH);

	digitalWrite(SLIDE_TOP_ENDSTOP, HIGH);
	digitalWrite(SLIDE_BOTTOM_ENDSTOP, HIGH);

	digitalWrite(LIFT_TOP_ENDSTOP, HIGH);
	digitalWrite(LIFT_BOTTOM_ENDSTOP, HIGH);
	//*****************************************

	//*****************************************
	//��ʼ������������
	//��������������
	pinMode(FRONT_LEFT_ULTRSONIC_TRIGGER_PIN, OUTPUT);
	pinMode(FRONT_RIGHT_ULTRSONIC_TRIGGER_PIN, OUTPUT);
	pinMode(LEFT_ULTRSONIC_TRIGGER_PIN, OUTPUT);
	pinMode(RIGHT_ULTRSONIC_TRIGGER_PIN, OUTPUT);
	pinMode(BACK_ULTRSONIC_TRIGGER_PIN, OUTPUT);
	//��������������
	pinMode(FRONT_LEFT_ULTRSONIC_ECHO_PIN, INPUT);
	pinMode(FRONT_RIGHT_ULTRSONIC_ECHO_PIN, INPUT);
	pinMode(LEFT_ULTRSONIC_ECHO_PIN, INPUT);
	pinMode(RIGHT_ULTRSONIC_ECHO_PIN, INPUT);
	pinMode(BACK_ULTRSONIC_ECHO_PIN, INPUT);
	//******************************************

	//******************************************
	//���������
	pinMode(PAINT_PUMP_PWM, OUTPUT);	//pwm����
}

struct motorstate {
	byte name;

	//position
	long position;

	//steps
	long steps;
	long stepshasgone;
	long speedupsteps;
	long speeddownsteps;
	float stepsPerUnit;

	//angle
	float angle;
	float stepsperangel; //degree

	//speed state
	float goalspeed;
	float currentspeed;
	float acc;
	float maxspeed;
	float startSpeed;

	//is motor  turning
	bool isRuning;
	//is motor speeding up
	bool isSpeedUp;
	//is motor speeding down
	bool isSpeedDown;
	//motor turning direction
	bool dir; //true for cw ,false for ccw
};

//�������ߺ�ת����
struct motorstate testmotor, turnmotor, walkmotorleft, walkmotorright,
		slidemotor, liftmotor;

//��ʼ�����ߵ��
void initialwalkmotor(struct motorstate *ms) {
	ms->name = SLIDE_MOTOR;
	//positon
	ms->position = 0;
	//steps
	ms->steps = 0;
	ms->stepshasgone = 0;
	ms->speedupsteps = 0;
	ms->speeddownsteps = 0;
	ms->stepsPerUnit = float(WALK_PULSES_PER_UNIT_WHEEL);

	//�Ƕȶ����ߵ�����岻��
	ms->angle = 0;
	ms->stepsperangel = 0; //degree

	//speed state
	ms->goalspeed = 0;
	ms->currentspeed = 0;
	ms->acc = 9000000;
	ms->maxspeed = 160000;
	ms->startSpeed = 200;

	//is motor  turning
	ms->isRuning = false;
	//is motor speeding up
	ms->isSpeedUp = false;
	//is motor speeding down
	ms->isSpeedDown = false;
	//motor turning directionn
	ms->dir = false; //true for cw ,false for ccw
}

//��ʼ��slidemotor
void initialslidemotor(struct motorstate *ms) {
	ms->name = WALK_MOTOR;
	//positon
	ms->position = 0;
	//steps
	ms->steps = 0;
	ms->stepshasgone = 0;
	ms->speedupsteps = 0;
	ms->speeddownsteps = 0;
	ms->stepsPerUnit = float(SLIDE_PULSES_PER_UNIT);

	//�Ƕȶ����ߵ�����岻��
	ms->angle = 0;
	ms->stepsperangel = 0; //degree

	//speed state
	ms->goalspeed = 0;
	ms->currentspeed = 0;
	ms->acc = 9000000;
	ms->maxspeed = 160000;
	ms->startSpeed = 200;

	//is motor  turning
	ms->isRuning = false;
	//is motor speeding up
	ms->isSpeedUp = false;
	//is motor speeding down
	ms->isSpeedDown = false;
	//motor turning directionn
	ms->dir = false; //true for cw ,false for ccw
}

//��ʼ��ת����
void initialturnmotor(struct motorstate *ms) {
	ms->name = TURN_MOTOR;
	//positon
	ms->position = 0;
	//steps
	ms->steps = 0;
	ms->stepshasgone = 0;
	ms->speedupsteps = 0;
	ms->speeddownsteps = 0;

	//ת���������ò���
	ms->stepsPerUnit = float(TURN_BELT_PULSE_PER_UNIT);

	ms->angle = 0;
	ms->stepsperangel = float(TURN_PULSES_PER_ANGLE_BELT); //degree

	//speed state
	ms->goalspeed = 0;
	ms->currentspeed = 0;
	ms->acc = 9000; // 9000000; //���ڽǶ� ����ļ��ٶ���ָ�Ǽ��ٶ�
	ms->maxspeed = 160000;
	ms->startSpeed = 1000;

	//is motor  turning
	ms->isRuning = false;
	//is motor speeding up
	ms->isSpeedUp = false;
	//is motor speeding down
	ms->isSpeedDown = false;
	//motor turning directionn
	ms->dir = true; //true for cw ,false for ccw
}

//���ֹͣ��ʱ�����Ҫ��ֵ��Ϊ
void resetmotor(struct motorstate *ms) {
	//steps
	ms->steps = 0;
	ms->stepshasgone = 0;
	ms->speedupsteps = 0;
	ms->speeddownsteps = 0;

	//speed state
	ms->goalspeed = 0;
	ms->currentspeed = 0;

	//is motor  turning
	ms->isRuning = false;
	//is motor speeding up
	ms->isSpeedUp = false;
	//is motor speeding down
	ms->isSpeedDown = false;
}

//ʹ�ܺ�ȡ���������
//ʹ�ܺ�ȡ�����ߵ��
void disablwalkmotor() {
	digitalWrite(LFFT_WALK_MOTOR_ENABLE_PIN, HIGH);
}

void enablwalkmotor() {
	digitalWrite(LFFT_WALK_MOTOR_ENABLE_PIN, LOW);
}

//ʹ�ܺ�ȡ��ת����
void disableturnmotor() {
	digitalWrite(TURN_MOTOR_ENABLE_PIN, HIGH);
}

void enableturnmotor() {
	digitalWrite(TURN_MOTOR_ENABLE_PIN, LOW);
}

//ʹ�ܺ�ȡ�����ݵ��
void disableslidemotor() {
	digitalWrite(SLIDE_ENABLE_PIN, HIGH);
}

void enableslidemotor() {
	digitalWrite(SLIDE_ENABLE_PIN, LOW);
}

//ʹ�ܺ�ȡ���������
void disableliftmotor() {
	digitalWrite(SLIDE_ENABLE_PIN, HIGH);
}

void enableliftmotor() {
	digitalWrite(SLIDE_ENABLE_PIN, LOW);
}

//speed step/sec
void leftwalkadistancestep(bool dir, float speed, long steps) {
	enablwalkmotor();
	digitalWrite(LFFT_WALK_MOTOR_DIR_PIN, dir);
	float delaytime = 1000000.0 / speed;
	for (; steps > 0; steps--) {
		digitalWrite(LFFT_WALK_MOTOR_STEP_PIN, HIGH);
		delayMicroseconds(delaytime / 2);
		digitalWrite(LFFT_WALK_MOTOR_STEP_PIN, LOW);
		delayMicroseconds(delaytime / 2);
	}
}

//speed mm/s distance mm
void leftwalkadistancemm(bool dir, float speed, float distance) {
	enablwalkmotor();
	long steps = distance * walkmotorleft.stepsPerUnit;
	digitalWrite(LFFT_WALK_MOTOR_DIR_PIN, dir);
	float delaytime = 1000000.0 / (speed * walkmotorleft.stepsPerUnit);
	for (; steps > 0; steps--) {
		digitalWrite(LFFT_WALK_MOTOR_STEP_PIN, HIGH);
		delayMicroseconds(delaytime / 2);
		digitalWrite(LFFT_WALK_MOTOR_STEP_PIN, LOW);
		delayMicroseconds(delaytime / 2);
	}
}

//speed mm/s distance mm
void walkadistancemm(bool dir, float speed, float distance) {
	enablwalkmotor();
	long steps = distance * walkmotorleft.stepsPerUnit;
	digitalWrite(LFFT_WALK_MOTOR_DIR_PIN, dir);
	digitalWrite(RIGHT_WALK_MOTOR_DIR_PIN, dir);
	float delaytime = 1000000.0 / (speed * walkmotorleft.stepsPerUnit);
	for (; steps > 0; steps--) {
		digitalWrite(LFFT_WALK_MOTOR_STEP_PIN, HIGH);
		digitalWrite(RIGHT_WALK_MOTOR_STEP_PIN, HIGH);
		delayMicroseconds(delaytime / 2);
		digitalWrite(LFFT_WALK_MOTOR_STEP_PIN, LOW);
		digitalWrite(RIGHT_WALK_MOTOR_STEP_PIN, LOW);
		delayMicroseconds(delaytime / 2);
	}
}

//���˼��ٶȵ�����  //speed mm/s distance mm acc mm^2/sec
void walkadistancemmacc(bool dir, float speed, float distance, float acc) {
	enablwalkmotor();
	long steps = distance * walkmotorleft.stepsPerUnit;
	digitalWrite(LFFT_WALK_MOTOR_DIR_PIN, dir);
	digitalWrite(RIGHT_WALK_MOTOR_DIR_PIN, dir);
	float stepsspeed = speed * walkmotorleft.stepsPerUnit;
	float delaytime = 1000000.0 / (stepsspeed);
	float stepacc = acc
			* (walkmotorleft.stepsPerUnit * walkmotorleft.stepsPerUnit); //steps^2/sec

	float downaccsteps = (stepsspeed * stepsspeed
			- walkmotorleft.startSpeed * walkmotorleft.startSpeed)
			/ (2 * stepacc); //������Ҫ�Ĳ���
	float upaccsteps = (stepsspeed * stepsspeed
			- walkmotorleft.startSpeed * walkmotorleft.startSpeed)
			/ (2 * stepacc); //������Ҫ�Ĳ���

	float startdelaytime = 1000000.0 / walkmotorleft.startSpeed;

	//steps per us
	int upstepsperus = upaccsteps / (startdelaytime - delaytime);
	int downstepsperus = downaccsteps / (startdelaytime - delaytime);

	float timeerror = 1;

	if (upstepsperus == 0) {
		upstepsperus = 1;
		timeerror = (startdelaytime - delaytime) / upaccsteps;
		MYSERIAL.print("timeerror 1= ");
		MYSERIAL.println(timeerror);
	}

	if (downstepsperus == 0) {
		downstepsperus = 1;
		timeerror = (startdelaytime - delaytime) / downaccsteps;
		MYSERIAL.print("timeerror 2= ");
		MYSERIAL.println(timeerror);
	}

	if (true) {
		MYSERIAL.print("steps = ");
		MYSERIAL.println(steps);
		MYSERIAL.print("stepsspeed = ");
		MYSERIAL.println(stepsspeed);
		MYSERIAL.print("delaytime = ");
		MYSERIAL.println(delaytime);
		MYSERIAL.print("stepacc = ");
		MYSERIAL.println(stepacc);
		MYSERIAL.print("upaccsteps = ");
		MYSERIAL.println(upaccsteps);
		MYSERIAL.print("downaccsteps = ");
		MYSERIAL.println(downaccsteps);
		MYSERIAL.print("startdelaytime = ");
		MYSERIAL.println(startdelaytime);
		MYSERIAL.print("upstepsperus = ");
		MYSERIAL.println(upstepsperus);
		MYSERIAL.print("downstepsperus = ");
		MYSERIAL.println(downstepsperus);
		MYSERIAL.print("timeerror = ");
		MYSERIAL.println(timeerror);
	}

	//����-����-���ٹ���
	if (stepsspeed <= walkmotorleft.startSpeed) {
		//�����ٶ�����С�ٶ�
		MYSERIAL.println("startspeed run!");

		float time = startdelaytime;
		for (int counts = 0; counts < steps; counts++) {
			digitalWrite(LFFT_WALK_MOTOR_STEP_PIN, HIGH);
			digitalWrite(RIGHT_WALK_MOTOR_STEP_PIN, HIGH);
			delayMicroseconds(STEP_PULSE_WIDTH);
			digitalWrite(LFFT_WALK_MOTOR_STEP_PIN, LOW);
			digitalWrite(RIGHT_WALK_MOTOR_STEP_PIN, LOW);
			delayMicroseconds(time);
		}
	} else if ((upaccsteps + downaccsteps) < steps) {

		MYSERIAL.println("speedup-stay-speeddown run!");

		float time = startdelaytime;
		for (long counts = 0; counts < steps; counts++) {
			if (counts < upaccsteps) {
				if (counts % upstepsperus == 0 & time >= delaytime) { //ÿ��upstepsperus +1us
					time -= timeerror;
				}
			} else if ((steps - counts) < downaccsteps) {

				if (counts % downstepsperus == 0 & time <= startdelaytime) { //ÿ��upstepsperus +1us
					time += timeerror;
				}
			} else if (counts == upaccsteps) {
				MYSERIAL.println("speedup-end!");
				time = delaytime;
			} else if ((steps - counts) == downaccsteps) {
				MYSERIAL.println("speeddown-start!");
			}

			digitalWrite(LFFT_WALK_MOTOR_STEP_PIN, HIGH);
			digitalWrite(RIGHT_WALK_MOTOR_STEP_PIN, HIGH);
			delayMicroseconds(STEP_PULSE_WIDTH);
			digitalWrite(LFFT_WALK_MOTOR_STEP_PIN, LOW);
			digitalWrite(RIGHT_WALK_MOTOR_STEP_PIN, LOW);
			delayMicroseconds(time);
		}
	} else
	//����-���ٹ���
	{
		MYSERIAL.println("speedup-speeddown run!");
		long flagstep = steps / 2;
		MYSERIAL.print("flagstep = ");
		MYSERIAL.println(flagstep);
		float time = startdelaytime;
		for (int counts = 0; counts < steps; counts++) {
			if (counts < flagstep) {
				if (counts % upstepsperus == 0 & time > delaytime) { //ÿ��upstepsperus +1us
					time -= timeerror;
				}
			} else if (counts == flagstep) {
				MYSERIAL.println("speeddown-start!");

			} else {

				if (counts % downstepsperus == 0 & time < startdelaytime) { //ÿ��upstepsperus +1us
					time += timeerror;
				}
			}

			digitalWrite(LFFT_WALK_MOTOR_STEP_PIN, HIGH);
			digitalWrite(RIGHT_WALK_MOTOR_STEP_PIN, HIGH);
			delayMicroseconds(STEP_PULSE_WIDTH);
			digitalWrite(LFFT_WALK_MOTOR_STEP_PIN, LOW);
			digitalWrite(RIGHT_WALK_MOTOR_STEP_PIN, LOW);
			delayMicroseconds(time);
		}

	}

}

void turndiferential(bool dir, float speed, float distance) {
	enablwalkmotor();
	long steps = distance * walkmotorleft.stepsPerUnit;
	digitalWrite(LFFT_WALK_MOTOR_DIR_PIN, dir);
	digitalWrite(RIGHT_WALK_MOTOR_DIR_PIN, !dir);
	float delaytime = 1000000.0 / (speed * walkmotorleft.stepsPerUnit);
	for (; steps > 0; steps--) {
		digitalWrite(LFFT_WALK_MOTOR_STEP_PIN, HIGH);
		digitalWrite(RIGHT_WALK_MOTOR_STEP_PIN, HIGH);
		delayMicroseconds(delaytime / 2);
		digitalWrite(LFFT_WALK_MOTOR_STEP_PIN, LOW);
		digitalWrite(RIGHT_WALK_MOTOR_STEP_PIN, LOW);
		delayMicroseconds(delaytime / 2);
	}
}

//speed step/sec
void turnananglestep(bool dir, float speed, long steps) {
	enableturnmotor();
	enablwalkmotor();
	digitalWrite(TURN_MOTOR_DIR_PIN, dir);
	float delaytime = 1000000.0 / speed;
	for (; steps > 0; steps--) {
		digitalWrite(TURN_MOTOR_STEP_PIN, HIGH);
		delayMicroseconds(delaytime / 2);
		digitalWrite(TURN_MOTOR_STEP_PIN, LOW);
		delayMicroseconds(delaytime / 2);
	}
}

//speed = angle /s  angle degree
void turnanangleangle(bool dir, float speed, float angle) {
	enableturnmotor();
	enablwalkmotor();
	long steps = angle * turnmotor.stepsperangel;

	MYSERIAL.print("angle to steps =");
	MYSERIAL.println(steps);

	digitalWrite(TURN_MOTOR_DIR_PIN, !dir);
	float delaytime = 1000000.0 / (speed * turnmotor.stepsperangel);

	MYSERIAL.print("angle to steps  delaytime=");
	MYSERIAL.println(delaytime);

	for (; steps > 0; steps--) {
		digitalWrite(TURN_MOTOR_STEP_PIN, HIGH);
		delayMicroseconds(delaytime / 2);
		digitalWrite(TURN_MOTOR_STEP_PIN, LOW);
		delayMicroseconds(delaytime / 2);
	}
	if (!dir == true) {
		turnmotor.angle = turnmotor.angle - angle;
	} else {
		turnmotor.angle = turnmotor.angle + angle;
	}

	MYSERIAL.print("TurnMotor Angle = ");
	MYSERIAL.println(turnmotor.angle);
}

//2015��09.27
//ת����㹦��
//->>>>>>>-endstophit -(LEFT_ERROR)-(ACTULLAY_POSITION)-(RIGHT_ERROR)-endsteprelease>>>>>>>>>-
//����-ת����������-�컨-���ת������������
#define LEFT_ERROR 11.5
#define RIGHT_ERROR -11.5
void turnmotorhome(bool dir) {
//dir is true for forward ;false for backward

}

//���������һ����ʱ������������
void pulsegenarater(byte steppin) {
	digitalWrite(steppin, HIGH);
	delayMicroseconds(1); //1΢���ȵ�����
	digitalWrite(steppin, LOW);
}

void FORCE_INLINE testmotorstep() {
	if (testmotor.steps > 0) {
//		digitalWrite(TEST_MOTOR_STEP_PIN, HIGH);
		digitalWrite(X_STEP_PIN, HIGH);
		delayMicroseconds(1); //1΢���ȵ�����
//		digitalWrite(TEST_MOTOR_STEP_PIN, LOW);
		digitalWrite(X_STEP_PIN, LOW);
		testmotor.steps--;
		testmotor.stepshasgone++;
		//��¼�����λ��
		if (testmotor.dir == true) {
			testmotor.position++;
		} else {
			testmotor.position--;
		}
	}

}

/*��������Ķ�ʱ������򣬼ȼ��ٶȹ���
 *���������Ҫ�Ĳ���
 *ÿ�������һ�� delaytime �� һ�μ�����Ҫ�Ĳ���
 */
void delaytimemanager() {
	//����������ж���ִ��
	//�������ߵ��
	//���������ǵ�� ״̬��isRuning�����ҵ���������߿ռ�

	//��������
	if (testmotor.isRuning == true & testmotor.steps != 0) {
		if (testmotor.currentspeed == 0
				& testmotor.currentspeed < testmotor.goalspeed) {
			//������ڼ���״̬
			testmotor.isSpeedUp = true;
			testmotor.isSpeedDown = false;
//			MYSERIAL.println("Start Speed up!");

		} else if (testmotor.speeddownsteps * SPEED_UP_STEPS_SPEED_DOWN_STEPS
				>= testmotor.steps) {
			//������ڼ���״̬
			testmotor.isSpeedUp = false;
			testmotor.isSpeedDown = true;
//			MYSERIAL.println("Start Speed down!");
		}

//		else {
//			//�����������״̬
//			testmotor.isSpeedUp = false;
//			testmotor.isSpeedDown = false;
//			MYSERIAL.println("Speed normal!");
//		}

		//speed up
		if (testmotor.isSpeedUp == true & testmotor.isSpeedDown == false) {
//			MYSERIAL.println("Speed up ing!");
			if (testmotor.currentspeed == 0) {
				testmotor.currentspeed = testmotor.startSpeed;
				//���¼�����Ҫ�Ĳ���
//				MYSERIAL.println("Speed at start speed!");
//				MYSERIAL.print("current speed is");
//				MYSERIAL.println(testmotor.currentspeed);

//				testmotor.speeddownsteps = testmotor.currentspeed
//						* testmotor.currentspeed / (2 * testmotor.acc);
				noInterrupts();

				Timer1.setPeriod(1000000 / testmotor.startSpeed);
				interrupts();
			} else if (testmotor.currentspeed < testmotor.goalspeed) {
//				MYSERIAL.println("Speed up a little!");
				testmotor.currentspeed = testmotor.currentspeed
						+ INTERRUPTTIME * testmotor.acc / 1000000.0;
//				MYSERIAL.print("current speed is");
//				MYSERIAL.println(testmotor.currentspeed);
//				//���¼�����Ҫ�Ĳ���

//				testmotor.speeddownsteps = testmotor.currentspeed
//						* testmotor.currentspeed / (2 * testmotor.acc);
				noInterrupts();
				Timer1.setPeriod(1000000 / testmotor.currentspeed);
				interrupts();
			}
//			else {
//				//�����������״̬
//				testmotor.isSpeedUp = false;
//				testmotor.isSpeedDown = false;
//				MYSERIAL.println("Speed normal!");
//			}
		} else if ((testmotor.isSpeedUp == false & testmotor.isSpeedDown == true)) {
			//��ʣ�µĲ����Ѿ����ڼ�����Ҫ�Ĳ��٣���ô��Ҫ��ʼ����
			//�˴�Ҳ���Զ�ȡ��Ӧ��������ֵ���жϼ�������
			if (testmotor.currentspeed <= testmotor.startSpeed) {
				//���óɼ��٣������������Ĳ���
				testmotor.currentspeed = testmotor.startSpeed;
				MYSERIAL.println("Speed down to start speed!");
				noInterrupts();
				Timer1.setPeriod(1000000 / testmotor.startSpeed);
				interrupts();
			} else if (testmotor.currentspeed * SPEED_UP_STEPS_SPEED_DOWN_STEPS
					> testmotor.startSpeed) {
				testmotor.currentspeed = testmotor.currentspeed
						- INTERRUPTTIME * testmotor.acc / 1000000.0;
				noInterrupts();
				Timer1.setPeriod(1000000 / testmotor.currentspeed);
				interrupts();
			}
		}

		//
//		if (testmotor.steps == 64000) {
//			MYSERIAL.println("Slow Speed!");
//			Timer1.setPeriod(1000000 / 1000);
//		} else if (testmotor.steps == 32000) {
//			MYSERIAL.println("High Speed!");
//			Timer1.setPeriod(1000000 / 3000);
//		}

		disablwalkmotor();
		disableturnmotor();

		//enable testmotor
		digitalWrite(TEST_MOTOR_ENABLE_PIN, LOW);

		Timer1.attachInterrupt(testmotorstep);
	} else {
		turnmotor.isRuning = false;

		MYSERIAL.println("Stop!");
	}

//��������
	if (testmotor.steps == 0) {
		noInterrupts();
		MYSERIAL.println("stop interrupt!");
		Timer1.stop();
		FlexiTimer2::stop();
		interrupts();
		//��ʼ�� ��� ���ٺ�״̬
		resetmotor(&testmotor);

		//disable testmotor
		digitalWrite(TEST_MOTOR_ENABLE_PIN, HIGH);

		MYSERIAL.print("Test Motor's Position is ");
		MYSERIAL.println(testmotor.position);
	}

}

//timer pulse test
//����ͨ����ʱ����������ķ���
//������ʱ��
void timerpulsetest(float para) {

//���õ��������
	testmotor.steps = 64000;
	testmotor.isRuning = true;
	testmotor.goalspeed = 80000;
	testmotor.acc = 900000;
//���¼�����Ҫ�Ĳ���
	testmotor.speeddownsteps = testmotor.goalspeed * testmotor.goalspeed
			/ (2 * testmotor.acc);
	MYSERIAL.print("testmotor.speeddownsteps = ");
	MYSERIAL.println(testmotor.speeddownsteps);
	MYSERIAL.println("start interrupt!");
	//����жϺ�������ʱ��
//��ʼ��timer1
//Ԥ��ʱ����1�룬δ����ж�ִ�г���
	Timer1.initialize(1000000);
//��ʼ��Timer2 Ԥ��ʱ���� 1ms
	FlexiTimer2::set(INTERRUPTTIME, 1.0 / 1000.0, delaytimemanager);
	FlexiTimer2::start();
//	//����жϺ�������ʱ��
//	Timer1.setPeriod(1000);
//	Timer1.attachInterrupt(delaytimemanager);
//	Timer1.resume();
}

//�����·
void checkendstop() {
	MYSERIAL.print("RUN!");
	MYSERIAL.print("SLIDE_TRIGER_ENDSTOP  =  ");
	MYSERIAL.println(digitalRead(SLIDE_TRIGER_ENDSTOP));
	MYSERIAL.print("SLIDE_TOP_ENDSTOP  =  ");
	MYSERIAL.println(digitalRead(SLIDE_TOP_ENDSTOP));
	MYSERIAL.print("SLIDE_BOTTOM_ENDSTOP =  ");
	MYSERIAL.println(digitalRead(SLIDE_BOTTOM_ENDSTOP));

	MYSERIAL.print("LIFT_BOTTOM_ENDSTOP =  ");
	MYSERIAL.println(digitalRead(LIFT_BOTTOM_ENDSTOP));

	MYSERIAL.print("Front-Right-EndStop =  ");
	MYSERIAL.println(digitalRead(FRONT_RIGHT_STOP));
	MYSERIAL.print("Front-Left-EndStop = ");
	MYSERIAL.println(digitalRead(FRONT_LEFT_STOP));
}

void slideup(float speed, bool dir) {
	MYSERIAL.println("Slide Up!");
	MYSERIAL.print("");
	//dir true for up ;false for down
	digitalWrite(SLIDE_DIR_PIN, dir);
	digitalWrite(LIFT_ENABLE_PIN, LOW);
	long delaytime = 1000000 / speed;
	for (long i = 0; i < 3200 * 75; i++) {
		digitalWrite(SLIDE_STEP_PIN, HIGH);
		delayMicroseconds(delaytime / 2);
		digitalWrite(SLIDE_STEP_PIN, LOW);
		delayMicroseconds(delaytime / 2);
	}
}

//
void disableallmotor() {
	WRITE(X_ENABLE_PIN, LOW);
}

/*
 *�Ӵ��ڻ�ȡ����
 *
 */
void serialmanager() {
	//first letter
//W for walk stepper
//T for turn stepper
//S for slide stepper
//L for lift stepper

//R �������ģʽ����ָ����ʹ�����ģʽ
//X �ƶ�ʹ�òģʽ
//D ����ģʽ

	//second letter
//F for speed----mm/s degree/s
//A for acceleration -- mm/s^2 degree/s^2

	//
	//��ȡ��ָ�� ��ʱ������ָ���

	//ִ��ָ��

	if (MYSERIAL.available() > 0) {
		int input = MYSERIAL.read();
		MYSERIAL.print("input command = ");
		MYSERIAL.println(input);

		if (input == 115) { //s
			//�����ʽ s for speed a for acceleration d for distance
			//s120a100d100
			//s200a10d-500
			int speed = MYSERIAL.parseInt();
			MYSERIAL.print("speed = ");
			MYSERIAL.println(speed);
			input = MYSERIAL.read();
			if (input == 97) //a
					{
				int acc = MYSERIAL.parseInt();
				MYSERIAL.print("acc = ");
				MYSERIAL.println(acc);
				input = MYSERIAL.read();
				if (input == 100) //d
						{
					int distance = MYSERIAL.parseInt();
					MYSERIAL.print("distance = ");
					MYSERIAL.println(distance);
					if (acc * speed * distance != 0) {
						if (distance > 0) {
							walkadistancemmacc(true, speed, abs(distance), acc);
						} else {
							walkadistancemmacc(false, speed, abs(distance),
									acc);
						}
					} else {
						MYSERIAL.println("MYSERIAL Error!");
					}
				}

			}
			//ֻ��һ��������������
			while (MYSERIAL.available() > 0) {
				MYSERIAL.read();
			}
		}

		if (input == 97) { //a ��ת��Ƕ���ص�����
			//axxx(a-xxx)�ڷ�����ת��xxx��
			float angle = MYSERIAL.parseFloat();
			if (angle > 0) {
				turnanangleangle(true, 15, abs(angle));
			} else {
				turnanangleangle(false, 15, abs(angle));
			}

			//ֻ��һ��������������
			while (MYSERIAL.available() > 0) {
				MYSERIAL.read();
			}
		}

//�������ܲ���
		//1 2 3 4 5 6 7 8 9 t
		if (input == 117) { //u
			slideup(1000, true);
		}

		if (input == 49) { //1
//			walkadistancestep(true, 1000, 6400);
			walkadistancemm(true, 30, 100);
		}
		if (input == 50) { //2
//			walkadistancestep(false, 1000, 6400);
			walkadistancemm(false, 30, 100);
		}
		if (input == 51) { //3
//			turnananglestep(true, 1000, 800);
			turnanangleangle(true, 15, 90);
		}
		if (input == 52) { //4
//			turnananglestep(false, 1000, 800);
			turnanangleangle(false, 15, 90);
		}
		if (input == 53) { //5
			disablwalkmotor();
			disableturnmotor();
		}
		if (input == 54) { //6
			enablwalkmotor();
			enableturnmotor();
		}
		if (input == 55) { //7
			checkendstop();
		}
		if (input == 56) { //8

			turndiferential(true, 1, 200);
		}
		if (input == 57) { //9

			turndiferential(false, 1, 200);
		}

		if (input == 116) { //t
			MYSERIAL.println("Test!");
			float para = MYSERIAL.parseFloat();
			timerpulsetest(para);
			//ֻ��һ��������������
			while (MYSERIAL.available() > 0) {
				MYSERIAL.read();
			}

		}
	}
}

void setup() {
	//��ʼ������
	initialPins();
	//���ֵ����״̬

	//�ϵ� ����ȫ���ĵ��
	//�˴���Ҫ���ݺͻ�����������������������Ҫɢ��
	disablwalkmotor();
	//��ʼ������
	MYSERIAL.begin(SERIAL_RATE);

	//**********************************
	//2015.10.20�㷨�������룬����
	//��ʼ����� ״̬�ṹ��
	initialwalkmotor(&walkmotorleft);
	initialwalkmotor(&walkmotorright);
	initialturnmotor(&turnmotor);
	//���Ե����ʼ��
	initialturnmotor(&testmotor);
	//***********************************

	// loads data from EEPROM if available else uses defaults (and resets step acceleration rate)
	Config_RetrieveSettings();
	//planner �����滮·����Ȼ����stepper���жϳ��������ĵ�
	plan_init();  // Initialize planner;
	watchdog_init(); //��ʼ2��
	st_init();    // Initialize stepper, this enables interrupts!

	//temporary ��ʱ
//	disableallmotor();
}

void loop() {

//check parameter
//calculate the necessary value
//	float walkratio = (float) WALK_DRIVE_TATIO;
//	MYSERIAL.print("ratio = ");
//	MYSERIAL.println(walkratio);
//
//	float walkperimeter = (float) WALK_WHEEL_PERIMETER;
//	MYSERIAL.print("perimeter = ");
//	MYSERIAL.println(walkperimeter);
//
//	float walkdriverpulsepercycle = (float) WALK_DRIVER_PULSES_PER_CYCLR;
//	MYSERIAL.print("walkdriverpulsepercycle = ");
//	MYSERIAL.println(walkdriverpulsepercycle);
//
//	float walkbeltpulseperunit = (float) WALK_PULSES_PER_UNIT_BELT;
//	MYSERIAL.print("beltpulseperunit = ");
//	MYSERIAL.println(walkbeltpulseperunit);
//
//	float walkwheelpulseperunit = (float) WALK_PULSES_PER_UNIT_WHEEL;
//	MYSERIAL.print("wheelpulseperunit = ");
//	MYSERIAL.println(walkwheelpulseperunit);
//	delay(1000);
//
//	float turnratio = (float) TURN_DRIVE_TATIO;
//	MYSERIAL.print("ratio = ");
//	MYSERIAL.println(turnratio);
//
//	float turnwheelpulsepercycle = (float) TURN_WHEEL_PULSES_PER_CYCLR;
//	MYSERIAL.print("wheelpulsepercycle = ");
//	MYSERIAL.println(turnwheelpulsepercycle);
//
//	float turnbeltpulseperangle = (float) TURN_PULSES_PER_ANGLE_BELT;
//	MYSERIAL.print("beltpulseperangle = ");
//	MYSERIAL.println(turnbeltpulseperangle);
//
//	delay(1000);

	//MYSERIAL Program Test for the base
//	serialmanager();

//****************************
//marlin �Ĳ���
	if (buflen < (BUFSIZE - 1))
		get_command();

#ifdef SDSUPPORT
	card.checkautostart(false);
#endif
	if (buflen) {
#ifdef SDSUPPORT
		if(card.saving)
		{
			if(strstr_P(cmdbuffer[bufindr], PSTR("M29")) == NULL)
			{
				card.write_command(cmdbuffer[bufindr]);
				if(card.logging)
				{
					process_commands();
				}
				else
				{
					SERIAL_PROTOCOLLNPGM(MSG_OK);
				}
			}
			else
			{
				card.closefile();
				SERIAL_PROTOCOLLNPGM(MSG_FILE_SAVED);
			}
		}
		else
		{
			process_commands();
		}
#else
		//��ӡ

		process_commands();
//		SERIAL_ECHO(cmdbuffer[bufindr]);
#endif //SDSUPPORT
		buflen = (buflen - 1);
		bufindr = (bufindr + 1) % BUFSIZE;
	}
}

void get_command() {
	while ( MYSERIAL.available() > 0 && buflen < BUFSIZE) {
		serial_char = MYSERIAL.read();
//		MYSERIAL.println(serial_char); //ok
		if (serial_char == '\n' || serial_char == '\r'
				|| (serial_char == ':' && comment_mode == false)
				|| serial_count >= (MAX_CMD_SIZE - 1)) {
			if (!serial_count) { //if empty line
				comment_mode = false; //for new command
				return;
			}
			cmdbuffer[bufindw][serial_count] = 0; //terminate string
			if (!comment_mode) {
				comment_mode = false; //for new command
				fromsd[bufindw] = false;
				if (strchr(cmdbuffer[bufindw], 'N') != NULL) {
					strchr_pointer = strchr(cmdbuffer[bufindw], 'N');
					gcode_N = (strtol(
							&cmdbuffer[bufindw][strchr_pointer
									- cmdbuffer[bufindw] + 1], NULL, 10));
					if (gcode_N != gcode_LastN + 1
							&& (strstr_P(cmdbuffer[bufindw], PSTR("M110"))
									== NULL)) {
						SERIAL_ERROR_START;
//            SERIAL_ERRORPGM(MSG_ERR_LINE_NO);
						SERIAL_ERRORLN(gcode_LastN);
						MYSERIAL.println(gcode_N);
						FlushSerialRequestResend();
						serial_count = 0;
						return;
					}

					if (strchr(cmdbuffer[bufindw], '*') != NULL) {
						byte checksum = 0;
						byte count = 0;
						while (cmdbuffer[bufindw][count] != '*')
							checksum = checksum ^ cmdbuffer[bufindw][count++];
						strchr_pointer = strchr(cmdbuffer[bufindw], '*');

						if ((int) (strtod(
								&cmdbuffer[bufindw][strchr_pointer
										- cmdbuffer[bufindw] + 1], NULL))
								!= checksum) {
							SERIAL_ERROR_START;
//              SERIAL_ERRORPGM(MSG_ERR_CHECKSUM_MISMATCH);
							SERIAL_ERRORLN(gcode_LastN);
							FlushSerialRequestResend();
							serial_count = 0;
							return;
						}
						//if no errors, continue parsing
					} else {
						SERIAL_ERROR_START;
//            SERIAL_ERRORPGM(MSG_ERR_NO_CHECKSUM);
						SERIAL_ERRORLN(gcode_LastN);
						FlushSerialRequestResend();
						serial_count = 0;
						return;
					}
					gcode_LastN = gcode_N;
					//if no errors, continue parsing
				} else  // if we don't receive 'N' but still see '*'
				{
					if ((strchr(cmdbuffer[bufindw], '*') != NULL)) {
						SERIAL_ERROR_START;
//            SERIAL_ERRORPGM(MSG_ERR_NO_LINENUMBER_WITH_CHECKSUM);
						SERIAL_ERRORLN(gcode_LastN);
						serial_count = 0;
						return;
					}
				}
				if ((strchr(cmdbuffer[bufindw], 'G') != NULL)) {
					strchr_pointer = strchr(cmdbuffer[bufindw], 'G');
					switch ((int) ((strtod(
							&cmdbuffer[bufindw][strchr_pointer
									- cmdbuffer[bufindw] + 1], NULL)))) {
					case 0:
					case 1:
					case 2:
					case 3:
						if (Stopped == true) {
//              SERIAL_ERRORLNPGM(MSG_ERR_STOPPED);
//              LCD_MESSAGEPGM(MSG_STOPPED);
						}
						break;
					default:
						break;
					}

				}

				//If command was e-stop process now
				if (strcmp(cmdbuffer[bufindw], "M112") == 0)
					;
//          kill();
				//�յ����� ���ͻ���

//				SERIAL_ECHOLN(cmdbuffer[bufindw]);
				SERIAL_ECHOLN("OK"); //�յ���Чָ���OK
				bufindw = (bufindw + 1) % BUFSIZE;
				buflen += 1;
			}
			serial_count = 0; //clear buffer
		} else {
			if (serial_char == ';')
				comment_mode = true;
			if (!comment_mode)
				cmdbuffer[bufindw][serial_count++] = serial_char;
		}
	}

#ifdef SDSUPPORT
	if(!card.sdprinting || serial_count!=0) {
		return;
	}

	//'#' stops reading from SD to the buffer prematurely, so procedural macro calls are possible
	// if it occurs, stop_buffering is triggered and the buffer is ran dry.
	// this character _can_ occur in serial com, due to checksums. however, no checksums are used in SD printing

	static bool stop_buffering=false;
	if(buflen==0) stop_buffering=false;

	while( !card.eof() && buflen < BUFSIZE && !stop_buffering) {
		int16_t n=card.get();
		serial_char = (char)n;
		if(serial_char == '\n' ||
				serial_char == '\r' ||
				(serial_char == '#' && comment_mode == false) ||
				(serial_char == ':' && comment_mode == false) ||
				serial_count >= (MAX_CMD_SIZE - 1)||n==-1)
		{
			if(card.eof()) {
				SERIAL_PROTOCOLLNPGM(MSG_FILE_PRINTED);
				stoptime=millis();
				char time[30];
				unsigned long t=(stoptime-starttime)/1000;
				int hours, minutes;
				minutes=(t/60)%60;
				hours=t/60/60;
				sprintf_P(time, PSTR("%i hours %i minutes"),hours, minutes);
				SERIAL_ECHO_START;
				SERIAL_ECHOLN(time);
				lcd_setstatus(time);
				card.printingHasFinished();
				card.checkautostart(true);

			}
			if(serial_char=='#')
			stop_buffering=true;

			if(!serial_count)
			{
				comment_mode = false; //for new command
				return;//if empty line
			}
			cmdbuffer[bufindw][serial_count] = 0; //terminate string
//      if(!comment_mode){
			fromsd[bufindw] = true;
			buflen += 1;
			bufindw = (bufindw + 1)%BUFSIZE;
//      }
			comment_mode = false;//for new command
			serial_count = 0;//clear buffer
		}
		else
		{
			if(serial_char == ';') comment_mode = true;
			if(!comment_mode) cmdbuffer[bufindw][serial_count++] = serial_char;
		}
	}

#endif //SDSUPPORT

}

void process_commands() {
	unsigned long codenum; //throw away variable
	char *starpos = NULL;
	if (code_seen('G')) {
		switch ((int) code_value()) {
		case 0: // G0 -> G1
		case 1: // G1
			if (Stopped == false) {
				get_coordinates(); // For X Y Z E F
#ifdef FWRETRACT
				if(autoretract_enabled)
				if( !(code_seen('X') || code_seen('Y') || code_seen('Z')) && code_seen('E')) {
					float echange=destination[E_AXIS]-current_position[E_AXIS];
					if((echange<-MIN_RETRACT && !retracted) || (echange>MIN_RETRACT && retracted)) { //move appears to be an attempt to retract or recover
						current_position[E_AXIS] = destination[E_AXIS];//hide the slicer-generated retract/recover from calculations
						plan_set_e_position(current_position[E_AXIS]);//AND from the planner
						retract(!retracted);
						return;
					}
				}
#endif //FWRETRACT
				enable_endstops(false);
				prepare_move();
//				ClearToSend();
//
//				SERIAL_ECHOLN("command ");
//				for (int8_t i = 0; i < NUM_AXIS; i++) {
//					MYSERIAL.print(i);
//					SERIAL_ECHO(" cur posi ");
//					MYSERIAL.println(current_position[i]);
//					MYSERIAL.print(i);
//					SERIAL_ECHO(" destination ");
//					MYSERIAL.println(destination[i]);
//				}
			}
			break;

		case 28: //G28 Home all Axis one at a time
			SERIAL_ECHOLN("G28 HOME CAN NOT BE USED NOW!");
			break;
		}
	} else if (code_seen('M')) {
		switch ((int) code_value()) {

		case 17:
			SERIAL_ECHOLN("enable");
			enable_x()
			;
			enable_y()
			;
			break;
		case 18:
			SERIAL_ECHOLN("disable");
			disable_x()
			;
			disable_y()
			;
			break;
		case 119: //print the end stops state
			SERIAL_ECHOLN("Check Stops!");
			void checkendstop();
			break;
		}
	}
}

void prepare_move() {
	//�����鲻�ܳ�������λλ��
//  clamp_to_software_endstops(destination);
	//��������������ʱ�䣬���ʱ���ȥ̫�ã�������� managerintivetyʹ��
	previous_millis_cmd = millis();

#ifdef true

	float difference[NUM_AXIS];
	for (int8_t i = 0; i < NUM_AXIS; i++) {
		difference[i] = destination[i] - current_position[i];

//		MYSERIAL.print(i);
//		SERIAL_ECHO(" destination ");
//		MYSERIAL.println(destination[i]);
//		MYSERIAL.print(i);
//		SERIAL_ECHO(" current_position ");
//		MYSERIAL.println(current_position[i]);
//		MYSERIAL.print(i);
//		SERIAL_ECHO(" difference ");
//		MYSERIAL.println(difference[i]);
	}

	float cartesian_mm = sqrt(
			sq(difference[X_AXIS]) +
			sq(difference[Y_AXIS]) +
			sq(difference[Z_AXIS]));
	if (cartesian_mm < 0.000001) {
		cartesian_mm = abs(difference[E_AXIS]);
	}
	if (cartesian_mm < 0.000001) {
		return;
	}
	float seconds = 6000 * cartesian_mm / feedrate / feedmultiply;
	int steps = max(1, int(paint_segments_per_second * seconds));

//	SERIAL_ECHOPGM("mm=");
//	SERIAL_ECHO(cartesian_mm);
//	SERIAL_ECHOPGM(" seconds=");
//	SERIAL_ECHO(seconds);
//	SERIAL_ECHOPGM(" steps=");
//	SERIAL_ECHOLN(steps);

	for (int s = 1; s <= steps; s++) {
		float fraction = float(s) / float(steps);
		for (int8_t i = 0; i < NUM_AXIS; i++) {
			destination[i] = current_position[i] + difference[i] * fraction;
		}

		//��Ӧslider��lift��������ϵ
//		destination[Y_AXIS] = destination[Y_AXIS] - 2 * destination[X_AXIS];

		calculate_paint(destination);

//		SERIAL_ECHOPGM("destination[X_AXIS]=");
//		SERIAL_ECHOLN(destination[X_AXIS]);
//		SERIAL_ECHOPGM("destination[Y_AXIS]=");
//		SERIAL_ECHOLN(destination[Y_AXIS]);
//		SERIAL_ECHOPGM("destination[Z_AXIS]=");
//		SERIAL_ECHOLN(destination[Z_AXIS]);

//		SERIAL_ECHOPGM("delta[X_AXIS]="); SERIAL_ECHOLN(delta[X_AXIS]);
//		SERIAL_ECHOPGM("delta[Y_AXIS]="); SERIAL_ECHOLN(delta[Y_AXIS]);
//		SERIAL_ECHOPGM("delta[Z_AXIS]="); SERIAL_ECHOLN(delta[Z_AXIS]);
//		SERIAL_ECHOPGM("feedrate="); SERIAL_ECHOLN(feedrate);

#ifdef PAINT
		plan_buffer_line(delta[X_AXIS], delta[Y_AXIS], delta[Z_AXIS],destination[E_AXIS],
				delta[U_AXIS], delta[V_AXIS], delta[W_AXIS], feedrate * feedmultiply / 60 / 100.0,
				active_extruder);
#else
		plan_buffer_line(delta[X_AXIS], delta[Y_AXIS], delta[Z_AXIS],
				destination[E_AXIS], feedrate * feedmultiply / 60 / 100.0,
				active_extruder);
#endif

#endif

#ifdef SCARA //for now same as delta-code

		float difference[NUM_AXIS];
		for (int8_t i = 0; i < NUM_AXIS; i++) {
			difference[i] = destination[i] - current_position[i];
		}

		float cartesian_mm = sqrt(
				sq(difference[X_AXIS]) +
				sq(difference[Y_AXIS]) +
				sq(difference[Z_AXIS]));
		if (cartesian_mm < 0.000001) {
			cartesian_mm = abs(difference[E_AXIS]);
		}
		if (cartesian_mm < 0.000001) {
			return;
		}
		float seconds = 6000 * cartesian_mm / feedrate / feedmultiply;
		int steps = max(1, int(scara_segments_per_second * seconds));
		//SERIAL_ECHOPGM("mm="); SERIAL_ECHO(cartesian_mm);
		//SERIAL_ECHOPGM(" seconds="); SERIAL_ECHO(seconds);
		//SERIAL_ECHOPGM(" steps="); SERIAL_ECHOLN(steps);
		for (int s = 1; s <= steps; s++) {
			float fraction = float(s) / float(steps);
			for (int8_t i = 0; i < NUM_AXIS; i++) {
				destination[i] = current_position[i] + difference[i] * fraction;
			}

			calculate_delta(destination);
			//SERIAL_ECHOPGM("destination[X_AXIS]="); SERIAL_ECHOLN(destination[X_AXIS]);
			//SERIAL_ECHOPGM("destination[Y_AXIS]="); SERIAL_ECHOLN(destination[Y_AXIS]);
			//SERIAL_ECHOPGM("destination[Z_AXIS]="); SERIAL_ECHOLN(destination[Z_AXIS]);
			//SERIAL_ECHOPGM("delta[X_AXIS]="); SERIAL_ECHOLN(delta[X_AXIS]);
			//SERIAL_ECHOPGM("delta[Y_AXIS]="); SERIAL_ECHOLN(delta[Y_AXIS]);
			//SERIAL_ECHOPGM("delta[Z_AXIS]="); SERIAL_ECHOLN(delta[Z_AXIS]);

			plan_buffer_line(delta[X_AXIS], delta[Y_AXIS], delta[Z_AXIS],
					destination[E_AXIS], feedrate * feedmultiply / 60 / 100.0,
					active_extruder);
		}
#endif // SCARA

#ifdef DELTA
		float difference[NUM_AXIS];
		for (int8_t i=0; i < NUM_AXIS; i++) {
			difference[i] = destination[i] - current_position[i];
		}
		float cartesian_mm = sqrt(sq(difference[X_AXIS]) +
				sq(difference[Y_AXIS]) +
				sq(difference[Z_AXIS]));
		if (cartesian_mm < 0.000001) {cartesian_mm = abs(difference[E_AXIS]);}
		if (cartesian_mm < 0.000001) {return;}
		float seconds = 6000 * cartesian_mm / feedrate / feedmultiply;
		int steps = max(1, int(delta_segments_per_second * seconds));
		// SERIAL_ECHOPGM("mm="); SERIAL_ECHO(cartesian_mm);
		// SERIAL_ECHOPGM(" seconds="); SERIAL_ECHO(seconds);
		// SERIAL_ECHOPGM(" steps="); SERIAL_ECHOLN(steps);
		for (int s = 1; s <= steps; s++) {
			float fraction = float(s) / float(steps);
			for(int8_t i=0; i < NUM_AXIS; i++) {
				destination[i] = current_position[i] + difference[i] * fraction;
			}
			calculate_delta(destination);
#ifdef NONLINEAR_BED_LEVELING
			adjust_delta(destination);
#endif
			plan_buffer_line(delta[X_AXIS], delta[Y_AXIS], delta[Z_AXIS],
					destination[E_AXIS], feedrate*feedmultiply/60/100.0,
					active_extruder);
		}

#endif // DELTA

#ifdef DUAL_X_CARRIAGE
		if (active_extruder_parked)
		{
			if (dual_x_carriage_mode == DXC_DUPLICATION_MODE && active_extruder == 0)
			{
				// move duplicate extruder into correct duplication position.
				plan_set_position(inactive_extruder_x_pos, current_position[Y_AXIS], current_position[Z_AXIS], current_position[E_AXIS]);
				plan_buffer_line(current_position[X_AXIS] + duplicate_extruder_x_offset, current_position[Y_AXIS], current_position[Z_AXIS],
						current_position[E_AXIS], max_feedrate[X_AXIS], 1);
				plan_set_position(current_position[X_AXIS], current_position[Y_AXIS], current_position[Z_AXIS], current_position[E_AXIS]);
				st_synchronize();
				extruder_duplication_enabled = true;
				active_extruder_parked = false;
			}
			else if (dual_x_carriage_mode == DXC_AUTO_PARK_MODE) // handle unparking of head
			{
				if (current_position[E_AXIS] == destination[E_AXIS])
				{
					// this is a travel move - skit it but keep track of current position (so that it can later
					// be used as start of first non-travel move)
					if (delayed_move_time != 0xFFFFFFFFUL)
					{
						memcpy(current_position, destination, sizeof(current_position));
						if (destination[Z_AXIS] > raised_parked_position[Z_AXIS])
						raised_parked_position[Z_AXIS] = destination[Z_AXIS];
						delayed_move_time = millis();
						return;
					}
				}
				delayed_move_time = 0;
				// unpark extruder: 1) raise, 2) move into starting XY position, 3) lower
				plan_buffer_line(raised_parked_position[X_AXIS], raised_parked_position[Y_AXIS], raised_parked_position[Z_AXIS], current_position[E_AXIS], max_feedrate[Z_AXIS], active_extruder);
				plan_buffer_line(current_position[X_AXIS], current_position[Y_AXIS], raised_parked_position[Z_AXIS],
						current_position[E_AXIS], min(max_feedrate[X_AXIS],max_feedrate[Y_AXIS]), active_extruder);
				plan_buffer_line(current_position[X_AXIS], current_position[Y_AXIS], current_position[Z_AXIS],
						current_position[E_AXIS], max_feedrate[Z_AXIS], active_extruder);
				active_extruder_parked = false;
			}
		}
#endif //DUAL_X_CARRIAGE

#if ! (defined DELTA || defined SCARA || defined PAINT)
		// Do not use feedmultiply for E or Z only moves
		if ((current_position[X_AXIS] == destination[X_AXIS])
				&& (current_position[Y_AXIS] == destination[Y_AXIS])) {
			plan_buffer_line(destination[X_AXIS], destination[Y_AXIS],
					destination[Z_AXIS], destination[E_AXIS], feedrate / 60,
					active_extruder);
		} else {
			plan_buffer_line(destination[X_AXIS], destination[Y_AXIS],
					destination[Z_AXIS], destination[E_AXIS],
					feedrate * feedmultiply / 60 / 100.0, active_extruder);
		}
#endif // !(DELTA || SCARA ||PAINT)

	}

	for (int8_t i = 0; i < NUM_AXIS; i++) {
		current_position[i] = destination[i];
		//����һ��block������һ��
//			MYSERIAL.print(i);
//			SERIAL_ECHO(" cur posi ");
//			MYSERIAL.println(current_position[i]);
//			MYSERIAL.print(i);
//			SERIAL_ECHO(" destination ");
//			MYSERIAL.println(destination[i]);
	}
}

void calculate_paint(float cartesian[3]) {
	delta[X_AXIS] = cartesian[X_AXIS];
	delta[Y_AXIS] = cartesian[Y_AXIS];
	delta[Z_AXIS] = cartesian[Z_AXIS];

//������
	/*
	 SERIAL_ECHOPGM("cartesian x="); SERIAL_ECHO(cartesian[X_AXIS]);
	 SERIAL_ECHOPGM(" y="); SERIAL_ECHO(cartesian[Y_AXIS]);
	 SERIAL_ECHOPGM(" z="); SERIAL_ECHOLN(cartesian[Z_AXIS]);

	 SERIAL_ECHOPGM("delta x="); SERIAL_ECHO(delta[X_AXIS]);
	 SERIAL_ECHOPGM(" y="); SERIAL_ECHO(delta[Y_AXIS]);
	 SERIAL_ECHOPGM(" z="); SERIAL_ECHOLN(delta[Z_AXIS]);
	 */
}
//�������ת�������ﲽ��Ҫ���ת��
void calculate_delta(float cartesian[3]) {
//  delta[X_AXIS] = sqrt(delta_diagonal_rod_2
//                       - sq(delta_tower1_x-cartesian[X_AXIS])
//                       - sq(delta_tower1_y-cartesian[Y_AXIS])
//                       ) + cartesian[Z_AXIS];
//  delta[Y_AXIS] = sqrt(delta_diagonal_rod_2
//                       - sq(delta_tower2_x-cartesian[X_AXIS])
//                       - sq(delta_tower2_y-cartesian[Y_AXIS])
//                       ) + cartesian[Z_AXIS];
//  delta[Z_AXIS] = sqrt(delta_diagonal_rod_2
//                       - sq(delta_tower3_x-cartesian[X_AXIS])
//                       - sq(delta_tower3_y-cartesian[Y_AXIS])
//                       ) + cartesian[Z_AXIS];
	/*
	 SERIAL_ECHOPGM("cartesian x="); SERIAL_ECHO(cartesian[X_AXIS]);
	 SERIAL_ECHOPGM(" y="); SERIAL_ECHO(cartesian[Y_AXIS]);
	 SERIAL_ECHOPGM(" z="); SERIAL_ECHOLN(cartesian[Z_AXIS]);

	 SERIAL_ECHOPGM("delta x="); SERIAL_ECHO(delta[X_AXIS]);
	 SERIAL_ECHOPGM(" y="); SERIAL_ECHO(delta[Y_AXIS]);
	 SERIAL_ECHOPGM(" z="); SERIAL_ECHOLN(delta[Z_AXIS]);
	 */
}

void get_coordinates() {
	bool seen[4] = { false, false, false, false };
	for (int8_t i = 0; i < NUM_AXIS; i++) {
		if (code_seen(axis_codes[i])) {
			destination[i] = (float) code_value()
					+ (axis_relative_modes[i] || relative_mode)
							* current_position[i];
			seen[i] = true;
		} else
			destination[i] = current_position[i]; //Are these else lines really needed?
//		SERIAL_ECHO(" get_coordinates ");
//		MYSERIAL.print(i);
//		SERIAL_ECHO(" destination ");
//		MYSERIAL.println(destination[i]);
	}
	if (code_seen('F')) {
		next_feedrate = code_value();
		if (next_feedrate > 0.0)
			feedrate = next_feedrate;
	}
}

float code_value() {
	return (strtod(&cmdbuffer[bufindr][strchr_pointer - cmdbuffer[bufindr] + 1],
	NULL));
}

bool code_seen(char code) {
	strchr_pointer = strchr(cmdbuffer[bufindr], code);
	return (strchr_pointer != NULL);  //Return True if a character was found
}

void FlushSerialRequestResend() {
//char cmdbuffer[bufindr][100]="Resend:";
	MYSERIAL.flush();
//  SERIAL_PROTOCOLPGM(MSG_RESEND);
	SERIAL_PROTOCOLLN(gcode_LastN + 1);
//  ClearToSend();
}
void serial_echopair_P(const char *s_P, float v) {
	serialprintPGM(s_P);
	SERIAL_ECHO(v);
}
void serial_echopair_P(const char *s_P, double v) {
	serialprintPGM(s_P);
	SERIAL_ECHO(v);
}
void serial_echopair_P(const char *s_P, unsigned long v) {
	serialprintPGM(s_P);
	SERIAL_ECHO(v);
}

