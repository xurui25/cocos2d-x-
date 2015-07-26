#ifndef __TRAN_SCENE_H__
#define __TRAN_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class TranScene : public cocos2d::Layer
{
	//关卡
	
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene(int i);

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	void menuMagic1Callback(cocos2d::Ref* pSender);
	void menuMagic2Callback(cocos2d::Ref* pSender);
	void menuMagic3Callback(cocos2d::Ref* pSender);

	//响应对话点击
	void menuTouch(cocos2d::Ref* pSender);

	//重写点击效果函数
	//virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	//判断是否有触碰
	//virtual bool isTap(Node* node, Touch* touch);
	//剧情透露
	void createLabel();
	//显示按钮
	void buttonShow();

	// implement the "static create()" method manually
	CREATE_FUNC(TranScene);

	//static int Checkpoint;
	//Sprite *Tou;
	Sprite *str;
	Sprite *str1;
	int word_num;
};

#endif // __TRAN_SCENE_H__