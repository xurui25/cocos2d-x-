#ifndef __FOURTHBOSSSCENE_H__
#define __FOURTHBOSSSCENE_H__

#include "ThirdBossScene.h"

class FourthBossScene :public ThirdBossScene {
public:
	static cocos2d::Scene* createScene();
	bool init();
	void setBomb();
	//��д������
	SkillButton* mSkillButton;
	void CMTouchSpriteSelectSprite(SkillButton *sprite);
	CREATE_FUNC(FourthBossScene);
};
#endif