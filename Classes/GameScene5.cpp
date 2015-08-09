#include "GameScene5.h"
#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include "Man_1.h"
#include "Man_2.h"
#include "Man_3.h"
#include "Man.h"
#include "SimpleAudioEngine.h"


using namespace CocosDenshion;

USING_NS_CC;

Scene* GameScene5::createScene() {
	auto scene = Scene::createWithPhysics();
	auto layer = GameScene5::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene5::init() {
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
		man_name = "chooseman1.png";
	}
	else {
		manfu = Man_3();
		man = Sprite::create("chooseman3.png");
		man_name = "chooseman1.png";
	}
	GameOverScene::win_num = 9;
	useKey = 0;     //��ʼ��useKey
	score = 0;		//��ʼ��Score
	type = 0;       //��ʼ��type
	blood_for_man = manfu.getBlood();    //��ʼ��Ѫ��
	speed_for_water = 4;  //��ʼ��ˮ���ٶ�
	bombNum = 0; // ��ʼ��������ը������
	totalTime = 100; // ��ʼ����ʱ��
	costTime = 0; // ��ʼ����ȥ��ʱ��
	GameScene2::bombnum = 1; // ��ʼ��ը�����Գ��ֵ�����
	cs = 0;
	xm = 0;
	isPause = false;
	useBgm = true;


	// Ԥ�������֡���Ч
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/bgm.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/boom.mp3");
	// ���ű�������
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/bgm.mp3", true);

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

	//����ˮ��
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

	// ������ͣ��ť,���ذ�ť�Ϳ������ְ�ť.
	auto btn3 = MenuItemImage::create("continue.png", "continue2.png", CC_CALLBACK_0(GameScene::pauseGame, this));
	auto btn4 = MenuItemImage::create("exit.png", "exit2.png", CC_CALLBACK_0(GameScene::goHomePage, this));
	auto btn5 = MenuItemImage::create("select_guan.png", "select_guan.png", CC_CALLBACK_0(GameScene::soundUsing, this));
	auto menu3 = Menu::create(btn3, btn4, btn5, NULL);
	menu3->alignItemsVerticallyWithPadding(30);
	menu3->setAnchorPoint(Vec2(0, 0));
	menu3->setPosition(visibleSize.width - 100, 500);
	this->addChild(menu3, 1);

	//Ԥ�Ƚ����ͼƬ���������
	spriteTexture1 = CCSpriteBatchNode::create("fish2.png");
	spriteTexture1->setPosition(Vec2(0, 0));
	addChild(spriteTexture1, 2);
	spriteTexture2 = CCSpriteBatchNode::create("fish1.png");
	spriteTexture2->setPosition(Vec2(0, 0));
	addChild(spriteTexture2, 2);
	spriteTexture3 = CCSpriteBatchNode::create("fish3.png");
	spriteTexture3->setPosition(Vec2(0, 0));
	addChild(spriteTexture3, 2);


	//��������
	man->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	man->setTag(3);
	man->setAnchorPoint(Vec2(0, 0));
	sp_file.insert(pair<int, string>(3, man_name));
	this->addChild(man, 5);

	//��ʾը��
	auto label6 = cocos2d::Label::createWithSystemFont("NUM:1", "Arial", 24);
	label6->setTag(117);
	label6->setPosition(Vec2(0, visibleSize.height - 6 * label6->getContentSize().height));
	label6->setHorizontalAlignment(kCCTextAlignmentRight);
	label6->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(label6, 1);

	//����������
	createMachine();

	//��ʱ�����ƶ�����
	this->schedule(schedule_selector(GameScene4::objectMove), 0.01);

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

	schedule(schedule_selector(GameScene5::playerGo), 0.01f);

	schedule(schedule_selector(GameScene5::MachineMove), 0.5f);

	schedule(schedule_selector(GameScene5::MachineBomb), 0.5f);

	return true;
}

//����������
void GameScene5::createMachine() {
	Machine = Sprite::create("Machine.png");
	Machine->setPosition(man->getPositionX() - man->getContentSize().width, man->getPositionY());
	Machine->setTag(6);
	Machine->setAnchorPoint(Vec2(0, 0));
	sp_file.insert(pair<int, string>(6, "Machine.png"));
	this->addChild(Machine, 5);
}

//�����˵��ƶ�
void GameScene5::MachineMove(float f) {
	if (Machine->getPositionX() < man->getPositionX() && Machine->getPositionY() <= man->getPositionY()) {
		Machine->setPosition(Vec2(Machine->getPositionX(), Machine->getPositionY() + man->getContentSize().height));
	}
	else if (Machine->getPositionX() <= man->getPositionX() && Machine->getPositionY() > man->getPositionY()) {
		Machine->setPosition(Vec2(Machine->getPositionX() + man->getContentSize().width, Machine->getPositionY()));
	}
	else if (Machine->getPositionX() > man->getPositionX() && Machine->getPositionY() >= man->getPositionY()) {
		Machine->setPosition(Vec2(Machine->getPositionX(), Machine->getPositionY() - man->getContentSize().height));
	}
	else if (Machine->getPositionX() >= man->getPositionX() && Machine->getPositionY() < man->getPositionY()) {
		Machine->setPosition(Vec2(Machine->getPositionX() - man->getContentSize().width, Machine->getPositionY()));
	}
}

//���Ｐ������˵��ƶ�
void GameScene5::playerGo(float t)
{
	if (useKey == 1)
	{
		if (man->getPositionY() < Director::getInstance()->getVisibleSize().height) {
			MoveBy *move = MoveBy::create(0.01f, Vec2(0, manfu.getSpeed()));
			auto callfunc = CallFunc::create(this, callfunc_selector(GameScene::eraseItem));
			man->runAction(Sequence::create(move, callfunc, NULL));
			//Machine->runAction(Sequence::create(move, NULL));
		}
	}

	else if (useKey == 2)
	{
		if (man->getPositionY() > 0) {
			MoveBy *move = MoveBy::create(0.01f, Vec2(0, -manfu.getSpeed()));
			auto callfunc = CallFunc::create(this, callfunc_selector(GameScene::eraseItem));
			man->runAction(Sequence::create(move, callfunc, NULL));
			//Machine->runAction(Sequence::create(move, NULL));
		}
	}
	else if (useKey == 3)
	{
		if (man->getPositionX() < Director::getInstance()->getVisibleSize().width) {
			MoveBy *move = MoveBy::create(0.01f, Vec2(manfu.getSpeed(), 0));
			auto callfunc = CallFunc::create(this, callfunc_selector(GameScene::eraseItem));
			man->runAction(Sequence::create(move, callfunc, NULL));
			//Machine->runAction(Sequence::create(move, NULL));
		}
	}
	else if (useKey == 4)
	{
		if (man->getPositionX() > 0) {
			MoveBy *move = MoveBy::create(0.01f, Vec2(-manfu.getSpeed(), 0));
			auto callfunc = CallFunc::create(this, callfunc_selector(GameScene::eraseItem));
			man->runAction(Sequence::create(move, callfunc, NULL));
			//Machine->runAction(Sequence::create(move, NULL));
		}
	}
}

//�����˷���ը��
void GameScene5::MachineBomb(float f) {
	int temp = rand() % 8;

	if (temp == 0) {
		//���ӿ��Է���ը��������
		GameScene2::bombnum++;
		//��������
		auto scoreSpire = (Label *)this->getChildByTag(117);
		scoreSpire->setString(String::createWithFormat("NUM:%d", bombnum)->_string);
		//����ը��
		bomb = Sprite::create("boom.png");
		bomb->setTag(1);
		sp_file.insert(pair<int, string>(1, "boom.png"));
		bomb->setPosition(Machine->getPosition());
		bomb->setAnchorPoint(Vec2(0, 0));
		this->addChild(bomb, 1);
		bombs.push_back(bomb);
		
		schedule(schedule_selector(GameScene::eraseBomb), 0.5f);
		scheduleOnce(schedule_selector(GameScene5::MachineReduc), 0.01f);
	}
}

//���ٿ��Է���ը��������
void GameScene5::MachineReduc(float f) {
	GameScene2::bombnum--;
	auto scoreSpire = (Label *)this->getChildByTag(117);
	scoreSpire->setString(String::createWithFormat("NUM:%d", bombnum)->_string);
}

