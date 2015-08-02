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
	//˽�б���
	int score;
	int curx;
	int cury;
	int type;

	int cs;
	int xm;

	// ��Ǵ�����ը������
	MenuItemImage* bombCount;

	// ��ʱ��
	float totalTime;
	// ��ȥ��ʱ��
	float costTime;

	//�洢�뾫���Ӧ���ļ���,ֻ��¼һЩ��Ҫ��
	map<int, string>sp_file;

	//��������
	int mantype;
	//��������
	Man manfu;
	//����
	Sprite *man;
	//ը��
	Sprite *bomb;
	vector<Sprite*> bombs;
	vector<Sprite*> bombs2;
	//����
	Sprite *item;
	vector<Sprite*> items;
	int bombNum;
	//�����Ѫ��
	int blood_for_man;
	int useKey;

	//�洢��
	cocos2d::Vector<cocos2d::Sprite *> enemyList;
	//�洢��ķ���
	vector<cocos2d::Sprite *> bloodListforPic;
	//�洢���Ѫ��
	vector<int> bloodList;
	//�洢��ķ���
	vector<int> directionList;
	//�ж����Ѫ���Ƿ��иı�
	vector<int> changeOrNot;

	static cocos2d::Scene* createScene();
	
	virtual bool init();
	virtual void onEnter();
	CREATE_FUNC(GameScene);
	
	//��Ӧ��꼰�����
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void keyPress(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void keyRelease(EventKeyboard::KeyCode keyCode, Event* event);

	void playerGo(float t);

	//ը�����ü��䱬ը
	void setBomb(Ref* ref);
	void setBomb2(Ref* ref);
	void eraseBomb(float t);
	void eraseBomb2(float t);
	
	//�����ζ�
	void objectMove(float f);
	//������
	void enemyCreate(float f);

	//����ը�����Ҹ�����
	void BombAndFish(int i);

	//�����ı���ʾ
	void createLabel();

	//ֹͣ���еĶ�ʱ��
	void stopAllSchedule();

	//�ж��Ƿ���ײ
	bool inIt(Node* node1, Node* node2, string src1, string src2);
	//bool isIn(Node* node1, Point a);

	// ���õ���
	void setItem(Sprite* enemy);
	// ��������
	void eraseItem();

	// ��ʱ��Ϸʧ��
	void timeOut(float t);

	//��Ϸ����
	void gameOver();
	void win();
};
#endif // __GAME_SCENE_H__