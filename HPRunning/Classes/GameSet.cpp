//
//  GameSet.cpp
//  HPRunning
//
//  Created by student on 14-5-12.
//
//

#include "GameSet.h"
#include "SimpleAudioEngine.h"
bool ismusicON=true;
float musicvalue=1.0;

bool GameSet::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    CCSprite* sprite=CCSprite::create("layer2.png");
    sprite->setPosition(ccp(350,70));
    sprite->setScale(0.4);
    this->addChild(sprite);
    CCMenuItemImage* item=CCMenuItemImage::create("taskIndex.png", "taskIndex.png");
    item->setScale(2.0);
    item->setPosition(ccp(190,-50));
    item->setTarget(this, menu_selector(GameSet::Back));
    CCMenu* menu=CCMenu::create(item,NULL);
    menu->setTouchPriority(-130);
    this->addChild(menu);
    this->addSwitch();
    this->setTouchEnabled(true);
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -129, true);
    return true;
}

CCScene* GameSet::scene()
{
    CCScene* scene=CCScene::create();
    GameSet* layer=GameSet::create();
    scene->addChild(layer);
    return scene;
}

void GameSet::musicOn()
{
    if(ismusicON)
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
        ismusicON=false;
    }
    else
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
        ismusicON=true;
    }

}

void GameSet::Back()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    this->removeAllChildren();
    this->removeFromParent();

}

void GameSet::addSwitch()
{
    CCLabelTTF* label=CCLabelTTF::create("音效", "Zapinfo", 25);
    label->setColor(ccc3(0, 0, 255));
    label->setPosition(ccp(220,120));
    this->addChild(label);
    
    CCLabelTTF* label1=CCLabelTTF::create("音量", "Zapinfo", 25);
    label1->setColor(ccc3(0, 0, 255));
    label1->setPosition(ccp(220,60));
    this->addChild(label1);
    
    CCMenuItemImage* item1=CCMenuItemImage::create("musicOn.png", "musicOn.png");
    CCMenuItemImage* item2=CCMenuItemImage::create("musicOff.png", "musicOff.png");
    if(ismusicON==true)
    {
        CCMenuItemToggle* toogle=CCMenuItemToggle::createWithTarget(this, menu_selector(GameSet::musicOn), item1,item2,NULL);
        toogle->setPosition(ccp(50,-118));
        toogle->setScale(0.3);
        CCMenu* menu=CCMenu::create(toogle,NULL);
        menu->setTouchPriority(-130);
        this->addChild(menu);
    }
    else
    {
        CCMenuItemToggle* toogle=CCMenuItemToggle::createWithTarget(this, menu_selector(GameSet::musicOn), item2,item1,NULL);
        toogle->setPosition(ccp(50,-118));
        toogle->setScale(0.3);
        CCMenu* menu=CCMenu::create(toogle,NULL);
        menu->setTouchPriority(-130);
        this->addChild(menu);
    }
    
    //声音大小
    slider=CCControlSlider::create("button1.png", "button2.png", "miner1.png");
    slider->setAnchorPoint(ccp(0.5,0.5));
    slider->setMinimumValue(0);
    slider->setTouchEnabled(true);
    slider->setMaximumValue(1.0);
    slider->setPosition(ccp(400,60));
    slider->addTargetWithActionForControlEvents(this, cccontrol_selector(GameSet::voicechange), CCControlEventValueChanged);
    slider->setScale(0.4);
    slider->setValue(musicvalue);
    slider->setTouchPriority(-130);
    this->addChild(slider);

}

void GameSet::voicechange()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(slider->getValue());
    musicvalue=slider->getValue();
    CCLog("%f",slider->getValue());
}

bool GameSet::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}

void GameSet::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}

void GameSet::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}

void GameSet::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    
}
