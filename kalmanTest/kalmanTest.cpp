#include "kalmanTest.h"

#include "ultraSonicSensor.h"
#include "math.h"

#define  FORCE_INLINE __attribute__((always_inline)) inline
//���Գ��������򣬲����������˲��Ľṹ��
//�ռ�����������

//���ٻ��߸߾���ģʽ
//Ĭ�ϴ��ڸ߾���ģʽ
bool highpre_highspe = false;

#define TRIGERPIN  8
#define ECHOPIN 9

const int trigerPin = TRIGERPIN;
const int echoPin = ECHOPIN;

ultraSonicSensor uss = ultraSonicSensor(TRIGERPIN, ECHOPIN);
////��ǰ��ֵ
float distance;

//kalman�õ��Ĳ���
//ϵͳ����
float distance_last = 100; //mm  ��ʼֵ
float p_last = 0; //��һ������ֵ��Э����
float Q = 2; //ϵͳ���
float R = 4; //�������

//�����õ����м�ֵ
float kg; //������ϵ����ÿ�θ���
float distance_mid; //�м����ֵ
float distance_now; //kalman�˲����
float p_mid; //Э�����м�ֵ
float p_now; //kalman���Ƴ�������ֵ
float distance_measure; //�������ֵ
uint32_t count = 0; //��������

//�������˲�����ֻ��
FORCE_INLINE float kalmanfilterforUS(float distance);

void setup() {

	Serial.begin(115200);

	distance_last = uss.ultrasonicDistance(); //mm ����һ��ֵ
}

void loop() {
	distance = uss.ultrasonicDistance(); //����һ��ֵ
	int value = distance;


	//kalman ����
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
	p_mid = p_last + Q; //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=����
	kg = p_mid / (p_mid + R); //kgΪkalman filter��RΪ����
	distance_measure = distance; //����ֵ
	distance_now = distance_mid + kg * (distance_measure - distance_mid); //���Ƴ�������ֵ
	p_now = (1 - kg) * p_mid; //����ֵ��Ӧ��covariance
	p_last = p_now; //����covarianceֵ
	distance_last = distance_now; //����ϵͳ״ֵ̬
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
//	return 2 * ((rand() / (double) RAND_MAX) - 0.5); //�������
//}
//

//int main(int arg, char **args) {
//	x_last = z_real + frand() * 0.03;
//	x_mid = x_last;
//	for (i = 0; i < 20; i++) {
//		x_mid = x_last; //x_last=x(k-1|k-1),x_mid=x(k|k-1)
//		p_mid = p_last + Q; //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=����
//		kg = p_mid / (p_mid + R); //kgΪkalman filter��RΪ����
//		z_measure = z_real + frand() * 0.03; //����ֵ
//		x_now = x_mid + kg * (z_measure - x_mid); //���Ƴ�������ֵ
//		p_now = (1 - kg) * p_mid; //����ֵ��Ӧ��covariance
////		printf("Real position: %6.3f \n", z_real); //��ʾ��ֵ
////		printf("Mesaured position: %6.3f [diff:%.3f]\n", z_measure,
////				fabs(z_real - z_measure)); //��ʾ����ֵ�Լ���ֵ�����ֵ֮������
////		printf("Kalman position: %6.3f [diff:%.3f]\n", x_now,
////				fabs(z_real - x_now)); //��ʾkalman����ֵ�Լ���ֵ�Ϳ���������ֵ�����
//		sumerror_kalman += fabs(z_real - x_now); //kalman����ֵ���ۻ����
//		sumerror_measure += fabs(z_real - z_measure); //��ֵ�����ֵ���ۻ����
//		p_last = p_now; //����covarianceֵ
//		x_last = x_now; //����ϵͳ״ֵ̬
//	}
////	printf("���������� : %f\n", sumerror_measure); //��������ۻ����
////	printf("���忨�����˲����: %f\n", sumerror_kalman); //���kalman�ۻ����
////	printf("�����������ռ����: %d%% \n",
////			100 - (int) ((sumerror_kalman / sumerror_measure) * 100));
//	return 0;
//}
