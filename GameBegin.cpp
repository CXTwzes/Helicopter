//GameBegin.cpp
#include "SimpleAudioEngine.h"
#include "GameBegin.h"
#include "define.h"
#include "GameLayer.h"
USING_NS_CC;
GameBegin::GameBegin()
{
}
GameBegin::~GameBegin()
{
}

cocos2d::Scene * GameBegin::createScene()
{
	auto scene=Scene::create();
	auto gameLayer=GameBegin::create();
	scene->addChild(gameLayer);
	return scene;
}

bool GameBegin::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//获取 OpenGL 视图的初始化时的可见大小
	auto origin=Director::getInstance()->getVisibleOrigin();
	auto visibleSize=Director::getInstance()->getVisibleSize();

	Sprite * bg;
	bg=Sprite::createWithSpriteFrameName(LAYER);
	bg->setPosition(Point(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));
	this->addChild(bg);

	//游戏名字
	auto title=Sprite::createWithSpriteFrameName("title.png");
	title->setPosition(Point(origin.x+visibleSize.width/2,origin.y+visibleSize.height*0.6));
	this->addChild(title);

	//直升机
	auto helicopter= Sprite::createWithSpriteFrameName("helicopter_1.png");
	helicopter->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height*0.65));
    helicopter->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(HELICOPTERANIMATION))));
	this->addChild(helicopter);

	//开始按钮
	auto start_sprite_1=Sprite::createWithSpriteFrameName("startGame.png");
	auto start_sprite_2 = Sprite::createWithSpriteFrameName("startGame2.png");
	auto start_button=MenuItemSprite::create(start_sprite_1,start_sprite_2,CC_CALLBACK_0(GameBegin::startGame,this));
	start_button->setPosition(Point(origin.x+visibleSize.width/2,origin.y+visibleSize.height*0.4));
	auto menu=Menu::create(start_button,NULL);
	menu->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	return true;
}

//按钮回调
void GameBegin::startGame()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("change.wav");
	//场景切换
	Director::getInstance()->replaceScene(TransitionFade::create(CHANGESCENE_TIME,GameLayer::createScene()));
}
