#ifndef __CHOOSE_GUAN_H__
#define __CHOOSE_GUAN_H__

#include "cocos2d.h"

USING_NS_CC;

class ChooseGuan :public cocos2d::Layer{
private:
	
public:
	static cocos2d::Scene* createScene();
	bool init();

	void selectGuan1();
	void selectGuan2();
	void selectGuan3();
	void selectGuan4();
	void selectGuan5();
	void goHello();
	void clearRec();

	static bool canChoose1;
	static bool canChoose2;
	static bool canChoose3;
	static bool canChoose4;
	static bool canChoose5;

	static int choosenum;

	CREATE_FUNC(ChooseGuan);
};
#endif