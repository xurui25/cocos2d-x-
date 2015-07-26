#ifndef __GAMEOVERSCENE_H__
#define __GAMEOVERSCENE_H__

#include "cocos2d.h"

class GameOverScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
    bool init();
    CREATE_FUNC(GameOverScene);

	//回调函数，返回游戏界面
	void back_(cocos2d::Ref* pSender);
	//返回主页
	void goHello(cocos2d::Ref* pSender);
	//回调函数，结束游戏
	void exitGame(cocos2d::Ref* pSender);
	//下一关卡（第一关的boss）
	void nextGame(cocos2d::Ref* pSender);

	//第二关
	void SecondGame(cocos2d::Ref* pSender);

	static int win_num;
};

#endif