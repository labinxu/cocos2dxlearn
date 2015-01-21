#ifndef _SPLASHSCREEN_H_
#define _SPLASHSCREEN_H_

#include "cocos2d.h"
#include <vector>

class SplashScreen :public cocos2d::Layer
{
  public:
    static cocos2d::Scene *createScene();
    virtual bool init();
    bool setupSprites();
    void swapPosition(cocos2d::Sprite* spr1, cocos2d::Sprite* spr2);
    void startMove(float dt);
    void moveKeSpriteToLeft();
    void moveMaiSpriteToLeft();
    void spriteFadeOut();
    void gotoMenuScene();
    CREATE_FUNC(SplashScreen);

  private:
    cocos2d::Sprite *pSprCheng;
    cocos2d::Sprite *pSprKe;
    cocos2d::Sprite *pSprJi;
    cocos2d::Sprite *pSprMai;
    cocos2d::Size spriteSize;
};
#endif
