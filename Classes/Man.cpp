#include "Man.h"

Man::Man() {

}

Man::~Man() {

}
//��ȡ��������
int Man::getBlood() {
	return blood_for_man;
}

int Man::getSpeed() {
	return speed_for_man;
}

int Man::getPower() {
	return power_of_man;
}

int Man::getDis() {
	return dis_of_man;
}


//������������
void Man::setBlood(int i) {
	blood_for_man = i;
}

void Man::setSpeed(int i) {
	speed_for_man = i;
}

void Man::setPower(int i) {
	power_of_man = i;
}

void Man::setDis(int i) {
	dis_of_man = i/10;
}
