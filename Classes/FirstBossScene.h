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
	//˽�б���
	//����
	int score;
	//��ǰ����
	int curx;
	int cury;
	//��������
	int TypeWeapon;
	//ħ��
	int Magic;
	//����
	Sprite *man;
	//ը��
	Sprite *bomb;
	//ը��������
	int weapon_eff;
	//boss
	Sprite *boss;
	//�����ƶ����ٶ�
	int speed_for_man;
	//����Ĵ�С
	float manscale;
	//ը�����ӵ�����
	int increase_for_weapon;
	//ը�����ӵľ���
	int increase_for_dis;
	//���ܵ����
	
	//�������
	int mantype;
	//��������
	Man manfu;
	
	//���＼�ܵ�����
	static int type_for_skill;


	//��������
	MenuItemImage *btn1;
	MenuItemImage *btn2;
	Menu *menu;

	//�洢����ը����ʣ�ľ���
	vector<int> bombs_dis;
	//�����Ѫ��
	int blood_for_man;
	//boss��Ѫ��
	int blood_for_boss;
	int useKey;

	//����boss���ƶ�����
	bool boss_move_up;

	//����boss���ܵ��������
	float rate;

	//�洢���е��㣨�����Ͳ�������
	cocos2d::Vector<cocos2d::Sprite *> enemyList;
	cocos2d::Vector<cocos2d::Sprite*> bombs;
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void onEnter();
	CREATE_FUNC(FirstBossScene);

	//��Ӧ��꼰�����
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void keyPress(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void keyRelease(EventKeyboard::KeyCode keyCode, Event* event);

	//��д������
	SkillButton* mSkillButton;
	void CMTouchSpriteSelectSprite(SkillButton *sprite);

	//�����ƶ�
	void playerGo(float t);

	//label����
	void createLabel();

	//����������
	void setBomb();
	void setnull(Ref* ref);

	//�����ζ�
	void objectMove(float f);
	//�������ƶ�
	void bombsMove(float f);
	//�������������
	void enemyCreate(float f);
	//����BOSS
	void bossCreate();
	//boss�ƶ�
	void bossMove(float f);

	//boss�ļ���
	//void BossKill_1();

	//��������
	void setRate(float f);
	//��ȡ����
	float getRate();

	//ֹͣ���еĶ�ʱ��
	void stopAllSchedule();

	//��������ļ���
	static void setTypeSkill(int i);
	static int getTypeSkill();

	float time_1;
	bool OK_;
	//��Ϸ����
	void gameOver();
	void win();
};
#endif // __FIRST_BOSS_SCENE_H__