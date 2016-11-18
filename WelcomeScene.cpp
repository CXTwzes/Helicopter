//WelcomeScene.cpp
#include "WelcomeScene.h"
#include "GameBegin.h"
#include "define.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
WelcomeScene::WelcomeScene()
{
}
WelcomeScene::~WelcomeScene()
{
}
cocos2d::Scene * WelcomeScene::createScene()
{
	auto scene=Scene::create();
	auto welcomeLayer=WelcomeScene::create();
	scene->addChild(welcomeLayer); 
	return scene;
}

bool WelcomeScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto origin=Director::getInstance()->getVisibleOrigin();
	auto visibleSize=Director::getInstance()->getVisibleSize();
	//读取游戏的图片资源
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("source.plist");
	//给加载场景设置背景
	auto bg=Sprite::createWithSpriteFrameName("loading.png");
	bg->setPosition(Point(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));
	this->addChild(bg);
	//加载声音
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("touch.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("fail1.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("change.wav");

	//相当于帧动画
	auto animation=Animation::create();
	animation->setDelayPerUnit(LOADING_FRE);
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("zt1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("zt2.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("zt3.png"));


	auto animate=Animate::create(animation);
	auto repeat=Repeat::create(animate,LOADING_NUM);
	//回调函数，切换场景
	auto callBack=CallFuncN::create(CC_CALLBACK_0(WelcomeScene::loadingDone,this));
	//然后把动画和回调函数放到一个列队中，先执行动画，动画执行完了回调切场景
	auto sequence=Sequence::create(repeat,callBack,NULL);
	//定义动画的第一帧
	auto loading = Sprite::createWithSpriteFrameName("zt1.png");
	loading->setPosition(Point(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));
	this->addChild(loading);
	//执行动画

	loading->runAction(sequence);

	//Helicopter的动画定义
	//放到缓存中
	auto helicopterAnimation=Animation::create();
	helicopterAnimation->setDelayPerUnit(HELICOPTER_FRE);
	helicopterAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("helicopter_1.png"));
	helicopterAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("helicopter_2.png"));
	helicopterAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("helicopter_3.png"));
	helicopterAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("helicopter_4.png"));
	helicopterAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("helicopter_5.png"));
	helicopterAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("helicopter_4.png"));
	helicopterAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("helicopter_3.png"));
	helicopterAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("helicopter_2.png"));
	helicopterAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("helicopter_1.png"));
	//放到缓存中，在define.h文件
	AnimationCache::getInstance()->addAnimation(helicopterAnimation, HELICOPTERANIMATION);

	return true;
}
//loading动画执行完后的回调函数
void WelcomeScene::loadingDone()
{
	//切换到GameBegin场景
	Director::getInstance()->replaceScene(TransitionFade::create(CHANGESCENE_TIME, GameBegin::createScene()));

}
