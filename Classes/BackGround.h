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

	//��������
	void createback(int i);

	//�˳�
	void setexit();

	//�޸�hitֵ
	static void sethit(int i);
	static int gethit();

	//��д���Ч������
	virtual bool onTouchBegan(Touch *touch, Event *event);

	CREATE_FUNC(BackGround);
};
#endif