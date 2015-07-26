#include "Man_1.h"
#include "cocos2d.h"

USING_NS_CC;

Man_1::Man_1() {
	setSpeed(5);
	setBlood(4);
	setPower(1);
	setDis(Director::getInstance()->getVisibleSize().width / 2);
}

Man_1::~Man_1() {

}