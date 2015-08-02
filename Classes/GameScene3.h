#ifndef __GAMESCENE3_H__
#define __GAMESCENE3_H__

#include "cocos2d.h"
#include "GameScene2.h"

class GameScene3 :public GameScene2 {
public:
	Vector<Sprite*>waterlist;
	vector<int>waterdis;
	int speed_for_water;

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene3);

	void createWater();
	void WaterMove(float f);

	void MoveAction(Sprite *sp, int dis);
};
#endif
