#include "AppDelegate.h"
#include "MainGame.h"
#include "Loading.h"
#include "StartGame.h"
#include "GameSet.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(800, 480, kResolutionFixedHeight);
    
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("jump.plist","jump.png");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("run.plist","run.png");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("enemy_att.plist","enemy_att.png");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("enemy2_att.plist","enemy2_att.png");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("enemy3_att.plist","enemy3_att.png");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("att.plist","att.png");
    // create a scene. it's an autorelease object
    CCScene *pScene =Loading::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
