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
	//����������
	auto scene=Scene::createWithPhysics();
	//GRAVITY��ֵΪ��0��-580��
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
	//�߿��
	auto edgeLayer = EdgeLayer::create();
	edgeLayer->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	edgeLayer->setPosition(Point::ZERO);
	this->addChild(edgeLayer, 2);

	//�ϰ���
	auto wallLayer = WallLayer::create();
	wallLayer->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	wallLayer->setPosition(Point::ZERO);
	this->addChild(wallLayer, 1);
	//����
	helicopter = SpriteHelicopter::createHelicopter();
	helicopter->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	helicopter->setPosition(Point::ZERO);
	this->addChild(helicopter, 2);

	helicopter->changeState(ACTION_STATE_IDLE);
	//���ﴴ���˴�������
	//�����Ļ����Ϸ��ʼ�����Ƴ��������
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
	//��ײ�������
	contactListener=EventListenerPhysicsContact::create();
	contactListener->onContactBegin=[=](const PhysicsContact& contact)
	{
		//����⵽��ײ��ʱ�򣬲�������
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("fail1.wav");
		//ֹͣ�˶�
		wallLayer->stopWall();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		//�ı�״̬
		helicopter->changeState(ACTION_STATE_DIE);
		//�Ƴ�������
		this->removeChild(NumberLayer::getInstance());
		//��Ϸ������Ʒְ����
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
	//��Ϸ��ʼ��ת��������״̬
	helicopter->changeState(ACTION_STATE_FLY);
	//�������������ʼ��
	NumberLayer::getInstance()->initScore();
	this->addChild(NumberLayer::getInstance(),10);

}


