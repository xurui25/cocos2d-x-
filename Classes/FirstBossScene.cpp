#include "FirstBossScene.h"
#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include "ChooseGuan.h"
#include "Man_1.h"
#include "Man_2.h"
#include "Man_3.h"
#include "AppDelegate.h"
#include <iostream>
#include <string>

#pragma execution_character_set("utf-8")

USING_NS_CC;

int FirstBossScene::type_for_skill = 1;

Scene* FirstBossScene::createScene()
{
	// 	//������������ĳ���
	auto scene = Scene::createWithPhysics();
	auto layer = FirstBossScene::create();
	scene->addChild(layer);

	return scene;
}

bool FirstBossScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//���Խ����Ĺؿ�
	ChooseGuan::choosenum = 2;
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
	GameOverScene::win_num = 2;
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
	mSkillButton->setPosition(ccp(visibleSize.width - 50, 2*mSkillButton->getContentSize().height + 50));
	addChild(mSkillButton);
	mSkillButton->setTouchSpriteProtocol(this);

	//boss����
	this->schedule(schedule_selector(FirstBossScene::objectMove), 0.01);

	//boss�ƶ�
	this->schedule(schedule_selector(FirstBossScene::bossMove), 0.02);

	//��Ĵ���
	this->schedule(schedule_selector(FirstBossScene::enemyCreate), 1);

	//ը���ƶ�
	this->schedule(schedule_selector(FirstBossScene::bombsMove), 0.01);

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

//������ʱ�����øú��������������������ײ���
void FirstBossScene::onEnter()
{
	Layer::onEnter();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto listener = EventListenerPhysicsContact::create();

	listener->onContactBegin = [=](PhysicsContact& contact)
	{


		auto spriteA = (Sprite *)contact.getShapeA()->getBody()->getNode();
		auto spriteB = (Sprite *)contact.getShapeB()->getBody()->getNode();
		int tag1 = spriteA->getTag();
		int tag2 = spriteB->getTag();
		Vec2 vec1 = spriteA->getPosition();
		Vec2 vec2 = spriteB->getPosition();

		//������Ͳ�����ײ����ײ��
		if (tag1 + tag2 == 206) {
			blood_for_man--;

			if (blood_for_man < 0) {
				gameOver();
			}

			auto scoreSpire = (Label *)this->getChildByTag(100);
			scoreSpire->setString(String::createWithFormat("HP:%d", blood_for_man)->_string);

			auto * system = ParticleSystemQuad::create("particle_texture.plist");
			if (tag1 == 104) {
				system->setPosition(vec1);
				this->addChild(system);
				spriteA->removeFromParent();
			}
			else {
				system->setPosition(vec2);
				this->addChild(system);
				spriteB->removeFromParent();
			}
		}
		else if (tag1 + tag2 == 207) {//������Ϳ���ײ����ײ��
			Magic += 3;

			auto * system = ParticleSystemQuad::create("particle_texture.plist");
			if (tag1 == 105) {
				system->setPosition(vec1);
				this->addChild(system);
				spriteA->removeFromParent();
			}
			else {
				system->setPosition(vec2);
				this->addChild(system);
				spriteB->removeFromParent();
			}

			if (getTypeSkill() == 3) {
				manscale = manscale * 0.9;
				speed_for_man++;
				if (manscale < 0.4) {
					manscale = 0.4;
				}
				if (speed_for_man > 10) {
					speed_for_man = 10;
				}
				man->setScale(manscale);
			}
		}
		else if (tag1 + tag2 == 112) {//��Boss������һ����ʱ
			blood_for_boss -= weapon_eff;

			auto * system = ParticleSystemQuad::create("particle_texture.plist");
			if (tag1 == 1) {
				system->setPosition(vec1);
				this->addChild(system);
				spriteA->removeFromParent();
			}
			else {
				system->setPosition(vec2);
				this->addChild(system);
				spriteB->removeFromParent();
			}
			//����boss��Ѫ��
			auto scoreSpire = (Label *)this->getChildByTag(121);
			scoreSpire->setString(String::createWithFormat("HP:%d", blood_for_boss)->_string);

			if (blood_for_boss <= 0) {
				//����Ҫ��Bosss��������Ч
				win();
			}
		}
		else if (tag1 + tag2 == 113) {//��Boss������������ʱ
			blood_for_boss --;

			auto * system = ParticleSystemQuad::create("particle_texture.plist");
			if (tag1 == 2) {
				system->setPosition(vec1);
				this->addChild(system);
				spriteA->removeFromParent();
			}
			else {
				system->setPosition(vec2);
				this->addChild(system);
				spriteB->removeFromParent();
			}
			//����boss��Ѫ��
			auto scoreSpire = (Label *)this->getChildByTag(121);
			scoreSpire->setString(String::createWithFormat("HP:%d", blood_for_boss)->_string);

			if (blood_for_boss <= 0) {
				//����Ҫ��Bosss��������Ч
				win();
			}
		}

		return true;
	};

	//ע�������
	EventDispatcher * eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

//label�ļ���
void FirstBossScene::createLabel() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = cocos2d::Label::createWithSystemFont("HP:", "Arial", 24);
	label->setTag(100);
	label->setPosition(Vec2(0, origin.y + visibleSize.height - 24));
	label->setHorizontalAlignment(kCCTextAlignmentRight);
	label->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(label, 1);

	auto scoreSpire = (Label *)this->getChildByTag(100);
	scoreSpire->setString(String::createWithFormat("HP:%d", manfu.getBlood())->_string);

	auto label3 = cocos2d::Label::createWithSystemFont("HP:20", "Arial", 24);
	label3->setTag(121);
	label3->setPosition(Vec2(Director::getInstance()->getVisibleSize().width - 40, visibleSize.height - 24));
	label3->setHorizontalAlignment(kCCTextAlignmentRight);
	this->addChild(label3, 1);

}

//��������
void FirstBossScene::setRate(float f) {
	rate += 0.2;
}

float FirstBossScene::getRate() {
	return rate;
}

//�����ƶ�
void FirstBossScene::objectMove(float f) {
	for (int i = 0; i < enemyList.size(); i++)
	{
		auto enemy = enemyList.at(i);

		int speed = getRate();

		//�����ƶ�
		enemy->setPositionX(enemy->getPositionX() - speed);

		if (enemy->getPositionX() < -(enemy->getContentSize().width + 100))
		{
			enemy->removeFromParent();		//�Ӳ����Ƴ�
			enemyList.eraseObject(enemy);	//����Ӽ�¼���Ƴ�

			//�Ƴ�����һ��������Ƶ���ǰ��������λ�ã�ʵ�ʻ��ǵ�ǰ���i������Ҫi--���ܷ��ʵ���һ������
			i--;
		}
	}
}


//�������ƶ�
void FirstBossScene::bombsMove(float f) {
	for (int i = 0; i < bombs.size(); i++) {
		auto bomb = bombs.at(i);

		bomb->setPositionX(bomb->getPositionX() + 10);
		bombs_dis[i]--;
		if (bomb->getPositionX() > Director::getInstance()->getVisibleSize().width + 100 || bombs_dis[i] <= 0) {
			bomb->removeFromParent();
			bombs.eraseObject(bomb);

			bombs_dis.erase(bombs_dis.begin() + i);

			i--;
		}
	}
}

//��boss�ƶ�
void FirstBossScene::bossMove(float f) {
	if (boss->getPositionY() + boss->getContentSize().height > Director::getInstance()->getVisibleSize().height) {
		boss_move_up = false;
	}
	if (boss->getPositionY() - boss->getContentSize().height < 0) {
		boss_move_up = true;
	}

	if (boss_move_up) {
		boss->setPosition(boss->getPositionX(), boss->getPositionY() + 5);
	}
	else {
		boss->setPosition(boss->getPositionX(), boss->getPositionY() - 5);
	}
}

//����boss
void FirstBossScene::bossCreate() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	boss = Sprite::create("man1.png");
	boss->setPosition(visibleSize.width - boss->getContentSize().width, visibleSize.height / 2);
	boss->setTag(111);
	auto bossbody = PhysicsBody::createBox(boss->getContentSize());
	bossbody->setContactTestBitmask(0x0003);
	bossbody->setCategoryBitmask(0x0001);
	bossbody->setCollisionBitmask(0x0007);
	bossbody->setGravityEnable(false);
	bossbody->setDynamic(false);
	boss->setPhysicsBody(bossbody);
	this->addChild(boss, 5);
}

//�������������
void FirstBossScene::enemyCreate(float f)
{
	string src;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	int temp = rand() % 4;
	if (temp < 3) {
		src = "fish2.png";
	}
	else {
		src = "bomb2.png";
	}

	auto enemy = Sprite::create(src);
	if (src == "fish2.png") {
		enemy->setTag(104);
	}
	else {
		enemy->setTag(105);
	}

	//����Ļ�����ұ߳���
	enemy->setPosition(Vec2((Director::getInstance()->getVisibleSize().width - boss->getContentSize().width + 2),
			rand() % (int)(Director::getInstance()->getVisibleSize().height)));
	
	auto enemyBody = PhysicsBody::createBox(enemy->getContentSize());
	enemyBody->setContactTestBitmask(0x0003);
	enemyBody->setCategoryBitmask(0x0002);
	enemyBody->setCollisionBitmask(0x0001);
	enemyBody->setGravityEnable(false);
	enemy->setPhysicsBody(enemyBody);

	this->addChild(enemy, 2);
	this->enemyList.pushBack(enemy);
}

// �����Ļʱ�������¼������ƶ���
bool FirstBossScene::onTouchBegan(Touch *touch, Event *unused_event)
{

	// ��0.3��ʱ���ڽ����ƶ��������
	MoveTo *move = MoveTo::create(0.3f, touch->getLocation());
	man->runAction(move);

	return true;
}

//��������1
void FirstBossScene::setBomb()
{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		if (Magic > 0) {
			if (getTypeSkill() == 1) {//��һ��ħ��ģʽ,�������
				bomb = Sprite::create("boom_1.png");
				increase_for_dis = 60;
				Magic--;
			}
			else if (getTypeSkill() == 2) {//�ڶ���ħ��ģʽ,��������
				bomb = Sprite::create("boom_1.png");
				increase_for_weapon = 1;
				Magic--;
			}
			else {//������ħ���������䲻�ı�ը��
				bomb = Sprite::create("boom.png");
			}
		} else{
			bomb = Sprite::create("boom.png");
		}
		
		bomb->setTag(1);
		bomb->setPosition(man->getPositionX() + bomb->getContentSize().width + 1, man->getPositionY());

		//����������ײ����
		auto bombBody = PhysicsBody::createBox(bomb->getContentSize());
		bombBody->setContactTestBitmask(0x0003);
		bombBody->setCategoryBitmask(0x0002);
		bombBody->setCollisionBitmask(0x0001);
		bombBody->setGravityEnable(false);
		bomb->setPhysicsBody(bombBody);

		this->addChild(bomb, 2);
		bombs.pushBack(bomb);

		//���ը�������
		int distance_ = manfu.getDis() + increase_for_dis;
		//���ը��������
		weapon_eff = manfu.getPower() + increase_for_weapon;
		//��ʼ������
		increase_for_dis = 0;
		increase_for_weapon = 0;
		//����̴洢��vector�����ݽṹ��
		bombs_dis.push_back(distance_);
}

void FirstBossScene::setnull(Ref* ref) {

}

//��Ӧ�������
void FirstBossScene::CMTouchSpriteSelectSprite(SkillButton *button){
	//����ȴ�������¼�
	setBomb();
}

//������Ӧ
void FirstBossScene::keyPress(EventKeyboard::KeyCode keyCode, Event* event)
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

void FirstBossScene::keyRelease(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		useKey = 0;
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_S)
	{
		useKey = 0;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		useKey = 0;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		useKey = 0;
	}
	//return true;
}
//�����ƶ�
void FirstBossScene::playerGo(float t)
{
	if (useKey == 1)
	{
		if (man->getPositionY() < Director::getInstance()->getVisibleSize().height) {
			MoveBy *move = MoveBy::create(0.01f, Vec2(0, speed_for_man));
			man->runAction(move);
		}
	}

	else if (useKey == 2)
	{
		if (man->getPositionY() > 0) {
			MoveBy *move = MoveBy::create(0.01f, Vec2(0, -speed_for_man));
			man->runAction(move);
		}
	}
	else if (useKey == 3)
	{
		if (man->getPositionX() < 2 * Director::getInstance()->getVisibleSize().width / 3 + 10) {
			MoveBy *move = MoveBy::create(0.01f, Vec2(speed_for_man, 0));
			man->runAction(move);
		}
	}
	else if (useKey == 4)
	{
		if (man->getPositionX() > 0) {
			MoveBy *move = MoveBy::create(0.01f, Vec2(-speed_for_man, 0));
			man->runAction(move);
		}
	}
}

//���á����ǿ������
void FirstBossScene::setTypeSkill(int i) {
	type_for_skill = i;
}

int FirstBossScene::getTypeSkill() {
	return type_for_skill;
}

//��Ϸ����
void FirstBossScene::gameOver() {
	GameOverScene::win_num = 0;
	auto scene = GameOverScene::createScene();
	auto gameOverScene = TransitionTurnOffTiles::create(1.0f, scene);
	Director::getInstance()->replaceScene(gameOverScene);
}

void FirstBossScene::win() {

	if (ChooseGuan::choosenum == 2) {
		// �����ڶ���
		ChooseGuan::canChoose2 = true;
		UserDefault::getInstance()->setBoolForKey("canChoose2", true);
	}
	else if (ChooseGuan::choosenum == 3) {
		// ����������
		ChooseGuan::canChoose3 = true;
		UserDefault::getInstance()->setBoolForKey("canChoose3", true);
	}
	else if (ChooseGuan::choosenum == 4) {
		// �������Ĺ�
		ChooseGuan::canChoose4 = true;
		UserDefault::getInstance()->setBoolForKey("canChoose4", true);
	}
	else if (ChooseGuan::choosenum == 5) {
		// ���������
		ChooseGuan::canChoose5 = true;
		UserDefault::getInstance()->setBoolForKey("canChoose5", true);
	}

	auto scene = GameOverScene::createScene();
	auto gameOverScene = TransitionTurnOffTiles::create(1.0f, scene);
	Director::getInstance()->replaceScene(gameOverScene);
}

//ֹͣ���еĶ�ʱ��
void FirstBossScene::stopAllSchedule()
{
	this->unscheduleAllSelectors();
}