#include "ThirdBossScene.h"
#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include "ChooseGuan.h"
#include "Man_1.h"
#include "Man_2.h"
#include "Man_3.h"
#include <iostream>
#include <string>
#include "Collision.h"

USING_NS_CC;

Scene* ThirdBossScene::createScene()
{
	// 	//������������ĳ���
	auto scene = Scene::createWithPhysics();
	auto layer = ThirdBossScene::create();
	scene->addChild(layer);
	//��ȡħ������

	return scene;
}

bool ThirdBossScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//���Խ����Ĺؿ�
	ChooseGuan::choosenum = 4;
	mantype = HelloWorld::getTypeMan();
	if (mantype == 1) {
		manfu = Man_1();
		man = Sprite::create("chooseman1.png");
	}
	else if (mantype == 2) {
		manfu = Man_2();
		man = Sprite::create("chooseman2.png");
	}
	else {
		manfu = Man_3();
		man = Sprite::create("chooseman3.png");
	}

	GameOverScene::win_num = 6;
	useKey = 0;     //��ʼ��useKey
	score = 0;		//��ʼ��Score
	Magic = 0;      //��ʼ������ħ��
	TypeWeapon = 0;       //��ʼ��type
	blood_for_man = manfu.getBlood();    //��ʼ��Ѫ��
	blood_for_boss = 20;  //��ʼ��Boss��Ѫ��
	boss_move_up = true; //boss��ʼ�������ƶ�
	rate = 5;   //����ƶ����ʳ�ʼ��Ϊ5
	weapon_eff = manfu.getPower(); //��ʼ��ը��������
	increase_for_dis = 0; //ħ�����������ľ���
	increase_for_weapon = 0; //ħ����������������
	speed_for_man = manfu.getSpeed(); //��ʼ���˵��ٶ�
	manscale = 1; //��ʼ���˵Ĵ�С
	time_1 = 0.5;
	speed_for_water = 5;

	//��������
	auto bg1 = Sprite::create("background.jpg");
	//Ϊ��Ӧ��Ļ��������
	bg1->setScaleX((float)visibleSize.width / (float)bg1->getContentSize().width);
	bg1->setScaleY((float)visibleSize.height / (float)bg1->getContentSize().height);
	bg1->setPosition(Vec2(origin.x + visibleSize.width / 2, 0));
	bg1->setAnchorPoint(Vec2(0.5, 0));
	bg1->setTag(101);
	this->addChild(bg1, 0);

	//�������Ｐ����������ײ
	man->setPosition(30, visibleSize.height / 2);
	man->setTag(102);
	auto manBody = PhysicsBody::createBox(man->getContentSize());
	manBody->setContactTestBitmask(0x0003);
	manBody->setCategoryBitmask(0x0001);
	manBody->setCollisionBitmask(0x0007);
	manBody->setGravityEnable(false);
	manBody->setDynamic(false);
	man->setPhysicsBody(manBody);
	this->addChild(man, 5);

	//label�ļ���
	createLabel();
	createWater(1, "bg1_1.png");

	//����Boss
	bossCreate();

	//����һ
	mSkillButton = SkillButton::createSkillButton(0.5, "boom_cd.png", "boom.png", "blood_blue_meitu_1.png");
	mSkillButton->setPosition(ccp(visibleSize.width - 50, 2 * mSkillButton->getContentSize().height + 50));
	addChild(mSkillButton);
	mSkillButton->setTouchSpriteProtocol(this);

	//boss����
	this->schedule(schedule_selector(FirstBossScene::objectMove), 0.01);

	//boss�ƶ�
	this->schedule(schedule_selector(FirstBossScene::bossMove), 0.02);

	//��Ĵ���
	this->schedule(schedule_selector(FirstBossScene::enemyCreate), 1);

	//ը���ƶ�
	this->schedule(schedule_selector(ThirdBossScene::bombsMove), 0.01);

	//�ж�ˮ�е����
	this->schedule(schedule_selector(ThirdBossScene::WaterMove), 0.01);

	//��������
	this->schedule(schedule_selector(FirstBossScene::setRate), 1);
	// �����ƶ�
	auto listenerkey = EventListenerKeyboard::create();
	listenerkey->onKeyPressed = CC_CALLBACK_2(FirstBossScene::keyPress, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerkey, this);

	auto listenerkey2 = EventListenerKeyboard::create();
	listenerkey2->onKeyReleased = CC_CALLBACK_2(FirstBossScene::keyRelease, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerkey2, this);


	schedule(schedule_selector(FirstBossScene::playerGo), 0.01f);

	return true;
}

//�������ƶ�
void ThirdBossScene::bombsMove(float f) {
	for (int i = 0; i < bombs.size(); i++) {
		auto bomb = bombs.at(i);

		bomb->setPosition(bomb->getPositionX() + 10, bomb->getPositionY() - 2);
		bombs_dis[i]--;
		if (bomb->getPositionX() > Director::getInstance()->getVisibleSize().width + 100 || bombs_dis[i] <= 0) {
			bomb->removeFromParent();
			bombs.eraseObject(bomb);

			bombs_dis.erase(bombs_dis.begin() + i);

			i--;
		}
	}
}

void ThirdBossScene::createWater(int i, string src) {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto water = Sprite::create(src);
	water->setTag(4);
	water->setAnchorPoint(Vec2(0, 0));
	water->setPosition(Vec2(visibleSize.width / 2, 0));
	sp_file.insert(pair<int, string>(4, src));
	waterlist.pushBack(water);
	this->addChild(water, 1);

	int dis = i;
	waterdis.push_back(dis);
}

void ThirdBossScene::WaterMove(float f) {
	for (int j = 0; j < waterlist.size(); j++) {
		auto water = waterlist.at(j);
		int waterd = waterdis.at(j);
		//�ж�ը���ڲ���ˮ����
		for (int i = 0; i < bombs.size(); i++) {
			auto boom = bombs.at(i);
			
			if (inIt(water, boom, sp_file[water->getTag()], sp_file[boom->getTag()])) {
				MoveAction(boom, waterd);
			}

			//�ж������ڲ���ˮ����
			if (inIt(man, water, sp_file[man->getTag()], sp_file[water->getTag()])) {
				MoveAction(man, waterd);
			}
		}
	}
}

void ThirdBossScene::MoveAction(Sprite* boom, int waterd) {
	//ˮ������
	if (waterd == 1) {
		if (boom->getPositionY() < Director::getInstance()->getVisibleSize().height) {
			boom->setPositionY(boom->getPositionY() + speed_for_water);
		}
	}
	else if (waterd == 2) { //ˮ������
		if (boom->getPositionY() > 0) {
			boom->setPositionY(boom->getPositionY() - speed_for_water);
		}
	}
	else if (waterd == 3) { //ˮ������
		if (boom->getPositionX() > 0) {
			boom->setPositionX(boom->getPositionX() - speed_for_water);
		}
	}
	else if (waterd == 4) { //ˮ������
		if (boom->getPositionX() < Director::getInstance()->getVisibleSize().width) {
			boom->setPositionX(boom->getPositionX() + speed_for_water);
		}
	}
	else if (waterd == 5) { //ˮ��������
		if (boom->getPositionX() > 0 && boom->getPositionY() < Director::getInstance()->getVisibleSize().height) {
			boom->setPosition(Vec2(boom->getPositionX() - speed_for_water / 2, boom->getPositionY() + speed_for_water));
		}
	}
	else if (waterd == 6) { //ˮ��������
		if (boom->getPositionX() < Director::getInstance()->getVisibleSize().width && boom->getPositionY() < Director::getInstance()->getVisibleSize().height) {
			boom->setPosition(Vec2(boom->getPositionX() + speed_for_water / 2, boom->getPositionY() + speed_for_water));
		}
	}
	else if (waterd == 7) { //ˮ��������
		if (boom->getPositionX() > 0 && boom->getPositionY() > 0) {
			boom->setPosition(Vec2(boom->getPositionX() - speed_for_water / 2, boom->getPositionY() - speed_for_water / 2));
		}
	}
	else if (waterd == 8) { //ˮ��������
		if (boom->getPositionX() < Director::getInstance()->getVisibleSize().width && boom->getPositionY() > 0) {
			boom->setPosition(Vec2(boom->getPositionX() + speed_for_water / 2, boom->getPositionY() - speed_for_water / 2));
		}
	}
}

bool ThirdBossScene::inIt(Node* node1, Node* node2, string src1, string src2) {
	Point a = node2->getPosition();
	Point b = node1->getPosition();

	Collision col1 = Collision();
	Collision col2 = Collision();

	col1.setThePlex(src1);
	col2.setThePlex(src2);

	for (int x = a.x; x < a.x + node2->getContentSize().width; x++) {
		for (int y = a.y; y < a.y + node2->getContentSize().height; y++) {
			if (x > node1->getPositionX() && x < node1->getPositionX() + node1->getContentSize().width
				&& y > node1->getPositionY() && y < node1->getPositionY() + node1->getContentSize().height) {
				int xy = col1.getThePlexByPoint(x - b.x, y - b.y) * col2.getThePlexByPoint(x - a.x, y - a.y);
				if (xy != 0) {
					delete col1.plex_t;
					delete col2.plex_t;
					return true;
				}
			}
		}
	}
	delete col1.plex_t;
	delete col2.plex_t;

	return false;
}