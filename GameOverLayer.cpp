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

	//获取历史最高分
	highScore=GetLocalScore::getInstance()->getHighScore();

	//再来一次按钮
	auto start_sprite_1 = Sprite::createWithSpriteFrameName("again1.png");
	auto start_sprite_2 = Sprite::createWithSpriteFrameName("again2.png");
	auto start_button = MenuItemSprite::create(start_sprite_1, start_sprite_2, CC_CALLBACK_0(GameOverLayer::gameAgain, this));
	start_button->setPosition(Point(origin.x + visibleSize.width / 2 , origin.y + visibleSize.height*0.7));
	auto menu = Menu::create(start_button, NULL);
	menu->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);


	//退出游戏按钮
	auto over_sprite1 = Sprite::createWithSpriteFrameName("gameOver.png");
	auto over_sprite2 = Sprite::createWithSpriteFrameName("gameOver2.png");
	auto over_button = MenuItemSprite::create(over_sprite1, over_sprite2, CC_CALLBACK_0(GameOverLayer::gameOver, this));
	over_button->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height*0.3));
	auto menu2 = Menu::create(over_button, NULL);
	menu2->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	menu2->setPosition(Point::ZERO);
	this->addChild(menu2);

	//计分区域动画
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

	//分数显示
	score=0;
	auto str=__String::createWithFormat("%d",score);
	numberLabel=Label::createWithBMFont("font2.fnt",str->getCString());
	numberLabel->setPosition(Point(origin.x+visibleSize.width/2+45,origin.y+visibleSize.height*0.5+25));
	this->addChild(numberLabel);
	
	//当分数大于0时执行一个分数从0到n的动画
	if (NumberLayer::getInstance()->getScore()>0)
	{
		this->schedule(schedule_selector(GameOverLayer::showScore),ADDSCORE_FRE);
	}

	//历史最高分
	auto str1=__String::createWithFormat("%d",highScore);
	auto highscorelabel = Label::createWithBMFont("font2.fnt", str1->getCString());
	highscorelabel->setPosition(Point(origin.x+visibleSize.width/2+45,origin.y+visibleSize.height*0.5-40));
	this->addChild(highscorelabel);
	//如果当前分数大于历史最高分，则写入 
	if (NumberLayer::getInstance()->getScore()>highScore)
	{
		GetLocalScore::getInstance()->setHighScore(NumberLayer::getInstance()->getScore());
	}

}

//再来一次，场景切换
void GameOverLayer::gameAgain()
{
	//音效
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("change.wav");
	Director::getInstance()->replaceScene(TransitionFade::create(CHANGESCENE_TIME,GameLayer::createScene()));
}

void GameOverLayer::gameOver()
{
	exit(0);
}

//分数显示动画
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
