//SpriteBird.cpp
#include "SpriteHelicopter.h"
#include "SimpleAudioEngine.h"
#include "define.h"
USING_NS_CC;
SpriteHelicopter * instance = NULL;
SpriteHelicopter::SpriteHelicopter()
{
}

SpriteHelicopter::~SpriteHelicopter()
{
}
//单例类最主要部分
SpriteHelicopter * SpriteHelicopter::getInstance()
{
	//判断这个对象是否存在
	if (instance == NULL)
	{
		//如果不存在，那就创建
		SpriteHelicopter * temp = new SpriteHelicopter();
		//然后初始化
		temp->init();
		instance = temp;
	}
	//如果已经存在了，那就直接返回
	return instance;
}

bool SpriteHelicopter::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto origin=Director::getInstance()->getVisibleOrigin();
	auto visibleSize=Director::getInstance()->getVisibleSize();

	Animate * animate;
	sprite_helicopter = Sprite::createWithSpriteFrameName("helicopter_1.png");
	animate=Animate::create(AnimationCache::getInstance()->getAnimation(HELICOPTERANIMATION));
	sprite_helicopter->runAction(RepeatForever::create(animate));

	PhysicsBody * body=PhysicsBody::create();
	body->addShape(PhysicsShapeBox::create(sprite_helicopter->getContentSize()*0.7));
	body->setDynamic(true);
	body->setLinearDamping(0.7f);
	body->setGravityEnable(false);
	body->setCategoryBitmask(1);
	body->setCollisionBitmask(-1);
	body->setContactTestBitmask(-1);
	sprite_helicopter->setPhysicsBody(body);
	sprite_helicopter->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height*0.6));
	this->addChild(sprite_helicopter);

	//点击侦听，listener是单点触控
	//每次点击都会向上（Y轴）飞一段距离
	//这里我们就给它赋值一个初速度（Y轴）
	listener=EventListenerTouchOneByOne::create();
	//设置触控是否向下传递
	listener->setSwallowTouches(false);
	//这里只用到了触控开始和结束
	listener->onTouchBegan=[=](Touch * t,Event *e)
	{
		return true;
	};
	listener->onTouchEnded=[=](Touch *t,Event *e)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("touch.wav");
		//初速度
		sprite_helicopter->getPhysicsBody()->setVelocity(VELOCITY);
	};
	this->scheduleUpdate();
	return true;
}
//创造对象
SpriteHelicopter * SpriteHelicopter::createHelicopter()
{
	SpriteHelicopter * temp = new SpriteHelicopter();
	temp->init();
	return temp;
}
//三种状态的切换
void SpriteHelicopter::changeState(ActionState as)
{
	switch (as)
	{
	case ACTION_STATE_IDLE:
		stateIdle();
		break;
	case ACTION_STATE_FLY:
		stateFly();
		break;
	case ACTION_STATE_DIE:
		stateDie();
		break;
	default:
		break;
	}
}

//切换到空闲状态
//1:添加到点击侦听中去
//2:移除重力感应（因为在这个状态下，悬停在空中的）
void SpriteHelicopter::stateIdle()
{
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, sprite_helicopter);
	sprite_helicopter->getPhysicsBody()->setGravityEnable(false);
}
//切换到飞行状态
//设置重力感应
void SpriteHelicopter::stateFly()
{
	sprite_helicopter->getPhysicsBody()->setGravityEnable(true);
}
//切换到死亡状态
void SpriteHelicopter::stateDie()
{
	//关闭定时器
	this->unscheduleUpdate();
	//移除点击侦听
	_eventDispatcher->removeEventListener(listener);
	
	//开启重力感应
	sprite_helicopter->getPhysicsBody()->setGravityEnable(true);
	//停止的所有动画
	sprite_helicopter->stopAllActions();

	sprite_helicopter->setRotation(HELICOPTER_DIE_ROTATION);

}

void SpriteHelicopter::update(float)
{
	auto origin=Director::getInstance()->getVisibleOrigin();
	auto visibleSize=Director::getInstance()->getVisibleSize();
	//防止飞出边界
	if (sprite_helicopter->getPositionY()>(origin.y + visibleSize.height)  )
	{
		sprite_helicopter->setPositionY(origin.y + visibleSize.height);
	}
	if (sprite_helicopter->getPositionY()<15)
	{
		sprite_helicopter->setPositionY(15);
	}
}
