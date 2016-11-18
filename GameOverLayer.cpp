//GameOverLayer.cpp
#include "SimpleAudioEngine.h"
#include "GameOverLayer.h"
#include "define.h"
#include "GameLayer.h"
#include "NumberLayer.h"
#include "GetLocalScore.h"
USING_NS_CC;

GameOverLayer::GameOverLayer()
{
	
}

GameOverLayer::~GameOverLayer()
{
}

bool GameOverLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto origin=Director::getInstance()->getVisibleOrigin();
	auto visibleSize=Director::getInstance()->getVisibleSize();

	//��ȡ��ʷ��߷�
	highScore=GetLocalScore::getInstance()->getHighScore();

	//����һ�ΰ�ť
	auto start_sprite_1 = Sprite::createWithSpriteFrameName("again1.png");
	auto start_sprite_2 = Sprite::createWithSpriteFrameName("again2.png");
	auto start_button = MenuItemSprite::create(start_sprite_1, start_sprite_2, CC_CALLBACK_0(GameOverLayer::gameAgain, this));
	start_button->setPosition(Point(origin.x + visibleSize.width / 2 , origin.y + visibleSize.height*0.7));
	auto menu = Menu::create(start_button, NULL);
	menu->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);


	//�˳���Ϸ��ť
	auto over_sprite1 = Sprite::createWithSpriteFrameName("gameOver.png");
	auto over_sprite2 = Sprite::createWithSpriteFrameName("gameOver2.png");
	auto over_button = MenuItemSprite::create(over_sprite1, over_sprite2, CC_CALLBACK_0(GameOverLayer::gameOver, this));
	over_button->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height*0.3));
	auto menu2 = Menu::create(over_button, NULL);
	menu2->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	menu2->setPosition(Point::ZERO);
	this->addChild(menu2);

	//�Ʒ����򶯻�
	box=Sprite::createWithSpriteFrameName("score_panel_2.png");
	box->setPosition(Point(origin.x+visibleSize.width/2,origin.y-visibleSize.height/2));
	auto moveto=MoveTo::create(SCORECARD_SHOW_TIME,Point(origin.x+visibleSize.width/2,origin.y+visibleSize.height*0.5));
	auto callback=CallFuncN::create(CC_CALLBACK_0(GameOverLayer::callBack,this));
	auto sequence=Sequence::create(moveto,callback,NULL);
	this->addChild(box);
	box->runAction(sequence);
	return true;
}

void GameOverLayer::callBack()
{
	auto origin=Director::getInstance()->getVisibleOrigin();
	auto visibleSize=Director::getInstance()->getVisibleSize();

	//������ʾ
	score=0;
	auto str=__String::createWithFormat("%d",score);
	numberLabel=Label::createWithBMFont("font2.fnt",str->getCString());
	numberLabel->setPosition(Point(origin.x+visibleSize.width/2+45,origin.y+visibleSize.height*0.5+25));
	this->addChild(numberLabel);
	
	//����������0ʱִ��һ��������0��n�Ķ���
	if (NumberLayer::getInstance()->getScore()>0)
	{
		this->schedule(schedule_selector(GameOverLayer::showScore),ADDSCORE_FRE);
	}

	//��ʷ��߷�
	auto str1=__String::createWithFormat("%d",highScore);
	auto highscorelabel = Label::createWithBMFont("font2.fnt", str1->getCString());
	highscorelabel->setPosition(Point(origin.x+visibleSize.width/2+45,origin.y+visibleSize.height*0.5-40));
	this->addChild(highscorelabel);
	//�����ǰ����������ʷ��߷֣���д�� 
	if (NumberLayer::getInstance()->getScore()>highScore)
	{
		GetLocalScore::getInstance()->setHighScore(NumberLayer::getInstance()->getScore());
	}

}

//����һ�Σ������л�
void GameOverLayer::gameAgain()
{
	//��Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("change.wav");
	Director::getInstance()->replaceScene(TransitionFade::create(CHANGESCENE_TIME,GameLayer::createScene()));
}

void GameOverLayer::gameOver()
{
	exit(0);
}

//������ʾ����
void GameOverLayer::showScore( float )
{
	score++;
	auto str=__String::createWithFormat("%d",score);
	numberLabel->setString(str->getCString());
	if (score==NumberLayer::getInstance()->getScore())
	{
		this->unschedule(schedule_selector(GameOverLayer::showScore));
	}
}
