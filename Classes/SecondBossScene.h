#ifndef __SECOND_BOSS_SCENE_H__
#define __SECOND_BOSS_SCENE_H__

#include "FirstBossScene.h"

class SecondBossScene :public FirstBossScene {
public:
	void bombsMove(float f);
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(SecondBossScene);
};
#endif