#include "AppDelegate.h"
#include "WelcomeScene.h"
#include "cocos2d.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}
void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("Helicopter", Rect(0, 0, 320, 480));
        director->setOpenGLView(glview);
    }

    director->getOpenGLView()->setDesignResolutionSize(320, 480, ResolutionPolicy::SHOW_ALL);
    director->setDisplayStats(false);
    director->setAnimationInterval(1.0 / 60);
    FileUtils::getInstance()->addSearchPath("res");
	auto scene = WelcomeScene::createScene();
	director->runWithScene(scene);

    return true;
}
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
}


void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

}
