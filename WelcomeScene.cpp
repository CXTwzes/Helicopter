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
	//��ȡ��Ϸ��ͼƬ��Դ
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("source.plist");
	//�����س������ñ���
	auto bg=Sprite::createWithSpriteFrameName("loading.png");
	bg->setPosition(Point(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));
	this->addChild(bg);
	//��������
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("touch.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("fail1.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("change.wav");

	//�൱��֡����
	auto animation=Animation::create();
	animation->setDelayPerUnit(LOADING_FRE);
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("zt1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("zt2.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("zt3.png"));


	auto animate=Animate::create(animation);
	auto repeat=Repeat::create(animate,LOADING_NUM);
	//�ص��������л�����
	auto callBack=CallFuncN::create(CC_CALLBACK_0(WelcomeScene::loadingDone,this));
	//Ȼ��Ѷ����ͻص������ŵ�һ���ж��У���ִ�ж���������ִ�����˻ص��г���
	auto sequence=Sequence::create(repeat,callBack,NULL);
	//���嶯���ĵ�һ֡
	auto loading = Sprite::createWithSpriteFrameName("zt1.png");
	loading->setPosition(Point(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));
	this->addChild(loading);
	//ִ�ж���

	loading->runAction(sequence);

	//Helicopter�Ķ�������
	//�ŵ�������
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
	//�ŵ������У���define.h�ļ�
	AnimationCache::getInstance()->addAnimation(helicopterAnimation, HELICOPTERANIMATION);

	return true;
}
//loading����ִ�����Ļص�����
void WelcomeScene::loadingDone()
{
	//�л���GameBegin����
	Director::getInstance()->replaceScene(TransitionFade::create(CHANGESCENE_TIME, GameBegin::createScene()));

}
