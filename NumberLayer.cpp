//NumberLayer.cpp
#include "NumberLayer.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
static NumberLayer * instance=NULL;
NumberLayer::NumberLayer()
{
}

NumberLayer::~NumberLayer()
{
}
//单例类初始化
NumberLayer * NumberLayer::getInstance()
{
	if (instance==NULL)
	{
		NumberLayer * temp=new NumberLayer();
		temp->init();
		instance=temp;
	}
	return instance;
}

bool NumberLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto origin=Director::getInstance()->getVisibleOrigin();
	auto visibleSize=Director::getInstance()->getVisibleSize();

	//初始化分数
	score=0;
	auto str=__String::createWithFormat("%d",score);
	numberLabel=Label::createWithBMFont("font1.fnt",str->getCString());
	numberLabel->setPosition(Point(origin.x+visibleSize.width/2,origin.y+visibleSize.height*0.85));
	this->addChild(numberLabel);

	return true;
}

void NumberLayer::addScore()
{
	score+=1;
	auto str=__String::createWithFormat("%d",score);
	numberLabel->setString(str->getCString());
}

void NumberLayer::initScore()
{
	score=0;
	auto str=__String::createWithFormat("%d",score);
	numberLabel->setString(str->getCString());
}

int NumberLayer::getScore()
{
	return score;
}
