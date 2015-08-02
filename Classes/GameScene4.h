#ifndef __GAMESCENE4_H__
#define __GAMESCENE4_H__

#include "GameScene3.h"

class GameScene4 :public GameScene3{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene4);

	void objectMove(float f);
};
#endif