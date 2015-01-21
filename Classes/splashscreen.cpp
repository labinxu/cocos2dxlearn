#include "splashscreen.h"
#include "menuscene.h"
USING_NS_CC;


Scene* SplashScreen::createScene()
{
    auto scene = Scene::create();
    auto layer = SplashScreen::create();
    scene->addChild(layer);
    return scene;
}

bool SplashScreen::init()
{
    if (!Layer::init())
    {
        log("init layer error");
        return false;
    }
    setupSprites();
    scheduleOnce(schedule_selector(SplashScreen::startMove), 1);
    return true;
}


void SplashScreen::moveKeSpriteToLeft()
{
    JumpBy *jumpChengToleft2 = JumpBy::create(1, Vec2(-spriteSize.width,0), 10, 4);
    pSprCheng->runAction(jumpChengToleft2);

    MoveBy *keSpritemoveBy = MoveBy::create(1, Vec2(spriteSize.width, 0));
    CallFunc *callFunc2 = CallFunc::create(std::bind(&SplashScreen::moveMaiSpriteToLeft,this));
    pSprKe->runAction(Sequence::create(keSpritemoveBy, callFunc2, NULL));
}


void SplashScreen::moveMaiSpriteToLeft()
{
    JumpBy *jumpChengToleft2 = JumpBy::create(1, Vec2(-spriteSize.width,0), 10, 4);
    //MoveBy *moveChengToLeft3 = MoveBy::create(1, Vec2(-spriteSize.width, 0));
    pSprCheng->runAction(jumpChengToleft2);

    MoveBy *maiSpriteMoveBy = MoveBy::create(1, Vec2(spriteSize.width, 0));
    //auto func = std::bind(&SplashScreen::spriteFadeOut, this);
    CallFunc *callFunc = CallFunc::create(std::bind(&SplashScreen::spriteFadeOut, this));
    pSprMai->runAction(Sequence::create(maiSpriteMoveBy, callFunc, NULL));
}
void SplashScreen::spriteFadeOut()
{
    FadeOut *fadeout1 = FadeOut::create(2);
    pSprCheng->runAction(fadeout1);
    pSprMai->runAction(fadeout1->clone());
    pSprKe->runAction(fadeout1->clone());

    CallFunc *callFunc = CallFunc::create(std::bind(&SplashScreen::gotoMenuScene, this));
    pSprJi->runAction(Sequence::create(fadeout1->clone(), callFunc, NULL));
}


void SplashScreen::gotoMenuScene()
{
    log("goto menu scene");
    Director::getInstance()->replaceScene(MenuScene::createScene());
}


void SplashScreen::startMove(float dt)
{
    JumpBy *jumpChengToleft2 = JumpBy::create(1, Vec2(-spriteSize.width,0), 10, 4);
    //MoveBy* moveByLeft = MoveBy::create(1, Vec2(-spriteSize.width, 0));
    pSprCheng->runAction(jumpChengToleft2);

    MoveBy *moveJiToRight = MoveBy::create(1, Vec2(spriteSize.width, 0));
    CallFunc *callFunc = CallFunc::create(CC_CALLBACK_0(SplashScreen::moveKeSpriteToLeft, this));
    pSprJi->runAction(Sequence::create(moveJiToRight, callFunc, NULL));
}


bool SplashScreen::setupSprites()
{
    log("splashScreen setupSprites");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 centre(visibleSize.width/2, visibleSize.height/2);
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /////////////

    pSprCheng = Sprite::create("cheng.png");
    spriteSize = pSprCheng->getContentSize();
    pSprCheng->setPosition(centre.x + 1.5*spriteSize.width, centre.y);
    pSprCheng->setAnchorPoint(Vec2(0.5, 0.5));
    this->addChild(pSprCheng, 0);

    pSprJi = Sprite::create("ji.png");
    pSprJi->setAnchorPoint(Vec2(0.5, 0.5));
    pSprJi->setPosition(centre.x + spriteSize.width/2, centre.y);
    this->addChild(pSprJi);

    pSprKe = Sprite::create("ke.png");
    pSprKe->setAnchorPoint(Vec2(0.5, 0.5));
    pSprKe->setPosition(centre.x - spriteSize.width/2, centre.y);
    this->addChild(pSprKe);


    pSprMai = Sprite::create("mai.png");
    pSprMai->setPosition(centre.x - 1.5*spriteSize.width, centre.y);
    this->addChild(pSprMai);

    return true;
}
