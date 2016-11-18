//EdgeLayer.cpp
#include "EdgeLayer.h"
#include "define.h"
USING_NS_CC;
EdgeLayer::EdgeLayer()
{
}

EdgeLayer::~EdgeLayer()
{
}

bool EdgeLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto origin=Director::getInstance()->getVisibleOrigin();
	auto visibleSize=Director::getInstance()->getVisibleSize();

	edge=Sprite::createWithSpriteFrameName("layer3.png");
	edge->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(edge,2);
	return true;
}

