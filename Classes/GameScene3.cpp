#include "GameScene3.h"
#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include "Man_1.h"
#include "Man_2.h"
#include "Man_3.h"
#include "Man.h"

USING_NS_CC;

Scene* GameScene3::createScene() {
	auto scene = Scene::createWithPhysics();
	auto layer = GameScene3::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene3::init() {
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//��ʼ������
	enemyList.clear();
	items.clear();
	bombs.clear();
	bombs2.clear();
	bloodListforPic.clear();
	bloodList.clear();
	directionList.clear();
	changeOrNot.clear();

	//��ʼ����������
	mantype = HelloWorld::getTypeMan();
	string man_name; //��¼man���ļ���
	if (mantype == 1) {
		manfu = Man_1();
		man = Sprite::create("chooseman1.png");
		man_name = "chooseman1.png";
	}
	else if (mantype == 2) {
		manfu = Man_2();
		man = Sprite::create("chooseman2.png");
		man_name = "chooseman2.png";
	}
	else {
		manfu = Man_3();
		man = Sprite::create("chooseman3.png");
		man_name = "chooseman3.png";
	}
	GameOverScene::win_num = 5;
	//manfu.setSpeed(manfu.getSpeed() * 4);
	useKey = 0;     //��ʼ��useKey
	score = 0;		//��ʼ��Score
	type = 0;       //��ʼ��type
	blood_for_man = manfu.getBlood();    //��ʼ��Ѫ��
	speed_for_water = 3;  //��ʼ��ˮ���ٶ�
	bombNum = 0; // ��ʼ��������ը������
	totalTime = 100; // ��ʼ����ʱ��
	costTime = 0; // ��ʼ����ȥ��ʱ��
	cs = 0;
	xm = 0;

	//��������
	auto bg1 = Sprite::create("background.jpg");
	//Ϊ��Ӧ��Ļ��������
	bg1->setScaleX((float)visibleSize.width / (float)bg1->getContentSize().width);
	bg1->setScaleY((float)visibleSize.height / (float)bg1->getContentSize().height);
	bg1->setPosition(Vec2(origin.x + visibleSize.width / 2, 0));
	bg1->setAnchorPoint(Vec2(0.5, 0));
	bg1->setTag(101);
	this->addChild(bg1, 0);

	//����Label
	createLabel();
	createWater();

	//����ը����ť
	auto btn1 = MenuItemImage::create("boom.png", "boom.png", CC_CALLBACK_1(GameScene2::setBomb, this));
	auto btn2 = MenuItemImage::create("boom2.png", "boom2.png", CC_CALLBACK_1(GameScene2::setBomb2, this));
	auto menu = Menu::create(btn1, btn2, NULL);
	menu->alignItemsVerticallyWithPadding(30);
	menu->setAnchorPoint(Vec2(0, 0));
	menu->setPosition(visibleSize.width - 150, btn1->getContentSize().height + 20);
	this->addChild(menu, 1);

	// ը���������
	bombCount = MenuItemImage::create("x0.png", "x0.png");
	auto menu2 = Menu::create(bombCount, NULL);
	menu2->setPosition(visibleSize.width - 50, 30);
	menu2->setAnchorPoint(Vec2(0, 0));
	this->addChild(menu2);

	//��������
	man->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	man->setTag(3);
	man->setAnchorPoint(Vec2(0, 0));
	sp_file.insert(pair<int, string>(102, man_name));
	this->addChild(man, 5);

	//��ʱ�����ƶ�����
	this->schedule(schedule_selector(GameScene::objectMove), 0.01);

	//��ʱ������
	this->schedule(schedule_selector(GameScene::enemyCreate), 0.5);

	//��ʱɨ���ж�ˮ�е����
	this->schedule(schedule_selector(GameScene3::WaterMove), 0.01);

	//�����ƶ�
	auto listenerkey = EventListenerKeyboard::create();
	listenerkey->onKeyPressed = CC_CALLBACK_2(GameScene::keyPress, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerkey, this);

	auto listenerkey2 = EventListenerKeyboard::create();
	listenerkey2->onKeyReleased = CC_CALLBACK_2(GameScene::keyRelease, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerkey2, this);

	schedule(schedule_selector(GameScene::timeOut), 0.1f);

	schedule(schedule_selector(GameScene::playerGo), 0.01f);

	return true;
}

void GameScene3::createWater() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
	auto water = Sprite::create("bg1_1.png");
	water->setTag(6);
	water->setAnchorPoint(Vec2(0, 0));
	water->setPosition(Vec2(visibleSize.width / 2, 0));
	sp_file.insert(pair<int, string>(6, "bg1_1.png"));
	waterlist.pushBack(water);
	this->addChild(water, 1);

	int dis = 1;
	waterdis.push_back(dis);
}

void GameScene3::WaterMove(float f) {
	for (int j = 0; j < waterlist.size(); j++) {
		auto water = waterlist.at(j);
		int waterd = waterdis.at(j);
		//�ж�ը���ڲ���ˮ����
		for (int i = 0; i < bombs.size(); i++) {
			auto sp = bombs.at(i);
			
			if (GameScene::inIt(water, sp, sp_file[water->getTag()], sp_file[sp->getTag()])) {
				MoveAction(sp, waterd);
			}
		}

		//�ж������ڲ���ˮ����
		if (GameScene::inIt(water, man, sp_file[water->getTag()], sp_file[man->getTag()])) {
			MoveAction(man, waterd);
		}
	}
}

void GameScene3::MoveAction(Sprite* sp, int waterd) {
	//ˮ������
	if (waterd == 1) {
		if (sp->getPositionY() < Director::getInstance()->getVisibleSize().height) {
			sp->setPositionY(sp->getPositionY() + speed_for_water);
		}
	}
	else if (waterd == 2) { //ˮ������
		if (sp->getPositionY() > 0) {
			sp->setPositionY(sp->getPositionY() - speed_for_water);
		}
	}
	else if (waterd == 3) { //ˮ������
		if (sp->getPositionX() > 0) {
			sp->setPositionX(sp->getPositionX() - speed_for_water);
		}
	}
	else if (waterd == 4) { //ˮ������
		if (sp->getPositionX() < Director::getInstance()->getVisibleSize().width) {
			sp->setPositionX(sp->getPositionX() + speed_for_water);
		}
	}
	else if (waterd == 5) { //ˮ��������
		if (sp->getPositionX() > 0 && sp->getPositionY() < Director::getInstance()->getVisibleSize().height) {
			sp->setPosition(Vec2(sp->getPositionX() - speed_for_water / 2, sp->getPositionY() + speed_for_water));
		}
	}
	else if (waterd == 6) { //ˮ��������
		if (sp->getPositionX() < Director::getInstance()->getVisibleSize().width && sp->getPositionY() < Director::getInstance()->getVisibleSize().height) {
			sp->setPosition(Vec2(sp->getPositionX() + speed_for_water / 2, sp->getPositionY() + speed_for_water));
		}
	}
	else if (waterd == 7) { //ˮ��������
		if (sp->getPositionX() > 0 && sp->getPositionY() > 0) {
			sp->setPosition(Vec2(sp->getPositionX() - speed_for_water / 2, sp->getPositionY() - speed_for_water / 2));
		}
	}
	else if (waterd == 8) { //ˮ��������
		if (sp->getPositionX() < Director::getInstance()->getVisibleSize().width && sp->getPositionY() > 0) {
			sp->setPosition(Vec2(sp->getPositionX() + speed_for_water / 2, sp->getPositionY() - speed_for_water / 2));
		}
	}
}