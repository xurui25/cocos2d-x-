#include "AppDelegate.h"
#include "BackGround.h"
#include "translate.h"

USING_NS_CC;

float AppDelegate::scale_x = 1.0;
float AppDelegate::scale_y = 1.0;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		//��������Ϸ���ƣ����Ǵ�win32�������Ϸ���ʾ��title
		glview = GLViewImpl::create(Translate::WStrToUTF8_(L"ը��"));
		//���ô��ڴ�С
		//Size visibleSize = Director::getInstance()->getVisibleSize();
		//scale_x = (float)visibleSize.width / 1200.0;
		//scale_y = (float)visibleSize.height / 720.0;

		//glview->setFrameSize(visibleSize.width, visibleSize.height);
        director->setOpenGLView(glview); 
    }
	//Ϊ�������ֻ���
	//glview->setDesignResolutionSize(1200, 720, ResolutionPolicy::SHOW_ALL);
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = BackGround::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
