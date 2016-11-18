#include "GameLayer.h"
#include "define.h"
#include "EdgeLayer.h"
#include "WallLayer.h"
#include "NumberLayer.h"
#include "GameOverLayer.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
GameLayer::GameLayer()
{
}
GameLayer::~GameLayer()
{
}
cocos2d::Scene * GameLayer::createScene()
{
	//创造物理场景
	auto scene=Scene::createWithPhysics();
	//GRAVITY的值为（0，-580）
	scene->getPhysicsWorld()->setGravity(GRAVITY);
	auto gameLayer=GameLayer::create();
	scene->addChild(gameLayer);
	return scene;
}

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	auto origin=Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();

	Sprite * bg;
	bg=Sprite::createWithSpriteFrameName(LAYER);
	bg->setPosition(Point(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));
	this->addChild(bg);
	//边框层
	auto edgeLayer = EdgeLayer::create();
	edgeLayer->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	edgeLayer->setPosition(Point::ZERO);
	this->addChild(edgeLayer, 2);

	//障碍层
	auto wallLayer = WallLayer::create();
	wallLayer->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	wallLayer->setPosition(Point::ZERO);
	this->addChild(wallLayer, 1);
	//主角
	helicopter = SpriteHelicopter::createHelicopter();
	helicopter->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	helicopter->setPosition(Point::ZERO);
	this->addChild(helicopter, 2);

	helicopter->changeState(ACTION_STATE_IDLE);
	//这里创建了触控侦听
	//点击屏幕，游戏开始，并移除这个侦听
	auto listener=EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan=[=](Touch * t,Event * e)
	{
		return true;
	};
	listener->onTouchEnded=[=](Touch * t,Event * e)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("touch.wav");
		wallLayer->startWall();
		startGame();
		_eventDispatcher->removeEventListener(listener);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	//碰撞检测侦听
	contactListener=EventListenerPhysicsContact::create();
	contactListener->onContactBegin=[=](const PhysicsContact& contact)
	{
		//当检测到碰撞的时候，播放声音
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("fail1.wav");
		//停止运动
		wallLayer->stopWall();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		//改变状态
		helicopter->changeState(ACTION_STATE_DIE);
		//移除积分器
		this->removeChild(NumberLayer::getInstance());
		//游戏结束后计分板出现
		auto scorecard=GameOverLayer::create();
		scorecard->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
		scorecard->setPosition(Point::ZERO);
		this->addChild(scorecard,3);
		_eventDispatcher->removeEventListener(contactListener);
		return true;
	};
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener,this);

	return true;
}


void GameLayer::startGame()
{
	//游戏开始，转换到飞行状态
	helicopter->changeState(ACTION_STATE_FLY);
	//加入积分器并初始化
	NumberLayer::getInstance()->initScore();
	this->addChild(NumberLayer::getInstance(),10);

}


