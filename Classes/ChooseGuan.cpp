#include "ChooseGuan.h"
#include "help.h"
#include "HelloWorldScene.h"
#include "GameScene.h"
#include "AppDelegate.h"

USING_NS_CC;

bool ChooseGuan::canChoose1 = true;
bool ChooseGuan::canChoose2 = false;
bool ChooseGuan::canChoose3 = false;
bool ChooseGuan::canChoose4 = false;
bool ChooseGuan::canChoose5 = false;

Scene* ChooseGuan::createScene()
{
	auto scene = Scene::create();
	auto layer = ChooseGuan::create();
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool ChooseGuan::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 根据UserDefault决定哪几关解锁，默认为只有第一关解锁
	if (!UserDefault::getInstance()->getBoolForKey("isExist"))
	{
		UserDefault::getInstance()->setBoolForKey("isExist", true);
		UserDefault::getInstance()->setBoolForKey("canChoose1", true);
		UserDefault::getInstance()->setBoolForKey("canChoose2", false);
		UserDefault::getInstance()->setBoolForKey("canChoose3", false);
		UserDefault::getInstance()->setBoolForKey("canChoose4", false);
		UserDefault::getInstance()->setBoolForKey("canChoose5", false);
	}
	canChoose1 = UserDefault::getInstance()->getBoolForKey("canChoose1");
	canChoose2 = UserDefault::getInstance()->getBoolForKey("canChoose2");
	canChoose3 = UserDefault::getInstance()->getBoolForKey("canChoose3");
	canChoose4 = UserDefault::getInstance()->getBoolForKey("canChoose4");
	canChoose5 = UserDefault::getInstance()->getBoolForKey("canChoose5");

	
	// 背景精灵
	auto bg1 = Sprite::create("background.jpg");
	//为适应屏幕进行缩放
	bg1->setScaleX((float)visibleSize.width / (float)bg1->getContentSize().width);
	bg1->setScaleY((float)visibleSize.height / (float)bg1->getContentSize().height);
	bg1->setPosition(Vec2(origin.x + visibleSize.width / 2, 0));
	bg1->setAnchorPoint(Vec2(0.5, 0));
	bg1->setTag(101);
	this->addChild(bg1, 0);
	
	// 添加关卡按钮
	auto btn1 = MenuItemImage::create("guan1.png", "guan1b.png", "guan1b.png", CC_CALLBACK_0(ChooseGuan::selectGuan1, this));
	auto btn2 = MenuItemImage::create("guan2.png", "guan2b.png", "guan2b.png", CC_CALLBACK_0(ChooseGuan::selectGuan2, this));
	auto btn3 = MenuItemImage::create("guan3.png", "guan3b.png", "guan3b.png", CC_CALLBACK_0(ChooseGuan::selectGuan3, this));
	auto btn4 = MenuItemImage::create("guan4.png", "guan4b.png", "guan4b.png", CC_CALLBACK_0(ChooseGuan::selectGuan4, this));
	auto btn5 = MenuItemImage::create("guan5.png", "guan5b.png", "guan5b.png", CC_CALLBACK_0(ChooseGuan::selectGuan5, this));

	auto menu = Menu::create(btn1, btn2, btn3, btn4, btn5, NULL);
	menu->alignItemsHorizontallyWithPadding(20);
	menu->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(menu, 1);

	// 设置关卡按钮是否可选
	if (!canChoose1) {
		btn1->setEnabled(false);
	}
	if (!canChoose2) {
		btn2->setEnabled(false);
	}
	if (!canChoose3) {
		btn3->setEnabled(false);
	}
	if (!canChoose4) {
		btn4->setEnabled(false);
	}
	if (!canChoose5) {
		btn5->setEnabled(false);
	}

	// 回主页按钮和清除记录按钮
	auto goHome = MenuItemImage::create("exit.png", "exit2.png", CC_CALLBACK_0(ChooseGuan::goHello, this));
	auto clearRecord = MenuItemImage::create("exit.png", "exit2.png", CC_CALLBACK_0(ChooseGuan::clearRec, this));

	auto menu2 = Menu::create(goHome, clearRecord, NULL);
	menu2->alignItemsHorizontallyWithPadding(30);
	menu2->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 100);
	this->addChild(menu2, 1);

	return true;
}

// 选择关卡
void ChooseGuan::selectGuan1() {
	// 进入GameScene场景
	Help::setPass(1);
	this->stopAllActions();
	auto scene = Help::createScene(1);
	auto gameScene = TransitionSlideInR::create(1.0f, scene);
	Director::getInstance()->replaceScene(gameScene);
}

void ChooseGuan::selectGuan2() {
	// 进入GameScene场景
	Help::setPass(2);
	this->stopAllActions();
	auto scene = Help::createScene(2);
	auto gameScene = TransitionSlideInR::create(1.0f, scene);
	Director::getInstance()->replaceScene(gameScene);
}

void ChooseGuan::selectGuan3() {
	// 进入GameScene场景
	Help::setPass(3);
	this->stopAllActions();
	auto scene = Help::createScene(3);
	auto gameScene = TransitionSlideInR::create(1.0f, scene);
	Director::getInstance()->replaceScene(gameScene);
}

void ChooseGuan::selectGuan4() {
	// 进入GameScene场景
	Help::setPass(4);
	this->stopAllActions();
	auto scene = Help::createScene(4);
	auto gameScene = TransitionSlideInR::create(1.0f, scene);
	Director::getInstance()->replaceScene(gameScene);
}

void ChooseGuan::selectGuan5() {
	// 进入GameScene场景
	Help::setPass(5);
	this->stopAllActions();
	auto scene = Help::createScene(5);
	auto gameScene = TransitionSlideInR::create(1.0f, scene);
	Director::getInstance()->replaceScene(gameScene);
}

// 返回首页
void ChooseGuan::goHello() {
	auto scene = HelloWorld::createScene();
	auto gameScene = TransitionSlideInR::create(1.0f, scene);
	Director::getInstance()->replaceScene(gameScene);
}

// 清除记录
void ChooseGuan::clearRec() {
	canChoose1 = true;
	canChoose2 = false;
	canChoose3 = false;
	canChoose4 = false;
	canChoose5 = false;

	// 保存到本地
	UserDefault::getInstance()->setBoolForKey("canChoose1", true);
	UserDefault::getInstance()->setBoolForKey("canChoose2", false);
	UserDefault::getInstance()->setBoolForKey("canChoose3", false);
	UserDefault::getInstance()->setBoolForKey("canChoose4", false);
	UserDefault::getInstance()->setBoolForKey("canChoose5", false);

	// 刷新场景
	auto scene = ChooseGuan::createScene();
	Director::getInstance()->replaceScene(scene);
}