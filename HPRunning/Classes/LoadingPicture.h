//
//  LoadingPicture.h
//  HPRunning
//
//  Created by student on 14-5-12.
//
//

#ifndef __HPRunning__LoadingPicture__
#define __HPRunning__LoadingPicture__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class LoadingPicture : public CCLayer
{
public:
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(LoadingPicture);
    
    void addpicture1();
    void addpicture2();
    void addpicture3();
    void addpicture4();
    
    void replaceScene();
};
#endif /* defined(__HPRunning__LoadingPicture__) */
