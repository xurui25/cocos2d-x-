#include "BackGround.h"
#include "cocos2d.h"
#include "HelloWorldScene.h"

USING_NS_CC;

int BackGround::hit = 0;

Scene* BackGround::createScene() {
	auto scene = Scene::createWithPhysics();
	auto layer = BackGround::create();
	scene->addChild(layer);
	return scene;
}

bool BackGround::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	//��ʼ��
	sethit(0);

	//����һ��ֱ���˳��İ�ť
	auto btn1 = MenuItemImage::create("closeOut.png", "closeOut.png", CC_CALLBACK_0(BackGround::setexit, this));
	auto menu = Menu::create(btn1, NULL);
	menu->alignItemsVerticallyWithPadding(30);
	menu->setPosition(visibleSize.width - 50, btn1->getContentSize().height);
	this->addChild(menu, 1);

	//��������
	createback(gethit());

	return true;
}

//��������
void BackGround::createback(int i) {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	if (i == 0) {
		auto sp = Sprite::create("js1.png");
		//Ϊ��Ӧ��Ļ��������
		sp->setScaleX((float)visibleSize.width / (float)sp->getContentSize().width);
		sp->setScaleY((float)visibleSize.height / (float)sp->getContentSize().height);
		sp->setPosition(Vec2(origin.x + visibleSize.width / 2, 0));
		sp->setAnchorPoint(Vec2(0.5, 0));
		sp->setTag(101);
		this->addChild(sp, 0);
	}
	else if (i == 1) {
		this->removeChildByTag(101);
		auto sp = Sprite::create("js2.png");
		//Ϊ��Ӧ��Ļ��������
		sp->setScaleX((float)visibleSize.width / (float)sp->getContentSize().width);
		sp->setScaleY((float)visibleSize.height / (float)sp->getContentSize().height);
		sp->setPosition(Vec2(origin.x + visibleSize.width / 2, 0));
		sp->setAnchorPoint(Vec2(0.5, 0));
		sp->setTag(101);
		this->addChild(sp, 0);
	}
	else if (i == 2) {
		this->removeChildByTag(101);
		auto sp = Sprite::create("js3.png");
		//Ϊ��Ӧ��Ļ��������
		sp->setScaleX((float)visibleSize.width / (float)sp->getContentSize().width);
		sp->setScaleY((float)visibleSize.height / (float)sp->getContentSize().height);
		sp->setPosition(Vec2(origin.x + visibleSize.width / 2, 0));
		sp->setAnchorPoint(Vec2(0.5, 0));
		sp->setTag(101);
		this->addChild(sp, 0);
	}
	else if (i >= 3) {
		auto scene = HelloWorld::createScene();
		auto gameOverScene = TransitionTurnOffTiles::create(1.0f, scene);
		CCTextureCache::sharedTextureCache()->removeAllTextures();
		Director::getInstance()->replaceScene(gameOverScene);
	}
}

bool BackGround::onTouchBegan(Touch *touch, Event *unused_event) {
	sethit(gethit() + 1);
	createback(gethit());
	return true;
}

//����hitֵ
void BackGround::sethit(int i) {
	hit = i;
}

//��ȡhitֵ
int BackGround::gethit() {
	return hit;
}

//ֱ���˳�
void BackGround::setexit() {
	auto scene = HelloWorld::createScene();
	auto gameOverScene = TransitionTurnOffTiles::create(1.0f, scene);
	CCTextureCache::sharedTextureCache()->removeAllTextures();
	Director::getInstance()->replaceScene(gameOverScene);
}