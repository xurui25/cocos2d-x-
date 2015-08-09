#include "GameScene.h"
#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include "Man_1.h"
#include "Man_2.h"
#include "Man_3.h"
#include "Collision.h"
#include <iostream>
#include <string>
#include "SimpleAudioEngine.h"


using namespace CocosDenshion;
USING_NS_CC;

#pragma execution_character_set("utf-8")

USING_NS_CC;

Scene* GameScene::createScene()
{
	//创建物理世界的场景
	auto scene = Scene::createWithPhysics();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
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
	string man_name; //记录man的文件名
	if (mantype == 1) {
		manfu = Man_1();
		man = Sprite::create("chooseman1.png");
		man_name = "chooseman1.png";
	}
	else if (mantype == 2) {
		manfu = Man_2();
		man = Sprite::create("chooseman2.png");
		man_name = "chooseman1.png";
	}
	else {
		manfu = Man_3();
		man = Sprite::create("chooseman3.png");
		man_name = "chooseman1.png";
	}
	GameOverScene::win_num = 1;
	useKey = 0;     //初始化useKey
	score = 0;		//初始化Score
	type = 0;       //初始化type
	blood_for_man = manfu.getBlood();    //初始化血量
	bombNum = 0; // 初始化大威力炸弹数量
	totalTime = 100; // 初始化总时长
	costTime = 0; // 初始化花去的时间
	cs = 0;
	xm = 0;
	isPause = false;
	useBgm = true;


	// 预载入音乐、音效
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/bgm.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/boom.mp3");
	// 播放背景音乐
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/bgm.mp3", true);


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
	auto btn1 = MenuItemImage::create("boom.png", "boom.png", CC_CALLBACK_1(GameScene::setBomb, this));
	auto btn2 = MenuItemImage::create("boom2.png", "boom2.png", CC_CALLBACK_1(GameScene::setBomb2, this));
	auto menu = Menu::create(btn1, btn2, NULL);
	menu->alignItemsVerticallyWithPadding(30);
	menu->setAnchorPoint(Vec2(0, 0));
	menu->setPosition(visibleSize.width - 150, btn1->getContentSize().height + 20);
	this->addChild(menu, 1);

	//预先将鱼的图片纹理存起来
	spriteTexture1 = CCSpriteBatchNode::create("fish2.png");
	spriteTexture1->setPosition(Vec2(0, 0));
	addChild(spriteTexture1, 2);
	spriteTexture2 = CCSpriteBatchNode::create("fish1.png");
	spriteTexture2->setPosition(Vec2(0, 0));
	addChild(spriteTexture2, 2);
	spriteTexture3 = CCSpriteBatchNode::create("fish3.png");
	spriteTexture3->setPosition(Vec2(0, 0));
	addChild(spriteTexture3, 2);

	// 炸弹数量标记
	bombCount = MenuItemImage::create("x0.png", "x0.png");
	auto menu2 = Menu::create(bombCount, NULL);
	menu2->setPosition(visibleSize.width - 50, 30);
	menu2->setAnchorPoint(Vec2(0, 0));
	this->addChild(menu2);

	
	// 创建暂停按钮,返回按钮和控制音乐按钮.
	auto btn3 = MenuItemImage::create("continue.png", "continue2.png", CC_CALLBACK_0(GameScene::pauseGame, this));
	auto btn4 = MenuItemImage::create("exit.png", "exit2.png", CC_CALLBACK_0(GameScene::goHomePage, this));
	auto btn5 = MenuItemImage::create("select_guan.png", "select_guan.png", CC_CALLBACK_0(GameScene::soundUsing, this));
	auto menu3 = Menu::create(btn3, btn4, btn5, NULL);
	menu3->alignItemsVerticallyWithPadding(30);
	menu3->setAnchorPoint(Vec2(0, 0));
	menu3->setPosition(visibleSize.width - 100, 500);
	this->addChild(menu3, 1);
	
	
	//创建人物
	man->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	man->setTag(3);
	man->setAnchorPoint(Vec2(0, 0));
	sp_file.insert(pair<int, string>(102, man_name));
	//auto manBody = PhysicsBody::createBox(man->getContentSize());
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

//层进入的时候会调用该函数，进行物理世界的碰撞检测
void GameScene::onEnter()
{
	Layer::onEnter();
}

//鱼的移动
void GameScene::objectMove(float f) {
	for (int i = 0; i < enemyList.size(); i++)
	{
		auto enemy = enemyList.at(i);
		auto bloodbody = bloodListforPic.at(i);
		auto blood = bloodList.at(i);
		auto direction_ = directionList.at(i);

		int num_ = enemy->getTag();
		int speed;

		if (num_ == 104) {
			speed = 3;
		}
		else if (num_ = 105) {
			speed = 2;
		}
		else if (num_ = 106) {
			speed = 1;
		}

		if (direction_ == 0) {
			//向左移动
			enemy->setPositionX(enemy->getPositionX() - speed);
		}
		else if (direction_ == 1) {
			//向右移动
			enemy->setPositionX(enemy->getPositionX() + speed);
		}
		else if (direction_ == 2) {
			//向下运动
			enemy->setPositionY(enemy->getPositionY() - speed);
		}
		else if (direction_ == 3){
			//向上运动
			enemy->setPositionY(enemy->getPositionY() + speed);
		}
		else if (direction_ == 4) {
			//左向上运动
			enemy->setPositionX(enemy->getPositionX() - (int)(speed/2));
			enemy->setPositionY(enemy->getPositionY() + (int)(speed/2));
		}
		else if (direction_ == 5) {
			//右向上运动
			enemy->setPositionX(enemy->getPositionX() + (int)(speed / 2));
			enemy->setPositionY(enemy->getPositionY() + (int)(speed / 2));
		}
		else if (direction_ == 6) {
			//左向下运动
			enemy->setPositionX(enemy->getPositionX() - (int)(speed / 2));
			enemy->setPositionY(enemy->getPositionY() - (int)(speed / 2));
		}
		else if (direction_ == 7) {
			//右向下运动
			enemy->setPositionX(enemy->getPositionX() + (int)(speed / 2));
			enemy->setPositionY(enemy->getPositionY() - (int)(speed / 2));

		}
		else if (direction_ == 8) {
			//左向下运动
			enemy->setPositionX(enemy->getPositionX() - (int)(speed / 2));
			enemy->setPositionY(enemy->getPositionY() - (int)(speed / 2));
		}
		else if (direction_ == 9) {
			//右向下运动
			enemy->setPositionX(enemy->getPositionX() + (int)(speed / 2));
			enemy->setPositionY(enemy->getPositionY() - (int)(speed / 2));
		}
		else if (direction_ == 10) {
			//左向上运动
			enemy->setPositionX(enemy->getPositionX() - (int)(speed / 2));
			enemy->setPositionY(enemy->getPositionY() + (int)(speed / 2));
		}
		else{
			//右向上运动
			enemy->setPositionX(enemy->getPositionX() + (int)(speed / 2));
			enemy->setPositionY(enemy->getPositionY() + (int)(speed / 2));
		}
		
		if (blood == 1) {
			if (changeOrNot[i] == 1) {
				//auto bloodBody1 = Sprite::create("blood_blue.png", CCRectMake(0, 0, 100, 12));
				bloodListforPic[i]->setScaleX(0.5);

			}
			bloodListforPic[i]->setPosition(Vec2(enemy->getPositionX() + enemy->getContentSize().width / 2 - bloodListforPic[i]->getContentSize().width / 2, enemy->getPositionY() + int(enemy->getContentSize().height) + 1));
		}
		else if (blood == 2){
			if (changeOrNot[i] == 1) {
				//auto bloodBody1 = Sprite::create("blood_blue.png", CCRectMake(0, 0, 200, 12));
				bloodListforPic[i]->setScaleX(0.66);
			}
			bloodListforPic[i]->setPosition(Vec2(enemy->getPositionX() + enemy->getContentSize().width / 2 - bloodListforPic[i]->getContentSize().width / 2, enemy->getPositionY() + int(enemy->getContentSize().height) + 1));
		}
		else {
			bloodListforPic[i]->setPosition(Vec2(enemy->getPositionX() + enemy->getContentSize().width / 2 - bloodListforPic[i]->getContentSize().width / 2, enemy->getPositionY() + int(enemy->getContentSize().height) + 1));
		}

		changeOrNot[i] = 0;
		if (enemy->getPositionX() < -(enemy->getContentSize().width) || enemy->getPositionX() > (Director::getInstance()->getVisibleSize().width)
			||enemy->getPositionY() < -(enemy->getContentSize().height) || enemy->getPositionY() > (Director::getInstance()->getVisibleSize().height))
		{
			enemy->removeFromParent();		//从层中移除
			enemyList.eraseObject(enemy);	//把鱼从记录中移除
			
			bloodbody->removeFromParent();  //血条从层中移除
			bloodListforPic.erase(bloodListforPic.begin()+i);//把血条从记录中移除

			//更新数据
			xm++;
			auto scoreSpire = (Label *)this->getChildByTag(114);
			scoreSpire->setString(String::createWithFormat("XM:%d", xm)->_string);

			bloodList.erase(bloodList.begin()+i);   //把鱼对应的血量的记录移除
			directionList.erase(directionList.begin()+i);   //把鱼对应的方向从记录中移除
			//移除后上一个对象会移到当前这个对象的位置，实际还是当前这个i，所以要i--才能访问到下一个对象
			i--;
		}
		else if (enemy->getTag() == 104) {		//判断是否和人碰撞且进行处理
			if (inIt(enemy, man, sp_file[104], sp_file[man->getTag()])) {
				blood_for_man--;

				if (blood_for_man <= 0) {
					gameOver();
				}
				//使用粒子系统
				auto * system = ParticleSystemQuad::create("particle_texture.plist");
				system->setPosition(enemy->getPositionX(), enemy->getPositionY());
				this->addChild(system);

				this->removeChild(enemy);
				//enemy->removeFromParent();		//从层中移除
				enemyList.eraseObject(enemy);	//把鱼从记录中移除
				
				//bloodbody->removeFromParent();  //血条从层中移除
				this->removeChild(bloodbody);
				bloodListforPic.erase(bloodListforPic.begin() + i);//把血条从记录中移除

				bloodList.erase(bloodList.begin() + i);   //把鱼对应的血量的记录移除
				directionList.erase(directionList.begin() + i);   //把鱼对应的方向从记录中移除

				xm++;
				auto scoreSpire1 = (Label *)this->getChildByTag(114);
				scoreSpire1->setString(String::createWithFormat("XM:%d", xm)->_string);

				//更新数据
				auto scoreSpire = (Label *)this->getChildByTag(100);
				scoreSpire->setString(String::createWithFormat("HP:%d", blood_for_man)->_string);

				i--;
			}
		}
	}
}

//鱼的创建
void GameScene::enemyCreate(float f)
{
	if (enemyList.size() > 15) {
		return;
	}

	string src;
	int blood;
	int director_;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//创建精灵
	Sprite* enemy;
	int temp = rand() % 3;
	if (temp == 0) {
		enemy = Sprite::createWithTexture(spriteTexture1->getTexture());
		blood = 1;
		enemy->setTag(104);
		sp_file.insert(pair<int, string>(104, "fish2.png"));
	}
	else if (temp == 1) {
		enemy = Sprite::createWithTexture(spriteTexture2->getTexture());
		blood = 2;
		enemy->setTag(105);
		sp_file.insert(pair<int, string>(105, "fish1.png"));
	}
	else {
		enemy = Sprite::createWithTexture(spriteTexture3->getTexture());
		blood = 3;
		enemy->setTag(106);
		sp_file.insert(pair<int, string>(106, "fish3.png"));
	}
	/*
	//CCSprite * enemy;
	//auto enemy = Sprite::create(src);
	if (src == "fish2.png") {
		//enemy = CCSprite::createWithTexture(batchNode1->getTexture());
		enemy->setTag(104);
		sp_file.insert(pair<int, string>(104, "fish2.png"));
	}
	else if (src == "fish1.png") {
		//enemy = CCSprite::createWithTexture(batchNode2->getTexture());
		enemy->setTag(105);
		sp_file.insert(pair<int, string>(105, "fish1.png"));
	}
	else {
		//enemy = CCSprite::createWithTexture(batchNode3->getTexture());
		enemy->setTag(106);
		sp_file.insert(pair<int, string>(106, "fish3.png"));
	}*/
	//设置锚点
	enemy->setAnchorPoint(Vec2(0, 0));
	director_ = rand() % 12;
	if (director_ == 0) {
		//在屏幕的最右边出现
		enemy->setPosition(Vec2((Director::getInstance()->getVisibleSize().width), 
			rand() % (int)(Director::getInstance()->getVisibleSize().height - enemy->getContentSize().height)));
	}
	else if (director_ == 1) {
		//在屏幕的最左边出现
		enemy->setPosition(Vec2((-enemy->getContentSize().width), 
			rand() % (int)(Director::getInstance()->getVisibleSize().height - enemy->getContentSize().height)));
	}
	else if (director_ == 2) {
		//在屏幕的最上边出现
		enemy->setPosition(Vec2((rand() % (int)(Director::getInstance()->getVisibleSize().width - enemy->getContentSize().width)),
			(Director::getInstance()->getVisibleSize().height + enemy->getContentSize().height)));
	}
	else if (director_ == 3){
		//在屏幕的最下方出现
		enemy->setPosition(Vec2((rand() % (int)(Director::getInstance()->getVisibleSize().width - enemy->getContentSize().width)),
			-enemy->getContentSize().height));
	}
	else if (director_ == 4) {
		//在屏幕的右边的下方出现
		enemy->setPosition(Vec2((Director::getInstance()->getVisibleSize().width),
			rand() % (int)(Director::getInstance()->getVisibleSize().height / 2)));
	}
	else if (director_ == 5) {
		//在屏幕的左边的下方出现
		enemy->setPosition(Vec2((-enemy->getContentSize().width),
			rand() % (int)(Director::getInstance()->getVisibleSize().height / 2)));
	}
	else if (director_ == 6) {
		//在屏幕的右边的上方出现
		enemy->setPosition(Vec2((Director::getInstance()->getVisibleSize().width),
			rand() % (int)(Director::getInstance()->getVisibleSize().height / 2) +(int)(Director::getInstance()->getVisibleSize().height / 2) - enemy->getContentSize().height));
	}
	else if (director_ == 7) {
		//在屏幕的左边的上方出现
		enemy->setPosition(Vec2((-enemy->getContentSize().width),
			rand() % (int)(Director::getInstance()->getVisibleSize().height / 2) + (int)(Director::getInstance()->getVisibleSize().height / 2) - enemy->getContentSize().height));

	}
	else if (director_ == 8) {
		//在屏幕的上方的右边出现
		enemy->setPosition(Vec2((rand() % (int)(Director::getInstance()->getVisibleSize().width / 2) + (int)(Director::getInstance()->getVisibleSize().width / 2) - enemy->getContentSize().width),
			(Director::getInstance()->getVisibleSize().height)));
	}
	else if (director_ == 9) {
		//在屏幕的上方的左边出现
		enemy->setPosition(Vec2((rand() % (int)(Director::getInstance()->getVisibleSize().width / 2)),
			(Director::getInstance()->getVisibleSize().height)));

	}
	else if (director_ == 10) {
		//在屏幕的下方的右边出现
		enemy->setPosition(Vec2((rand() % (int)(Director::getInstance()->getVisibleSize().width / 2) + (int)(Director::getInstance()->getVisibleSize().width / 2) - enemy->getContentSize().width),
			-enemy->getContentSize().height));
	}
	else {
		//在屏幕的下方的左边出现
		enemy->setPosition(Vec2((rand() % (int)(Director::getInstance()->getVisibleSize().width / 2)),
			-enemy->getContentSize().height));

	}

	this->addChild(enemy, 2);
	this->enemyList.pushBack(enemy);
	this->bloodList.push_back(blood);
	this->directionList.push_back(director_);
	this->changeOrNot.push_back(0);
	
	cs++;
	//更新数据
	auto scoreSpire = (Label *)this->getChildByTag(113);
	scoreSpire->setString(String::createWithFormat("CS:%d", cs)->_string);

	int x1, y1;
	if (enemy->getTag() == 104) {
		x1 = 80;
		y1 = 12;
	}
	else if (enemy->getTag() == 105) {
		x1 = 160;
		y1 = 12;
	}
	else if (enemy->getTag() == 106) {
		x1 = 240;
		y1 = 12;
	}
	auto bloodBody = Sprite::create("blood_blue.png", CCRectMake(0,0,x1,y1));
	bloodBody->setAnchorPoint(Vec2(0, 0));
	bloodBody->setPosition(Vec2(enemy->getPositionX() + enemy->getContentSize().width / 2 - bloodBody->getContentSize().width / 2, enemy->getPositionY() + int(enemy->getContentSize().height) + 1));
	this->addChild(bloodBody, 3);
	this->bloodListforPic.push_back(bloodBody);
}

// 点击屏幕时触发的事件（鱼移动）
bool GameScene::onTouchBegan(Touch *touch, Event *unused_event)
{

	// 在0.3的时间内将鱼移动到点击处
	MoveTo *move = MoveTo::create(0.3f, touch->getLocation());
	man->runAction(move);

	return true;
}

void GameScene::setBomb(Ref* ref)
{
	if (bombs.size() < 1) {
		bomb = Sprite::create("boom.png");
		bomb->setTag(1);
		sp_file.insert(pair<int, string>(1, "boom.png"));
		bomb->setPosition(man->getPosition());
		bomb->setAnchorPoint(Vec2(0, 0));
		this->addChild(bomb, 1);
		bombs.push_back(bomb);
	}

	schedule(schedule_selector(GameScene::eraseBomb), 0.5f);
}

void GameScene::setBomb2(Ref* ref)
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

	schedule(schedule_selector(GameScene::eraseBomb2), 0.8f);

}
//炸弹效果
void GameScene::eraseBomb(float t)
{
	vector<Sprite*>::iterator i = bombs.begin();

	Size bombSize = (*i)->getContentSize();
	
	if (!bombs.empty())
	{
		Vec2 pos = (*i)->getPosition();
		curx = pos.x;
		cury = pos.y;
		
		if ((*i)->getTag() == 1)
		{
			Sprite* temp[9];
			int count = 0;
			CCSpriteBatchNode* spriteTexture = CCSpriteBatchNode::create("b1.png"); 
			spriteTexture->setPosition(Vec2(0, 0));
			addChild(spriteTexture, 2); 
			//CCSprite* sprite = CCSprite::createWithTexture(spriteTexture->getTexture());
			//sprite->setPosition(ccp(visiblesize.width / 2, 100)); spriteTexture->addChild(sprite, 2);
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					temp[count] = Sprite::createWithTexture(spriteTexture->getTexture());
					temp[count]->setPosition(pos.x + bombSize.width * i, pos.y + bombSize.height * j);
					this->addChild(temp[count], 2);
					temp[count]->runAction(Sequence::create(DelayTime::create(0.4f), Hide::create(), NULL));
					count++;
				}
			}

			type = 1;
			BombAndFish(1);
		}
		(*i)->removeFromParent();
		//this->removeChild(*i);
		bombs.erase(i);

		// 发出音效
		SimpleAudioEngine::getInstance()->playEffect("music/boom.mp3");
	}

	if (bombs.empty())
	{
		unschedule(schedule_selector(GameScene::eraseBomb));
	}
}

//炸弹效果
void GameScene::eraseBomb2(float t)
{
	vector<Sprite*>::iterator i = bombs2.begin();

	Size bombSize = (*i)->getContentSize();

	if (!bombs2.empty())
	{
		Vec2 pos = (*i)->getPosition();
		curx = pos.x;
		cury = pos.y;

		if ((*i)->getTag() == 2)
		{
			Sprite* temp[25];
			int count = 0;
			CCSpriteBatchNode* spriteTexture = CCSpriteBatchNode::create("b2.png");
			spriteTexture->setPosition(Vec2(0,0));
			addChild(spriteTexture, 2);
			for (int i = -2; i <= 2; i++)
			{
				for (int j = -2; j <= 2; j++)
				{
					temp[count] = Sprite::createWithTexture(spriteTexture->getTexture());
					temp[count]->setPosition(pos.x + bombSize.width * i, pos.y + bombSize.height * j);
					this->addChild(temp[count], 2);
					temp[count]->runAction(Sequence::create(DelayTime::create(0.4f), Hide::create(), NULL));
					count++;
				}
			}
			type = 2;
			BombAndFish(2);
		}
		(*i)->removeFromParent();
		//this->removeChild(*i);
		bombs2.erase(i);

		// 发出音效
		SimpleAudioEngine::getInstance()->playEffect("music/boom.mp3");
	}

	if (bombs2.empty())
	{
		unschedule(schedule_selector(GameScene::eraseBomb2));
	}
}

//检测鱼和炸弹的碰撞
void GameScene::BombAndFish(int ty) {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	for (int i = 0; i < enemyList.size(); i++)
	{
		auto enemy = enemyList.at(i);
		auto bloodbody = bloodListforPic.at(i);

		Size bombSize;
		if (ty == 1)
			bombSize = bombs[0]->getContentSize();
		else if (ty == 2)
			bombSize = bombs2[0]->getContentSize();

		int x = enemy->getPositionX() + enemy->getContentSize().width / 2;
		int y = enemy->getPositionY() + enemy->getContentSize().height / 2;
		int xwidth = enemy->getPositionX() + enemy->getContentSize().width;
		int yheight = enemy->getPositionY() + enemy->getContentSize().height;

		if (type == 1) {
			int xmin, xmax, ymin, ymax;
			//获取炸弹x轴的范围
			xmin = max(int(curx - bombSize.width), 0);
			xmax = min(int(curx + 2 * bombSize.width), int(visibleSize.width));
			//获取炸弹y轴的范围
			ymin = max(int(cury - bombSize.height), 0);
			ymax = min(int(cury + 2 * bombSize.height), int(visibleSize.height));

			//int wid = (xmax - xmin) / 6;
			//int hei = (ymax - ymin) / 6;

			if (x >= xmin && x <= xmax && y >= ymin && y <= ymax) {
				bloodList[i] -= manfu.getPower();
				changeOrNot[i] = 1;
			}
			/*
			if ((x >= curx - wid && x <= curx + wid && y <= ymax && y >= ymin) ||
				(x >= xmin && x <= xmax && y >= cury - hei && y <= cury + hei)) {
				bloodList[i] -= manfu.getPower();
				changeOrNot[i] = 1;
			}*/
		}
		else if (type == 2) {
			int xmin, xmax, ymin, ymax;
			//获取炸弹x轴的范围
			xmin = max(int(curx - 2 * bombSize.width), 0);
			xmax = min(int(curx + 3 * bombSize.width), int(visibleSize.width));
			//获取炸弹y轴的范围
			ymin = max(int(cury - 2 * bombSize.height), 0);
			ymax = min(int(cury + 3 * bombSize.height), int(visibleSize.height));

			if (x >= xmin && x <= xmax && y >= ymin && y <= ymax) {
				bloodList[i] -= manfu.getPower();
				changeOrNot[i] = 1;
			}
		}

		if (bloodList[i] <= 0) {
			//不同种类鱼的分数不同
			if (enemy->getTag() == 104) {
				score += 100;
			}
			else if (enemy->getTag() == 105) {
				score += 150;
			}
			else if (enemy->getTag() == 106) {
				score += 200;
			}

			//更新分数
			auto scoreSpire = (Label *)this->getChildByTag(111);
			scoreSpire->setString(String::createWithFormat("分数:%d", score)->_string);

			//游戏获胜的条件
			if (score > 999) {
				win();
			}

			setItem(enemy);

			enemy->removeFromParent();		//从层中移除
			enemyList.eraseObject(enemy);	//把鱼从记录中移除

			bloodbody->removeFromParent();  //血条从层中移除
			bloodListforPic.erase(bloodListforPic.begin() + i);//把血条从记录中移除

			bloodList.erase(bloodList.begin() + i);   //把鱼对应的血量的记录移除
			directionList.erase(directionList.begin() + i);   //把鱼对应的方向从记录中移除
			//移除后上一个对象会移到当前这个对象的位置，实际还是当前这个i，所以要i--才能访问到下一个对象
			i--;
		}
	}
}

void GameScene::keyPress(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		useKey = 1;

	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_S)
	{
		useKey = 2;

	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		useKey = 3;

	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		useKey = 4;

	}
	//return true;
}

void GameScene::keyRelease(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		useKey = 0;
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_S)
	{
		useKey = 0;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		useKey = 0;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		useKey = 0;
	}
	//return true;
}

void GameScene::playerGo(float t)
{
	if (useKey == 1)
	{
		if (man->getPositionY() < Director::getInstance()->getVisibleSize().height) {
			MoveBy *move = MoveBy::create(0.01f, Vec2(0, manfu.getSpeed()));
			auto callfunc = CallFunc::create(this, callfunc_selector(GameScene::eraseItem));
			man->runAction(Sequence::create(move, callfunc, NULL));
		}
	}

	else if (useKey == 2)
	{
		if (man->getPositionY() > 0) {
			MoveBy *move = MoveBy::create(0.01f, Vec2(0, -manfu.getSpeed()));
			auto callfunc = CallFunc::create(this, callfunc_selector(GameScene::eraseItem));
			man->runAction(Sequence::create(move, callfunc, NULL));
		}
	}
	else if (useKey == 3)
	{
		if (man->getPositionX() < Director::getInstance()->getVisibleSize().width) {
			MoveBy *move = MoveBy::create(0.01f, Vec2(manfu.getSpeed(), 0));
			auto callfunc = CallFunc::create(this, callfunc_selector(GameScene::eraseItem));
			man->runAction(Sequence::create(move, callfunc, NULL));
		}
	}
	else if (useKey == 4)
	{
		if (man->getPositionX() > 0) {
			MoveBy *move = MoveBy::create(0.01f, Vec2(-manfu.getSpeed(), 0));
			auto callfunc = CallFunc::create(this, callfunc_selector(GameScene::eraseItem));
			man->runAction(Sequence::create(move, callfunc, NULL));
		}
	}
}

// 设置掉落道具
void GameScene::setItem(Sprite* enemy) {

	// 掉落道具
	srand((unsigned)time(NULL));// 设置种子 

	int itemNum;
	if (enemy->getTag() == 104) {
		itemNum = rand() % 1;
		if (itemNum == 0) {
			auto item = Sprite::create("dropbomb2.png");
			item->setPosition(enemy->getPosition());
			this->addChild(item, 5);
			item->setTag(14);
			sp_file.insert(pair<int, string>(14, "dropbomb2.png"));
			items.push_back(item);
		}
	}
	else if (enemy->getTag() == 105) {
		itemNum = rand() % 1;
		if (itemNum == 0) {
			auto item = Sprite::create("hp.png");
			item->setPosition(enemy->getPosition());
			this->addChild(item, 5);
			item->setTag(15);
			sp_file.insert(pair<int, string>(15, "hp.png"));
			items.push_back(item);
		}
	}
	else if (enemy->getTag() == 106) {
		itemNum = rand() % 1;
		if (itemNum == 0) {
			auto item = Sprite::create("dropbomb2.png");
			item->setPosition(enemy->getPosition());
			this->addChild(item, 5);
			item->setTag(14);
			sp_file.insert(pair<int, string>(14, "dropbomb2.png"));
			items.push_back(item);
		}
	}

}

// 道具碰到人物后消除
void GameScene::eraseItem()
{
	for (vector<Sprite*>::iterator it = items.begin(); it != items.end();) {
		if (inIt(*it, man, sp_file[(*it)->getTag()], sp_file[man->getTag()])) {
			if ((*it)->getTag() == 15) {
				blood_for_man += 1;

				//更新数据
				auto scoreSpire = (Label *)this->getChildByTag(100);
				scoreSpire->setString(String::createWithFormat("HP:%d", blood_for_man)->_string);
			}
			else if ((*it)->getTag() == 14) {
				if (bombNum <= 4)
					bombNum++;

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
			this->removeChild(*it);
			it = items.erase(it);
		}
		else {
			++it;
		}
	}
}

//碰撞检测
bool GameScene::inIt(Node* node1, Node* node2, string src1, string src2) {
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

//创建文本显示
void GameScene::createLabel() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//显示血量
	auto label = cocos2d::Label::createWithSystemFont("HP:", "Arial", 24);
	label->setTag(100);
	label->setPosition(Vec2(0, visibleSize.height - label->getContentSize().height));
	label->setHorizontalAlignment(kCCTextAlignmentRight);
	label->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(label, 1);

	auto scoreSpire = (Label *)this->getChildByTag(100);
	scoreSpire->setString(String::createWithFormat("HP:%d", manfu.getBlood())->_string);

	//显示分数
	auto label2 = cocos2d::Label::createWithSystemFont("分数:0", "Arial", 24);
	label2->setTag(111);
	label2->setPosition(Vec2(0, visibleSize.height - 2 * label2->getContentSize().height));
	label2->setHorizontalAlignment(kCCTextAlignmentRight);
	label2->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(label2, 1);

	// 显示时间
	auto label3 = cocos2d::Label::createWithSystemFont("Time:10.0", "Arial", 24);
	label3->setTag(112);
	label3->setPosition(Vec2(0, visibleSize.height - 3 * label2->getContentSize().height));
	label3->setHorizontalAlignment(kCCTextAlignmentRight);
	label3->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(label3, 1);

	// 显示产生的鱼的个数
	auto label4 = cocos2d::Label::createWithSystemFont("CS：0", "Arial", 24);
	label4->setTag(113);
	label4->setPosition(Vec2(0, visibleSize.height - 4 * label2->getContentSize().height));
	label4->setHorizontalAlignment(kCCTextAlignmentRight);
	label4->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(label4, 1);

	//消灭的
	auto label5 = cocos2d::Label::createWithSystemFont("XM:0", "Arial", 24);
	label5->setTag(114);
	label5->setPosition(Vec2(0, visibleSize.height - 5 * label2->getContentSize().height));
	label5->setHorizontalAlignment(kCCTextAlignmentRight);
	label5->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(label5, 1);
}

//游戏结束
void GameScene::gameOver() {
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->stopAllEffects();
	GameOverScene::win_num = 0;
	auto scene = GameOverScene::createScene();
	auto gameOverScene = TransitionTurnOffTiles::create(1.0f, scene);
	CCTextureCache::sharedTextureCache()->removeAllTextures();
	Director::getInstance()->replaceScene(gameOverScene);
}

//游戏胜利
void GameScene::win() {
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->stopAllEffects();
	auto scene = GameOverScene::createScene();
	auto gameOverScene = TransitionTurnOffTiles::create(1.0f, scene);
	CCTextureCache::sharedTextureCache()->removeAllTextures();
	Director::getInstance()->replaceScene(gameOverScene);
}

// 超时失败
void GameScene::timeOut(float t) {
	costTime += t;

	// 更新时间
	auto leftTimeLabel = (Label *)this->getChildByTag(112);
	float leftTime = totalTime - costTime;
	if (leftTime < 0)
		leftTime = 0;
	leftTimeLabel->setString(String::createWithFormat("Time:%.1f", leftTime)->_string);

	if (costTime >= totalTime) {
		unscheduleAllSelectors();
		GameOverScene::win_num = 0;
		gameOver();
	}

}
//停止所有的定时器
void GameScene::stopAllSchedule()
{
	this->unscheduleAllSelectors();
}

// 暂停游戏
void GameScene::pauseGame()
{
	if (!isPause) {
		this->pause();
		isPause = true;
	}		
	else {
		this->resume();
		isPause = false;
	}
}

// 返回主页面
void GameScene::goHomePage()
{
	unscheduleAllSelectors();
	GameOverScene::win_num = 0;
	auto scene = HelloWorld::createScene();
	auto gameOverScene = TransitionTurnOffTiles::create(1.0f, scene);
	CCTextureCache::sharedTextureCache()->removeAllTextures();
	Director::getInstance()->replaceScene(gameOverScene);
}

// 是否使用音乐音效
void GameScene::soundUsing()
{
	if (!useBgm) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic("music/bgm.mp3", true);
		useBgm = true;
	}
	else {
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		useBgm = false;
	}
}