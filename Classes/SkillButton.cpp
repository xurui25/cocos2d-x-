#include "SkillButton.h"

USING_NS_CC;

SkillButton::SkillButton() :
mItemSkill(NULL),
mMenuSkill(NULL),
mStencil(NULL),
mProgressTimer(NULL),
mCDTime(1.f)
{

}

SkillButton::~SkillButton()
{

}

SkillButton* SkillButton::createSkillButton(float cdTime, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name)
{
	SkillButton* skillButton = new SkillButton();
	if (skillButton && skillButton->init(cdTime, stencil_file_name, button_normal_name, button_click_name))
	{
		skillButton->autorelease();
		return skillButton;
	}
	else
	{
		delete skillButton;
		skillButton = NULL;
	}

	return NULL;
}

bool SkillButton::init(float cdTime, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name)
{
	CCAssert(stencil_file_name, "SkillButton::init stencil_file_name != NULL");
	CCAssert(button_normal_name, "SkillButton::init button_normal_name != NULL");
	CCAssert(button_click_name, "SkillButton::init button_click_name != NULL");

	// Notice:���childʱҪע�����²�
	// ���·���CCMenuItemImage �����ģ��ͼƬ ���Ϸ���CCProgressTimer

	// ��Ӽ��ܰ�ť
	mItemSkill = CCMenuItemImage::create(button_normal_name, button_click_name, this, menu_selector(SkillButton::skillClickCallBack));
	mItemSkill->setPosition(ccp(0,0));

	mMenuSkill = CCMenu::create(mItemSkill, NULL);
	mMenuSkill->setPosition(ccp(0,0));
	addChild(mMenuSkill, -100);

	// �����Ӱģ��
	mStencil = CCSprite::create(stencil_file_name);
	mStencil->setPosition(ccp(0,0));
	mStencil->setVisible(false);
	addChild(mStencil);

	// �����ת����������
	CCSprite* progressSprite = CCSprite::create(button_normal_name);
	mProgressTimer = CCProgressTimer::create(progressSprite);
	mProgressTimer->setPosition(ccp(0,0));
	mProgressTimer->setVisible(false);
	addChild(mProgressTimer, 100);

	mCDTime = cdTime;
	return true;
}

void SkillButton::skillClickCallBack(cocos2d::CCObject* obj)
{
	// ��ȴ��ʱ����ʱ״̬���ܰ�ť���ɵ��
	mItemSkill->setEnabled(false);

	// ģ��ɼ�
	mStencil->setVisible(true);

	// ���þ��������Ϊ˳ʱ��
	mProgressTimer->setVisible(true);
	mProgressTimer->setType(kCCProgressTimerTypeRadial);
	mProgressTimer->setPercentage(0);

	_touchSpriteProtocol->CMTouchSpriteSelectSprite(this);
	//׼��һ��5����ת360�ȵĶ���(�𽥸��ǰ�͸ģ���γ���ȴЧ��;������м�ʱ��ȴ������ʵ�ֺ�ʱ�����)
	Action_for();
}

void SkillButton::Action_for() {
	CCCallFunc* action_callback = CCCallFuncN::create(this, callfuncN_selector(SkillButton::skillCoolDownCallBack));
	CCActionInterval* action_progress_to = CCProgressTo::create(mCDTime, 100);
	mProgressTimer->runAction(CCSequence::create(action_progress_to, action_callback, NULL));
}

void SkillButton::skillCoolDownCallBack(CCNode* node)
{
	// �����ɰ岻�ɼ�
	mStencil->setVisible(false);

	// ���������ܲ��ɼ�
	mProgressTimer->setVisible(false);

	// ��ť��Ϊ����
	mItemSkill->setEnabled(true);
	
}

// ����Э��
void SkillButton::setTouchSpriteProtocol(CMTouchSpriteProtocol *protocol) {
	_touchSpriteProtocol = protocol;
}
CMTouchSpriteProtocol*SkillButton::getTouchSpriteProtocol() {
	return _touchSpriteProtocol;
}
