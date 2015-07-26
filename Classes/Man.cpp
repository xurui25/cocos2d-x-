#include "Man.h"

Man::Man() {

}

Man::~Man() {

}
//获取人物特征
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


//设置人物特征
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
