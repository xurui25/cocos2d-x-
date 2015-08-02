#ifndef __HELP_H__
#define __HELP_H__

#include "cocos2d.h"
USING_NS_CC;

class Help :public cocos2d::Layer {
public:
	
	static cocos2d::Scene* createScene();
	virtual bool init();
	
	//»Øµ÷º¯Êý
	void menuContinueCallback(cocos2d::Ref* pSender);

	static int pass;
	static void setPass(int i);
	static int getPass();

	CREATE_FUNC(Help);	
};
#endif