#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#pragma once
#include "cocos2d.h"
class WelcomeScene:public cocos2d::Layer
{
public:
	WelcomeScene();
	~WelcomeScene();
	//创建欢迎界面的场景
	static cocos2d::Scene * createScene();
	//初始化函数
	bool init();
	//加载资源结束后场景切换函数
	void loadingDone();
	CREATE_FUNC(WelcomeScene);
private:

};
#endif
