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
//����������Ҫ����
SpriteHelicopter * SpriteHelicopter::getInstance()
{
	//�ж���������Ƿ����
	if (instance == NULL)
	{
		//��������ڣ��Ǿʹ���
		SpriteHelicopter * temp = new SpriteHelicopter();
		//Ȼ���ʼ��
		temp->init();
		instance = temp;
	}
	//����Ѿ������ˣ��Ǿ�ֱ�ӷ���
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

	//���������listener�ǵ��㴥��
	//ÿ�ε���������ϣ�Y�ᣩ��һ�ξ���
	//�������Ǿ͸�����ֵһ�����ٶȣ�Y�ᣩ
	listener=EventListenerTouchOneByOne::create();
	//���ô����Ƿ����´���
	listener->setSwallowTouches(false);
	//����ֻ�õ��˴��ؿ�ʼ�ͽ���
	listener->onTouchBegan=[=](Touch * t,Event *e)
	{
		return true;
	};
	listener->onTouchEnded=[=](Touch *t,Event *e)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("touch.wav");
		//���ٶ�
		sprite_helicopter->getPhysicsBody()->setVelocity(VELOCITY);
	};
	this->scheduleUpdate();
	return true;
}
//�������
SpriteHelicopter * SpriteHelicopter::createHelicopter()
{
	SpriteHelicopter * temp = new SpriteHelicopter();
	temp->init();
	return temp;
}
//����״̬���л�
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

//�л�������״̬
//1:��ӵ����������ȥ
//2:�Ƴ�������Ӧ����Ϊ�����״̬�£���ͣ�ڿ��еģ�
void SpriteHelicopter::stateIdle()
{
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, sprite_helicopter);
	sprite_helicopter->getPhysicsBody()->setGravityEnable(false);
}
//�л�������״̬
//����������Ӧ
void SpriteHelicopter::stateFly()
{
	sprite_helicopter->getPhysicsBody()->setGravityEnable(true);
}
//�л�������״̬
void SpriteHelicopter::stateDie()
{
	//�رն�ʱ��
	this->unscheduleUpdate();
	//�Ƴ��������
	_eventDispatcher->removeEventListener(listener);
	
	//����������Ӧ
	sprite_helicopter->getPhysicsBody()->setGravityEnable(true);
	//ֹͣ�����ж���
	sprite_helicopter->stopAllActions();

	sprite_helicopter->setRotation(HELICOPTER_DIE_ROTATION);

}

void SpriteHelicopter::update(float)
{
	auto origin=Director::getInstance()->getVisibleOrigin();
	auto visibleSize=Director::getInstance()->getVisibleSize();
	//��ֹ�ɳ��߽�
	if (sprite_helicopter->getPositionY()>(origin.y + visibleSize.height)  )
	{
		sprite_helicopter->setPositionY(origin.y + visibleSize.height);
	}
	if (sprite_helicopter->getPositionY()<15)
	{
		sprite_helicopter->setPositionY(15);
	}
}
