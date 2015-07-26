#ifndef __SKILLBUTTON_H__
#define __SKILLBUTTON_H__

#include "cocos2d.h"

class CMTouchSpriteProtocol;

class SkillButton : public cocos2d::CCNode {
	public:
		SkillButton();
		virtual ~SkillButton();

		static SkillButton* createSkillButton(float cdTime,
			const char* stencil_file_name,
			const char* button_normal_name,
			const char* button_click_name);


		void    setCDTime(float time) { mCDTime = time; }
		float   getCDTime() const { return mCDTime; }

		void    skillClickCallBack(cocos2d::CCObject* obj);

		void    Action_for();

		void    skillCoolDownCallBack(cocos2d::CCNode* node);
		CC_PROPERTY(CMTouchSpriteProtocol*, _touchSpriteProtocol, TouchSpriteProtocol);
    private:
		bool    init(float cdTime, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name);

    	cocos2d::CCMenuItemImage*   mItemSkill;     // 技能按钮
	    cocos2d::CCMenu*            mMenuSkill;     // 技能按钮所在menu
	    cocos2d::CCSprite*          mStencil;       // 蒙板精灵,黑色半透明(这个是为了显示一个冷却计时效果)
	    cocos2d::CCProgressTimer*   mProgressTimer; // 时间进度条精灵(360度旋转)
	    float                       mCDTime;          // CD时间
};

class CMTouchSpriteProtocol {
public:
	// optional
	virtual void CMTouchSpriteSelectSprite(SkillButton *sprite) {
	};

};
#endif