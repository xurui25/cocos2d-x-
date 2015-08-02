#include "TranScene.h"
#include "SecondBossScene.h"
#include "FirstBossScene.h"
#include "ThirdBossScene.h"
#include "FourthBossScene.h"

USING_NS_CC;

int Checkpoint;

Scene* TranScene::createScene(int i)
{
	auto scene = Scene::create();
	auto layer = TranScene::create();
	scene->addChild(layer);

	Checkpoint = i;
	return scene;
}

// on "init" you need to initialize your instance
bool TranScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//初始化
	word_num = 0;


	//背景精灵
	auto bg1 = Sprite::create("background.jpg");
	//为适应屏幕进行缩放
	bg1->setScaleX((float)visibleSize.width / (float)bg1->getContentSize().width);
	bg1->setScaleY((float)visibleSize.height / (float)bg1->getContentSize().height);
	bg1->setPosition(Vec2(origin.x + visibleSize.width / 2, 0));
	bg1->setAnchorPoint(Vec2(0.5, 0));
	bg1->setTag(101);
	this->addChild(bg1, 0);

	auto MagicItem = MenuItemImage::create("boom.png", "boom_1.png",
		CC_CALLBACK_1(TranScene::menuTouch, this));
	MagicItem->setPosition(Vec2(visibleSize.width - MagicItem->getContentSize().width - 20, MagicItem->getContentSize().height * 2));
	MagicItem->setAnchorPoint(Vec2(0.5, 0.5));
	//MagicItem->setTag(102);
	auto menu = Menu::create(MagicItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	createLabel();

	return true;
}

void TranScene::menuTouch(Ref* pSender) {
	word_num++;
	createLabel();
}

void TranScene::buttonShow() {
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto Magic1Item = MenuItemImage::create("distance.png", "distance2.png",
		CC_CALLBACK_1(TranScene::menuMagic1Callback, this));
	Magic1Item->setPosition(Vec2(visibleSize.width / 2 - Magic1Item->getContentSize().width - 50, 120));
	auto Magic2Item = MenuItemImage::create("power.png", "power2.png",
		CC_CALLBACK_1(TranScene::menuMagic2Callback, this));
	Magic2Item->setPosition(Vec2(visibleSize.width / 2, 120));
	auto Magic3Item = MenuItemImage::create("man.png", "man2.png",
		CC_CALLBACK_1(TranScene::menuMagic3Callback, this));
	Magic3Item->setPosition(Vec2(visibleSize.width / 2 + Magic1Item->getContentSize().width + 50, 120));
	auto menu = Menu::create(Magic1Item, Magic2Item, Magic3Item, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}

void TranScene::createLabel() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	if (word_num == 0) {
		str = Sprite::create("wenzi.png");
		str->setPosition(Vec2(str->getContentSize().width / 2, visibleSize.height - str->getContentSize().height));
		addChild(str, 1);
	}
	else if (word_num == 1) {
		str1 = Sprite::create("shaonian1.png");
		str1->setPosition(Vec2(visibleSize.width - str->getContentSize().width / 2 + 100, visibleSize.height - str->getContentSize().height - str1->getContentSize().height));
		addChild(str1, 1);
	}
	else if (word_num == 2) {
		str->removeFromParent();
		removeChildByName("wenzi.png");
		str = Sprite::create("wenzi2.png");
		str->setPosition(Vec2(str->getContentSize().width / 2, visibleSize.height - str->getContentSize().height));
		addChild(str, 1);
	}
	else if (word_num == 3) {
		str1->removeFromParent();
		removeChildByName("shaonian1.png");
		str1 = Sprite::create("shaonian2.png");
		str1->setPosition(Vec2(visibleSize.width - str->getContentSize().width / 2 + 100, visibleSize.height - str->getContentSize().height - str1->getContentSize().height - 50));
		addChild(str1, 1);
	}
	else if (word_num == 4) {
		str->removeFromParent();
		removeChildByName("wenzi2.png");
		str = Sprite::create("wenzi3.png");
		str->setPosition(Vec2(str->getContentSize().width / 2, visibleSize.height - str->getContentSize().height));
		addChild(str, 1);
	}
	else if (word_num == 5) {
		str1->removeFromParent();
		removeChildByName("shaonian2.png");
		str1 = Sprite::create("shaonian3.png");
		str1->setPosition(Vec2(visibleSize.width - str->getContentSize().width / 2 + 100, visibleSize.height - str->getContentSize().height - str1->getContentSize().height - 50));
		addChild(str1, 1);
	}
	else if (word_num == 6) {
		str->removeFromParent();
		removeChildByName("wenzi3.png");
		str = Sprite::create("wenzi4.png");
		str->setPosition(Vec2(str->getContentSize().width / 2, visibleSize.height - str->getContentSize().height));
		addChild(str, 1);
	}
	else if (word_num == 7) {
		str1->removeFromParent();
		removeChildByName("shaonian3.png");
		str1 = Sprite::create("shaonian4.png");
		str1->setPosition(Vec2(visibleSize.width - str->getContentSize().width / 2 + 100, visibleSize.height - str->getContentSize().height - str1->getContentSize().height - 50));
		addChild(str1, 1);
	}
	else if (word_num == 8) {
		str->removeFromParent();
		removeChildByName("wenzi4.png");
		str = Sprite::create("wenzi5.png");
		str->setPosition(Vec2(str->getContentSize().width / 2, visibleSize.height - str->getContentSize().height));
		addChild(str, 1);
	}
	else if (word_num == 9) {
		str1->removeFromParent();
		removeChildByName("shaonian4.png");
		str1 = Sprite::create("shaonian5.png");
		str1->setPosition(Vec2(visibleSize.width - str->getContentSize().width / 2 + 100, visibleSize.height - str->getContentSize().height - str1->getContentSize().height - 50));
		addChild(str1, 1);
	}
	else if (word_num == 10) {
		str->removeFromParent();
		removeChildByName("wenzi5.png");
		str = Sprite::create("wenzi6.png");
		str->setPosition(Vec2(str->getContentSize().width / 2, visibleSize.height - str->getContentSize().height));
		addChild(str, 1);
	}
	else if (word_num == 11) {
		str1->removeFromParent();
		removeChildByName("shaonian5.png");
		str1 = Sprite::create("shaonian6.png");
		str1->setPosition(Vec2(visibleSize.width - str->getContentSize().width / 2 + 100, visibleSize.height - str->getContentSize().height - str1->getContentSize().height - 50));
		addChild(str1, 1);
	}
	else if (word_num == 12){
		buttonShow();
	}
}

void TranScene::menuMagic1Callback(Ref* pSender)
{
	FirstBossScene::type_for_skill = 1;
	if (Checkpoint == 1) {
		auto scene = FirstBossScene::createScene();
		auto gameScene = TransitionSlideInR::create(1.0f, scene);
		Director::getInstance()->replaceScene(gameScene);
	}
	else if (Checkpoint == 2) {
		auto scene = SecondBossScene::createScene();
		auto gameScene = TransitionSlideInR::create(1.0f, scene);
		Director::getInstance()->replaceScene(gameScene);
	}
	else if (Checkpoint == 3) {
		auto scene = ThirdBossScene::createScene();
		auto gameScene = TransitionSlideInR::create(1.0f, scene);
		Director::getInstance()->replaceScene(gameScene);
	}
	else if (Checkpoint == 4) {
		auto scene = FourthBossScene::createScene();
		auto gameScene = TransitionSlideInR::create(1.0f, scene);
		Director::getInstance()->replaceScene(gameScene);
	}
}

void TranScene::menuMagic2Callback(Ref* pSender) {
	FirstBossScene::type_for_skill = 2;
	if (Checkpoint == 1) {
		auto scene = FirstBossScene::createScene();
		auto gameScene = TransitionSlideInR::create(1.0f, scene);
		Director::getInstance()->replaceScene(gameScene);
	}
	else if (Checkpoint == 2) {
		auto scene = SecondBossScene::createScene();
		auto gameScene = TransitionSlideInR::create(1.0f, scene);
		Director::getInstance()->replaceScene(gameScene);
	}
	else if (Checkpoint == 3) {
		auto scene = ThirdBossScene::createScene();
		auto gameScene = TransitionSlideInR::create(1.0f, scene);
		Director::getInstance()->replaceScene(gameScene);
	}
	else if (Checkpoint == 4) {
		auto scene = FourthBossScene::createScene();
		auto gameScene = TransitionSlideInR::create(1.0f, scene);
		Director::getInstance()->replaceScene(gameScene);
	}
}

void TranScene::menuMagic3Callback(Ref* pSender) {
	FirstBossScene::type_for_skill = 3;
	if (Checkpoint == 1) {
		auto scene = FirstBossScene::createScene();
		auto gameScene = TransitionSlideInR::create(1.0f, scene);
		Director::getInstance()->replaceScene(gameScene);
	}
	else if (Checkpoint == 2) {
		auto scene = SecondBossScene::createScene();
		auto gameScene = TransitionSlideInR::create(1.0f, scene);
		Director::getInstance()->replaceScene(gameScene);
	}
	else if (Checkpoint == 3) {
		auto scene = ThirdBossScene::createScene();
		auto gameScene = TransitionSlideInR::create(1.0f, scene);
		Director::getInstance()->replaceScene(gameScene);
	}
	else if (Checkpoint == 4) {
		auto scene = FourthBossScene::createScene();
		auto gameScene = TransitionSlideInR::create(1.0f, scene);
		Director::getInstance()->replaceScene(gameScene);
	}
}


