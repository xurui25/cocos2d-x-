#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Man.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>

USING_NS_CC;
using namespace std;

class GameScene : public cocos2d::Layer
{
	
public:
	//私有变量
	int score;
	int curx;
	int cury;
	int type;

	int cs;
	int xm;

	// 标记大威力炸弹数量
	MenuItemImage* bombCount;

	// 总时间
	float totalTime;
	// 花去的时间
	float costTime;

	//存储与精灵对应的文件名,只记录一些重要的
	map<int, string>sp_file;

	//人物类型
	int mantype;
	//人物特征
	Man manfu;
	//人物
	Sprite *man;
	//炸弹
	Sprite *bomb;
	vector<Sprite*> bombs;
	vector<Sprite*> bombs2;
	//道具
	Sprite *item;
	vector<Sprite*> items;
	int bombNum;
	//人物的血量
	int blood_for_man;
	int useKey;

	//存储鱼
	cocos2d::Vector<cocos2d::Sprite *> enemyList;
	//存储鱼的方向
	vector<cocos2d::Sprite *> bloodListforPic;
	//存储鱼的血量
	vector<int> bloodList;
	//存储鱼的方向
	vector<int> directionList;
	//判断鱼的血量是否有改变
	vector<int> changeOrNot;

	static cocos2d::Scene* createScene();
	
	virtual bool init();
	virtual void onEnter();
	CREATE_FUNC(GameScene);
	
	//响应鼠标及其键盘
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void keyPress(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void keyRelease(EventKeyboard::KeyCode keyCode, Event* event);

	void playerGo(float t);

	//炸弹放置及其爆炸
	void setBomb(Ref* ref);
	void setBomb2(Ref* ref);
	void eraseBomb(float t);
	void eraseBomb2(float t);
	
	//让鱼游动
	void objectMove(float f);
	//创建鱼
	void enemyCreate(float f);

	//鱼与炸弹的幸福生活
	void BombAndFish(int i);

	//创建文本显示
	void createLabel();

	//停止所有的定时器
	void stopAllSchedule();

	//判断是否碰撞
	bool inIt(Node* node1, Node* node2, string src1, string src2);
	//bool isIn(Node* node1, Point a);

	// 设置道具
	void setItem(Sprite* enemy);
	// 道具消除
	void eraseItem();

	// 超时游戏失败
	void timeOut(float t);

	//游戏结束
	void gameOver();
	void win();
};
#endif // __GAME_SCENE_H__