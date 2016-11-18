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
	//���������ͷ�����
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
	//wall_arr1 ���������ӷֵ�
	wall_arr1=Array::create();
	//��ֹ���Զ��ͷ�
	wall_arr1->retain();
	//wall_arr2 �������ֹͣ�˶�
	wall_arr2 = Array::create();
	//��ֹ���Զ��ͷ�
	wall_arr2->retain();
	return true;
}

void WallLayer::addWall(float)
{
	random = rand() % 10;
	int wall_number = 0;
	if (random <= 5){
		wall_number = 0;   // ϸ����
	}
	else if (random <= 7){
		wall_number = 1;   // ����
	}
	else if (random <= 9){
		wall_number = 2;   // ϸ����
	}
	//���Ϲܵ���ʼ��
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

	//���¹ܵ���ʼ������ߵ�THROUGH_HEIGHT�������ܵ�֮��Ŀ�϶
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
	//�����node��
	auto node=Node::create();
	node->addChild(wall_up, 0, WALL_UP);
	node->addChild(wall_down, 0, WALL_DOWN);
	node->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	//ǽ�����ƶ��ķ�Χ
	Wall_Range = 100;  
	int range = rand() % Wall_Range;
	node->setPosition(Point(WALL_X, WALL_Y + range));
	//ǽ�ƶ���ʱ�䣬���룬�Լ�����
	wall_left_speed = -120 * 3.6;
	wall_upanddown_speed = 0;  
	if (NumberLayer::getInstance()->getScore() <10 ){
		//�����ƶ�ǽ�ĸ���Ϊ1/3
		if ((rand()%9) >= 7 ){
			wall_upanddown_speed = 60;
		}
		else{
			wall_upanddown_speed = 0;
		}
		//�ƶ��������
		if ((rand() % 2) == 1){
			wall_upanddown_speed = -wall_upanddown_speed;
		}
	}
	else if (NumberLayer::getInstance()->getScore() < 20){
		Wall_Range = 120;  //ǽ�����ƶ��ķ�Χ
		//�����ƶ�ǽ�ĸ���Ϊ1/2
		if ((rand() % 10) >= 5){
			wall_upanddown_speed = 100;
		}
		else{
			wall_upanddown_speed = 0;
		}
		//�ƶ��������
		if ((rand() % 2) == 1){
			wall_upanddown_speed = -wall_upanddown_speed;
		}
	}
	else if (NumberLayer::getInstance()->getScore() < 30){
		Wall_Range = 140;  //ǽ�����ƶ��ķ�Χ
		//�����ƶ�ǽ�ĸ���Ϊ2/3
		if ((rand() % 9) >= 2){
			wall_upanddown_speed = 140;
		}
		else{
			wall_upanddown_speed = 0;
		}
		//�ƶ��������
		if ((rand() % 2) == 1){
			wall_upanddown_speed = -wall_upanddown_speed;
		}
	}
	else if (NumberLayer::getInstance()->getScore() > 30){
		Wall_Range = 160;  //ǽ�����ƶ��ķ�Χ
		//�����ƶ�ǽ�ĸ���Ϊ1 
		wall_upanddown_speed = 150;
		//�ƶ��������
		if ((rand() % 2) == 1){
			wall_upanddown_speed = -wall_upanddown_speed;
		}
	}
	auto moveby = MoveBy::create(WALL_TIME, Point(wall_left_speed, wall_upanddown_speed));
	//�ƶ�������ִ�еĻص�����
	auto callback=CallFuncN::create(CC_CALLBACK_1(WallLayer::wallMoveOver,this));
	//�ƶ��ͽ�����Ļص��ŵ��ж���
	auto sequence=Sequence::create(moveby,callback,NULL);
	node->runAction(sequence);

	this->addChild(node);
	//��ǽ�ŵ�����������
	wall_arr1->addObject(node);
	wall_arr2->addObject(node);
	//��ͬ��ȵ�ǽ���ֳ���ʱ�䲻ͬ
	if (random <= 5){
		wall_show = 1.4f;   // ϸ
	}
	else if (random <= 7){
		wall_show = 1.7f;   // �ϴ�
	}
	else if (random <= 9){
		wall_show = 2.0f;   // ��
	}
	if (btn)
	{
		this->scheduleUpdate();
		btn = false;
	}
	this->schedule(schedule_selector(WallLayer::addWall), wall_show);
}
//�ƶ������󣬴��������������Ƴ�
void WallLayer::wallMoveOver(Ref * r)
{
	Sprite * sp=(Sprite* )r;
	this->removeChild(sp);
	wall_arr2->removeObject(sp);
	wall_arr1->removeObject(sp);
}
//ֹͣ�ƶ���������
void WallLayer::stopWall()
{
	this->unschedule(schedule_selector(WallLayer::addWall));
	this->unscheduleUpdate();
	Ref * p;
	CCARRAY_FOREACH(wall_arr2,p)
	{
		auto n=(Node*)p;
		//ֹͣ�ƶ�
		n->stopAllActions();
	}
	
}
//����
void WallLayer::update(float)
{
	auto origin=Director::getInstance()->getVisibleOrigin();
	auto visibleSize=Director::getInstance()->getVisibleSize();
	//����ܵ�����Ϊ0����ֱ�ӷ���
    if (wall_arr1->count()<=0)
	{
		return;
	}
	Node * tn = (Node*)wall_arr1->getObjectAtIndex(0);
	//�ӷֲ���
	if (tn->getPositionX()<(visibleSize.width / 2-40 ))
	{
		wall_arr1->removeObjectAtIndex(0);
		NumberLayer::getInstance()->addScore();
	}
}
//��ʼ�ƶ�
void WallLayer::startWall()
{
	random = rand() % 10;
	if (random <= 5){
		wall_show = 1.4f;   // ϸ
	}
	else if (random <= 7){
		wall_show = 1.7f;   // �ϴ�
	}
	else if (random <= 9){
		wall_show = 2.0f;   // ��
	}
	this->schedule(schedule_selector(WallLayer::addWall), wall_show);
}
