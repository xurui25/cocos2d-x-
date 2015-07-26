#include "SecondBossScene.h"
#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include "Man_1.h"
#include "Man_2.h"
#include "Man_3.h"
#include <iostream>
#include <string>

USING_NS_CC;

Scene* SecondBossScene::createScene()
{
	// 	//������������ĳ���
	auto scene = Scene::createWithPhysics();
	auto layer = SecondBossScene::create();
	scene->addChild(layer);
	//��ȡħ������

	return scene;
}

bool SecondBossScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

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
	bool OK_ = true;

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
	this->schedule(schedule_selector(SecondBossScene::bombsMove), 0.01);

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
void SecondBossScene::bombsMove(float f) {
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
