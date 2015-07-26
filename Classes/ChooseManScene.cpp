#include "ChooseManScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;


Scene* ChooseMan::createScene()
{
	auto scene = Scene::create();
	auto layer = ChooseMan::create();
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool ChooseMan::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//背景精灵
	auto bg1 = Sprite::create("choose_bg.jpg");
	//为适应屏幕进行缩放
	bg1->setScaleX((float)visibleSize.width / (float)bg1->getContentSize().width);
	bg1->setScaleY((float)visibleSize.height / (float)bg1->getContentSize().height);
	bg1->setPosition(Vec2(origin.x + visibleSize.width / 2, 0));
	bg1->setAnchorPoint(Vec2(0.5, 0));
	bg1->setTag(101);
	this->addChild(bg1, 0);

	CreateItem();

	return true;
}

void ChooseMan::CreateItem() {
	Point poin = Director::getInstance()->getVisibleSize();

	man1 = MenuItemImage::create("chooseman1.png","chooseman1.png",CC_CALLBACK_0(ChooseMan::CallBackMan1, this));
	man1->setPosition(Vec2(poin.x / 2 - 3 * man1->getContentSize().width / 2, Director::getInstance()->getVisibleSize().height / 2));

	man2 = MenuItemImage::create("chooseman2.png", "chooseman2.png", CC_CALLBACK_0(ChooseMan::CallBackMan2, this));
	man2->setPosition(Vec2(poin.x / 2 - man1->getContentSize().width / 2, Director::getInstance()->getVisibleSize().height / 2));

	man3 = MenuItemImage::create("chooseman3.png", "chooseman3.png", CC_CALLBACK_0(ChooseMan::CallBackMan3, this));
	man3->setPosition(Vec2(poin.x / 2 + man1->getContentSize().width / 2, Director::getInstance()->getVisibleSize().height / 2));

	auto menu = Menu::create(man1, man2, man3, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}

void ChooseMan::CallBackMan1() {
	HelloWorld::setTypeMan(1);
	auto scene = HelloWorld::createScene();
	auto gameScene = TransitionSlideInR::create(1.0f, scene);
	Director::getInstance()->replaceScene(gameScene);
}

void ChooseMan::CallBackMan2() {
	HelloWorld::setTypeMan(2);
	auto scene = HelloWorld::createScene();
	auto gameScene = TransitionSlideInR::create(1.0f, scene);
	Director::getInstance()->replaceScene(gameScene);
}

void ChooseMan::CallBackMan3() {
	HelloWorld::setTypeMan(3);
	auto scene = HelloWorld::createScene();
	auto gameScene = TransitionSlideInR::create(1.0f, scene);
	Director::getInstance()->replaceScene(gameScene);
}



