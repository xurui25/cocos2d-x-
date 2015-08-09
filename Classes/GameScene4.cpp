#include "GameScene4.h"
#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include "Man_1.h"
#include "Man_2.h"
#include "Man_3.h"
#include "Man.h"
#include "SimpleAudioEngine.h"


using namespace CocosDenshion;

USING_NS_CC;

Scene* GameScene4::createScene() {
	auto scene = Scene::createWithPhysics();
	auto layer = GameScene4::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene4::init() {
	if (!Layer::init()) {
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
	GameOverScene::win_num = 7;
	useKey = 0;     //初始化useKey
	score = 0;		//初始化Score
	type = 0;       //初始化type
	blood_for_man = manfu.getBlood();    //初始化血量
	speed_for_water = 4;  //初始化水流速度
	bombNum = 0; // 初始化大威力炸弹数量
	totalTime = 100; // 初始化总时长
	costTime = 0; // 初始化花去的时间
	GameScene2::bombnum = 1; // 初始化炸弹可以出现的数量
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
	createWater();

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

	// 创建暂停按钮,返回按钮和控制音乐按钮.
	auto btn3 = MenuItemImage::create("continue.png", "continue2.png", CC_CALLBACK_0(GameScene::pauseGame, this));
	auto btn4 = MenuItemImage::create("exit.png", "exit2.png", CC_CALLBACK_0(GameScene::goHomePage, this));
	auto btn5 = MenuItemImage::create("select_guan.png", "select_guan.png", CC_CALLBACK_0(GameScene::soundUsing, this));
	auto menu3 = Menu::create(btn3, btn4, btn5, NULL);
	menu3->alignItemsVerticallyWithPadding(30);
	menu3->setAnchorPoint(Vec2(0, 0));
	menu3->setPosition(visibleSize.width - 100, 500);
	this->addChild(menu3, 1);

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


	//创建人物
	man->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	man->setTag(3);
	man->setAnchorPoint(Vec2(0, 0));
	sp_file.insert(pair<int, string>(3, man_name));
	this->addChild(man, 5);

	//定时调用移动函数
	this->schedule(schedule_selector(GameScene4::objectMove), 0.01);

	//定时创建鱼
	this->schedule(schedule_selector(GameScene::enemyCreate), 0.5);

	//定时扫描判断水中的情况
	this->schedule(schedule_selector(GameScene3::WaterMove), 0.01);

	//按键移动
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

//鱼的移动并对炸弹的智能响应
void GameScene4::objectMove(float f) {
	int speedlist[100];
	memset(speedlist, 0, sizeof(speedlist));

	for (int i = 0; i < enemyList.size(); i++) {
		auto enemy = enemyList.at(i);
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
		speedlist[i] = speed;
	}

	//判断鱼是否在响应的范围类
	for (int j = 0; j < bombs.size(); j++) {
		auto boom = bombs.at(j);
		for (int i = 0; i < enemyList.size(); i++) {
			auto enemy = enemyList.at(i);
			auto Lspeed = speedlist[i];

			int speed;
			int num_ = enemy->getTag();

			if (num_ == 104) {
				speed = 3;
			}
			else if (num_ = 105) {
				speed = 2;
			}
			else if (num_ = 106) {
				speed = 1;
			}

			if (enemy->getPositionX() < boom->getPositionX() + 200 + boom->getContentSize().width / 2 && enemy->getPositionX() > boom->getPositionX() - 200 - boom->getContentSize().width / 2
				&& enemy->getPositionY() < boom->getPositionY() + 150 + boom->getContentSize().height / 2 && enemy->getPositionY() > boom->getPositionY() - 150 - boom->getContentSize().height / 2) {
				speed += 3;
			}

			if (speed > Lspeed) {
				speedlist[i] = speed;
			}
		}
	}

	for (int i = 0; i < enemyList.size(); i++)
	{
		auto enemy = enemyList.at(i);
		auto bloodbody = bloodListforPic.at(i);
		auto blood = bloodList.at(i);
		auto direction_ = directionList.at(i);
		
		int speed = speedlist[i];
		int num_ = enemy->getTag();
		
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
			enemy->setPositionX(enemy->getPositionX() - (int)(speed / 2));
			enemy->setPositionY(enemy->getPositionY() + (int)(speed / 2));
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
			bloodListforPic[i]->setPosition(Vec2(enemy->getPositionX() + enemy->getContentSize().width / 2 - bloodbody->getContentSize().width / 2, enemy->getPositionY() + int(enemy->getContentSize().height) + 1));
		}
		else if (blood == 2){
			if (changeOrNot[i] == 1) {
				//auto bloodBody1 = Sprite::create("blood_blue.png", CCRectMake(0, 0, 200, 12));
				bloodListforPic[i]->setScaleX(0.66);
			}
			bloodListforPic[i]->setPosition(Vec2(enemy->getPositionX() + enemy->getContentSize().width / 2 - bloodbody->getContentSize().width / 2, enemy->getPositionY() + int(enemy->getContentSize().height) + 1));
		}
		else {
			bloodListforPic[i]->setPosition(Vec2(enemy->getPositionX() + enemy->getContentSize().width / 2 - bloodbody->getContentSize().width / 2, enemy->getPositionY() + int(enemy->getContentSize().height) + 1));
		}

		changeOrNot[i] = 0;
		if (enemy->getPositionX() < -(enemy->getContentSize().width) || enemy->getPositionX() > (Director::getInstance()->getVisibleSize().width)
			|| enemy->getPositionY() < -(enemy->getContentSize().height) || enemy->getPositionY() > (Director::getInstance()->getVisibleSize().height))
		{
			enemy->removeFromParent();		//从层中移除
			enemyList.eraseObject(enemy);	//把鱼从记录中移除

			bloodbody->removeFromParent();  //血条从层中移除
			bloodListforPic.erase(bloodListforPic.begin() + i);//把血条从记录中移除

			//更新数据
			xm++;
			auto scoreSpire = (Label *)this->getChildByTag(114);
			scoreSpire->setString(String::createWithFormat("XM:%d", xm)->_string);

			bloodList.erase(bloodList.begin() + i);   //把鱼对应的血量的记录移除
			directionList.erase(directionList.begin() + i);   //把鱼对应的方向从记录中移除
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
