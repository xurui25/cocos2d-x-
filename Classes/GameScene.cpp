#include "GameScene.h"
#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include "Man_1.h"
#include "Man_2.h"
#include "Man_3.h"
#include <iostream>
#include <string>

#pragma execution_character_set("utf-8")

USING_NS_CC;

Scene* GameScene::createScene()
{
	// 	//创建物理世界的场景
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
	GameOverScene::win_num = 1;
	useKey = 0;     //初始化useKey
	score = 0;		//初始化Score
	type = 0;       //初始化type
	blood_for_man = manfu.getBlood();    //初始化血量


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
	menu->setPosition(visibleSize.width - 50, 2*btn1->getContentSize().height);
	this->addChild(menu, 1);
	
	//创建人物及设置物理碰撞
	
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

	return true;
}

//层进入的时候会调用该函数，进行物理世界的碰撞检测
void GameScene::onEnter()
{
	Layer::onEnter();
}

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
				auto bloodBody1 = Sprite::create("blood_blue.png", CCRectMake(0, 0, 100, 12));
				bloodListforPic[i]->setScaleX(0.5);

			}
			bloodListforPic[i]->setPosition(Vec2(enemy->getPositionX(), enemy->getPositionY() + int(enemy->getContentSize().height / 2) + 1));
		}
		else if (blood == 2){
			if (changeOrNot[i] == 1) {
				auto bloodBody1 = Sprite::create("blood_blue.png", CCRectMake(0, 0, 200, 12));
				bloodListforPic[i]->setScaleX(0.66);
			}
			bloodListforPic[i]->setPosition(Vec2(enemy->getPositionX(), enemy->getPositionY() + int(enemy->getContentSize().height / 2) + 1));
		}
		else {
			bloodListforPic[i]->setPosition(Vec2(enemy->getPositionX(), enemy->getPositionY() + int(enemy->getContentSize().height / 2) + 1));
		}

		changeOrNot[i] = 0;
		if (enemy->getPositionX() < -(enemy->getContentSize().width + 100) || enemy->getPositionX() > (Director::getInstance()->getVisibleSize().width + enemy->getContentSize().width + 100)
			||enemy->getPositionY() < -(enemy->getContentSize().height + 100) || enemy->getPositionY() > (Director::getInstance()->getVisibleSize().height + enemy->getContentSize().height + 100))
		{
			enemy->removeFromParent();		//从层中移除
			enemyList.eraseObject(enemy);	//把鱼从记录中移除

			bloodbody->removeFromParent();  //血条从层中移除
			bloodListforPic.erase(bloodListforPic.begin()+i);//把血条从记录中移除

			bloodList.erase(bloodList.begin()+i);   //把鱼对应的血量的记录移除
			directionList.erase(directionList.begin()+i);   //把鱼对应的方向从记录中移除
			//移除后上一个对象会移到当前这个对象的位置，实际还是当前这个i，所以要i--才能访问到下一个对象
			i--;
		}
		else if (enemy->getTag() == 104) {		//判断是否和人碰撞且进行处理
			if (inIt(enemy, man)) {
				blood_for_man--;

				if (blood_for_man <= 0) {
					gameOver();
				}
				//使用粒子系统
				auto * system = ParticleSystemQuad::create("particle_texture.plist");
				system->setPosition(enemy->getPositionX(), enemy->getPositionY());
				this->addChild(system);

				enemy->removeFromParent();		//从层中移除
				enemyList.eraseObject(enemy);	//把鱼从记录中移除

				bloodbody->removeFromParent();  //血条从层中移除
				bloodListforPic.erase(bloodListforPic.begin() + i);//把血条从记录中移除

				//更新数据
				auto scoreSpire = (Label *)this->getChildByTag(100);
				scoreSpire->setString(String::createWithFormat("HP:%d", blood_for_man)->_string);
			}
		}
	}
}

void GameScene::enemyCreate(float f)
{
	string src;
	int blood;
	int director_;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	int temp = rand() % 3;
	if (temp == 0) {
		src = "fish2.png";
		blood = 1;
	}
	else if (temp == 1) {
		src = "fish1.png";
		blood = 2;
	}
	else {
		src = "fish3.png";
		blood = 3;
	}

	auto enemy = Sprite::create(src);
	if (src == "fish2.png") {
		enemy->setTag(104);
	}
	else if (src == "fish1.png") {
		enemy->setTag(105);
	}
	else {
		enemy->setTag(106);
	}
	//srand(time(NULL));
	director_ = rand() % 12;
	if (director_ == 0) {
		//在屏幕的最右边出现
		enemy->setPosition(Vec2((Director::getInstance()->getVisibleSize().width + enemy->getContentSize().width), 
			rand() % (int)(Director::getInstance()->getVisibleSize().height)));
	}
	else if (director_ == 1) {
		//在屏幕的最左边出现
		enemy->setPosition(Vec2((-enemy->getContentSize().width), 
			rand() % (int)(Director::getInstance()->getVisibleSize().height)));
	}
	else if (director_ == 2) {
		//在屏幕的最上边出现
		enemy->setPosition(Vec2((rand() % (int)(Director::getInstance()->getVisibleSize().width)),
			(Director::getInstance()->getVisibleSize().height + enemy->getContentSize().height)));
	}
	else if (director_ == 3){
		//在屏幕的最下方出现
		enemy->setPosition(Vec2((rand() % (int)(Director::getInstance()->getVisibleSize().width)),
			-enemy->getContentSize().height));
	}
	else if (director_ == 4) {
		//在屏幕的右边的下方出现
		enemy->setPosition(Vec2((Director::getInstance()->getVisibleSize().width + enemy->getContentSize().width),
			rand() % (int)(Director::getInstance()->getVisibleSize().height / 2)));
	}
	else if (director_ == 5) {
		//在屏幕的左边的下方出现
		enemy->setPosition(Vec2((-enemy->getContentSize().width),
			rand() % (int)(Director::getInstance()->getVisibleSize().height / 2)));
	}
	else if (director_ == 6) {
		//在屏幕的右边的上方出现
		enemy->setPosition(Vec2((Director::getInstance()->getVisibleSize().width + enemy->getContentSize().width),
			rand() % (int)(Director::getInstance()->getVisibleSize().height / 2) +(int)(Director::getInstance()->getVisibleSize().height / 2)));
	}
	else if (director_ == 7) {
		//在屏幕的左边的上方出现
		enemy->setPosition(Vec2((-enemy->getContentSize().width),
			rand() % (int)(Director::getInstance()->getVisibleSize().height / 2) + (int)(Director::getInstance()->getVisibleSize().height / 2)));

	}
	else if (director_ == 8) {
		//在屏幕的上方的右边出现
		enemy->setPosition(Vec2((rand() % (int)(Director::getInstance()->getVisibleSize().width / 2) + (int)(Director::getInstance()->getVisibleSize().width / 2)),
			(Director::getInstance()->getVisibleSize().height + enemy->getContentSize().height)));
	}
	else if (director_ == 9) {
		//在屏幕的上方的左边出现
		enemy->setPosition(Vec2((rand() % (int)(Director::getInstance()->getVisibleSize().width / 2)),
			(Director::getInstance()->getVisibleSize().height + enemy->getContentSize().height)));

	}
	else if (director_ == 10) {
		//在屏幕的下方的右边出现
		enemy->setPosition(Vec2((rand() % (int)(Director::getInstance()->getVisibleSize().width / 2) + (int)(Director::getInstance()->getVisibleSize().width / 2)),
			-enemy->getContentSize().height));
	}
	else {
		//在屏幕的下方的左边出现
		enemy->setPosition(Vec2((rand() % (int)(Director::getInstance()->getVisibleSize().width / 2)),
			-enemy->getContentSize().height));

	}
	if (temp == 0) {
		auto enemyBody = PhysicsBody::createBox(enemy->getContentSize());
		enemyBody->setContactTestBitmask(0x0003);
		enemyBody->setCategoryBitmask(0x0002);
		enemyBody->setCollisionBitmask(0x0001);
		enemyBody->setGravityEnable(false);
		enemy->setPhysicsBody(enemyBody);
	}
	this->addChild(enemy);
	this->enemyList.pushBack(enemy);
	this->bloodList.push_back(blood);
	this->directionList.push_back(director_);
	this->changeOrNot.push_back(0);

	int x1, y1;
	if (enemy->getTag() == 104) {
		x1 = 100;
		y1 = 12;
	}
	else if (enemy->getTag() == 105) {
		x1 = 200;
		y1 = 12;
	}
	else if (enemy->getTag() == 106) {
		x1 = 300;
		y1 = 12;
	}
	auto bloodBody = Sprite::create("blood_blue.png", CCRectMake(0,0,x1,y1));
	//bloodBody->setPosition(Vec2(enemy->getPositionX(), enemy->getPositionY() + enemy->getContentSize().height + 50));
	this->addChild(bloodBody);
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
	if (bombs.size() < 4) {
		bomb = Sprite::create("boom.png");
		bomb->setTag(1);
		bomb->setPosition(man->getPosition());
		bomb->setAnchorPoint(Vec2(0.5, 0.5));
		this->addChild(bomb, 1);
		bombs.push_back(bomb);
	}

	schedule(schedule_selector(GameScene::eraseBomb), 0.2f);
}

void GameScene::setBomb2(Ref* ref)
{
	if (bombs.size() < 4) {
		bomb = Sprite::create("boom2.png");
		bomb->setTag(2);
		bomb->setPosition(man->getPosition());
		bomb->setAnchorPoint(Vec2(0.5, 0.5));
		this->addChild(bomb, 1);
		bombs.push_back(bomb);
	}

	schedule(schedule_selector(GameScene::eraseBomb), 0.5f);

}

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
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					temp[count] = Sprite::create("b1.png");
					temp[count]->setPosition(pos.x + bombSize.width * i, pos.y + bombSize.height * j);
					this->addChild(temp[count], 2);
					temp[count]->runAction(Sequence::create(DelayTime::create(0.4f), Hide::create(), NULL));
					count++;
				}
			}

			type = 1;
			BombAndFish();
		}
		else if ((*i)->getTag() == 2)
		{
			Sprite* temp[25];
			int count = 0;
			for (int i = -2; i <= 2; i++)
			{
				for (int j = -2; j <= 2; j++)
				{
					temp[count] = Sprite::create("b2.png");
					temp[count]->setPosition(pos.x + bombSize.width * i, pos.y + bombSize.height * j);
					this->addChild(temp[count], 2);
					temp[count]->runAction(Sequence::create(DelayTime::create(0.4f), Hide::create(), NULL));
					count++;
				}
			}
			type = 2;
			BombAndFish();

		}

		this->removeChild(*i);
		bombs.erase(i);
	}

	if (bombs.empty())
	{
		unschedule(schedule_selector(GameScene::eraseBomb));
	}
}

void GameScene::BombAndFish() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	for (int i = 0; i < enemyList.size(); i++)
	{
		auto enemy = enemyList.at(i);
		auto bloodbody = bloodListforPic.at(i);

		Size bombSize = bombs[0]->getContentSize();

		int x = enemy->getPositionX();
		int y = enemy->getPositionY();
		int xwidth = enemy->getPositionX() + enemy->getContentSize().width;
		int yheight = enemy->getPositionY() + enemy->getContentSize().height;

		if (type == 1) {
			int xmin, xmax, ymin, ymax;
			//获取炸弹x轴的范围
			xmin = max(int(curx - bombSize.width), 0);
			xmax = min(int(curx + 2*bombSize.width), int(visibleSize.width));
			//获取炸弹y轴的范围
			ymin = max(int(cury - bombSize.height), 0);
			ymax = min(int(cury + 2*bombSize.height), int(visibleSize.height));

			int wid = (xmax - xmin) / 6;
			int hei = (ymax - ymin) / 6;

			if ((x >= curx - wid && x <= curx + wid && y <= ymax && y >= ymin) ||
				(x >= xmin && x <= xmax && y >= cury - hei && y <= cury + hei)) {
				bloodList[i] -= manfu.getPower();
				changeOrNot[i] = 1;
			}
		}
		else if (type == 2) {
			int xmin, xmax, ymin, ymax;
			//获取炸弹x轴的范围
			xmin = max(int(curx - 2*bombSize.width), 0);
			xmax = min(int(curx + 3*bombSize.width), int(visibleSize.width));
			//获取炸弹y轴的范围
			ymin = max(int(cury - 2*bombSize.height), 0);
			ymax = min(int(cury + 3*bombSize.height), int(visibleSize.height));

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
			items.push_back(item);
		}
	}

}

// 道具碰到人物后消除
void GameScene::eraseItem()
{
	for (vector<Sprite*>::iterator it = items.begin(); it != items.end();) {
		if (inIt(*it, man)) {
			if ((*it)->getTag() == 15) {
				blood_for_man += 1;
			}
			else if ((*it)->getTag() == 14) {
				bombNum += 1;
			}
			this->removeChild(*it);
			it = items.erase(it);

		}
		else {
			++it;
		}
	}
}

bool GameScene::inIt(Node* node1, Node* node2) {
	Point a = node2->getPosition();
	//左下角顶点
	if (isIn(node1, a)) {
		return true;
	}
	//右下角顶点
	Point a1 = Vec2(a.x + node2->getContentSize().width, a.y);
	if (isIn(node1, a1)) {
		return true;
	}
	//左上角顶点
	Point a2 = Vec2(a.x, a.y + node2->getContentSize().height);
	if (isIn(node1, a2)) {
		return true;
	}
	//右上角顶点
	Point a3 = Vec2(a.x + node2->getContentSize().width, a.y + node2->getContentSize().height);
	if (isIn(node1, a3)) {
		return true;
	}

	return false;
}

bool GameScene::isIn(Node* node1, Point a) {
	if (a.x > node1->getPositionX() && a.x < node1->getPositionX() + node1->getContentSize().width
		&& a.y > node1->getPositionY() && a.y < node1->getPositionY() + node1->getContentSize().height) {
		return true;
	}
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
}

//游戏结束
void GameScene::gameOver() {
	GameOverScene::win_num = 0;
	auto scene = GameOverScene::createScene();
	auto gameOverScene = TransitionTurnOffTiles::create(1.0f, scene);
	Director::getInstance()->replaceScene(gameOverScene);
}

//游戏胜利
void GameScene::win() {
	auto scene = GameOverScene::createScene();
	auto gameOverScene = TransitionTurnOffTiles::create(1.0f, scene);
	Director::getInstance()->replaceScene(gameOverScene);
}

//停止所有的定时器
void GameScene::stopAllSchedule()
{
	this->unscheduleAllSelectors();
}