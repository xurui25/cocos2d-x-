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

    	cocos2d::CCMenuItemImage*   mItemSkill;     // ���ܰ�ť
	    cocos2d::CCMenu*            mMenuSkill;     // ���ܰ�ť����menu
	    cocos2d::CCSprite*          mStencil;       // �ɰ徫��,��ɫ��͸��(�����Ϊ����ʾһ����ȴ��ʱЧ��)
	    cocos2d::CCProgressTimer*   mProgressTimer; // ʱ�����������(360����ת)
	    float                       mCDTime;          // CDʱ��
};

class CMTouchSpriteProtocol {
public:
	// optional
	virtual void CMTouchSpriteSelectSprite(SkillButton *sprite) {
	};

};
#endif