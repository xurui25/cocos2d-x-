#include "help.h"
#include "GameScene.h"
#include "GameScene2.h"
#include "ChooseGuan.h"
#include "AppDelegate.h"
#include "GameScene3.h"
#include "GameScene4.h"

USING_NS_CC;

int Help::pass = 1;

Scene* Help::createScene()
{
	auto scene = Scene::create();
	auto layer = Help::create();
	scene->addChild(layer);

	return scene;
}

bool Help::init() {
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//背景精灵
	if (getPass() == 1) {
		auto bg1 = Sprite::create("help_bg1.jpg");
		//为适应屏幕进行缩放
		bg1->setScaleX((float)visibleSize.width / (float)bg1->getContentSize().width);
		bg1->setScaleY((float)visibleSize.height / (float)bg1->getContentSize().height);
		bg1->setPosition(Vec2(origin.x + visibleSize.width / 2, 0));
		bg1->setAnchorPoint(Vec2(0.5, 0));
		bg1->setTag(101);
		this->addChild(bg1, 0);
	}
	else if (getPass() == 2) {
		auto bg1 = Sprite::create("help_bg2.jpg");
		//为适应屏幕进行缩放
		bg1->setScaleX((float)visibleSize.width / (float)bg1->getContentSize().width);
		bg1->setScaleY((float)visibleSize.height / (float)bg1->getContentSize().height);
		bg1->setPosition(Vec2(origin.x + visibleSize.width / 2, 0));
		bg1->setAnchorPoint(Vec2(0.5, 0));
		bg1->setTag(101);
		this->addChild(bg1, 0);
	}
	else if (getPass() == 3){
		auto bg1 = Sprite::create("help_bg3.jpg");
		//为适应屏幕进行缩放
		bg1->setScaleX((float)visibleSize.width / (float)bg1->getContentSize().width);
		bg1->setScaleY((float)visibleSize.height / (float)bg1->getContentSize().height);
		bg1->setPosition(Vec2(origin.x + visibleSize.width / 2, 0));
		bg1->setAnchorPoint(Vec2(0.5, 0));
		bg1->setTag(101);
		this->addChild(bg1, 0);
	}
	else if (getPass() == 4) {
		auto bg1 = Sprite::create("help_bg4.png");
		//为适应屏幕进行缩放
		bg1->setScaleX((float)visibleSize.width / (float)bg1->getContentSize().width);
		bg1->setScaleY((float)visibleSize.height / (float)bg1->getContentSize().height);
		bg1->setPosition(Vec2(origin.x + visibleSize.width / 2, 0));
		bg1->setAnchorPoint(Vec2(0.5, 0));
		bg1->setTag(101);
		this->addChild(bg1, 0);
	}
	
	auto MagicItem = MenuItemImage::create("continue.png", "continue2.png",
		CC_CALLBACK_1(Help::menuContinueCallback, this));
	MagicItem->setPosition(Vec2(visibleSize.width - MagicItem->getContentSize().width - 20, MagicItem->getContentSize().height * 2));
	MagicItem->setAnchorPoint(Vec2(0.5, 0.5));
	auto menu = Menu::create(MagicItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void Help::menuContinueCallback(Ref* spender) {
	if (getPass() == 1) {
		auto scene = GameScene::createScene();
		auto gameScene = TransitionSlideInR::create(1.0f, scene);
		Director::getInstance()->replaceScene(gameScene);
	}
	else if (getPass() == 2) {
		auto scene = GameScene2::createScene();
		auto gameScene = TransitionSlideInR::create(1.0f, scene);
		Director::getInstance()->replaceScene(gameScene);
	}
	else if (getPass() == 3) {
		auto scene = GameScene3::createScene();
		auto gameScene = TransitionSlideInR::create(1.0f, scene);
		Director::getInstance()->replaceScene(gameScene);
	}
	else if (getPass() == 4) {
		auto scene = GameScene4::createScene();
		auto gameScene = TransitionSlideInR::create(1.0f, scene);
		Director::getInstance()->replaceScene(gameScene);
	}
}

void Help::setPass(int i) {
	pass = i;
}

int Help::getPass() {
	return pass;
}



