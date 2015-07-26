#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
	
public:
    static cocos2d::Scene* createScene();
	static int man;

    virtual bool init();
    
    //�ص�����
    void menuCloseCallback(cocos2d::Ref* pSender);
	void menuStartCallback(cocos2d::Ref* pSender);
	void menuChooseGuanCallback(cocos2d::Ref* pSender);
	void menuChooseCallback(cocos2d::Ref* pSender);

	//����ѡ������
	static void setTypeMan(int i);
	//�������ѡ������
	static int getTypeMan();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
