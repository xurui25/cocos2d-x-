#include "GameScene2.h"
#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include "Man_1.h"
#include "Man_2.h"
#include "Man_3.h"
#include <iostream>
#include <string>

#pragma execution_character_set("utf-8")

USING_NS_CC;

Scene* GameScene2::createScene()
{
	// 	//创建物理世界的场景
	auto scene = Scene::createWithPhysics();
	auto layer = GameScene2::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene2::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//初始化数据
	enemyList.clear();
	items.clear();
	bombs.clear();
	bombs2.clear();
	bloodListforPic.clear();
	bloodList.clear();
	directionList.clear();
	changeOrNot.clear();

	//初始化人物特征
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

	GameOverScene::win_num = 3;
	useKey = 0;     //初始化useKey
	score = 0;		//初始化Score
	type = 0;       //初始化type
	blood_for_man = manfu.getBlood();    //初始化血量
	bombNum = 0; // 初始化大威力炸弹数量
	totalTime = 100; // 初始化总时长
	costTime = 0; // 初始化花去的时间
	cs = 0;
	xm = 0;

	//背景精灵
	auto bg1 = Sprite::create("background.jpg");
	//为适应屏幕进行缩放
	bg1->setScaleX((float)visibleSize.width / (float)bg1->getContentSize().width);
	bg1->setScaleY((float)visibleSize.height / (float)bg1->getContentSize().height);
	bg1->setPosition(Vec2(origin.x + visibleSize.width / 2, 0));
	bg1->setAnchorPoint(Vec2(0.5, 0));
	bg1->setTag(101);
	this->addChild(bg1, 0);

	//创建Label
	createLabel();

	//创建炸弹按钮
	auto btn1 = MenuItemImage::create("boom.png", "boom.png", CC_CALLBACK_1(GameScene2::setBomb, this));
	auto btn2 = MenuItemImage::create("boom2.png", "boom2.png", CC_CALLBACK_1(GameScene2::setBomb2, this));
	auto menu = Menu::create(btn1, btn2, NULL);
	menu->alignItemsVerticallyWithPadding(30);
	menu->setAnchorPoint(Vec2(0, 0));
	menu->setPosition(visibleSize.width - 150, btn1->getContentSize().height + 20);
	this->addChild(menu, 1);

	// 炸弹数量标记
	bombCount = MenuItemImage::create("x0.png", "x0.png");
	auto menu2 = Menu::create(bombCount, NULL);
	menu2->setPosition(visibleSize.width - 50, 30);
	menu2->setAnchorPoint(Vec2(0, 0));
	this->addChild(menu2);

	//创建人物及设置物理碰撞
	man = Sprite::create("man1.png");
	man->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	man->setTag(102);
	auto manBody = PhysicsBody::createBox(man->getContentSize());
	this->addChild(man, 5);

	//定时调用移动函数
	this->schedule(schedule_selector(GameScene::objectMove), 0.01);

	//定时创建鱼
	this->schedule(schedule_selector(GameScene::enemyCreate), 0.5);

	//按键移动
	auto listenerkey = EventListenerKeyboard::create();
	listenerkey->onKeyPressed = CC_CALLBACK_2(GameScene::keyPress, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerkey, this);

	auto listenerkey2 = EventListenerKeyboard::create();
	listenerkey2->onKeyReleased = CC_CALLBACK_2(GameScene::keyRelease, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerkey2, this);


	schedule(schedule_selector(GameScene::playerGo), 0.01f);

	schedule(schedule_selector(GameScene::timeOut), 0.1f);

	return true;
}

void GameScene2::setBomb(Ref* ref) {
	if (bombs.size() < 1) {
		bomb = Sprite::create("boom.png");
		bomb->setTag(1);
		sp_file.insert(pair<int, string>(1, "boom.png"));
		bomb->setPosition(man->getPosition());
		bomb->setAnchorPoint(Vec2(0, 0));
		this->addChild(bomb, 1);
		bombs.push_back(bomb);
	}

	schedule(schedule_selector(GameScene2::BombsMove), 0.01f);
	schedule(schedule_selector(GameScene::eraseBomb), 1.0f);
}

void GameScene2::setBomb2(Ref* ref)
{

	// 需要足够的炸弹道具数量
	if (bombNum <= 0)
		return;

	if (bombs.size() < 1) {
		bomb = Sprite::create("boom2.png");
		bomb->setTag(2);
		sp_file.insert(pair<int, string>(2, "boom2.png"));
		bomb->setPosition(man->getPosition());
		bomb->setAnchorPoint(Vec2(0, 0));
		this->addChild(bomb, 1);
		bombs2.push_back(bomb);

		// 用掉一个炸弹
		bombNum--;

		if (bombNum == 0)
			bombCount->setNormalImage(Sprite::create("x0.png"));
		else if (bombNum == 1)
			bombCount->setNormalImage(Sprite::create("x1.png"));
		else if (bombNum == 2)
			bombCount->setNormalImage(Sprite::create("x2.png"));
		else if (bombNum == 3)
			bombCount->setNormalImage(Sprite::create("x3.png"));
		else if (bombNum == 4)
			bombCount->setNormalImage(Sprite::create("x4.png"));
		else if (bombNum == 5)
			bombCount->setNormalImage(Sprite::create("x5.png"));
		else if (bombNum == 6)
			bombCount->setNormalImage(Sprite::create("x6.png"));
		else if (bombNum == 7)
			bombCount->setNormalImage(Sprite::create("x7.png"));
		else if (bombNum == 8)
			bombCount->setNormalImage(Sprite::create("x8.png"));
		else if (bombNum == 9)
			bombCount->setNormalImage(Sprite::create("x9.png"));
		else
			bombCount->setNormalImage(Sprite::create("x10.png"));
	}

	schedule(schedule_selector(GameScene2::BombsMove), 0.01f);
	schedule(schedule_selector(GameScene::eraseBomb2), 1.0f);
}

void GameScene2::BombsMove(float f) {
	for (int i = 0; i < bombs.size(); i++) {
		auto bomb_ = bombs.at(i);

		bomb_->setPosition(bomb_->getPositionX(), bomb_->getPositionY() - 1);
		if (bomb_->getPositionY() < 0) {
			bomb_->setPositionY(0);
		}
	}

	for (int i = 0; i < bombs2.size(); i++) {
		auto bomb_ = bombs2.at(i);

		bomb_->setPosition(bomb_->getPositionX(), bomb_->getPositionY() - 1);
		if (bomb_->getPositionY() < 0) {
			bomb_->setPositionY(0);
		}
	}
}