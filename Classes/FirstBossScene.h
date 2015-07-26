#ifndef __FIRST_BOSS_SCENE_H__
#define __FIRST_BOSS_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "SkillButton.h"
#include "Man.h"
#include <iostream>
#include <string>
#include <vector>

USING_NS_CC;
using namespace std;
//
class FirstBossScene : public cocos2d::Layer, public CMTouchSpriteProtocol
{
public:
	//私有变量
	//分数
	int score;
	//当前坐标
	int curx;
	int cury;
	//武器类型
	int TypeWeapon;
	//魔法
	int Magic;
	//人物
	Sprite *man;
	//炸弹
	Sprite *bomb;
	//炸弹的威力
	int weapon_eff;
	//boss
	Sprite *boss;
	//人物移动的速度
	int speed_for_man;
	//人物的大小
	float manscale;
	//炸弹增加的威力
	int increase_for_weapon;
	//炸弹增加的距离
	int increase_for_dis;
	//技能的类别
	
	//人物类别
	int mantype;
	//人物特征
	Man manfu;
	
	//人物技能的种类
	static int type_for_skill;


	//武器精灵
	MenuItemImage *btn1;
	MenuItemImage *btn2;
	Menu *menu;

	//存储所有炸弹还剩的距离
	vector<int> bombs_dis;
	//人物的血量
	int blood_for_man;
	//boss的血量
	int blood_for_boss;
	int useKey;

	//设置boss的移动方向
	bool boss_move_up;

	//设置boss技能的鱼的速率
	float rate;

	//存储所有的鱼（可碰和不可碰）
	cocos2d::Vector<cocos2d::Sprite *> enemyList;
	cocos2d::Vector<cocos2d::Sprite*> bombs;
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void onEnter();
	CREATE_FUNC(FirstBossScene);

	//响应鼠标及其键盘
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void keyPress(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void keyRelease(EventKeyboard::KeyCode keyCode, Event* event);

	//重写代理方法
	SkillButton* mSkillButton;
	void CMTouchSpriteSelectSprite(SkillButton *sprite);

	//人物移动
	void playerGo(float t);

	//label集合
	void createLabel();

	//武器的生成
	void setBomb();
	void setnull(Ref* ref);

	//让鱼游动
	void objectMove(float f);
	//让武器移动
	void bombsMove(float f);
	//创建鱼和能量球
	void enemyCreate(float f);
	//创建BOSS
	void bossCreate();
	//boss移动
	void bossMove(float f);

	//boss的技能
	//void BossKill_1();

	//设置速率
	void setRate(float f);
	//获取速率
	float getRate();

	//停止所有的定时器
	void stopAllSchedule();

	//设置人物的技能
	static void setTypeSkill(int i);
	static int getTypeSkill();

	float time_1;
	bool OK_;
	//游戏结束
	void gameOver();
	void win();
};
#endif // __FIRST_BOSS_SCENE_H__