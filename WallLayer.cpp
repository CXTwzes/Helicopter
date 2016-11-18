//WallLayer.cpp
#include "WallLayer.h"
#include "define.h"
#include "NumberLayer.h"
USING_NS_CC;

char up_Wall[3][9] = { "bar1.png", "bar2.png", "bar3.png" };
char down_Wall[3][10] = { "bar12.png", "bar22.png", "bar32.png" };

//int random = rand() % 4;
double wall_show = 0.0;

WallLayer::WallLayer()
{
}

WallLayer::~WallLayer()
{
	//析构函数释放数组
	wall_arr1->release();
	wall_arr2->release();
}

bool WallLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	btn = true;
	//wall_arr1 这个数组检测加分的
	wall_arr1=Array::create();
	//防止被自动释放
	wall_arr1->retain();
	//wall_arr2 这个数组停止运动
	wall_arr2 = Array::create();
	//防止被自动释放
	wall_arr2->retain();
	return true;
}

void WallLayer::addWall(float)
{
	random = rand() % 10;
	int wall_number = 0;
	if (random <= 5){
		wall_number = 0;   // 细管子
	}
	else if (random <= 7){
		wall_number = 1;   // 管子
	}
	else if (random <= 9){
		wall_number = 2;   // 细管子
	}
	//向上管道初始化
	auto wall_up = Sprite::createWithSpriteFrameName(up_Wall[wall_number]);
	wall_up->setPosition(Point(wall_up->getContentSize().width/2,wall_up->getContentSize().height/2-20));
	auto body_up=PhysicsBody::create();
	auto body_shape_up=PhysicsShapeBox::create(wall_up->getContentSize());
	body_up->addShape(body_shape_up);
	body_up->setDynamic(false);
	body_up->setGravityEnable(false);
	body_up->setCategoryBitmask(1);
	body_up->setCollisionBitmask(-1);
	body_up->setContactTestBitmask(-1);
	wall_up->setPhysicsBody(body_up);

	//向下管道初始化，这边的THROUGH_HEIGHT是两根管道之间的空隙
	auto wall_down = Sprite::createWithSpriteFrameName(down_Wall[wall_number]);
	wall_down->setPosition(Point(wall_down->getContentSize().width/2,wall_down->getContentSize().height/2+wall_up->getContentSize().height+THROUGH_HEIGHT));
	auto body_down=PhysicsBody::create();
	auto body_shape_down=PhysicsShapeBox::create(wall_down->getContentSize());
	body_down->addShape(body_shape_down);
	body_down->setDynamic(false);
	body_down->setGravityEnable(false);
	body_down->setCategoryBitmask(1);
	body_down->setCollisionBitmask(-1);
	body_down->setContactTestBitmask(-1);
	wall_down->setPhysicsBody(body_down);
	//存放在node中
	auto node=Node::create();
	node->addChild(wall_up, 0, WALL_UP);
	node->addChild(wall_down, 0, WALL_DOWN);
	node->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	//墙上下移动的范围
	Wall_Range = 100;  
	int range = rand() % Wall_Range;
	node->setPosition(Point(WALL_X, WALL_Y + range));
	//墙移动的时间，距离，以及方向
	wall_left_speed = -120 * 3.6;
	wall_upanddown_speed = 0;  
	if (NumberLayer::getInstance()->getScore() <10 ){
		//出现移动墙的概率为1/3
		if ((rand()%9) >= 7 ){
			wall_upanddown_speed = 60;
		}
		else{
			wall_upanddown_speed = 0;
		}
		//移动方向随机
		if ((rand() % 2) == 1){
			wall_upanddown_speed = -wall_upanddown_speed;
		}
	}
	else if (NumberLayer::getInstance()->getScore() < 20){
		Wall_Range = 120;  //墙上下移动的范围
		//出现移动墙的概率为1/2
		if ((rand() % 10) >= 5){
			wall_upanddown_speed = 100;
		}
		else{
			wall_upanddown_speed = 0;
		}
		//移动方向随机
		if ((rand() % 2) == 1){
			wall_upanddown_speed = -wall_upanddown_speed;
		}
	}
	else if (NumberLayer::getInstance()->getScore() < 30){
		Wall_Range = 140;  //墙上下移动的范围
		//出现移动墙的概率为2/3
		if ((rand() % 9) >= 2){
			wall_upanddown_speed = 140;
		}
		else{
			wall_upanddown_speed = 0;
		}
		//移动方向随机
		if ((rand() % 2) == 1){
			wall_upanddown_speed = -wall_upanddown_speed;
		}
	}
	else if (NumberLayer::getInstance()->getScore() > 30){
		Wall_Range = 160;  //墙上下移动的范围
		//出现移动墙的概率为1 
		wall_upanddown_speed = 150;
		//移动方向随机
		if ((rand() % 2) == 1){
			wall_upanddown_speed = -wall_upanddown_speed;
		}
	}
	auto moveby = MoveBy::create(WALL_TIME, Point(wall_left_speed, wall_upanddown_speed));
	//移动结束后执行的回调函数
	auto callback=CallFuncN::create(CC_CALLBACK_1(WallLayer::wallMoveOver,this));
	//移动和结束后的回调放到列队中
	auto sequence=Sequence::create(moveby,callback,NULL);
	node->runAction(sequence);

	this->addChild(node);
	//把墙放到两个数组中
	wall_arr1->addObject(node);
	wall_arr2->addObject(node);
	//不同厚度的墙出现出现时间不同
	if (random <= 5){
		wall_show = 1.4f;   // 细
	}
	else if (random <= 7){
		wall_show = 1.7f;   // 较粗
	}
	else if (random <= 9){
		wall_show = 2.0f;   // 粗
	}
	if (btn)
	{
		this->scheduleUpdate();
		btn = false;
	}
	this->schedule(schedule_selector(WallLayer::addWall), wall_show);
}
//移动结束后，从这个类和数组中移除
void WallLayer::wallMoveOver(Ref * r)
{
	Sprite * sp=(Sprite* )r;
	this->removeChild(sp);
	wall_arr2->removeObject(sp);
	wall_arr1->removeObject(sp);
}
//停止移动（死亡后）
void WallLayer::stopWall()
{
	this->unschedule(schedule_selector(WallLayer::addWall));
	this->unscheduleUpdate();
	Ref * p;
	CCARRAY_FOREACH(wall_arr2,p)
	{
		auto n=(Node*)p;
		//停止移动
		n->stopAllActions();
	}
	
}
//积分
void WallLayer::update(float)
{
	auto origin=Director::getInstance()->getVisibleOrigin();
	auto visibleSize=Director::getInstance()->getVisibleSize();
	//如果管道数量为0，则直接返回
    if (wall_arr1->count()<=0)
	{
		return;
	}
	Node * tn = (Node*)wall_arr1->getObjectAtIndex(0);
	//加分操作
	if (tn->getPositionX()<(visibleSize.width / 2-40 ))
	{
		wall_arr1->removeObjectAtIndex(0);
		NumberLayer::getInstance()->addScore();
	}
}
//开始移动
void WallLayer::startWall()
{
	random = rand() % 10;
	if (random <= 5){
		wall_show = 1.4f;   // 细
	}
	else if (random <= 7){
		wall_show = 1.7f;   // 较粗
	}
	else if (random <= 9){
		wall_show = 2.0f;   // 粗
	}
	this->schedule(schedule_selector(WallLayer::addWall), wall_show);
}
