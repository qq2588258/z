//
//  Role.cpp
//  HPRunning
//
//  Created by student on 14-5-6.
//
//

#include "Role.h"
Role::Role()
{
    IsAttack=false;
    time=0;
    stateCtl=0;
    statejump=0;
    MaxJumpCount=2;
    currentJumpCount=0;
}

Role::~Role()
{

}

bool Role::init()
{
    return true;
}


void Role::setCurrentRolePoint(CCPoint point)
{
    this->setPosition(point);
}

CCPoint Role::getCurrentRolePoint()
{
    return this->getPosition();
}

void Role::runSate()//跑动帧动画
{
    CCArray* array=CCArray::createWithCapacity(40);
    array->retain();
    for(int i=0;i<10;i++)
    {
        char fram[30];
        if(i<9)
        {
            sprintf(fram, "run%d.png",i+1);
        }
        else
        {
            sprintf(fram, "run%d.png",i+1);
        }
        CCSpriteFrame* framName=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fram);
        array->addObject(framName);
    }
    CCAnimation* animation=CCAnimation::createWithSpriteFrames(array,0.05);
    CCAnimate* animate=CCAnimate::create(animation);
    CCRepeatForever* forever=CCRepeatForever::create(animate);
    this->runAction(forever);
    array->release();
}

void Role::jumpState()//跳动帧动画
{
    CCArray* array=CCArray::createWithCapacity(40);
    array->retain();
    for(int i=0;i<8;i++)
    {
        char fram[30];
        sprintf(fram, "jump1%d.png",i+1);
        CCSpriteFrame* framName=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fram);
        array->addObject(framName);
    }
    CCAnimation* animation=CCAnimation::createWithSpriteFrames(array,0.05);
    CCAnimate* animate=CCAnimate::create(animation);
    this->runAction(animate);
    array->release();
}

void Role::attackState()
{
    IsAttack=true;
    CCArray* array=CCArray::createWithCapacity(40);
    array->retain();
    for(int i=0;i<6;i++)
    {
        char fram[30];
        sprintf(fram, "att%d.png",i+1);
        CCSpriteFrame* framName=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fram);
        array->addObject(framName);
    }
    CCAnimation* animation=CCAnimation::createWithSpriteFrames(array,0.05);
    CCAnimate* animate=CCAnimate::create(animation);
    this->runAction(animate);
    array->release();
}