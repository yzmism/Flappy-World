#ifndef MainMenuScene_h
#define MainMenuScene_h

#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include <stdio.h>

class MainMenu : public cocos2d::Layer {
public:
    // there's no 'id' in cpp, so we recommend returning the class instance
    // pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of
    // returning 'id' in cocos2d-iphone
    virtual bool init();

    // a selector callback
    void startGameCall(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);

private:
    CocosDenshion::SimpleAudioEngine* sceneAudio;

    void setAudio();
    void preloadAudio();
    void playBackgroundMusic();
    void stopBackgroundMusic();
};

#endif // MainMenuScene_h //
