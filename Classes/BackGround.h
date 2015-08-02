#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class BackGround :public cocos2d::Layer {
	static int hit;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	//创建背景
	void createback(int i);

	//退出
	void setexit();

	//修改hit值
	static void sethit(int i);
	static int gethit();

	//重写点击效果函数
	virtual bool onTouchBegan(Touch *touch, Event *event);

	CREATE_FUNC(BackGround);
};
#endif