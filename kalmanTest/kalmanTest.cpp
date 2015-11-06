#include "kalmanTest.h"

#include "ultraSonicSensor.h"
#include "math.h"

#define  FORCE_INLINE __attribute__((always_inline)) inline
//测试超声波程序，并将卡尔曼滤波的结构用
//收集超声波数据

//高速或者高精度模式
//默认处于高精度模式
bool highpre_highspe = false;

#define TRIGERPIN  8
#define ECHOPIN 9

const int trigerPin = TRIGERPIN;
const int echoPin = ECHOPIN;

ultraSonicSensor uss = ultraSonicSensor(TRIGERPIN, ECHOPIN);
////当前的值
float distance;

//kalman用到的参数
//系统参数
float distance_last = 100; //mm  初始值
float p_last = 0; //上一次最优值的协方差
float Q = 2; //系统误差
float R = 4; //测量误差

//计算用到的中间值
float kg; //卡尔曼系数，每次更新
float distance_mid; //中间测量值
float distance_now; //kalman滤波结果
float p_mid; //协方差中间值
float p_now; //kalman估计出的最优值
float distance_measure; //距离测量值
uint32_t count = 0; //测量次数

//卡尔曼滤波程序，只对
FORCE_INLINE float kalmanfilterforUS(float distance);

void setup() {

	Serial.begin(115200);

	distance_last = uss.ultrasonicDistance(); //mm 测量一次值
}

void loop() {
	distance = uss.ultrasonicDistance(); //测量一次值
	int value = distance;


	//kalman 计算
	distance = kalmanfilterforUS(distance);
//	Serial.print(" distance is  :  ");
//	Serial.print(distance_last);
//	Serial.print("\t");
//	Serial.print(" value is  :  ");
//	Serial.print('S');

	Serial.print(value);
	Serial.print('\t');
	Serial.print(int(distance));
	Serial.print('\n');

//	Serial.write(byte(0xff));
//	Serial.println();
////	Serial.write((distance_last>>24)&0xff);
////	Serial.write((distance_last>>16)&0xff);
////	Serial.write((distance_last>>8)&0xff);
////	Serial.write((distance_last)&0xff);
//	Serial.write(byte((value >> 8) & 0xff));
//	Serial.println();
//	Serial.write(byte(value & 0xff));
//	Serial.println();

	delay(10); //delay 5ms
}

FORCE_INLINE float kalmanfilterforUS(float distance) {

	distance_mid = distance_last; //distance_last=distance(k-1|k-1),distance_mid=distance(k|k-1)
	p_mid = p_last + Q; //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=噪声
	kg = p_mid / (p_mid + R); //kg为kalman filter，R为噪声
	distance_measure = distance; //测量值
	distance_now = distance_mid + kg * (distance_measure - distance_mid); //估计出的最优值
	p_now = (1 - kg) * p_mid; //最优值对应的covariance
	p_last = p_now; //更新covariance值
	distance_last = distance_now; //更新系统状态值
	return distance_last;
}

////#include "math.h"
//float x_last = 0;
//float p_last = 0.02;
//float Q = 0.018;
//float R = 0.542;
//float kg;
//float x_mid;
//float x_now;
//float p_mid;
//float p_now;
//float z_real = 0.56; //0.56
//float z_measure;
//float sumerror_kalman = 0;
//float sumerror_measure = 0;
//int i;
//
//double frand() {
//	return 2 * ((rand() / (double) RAND_MAX) - 0.5); //随机噪声
//}
//

//int main(int arg, char **args) {
//	x_last = z_real + frand() * 0.03;
//	x_mid = x_last;
//	for (i = 0; i < 20; i++) {
//		x_mid = x_last; //x_last=x(k-1|k-1),x_mid=x(k|k-1)
//		p_mid = p_last + Q; //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=噪声
//		kg = p_mid / (p_mid + R); //kg为kalman filter，R为噪声
//		z_measure = z_real + frand() * 0.03; //测量值
//		x_now = x_mid + kg * (z_measure - x_mid); //估计出的最优值
//		p_now = (1 - kg) * p_mid; //最优值对应的covariance
////		printf("Real position: %6.3f \n", z_real); //显示真值
////		printf("Mesaured position: %6.3f [diff:%.3f]\n", z_measure,
////				fabs(z_real - z_measure)); //显示测量值以及真值与测量值之间的误差
////		printf("Kalman position: %6.3f [diff:%.3f]\n", x_now,
////				fabs(z_real - x_now)); //显示kalman估计值以及真值和卡尔曼估计值的误差
//		sumerror_kalman += fabs(z_real - x_now); //kalman估计值的累积误差
//		sumerror_measure += fabs(z_real - z_measure); //真值与测量值的累积误差
//		p_last = p_now; //更新covariance值
//		x_last = x_now; //更新系统状态值
//	}
////	printf("总体测量误差 : %f\n", sumerror_measure); //输出测量累积误差
////	printf("总体卡尔曼滤波误差: %f\n", sumerror_kalman); //输出kalman累积误差
////	printf("卡尔曼误差所占比例: %d%% \n",
////			100 - (int) ((sumerror_kalman / sumerror_measure) * 100));
//	return 0;
//}
