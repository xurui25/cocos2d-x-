#include "GameOverScene.h"
#include "GameScene.h"
#include "HelloWorldScene.h"
#include "TranScene.h"
#include "help.h"
#include "GameScene2.h"
#include "AppDelegate.h"

USING_NS_CC;

//用于设置模式
int GameOverScene::win_num = 1;

Scene* GameOverScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOverScene::create();
	scene->addChild(layer);

	return scene;
}

bool GameOverScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("background.jpg");
	//为适应屏幕进行缩放
	bg->setScaleX((float)visibleSize.width / (float)bg->getContentSize().width);
	bg->setScaleY((float)visibleSize.height / (float)bg->getContentSize().height);
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, 0));
	bg->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(bg, 0);

	if (win_num == 0) {
		//返回游戏界面选项
		//auto backItem = MenuItemImage::create("continue.png", "continue2.png", CC_CALLBACK_1(GameOverScene::back_, this));
		//backItem->setPosition(Vec2(origin.x + visibleSize.width / 2, visibleSize.height / 2 + origin.y));
		// 回主页选项
		auto backHello = MenuItemImage::create("return.png", "return2.png", CC_CALLBACK_1(GameOverScene::goHello, this));
		backHello->setPosition(Vec2(origin.x + visibleSize.width / 2, visibleSize.height / 2 + origin.y - 1 * backHello->getContentSize().height));
		//退出游戏菜单项
		auto closeItem = MenuItemImage::create("exit.png", "exit2.png", CC_CALLBACK_1(GameOverScene::exitGame, this));
		closeItem->setPosition(Vec2(origin.x + visibleSize.width / 2, visibleSize.height / 2 + origin.y - 2 * backHello->getContentSize().height));
		//把菜单项添加到菜单精灵中
		auto menu = Menu::create(backHello, closeItem, NULL);
		menu->setPosition(Vec2::ZERO);
		//把菜单精灵添加到当前的层中
		this->addChild(menu, 1);
	}
	else {
		//下一关选项
		auto backItem = MenuItemImage::create("next.png", "next2.png", CC_CALLBACK_1(GameOverScene::nextGame, this));
		backItem->setPosition(Vec2(origin.x + visibleSize.width / 2, visibleSize.height / 2 + origin.y));
		// 回主页选项
		auto backHello = MenuItemImage::create("return.png", "return2.png", CC_CALLBACK_1(GameOverScene::goHello, this));
		backHello->setPosition(Vec2(origin.x + visibleSize.width / 2, visibleSize.height / 2 + origin.y - 1 * backItem->getContentSize().height));
		//退出游戏菜单项
		auto closeItem = MenuItemImage::create("exit.png", "exit2.png", CC_CALLBACK_1(GameOverScene::exitGame, this));
		closeItem->setPosition(Vec2(origin.x + visibleSize.width / 2, visibleSize.height / 2 + origin.y - 2 * backItem->getContentSize().height));
		//把菜单项添加到菜单精灵中
		auto menu = Menu::create(backItem, backHello, closeItem, NULL);
		menu->setPosition(Vec2::ZERO);
		//把菜单精灵添加到当前的层中
		this->addChild(menu, 1);
	}

	return true;
}

//返回游戏界面
void GameOverScene::back_(Ref* pSender) {
	auto scene = HelloWorld::createScene();
	auto gameScene = TransitionSlideInR::create(1.0f, scene);
	Director::getInstance()->replaceScene(gameScene);
}

//返回主页
void GameOverScene::goHello(Ref* pSender) {
	auto scene = HelloWorld::createScene();
	auto gameScene = TransitionSlideInR::create(1.0f, scene);
	Director::getInstance()->replaceScene(gameScene);
}

//关数界面的显示
void GameOverScene::nextGame(Ref* pSender) {
	if (win_num == 1) {
		auto scene = TranScene::createScene(1);
		auto gameScene = TransitionSlideInR::create(1.0f, scene);
		Director::getInstance()->replaceScene(gameScene);
	}
	else if (win_num == 2) {
		Help::setPass(2);
		auto scene = Help::createScene();
		auto gameScene = TransitionSlideInR::create(1.0f, scene);
		Director::getInstance()->replaceScene(gameScene);
	}
	else if (win_num == 3) {
		auto scene = TranScene::createScene(2);
		auto gameScene = TransitionSlideInR::create(1.0f, scene);
		Director::getInstance()->replaceScene(gameScene);
	}
	else if (win_num == 4) {
		Help::setPass(3);
		auto scene = Help::createScene();
		auto gameScene = TransitionSlideInR::create(1.0f, scene);
		Director::getInstance()->replaceScene(gameScene);
	}
	else if (win_num == 5) {
		auto scene = TranScene::createScene(3);
		auto gameScene = TransitionSlideInR::create(1.0f, scene);
		Director::getInstance()->replaceScene(gameScene);
	}
	else if (win_num == 6) {
		Help::setPass(4);
		auto scene = Help::createScene();
		auto gameScene = TransitionSlideInR::create(1.0f, scene);
		Director::getInstance()->replaceScene(gameScene);
	}
	else if (win_num == 7) {
		auto scene = TranScene::createScene(4);
		auto gameScene = TransitionSlideInR::create(1.0f, scene);
		Director::getInstance()->replaceScene(gameScene);
	}
	else if (win_num == 8) {
		Help::setPass(5);
		auto scene = Help::createScene();
		auto gameScene = TransitionSlideInR::create(1.0f, scene);
		Director::getInstance()->replaceScene(gameScene);
	}
}

//第二关
void GameOverScene::SecondGame(Ref* pSender) {
	auto scene = GameScene2::createScene();
	auto gameScene = TransitionSlideInR::create(1.0f, scene);
	Director::getInstance()->replaceScene(gameScene);
}

void GameOverScene::exitGame(Ref* pSender)
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();			//退出

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}