#ifndef __CHOOSE_MAN_SCENE_H__
#define __CHOOSE_MAN_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class ChooseMan :public cocos2d::Layer{
private:
	MenuItemImage* man1;
	MenuItemImage* man2;
	MenuItemImage* man3;

public:
	static cocos2d::Scene* createScene();
	bool init();

	//�ص�ѡ������
	void CallBackMan1();
	void CallBackMan2();
	void CallBackMan3();

	//������ذ�ť
	void CreateItem();

	CREATE_FUNC(ChooseMan);
};
#endif