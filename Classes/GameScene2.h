#ifndef __GAME_SCENE_2_H__
#define __GAME_SCENE_2_H__

#include "cocos2d.h"
#include "GameScene.h"

USING_NS_CC;

class GameScene2 :public GameScene {


public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	CREATE_FUNC(GameScene2);

	void setBomb(Ref* ref);
	void setBomb2(Ref* ref);
	void BombsMove(float f);

	//”Œœ∑Ω· ¯
	//void gameOver();
	//void win();
};
#endif