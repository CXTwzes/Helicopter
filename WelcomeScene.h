#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#pragma once
#include "cocos2d.h"
class WelcomeScene:public cocos2d::Layer
{
public:
	WelcomeScene();
	~WelcomeScene();
	//������ӭ����ĳ���
	static cocos2d::Scene * createScene();
	//��ʼ������
	bool init();
	//������Դ�����󳡾��л�����
	void loadingDone();
	CREATE_FUNC(WelcomeScene);
private:

};
#endif
