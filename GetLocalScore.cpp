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
//获得分数
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
//写入分数
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

