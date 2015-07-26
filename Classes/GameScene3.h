#ifndef __GAME_SCENE3_H__
#define __GAME_SCENE3_H__

#include "cocos2d.h"
#include "GameScene.h"

class GameScene3 :public GameScene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	CREATE_FUNC(GameScene3);

	void setBomb(Ref* ref);
	void setBomb2(Ref* ref);
	void BombsMove3(float f);
};
#endif