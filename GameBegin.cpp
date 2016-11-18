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
	//��ȡ OpenGL ��ͼ�ĳ�ʼ��ʱ�Ŀɼ���С
	auto origin=Director::getInstance()->getVisibleOrigin();
	auto visibleSize=Director::getInstance()->getVisibleSize();

	Sprite * bg;
	bg=Sprite::createWithSpriteFrameName(LAYER);
	bg->setPosition(Point(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));
	this->addChild(bg);

	//��Ϸ����
	auto title=Sprite::createWithSpriteFrameName("title.png");
	title->setPosition(Point(origin.x+visibleSize.width/2,origin.y+visibleSize.height*0.6));
	this->addChild(title);

	//ֱ����
	auto helicopter= Sprite::createWithSpriteFrameName("helicopter_1.png");
	helicopter->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height*0.65));
    helicopter->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(HELICOPTERANIMATION))));
	this->addChild(helicopter);

	//��ʼ��ť
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

//��ť�ص�
void GameBegin::startGame()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("change.wav");
	//�����л�
	Director::getInstance()->replaceScene(TransitionFade::create(CHANGESCENE_TIME,GameLayer::createScene()));
}
