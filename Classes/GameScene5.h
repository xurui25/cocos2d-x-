#ifndef __GAMESCENE5_H__
#define __GAMESCENE5_H__

#include "cocos2d.h"
#include "GameScene4.h"

class GameScene5 :public GameScene4 {
	Sprite* Machine;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene5);

	void createMachine();
	void MachineMove(float f);

	void playerGo(float f);

	void MachineBomb(float f);
	void MachineReduc(float f);
};
#endif
