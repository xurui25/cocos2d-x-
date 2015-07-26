#include "HelloWorldScene.h"
#include "TranScene.h"
#include "GameScene.h"
#include "ChooseManScene.h"
#include "ChooseGuan.h"
#include "cocostudio/CocoStudio.h"
#include "help.h"

USING_NS_CC;
using namespace cocostudio;

int HelloWorld::man = 1;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    //��ʼ��
	

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//��������
	auto bg1 = Sprite::create("background.jpg");
	//Ϊ��Ӧ��Ļ��������
	bg1->setScaleX((float)visibleSize.width / (float) bg1->getContentSize().width);
	bg1->setScaleY((float)visibleSize.height / (float)bg1->getContentSize().height);
	bg1->setPosition(Vec2(origin.x + visibleSize.width / 2, 0));
	bg1->setAnchorPoint(Vec2(0.5, 0));
	bg1->setTag(101);
	this->addChild(bg1, 0);

	//��������
	ArmatureDataManager::getInstance()->addArmatureFileInfo("StartAnimation0.png", "StartAnimation0.plist", "StartAnimation.ExportJson");
	Armature *armature = Armature::create("StartAnimation");
	armature->setPosition(Point(visibleSize.width * 0.5, visibleSize.height * 0.8));
	// ���Ŷ���
	armature->getAnimation()->play("Animation1");
	this->addChild(armature);


	//��һ��
	auto startItem = MenuItemImage::create("start.png", "start2.png",
		CC_CALLBACK_1(HelloWorld::menuStartCallback, this));
	startItem->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//�ؿ�ѡ��
	auto chooseGuan = MenuItemImage::create("select.png", "select2.png",
		CC_CALLBACK_1(HelloWorld::menuChooseGuanCallback, this));
	chooseGuan->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 1 * startItem->getContentSize().height));
	//����ѡ���
	auto chooseMan = MenuItemImage::create("select.png", "select2.png",
		CC_CALLBACK_1(HelloWorld::menuChooseCallback, this));
	chooseMan->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 2 * startItem->getContentSize().height));
	//����
	auto closeItem = MenuItemImage::create("exit.png", "exit2.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	closeItem->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 3*startItem->getContentSize().height));
	auto menu = Menu::create(startItem, chooseGuan, chooseMan, closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    return true;
}

//������������
void HelloWorld::setTypeMan(int i) {
	man = i;
}

//�����������
int HelloWorld::getTypeMan() {
	return man;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::menuStartCallback(Ref* pSender) {
	auto scene = Help::createScene(1);
	auto gameScene = TransitionSlideInR::create(1.0f, scene);
	Director::getInstance()->replaceScene(gameScene);
}

void HelloWorld::menuChooseGuanCallback(Ref* pSender) {
	auto scene = ChooseGuan::createScene();
	auto gameScene = TransitionSlideInR::create(1.0f, scene);
	Director::getInstance()->replaceScene(gameScene);
}

void HelloWorld::menuChooseCallback(Ref* pSender) {
	auto scene = ChooseMan::createScene();
	auto gameScene = TransitionSlideInR::create(1.0f, scene);
	Director::getInstance()->replaceScene(gameScene);
}