#ifndef __EDGE_LAYER_H__
#define __EDGE_LAYER_H__
#pragma once
#include "cocos2d.h"

class EdgeLayer:public cocos2d::Layer
{
public:
	EdgeLayer();
	~EdgeLayer();
	bool init();
	CREATE_FUNC(EdgeLayer);
private:
	cocos2d::Sprite * edge;
};
#endif
