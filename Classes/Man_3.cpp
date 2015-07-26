#include "Man_3.h"
#include "cocos2d.h"

USING_NS_CC;

Man_3::Man_3() {
	setSpeed(3);
	setBlood(6);
	setPower(2);
	setDis(Director::getInstance()->getVisibleSize().width / 3);
}

Man_3::~Man_3() {

}