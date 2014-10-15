//
//  Loading.cpp
//  HPRunning
//
//  Created by student on 14-5-12.
//
//

#include "Loading.h"
#include "LoadingPicture.h"
bool Loading::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    //添加精灵帧动画
    spriterMiner=CCSprite::create();
    spriterMiner->initWithFile("loading_01.png");
    spriterMiner->setPosition(ccp(600,100));
    spriterMiner->setScale(0.8);
    this->addChild(spriterMiner);
    
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
    spriterMiner->runAction(forever);
    array->release();

    CCSprite* sprite=CCSprite::create("loadfont.png");
    sprite->setPosition(ccp(600,50));
    sprite->setScale(0.5);
    this->addChild(sprite);
    
    i=0;
    //添加进度条
    timer=CCProgressTimer::create(CCSprite::create("load.png"));
    timer->setPercentage(0.0f);
    timer->setBarChangeRate(ccp(1,0));
    timer->setType(kCCProgressTimerTypeBar);
    timer->setMidpoint(ccp(0,0));
    timer->setPosition(ccp(350,200));
    timer->setScale(1.5);
    this->addChild(timer);
    
    //加载资源
    this->loading();

    return true;
}

CCScene* Loading::scene()
{
    CCScene* scene=CCScene::create();
    Loading* layer=Loading::create();
    scene->addChild(layer);
    return scene;
}

void Loading::jumpScene()
{
    if(i==10)
    {
        CCTransitionFade* scene=CCTransitionFade::create(3, LoadingPicture::scene(), ccYELLOW);
        CCDirector::sharedDirector()->replaceScene(scene);
    }

}

void Loading::loading()
{
    CCTextureCache::sharedTextureCache()->addImageAsync("Screenshot1.png", this, callfuncO_selector(Loading::loadPic));
    CCTextureCache::sharedTextureCache()->addImageAsync("Screenshot2.png", this, callfuncO_selector(Loading::loadPic));
    CCTextureCache::sharedTextureCache()->addImageAsync("Screenshot3.png", this, callfuncO_selector(Loading::loadPic));
    CCTextureCache::sharedTextureCache()->addImageAsync("Screenshot4.png", this, callfuncO_selector(Loading::loadPic));
    CCTextureCache::sharedTextureCache()->addImageAsync("Icon57.png", this, callfuncO_selector(Loading::loadPic));
    CCTextureCache::sharedTextureCache()->addImageAsync("Icon72.png", this, callfuncO_selector(Loading::loadPic));
    CCTextureCache::sharedTextureCache()->addImageAsync("Icon80.png", this, callfuncO_selector(Loading::loadPic));
    CCTextureCache::sharedTextureCache()->addImageAsync("Icon114.png", this, callfuncO_selector(Loading::loadPic));
    CCTextureCache::sharedTextureCache()->addImageAsync("logo.png", this, callfuncO_selector(Loading::loadPic));
    CCTextureCache::sharedTextureCache()->addImageAsync("load.png", this, callfuncO_selector(Loading::loadPic));
}

void Loading::loadPic()
{
    i++;
    timer->setPercentage(i*10);
    CCLog("%d",i);
    this->jumpScene();
}