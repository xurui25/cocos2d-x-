#ifndef __THIRDBOSSSCENE_H__
#define __THIRDBOSSSCENE_H__

#include "FirstBossScene.h"
#include <string>

using namespace std;

class ThirdBossScene :public FirstBossScene {
public:
	Vector<Sprite*>waterlist;
	vector<int>waterdis;
	int speed_for_water;
	map<int, string>sp_file;

	static cocos2d::Scene* createScene();

	virtual bool init();

	void createWater(int i, string src);
	void WaterMove(float f);
	void MoveAction(Sprite *sp, int dis);
	void bombsMove(float f);
	bool inIt(Node* node1, Node* node2, string src1, string src2);
	CREATE_FUNC(ThirdBossScene);
};
#endif