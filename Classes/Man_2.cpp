#include "Man_2.h"
#include "cocos2d.h"

USING_NS_CC;

Man_2::Man_2() {
	setSpeed(6);
	setBlood(3);
	setPower(1);
	setDis(3 * Director::getInstance()->getVisibleSize().width / 5);
}

Man_2::~Man_2() {

}