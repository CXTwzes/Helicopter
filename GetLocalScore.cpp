//GetLocalScore.cpp
#include "GetLocalScore.h"
USING_NS_CC;
static GetLocalScore * instance=NULL;

GetLocalScore::GetLocalScore()
{

}

GetLocalScore::~GetLocalScore()
{

}
GetLocalScore * GetLocalScore::getInstance()
{
	if (instance==NULL)
	{
		GetLocalScore * temp=new GetLocalScore();
		instance=temp;
	}
	return instance;
}

bool GetLocalScore::isHaveLocalFile()
{
	if (UserDefault::getInstance()->getBoolForKey("isHaveLocalFile"))
	{
		return true;
	}
	else
	{
		UserDefault::getInstance()->setBoolForKey("isHaveLocalFile",true);
		UserDefault::getInstance()->setIntegerForKey("highScore",0);
		UserDefault::getInstance()->flush();
		return false;
	}
}
//��÷���
int GetLocalScore::getHighScore()
{
	if (isHaveLocalFile())
	{
		return UserDefault::getInstance()->getIntegerForKey("highScore");
	}
	else
	{
		return 0;
	}
}
//д�����
void GetLocalScore::setHighScore( int n)
{
	if (isHaveLocalFile())
	{
		UserDefault::getInstance()->setIntegerForKey("highScore",n);
		UserDefault::getInstance()->flush();
	}
	else
	{
		UserDefault::getInstance()->setBoolForKey("isHaveLocalFile",true);
		UserDefault::getInstance()->setIntegerForKey("highScore",n);
		UserDefault::getInstance()->flush();
	}
}

