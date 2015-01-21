#include "menuscene.h"
#include <vector>
#include "popuplayer.h"
#include "mapchoosescene.h"


bool MenuScene::init()
{
    if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    log("width %f, height %f" , visibleSize.width, visibleSize.height);
    addBackGroundSprite();
    addMenuSprites();
    return true;
}

Scene* MenuScene::createScene()
{
    log("MenuScene createScene");
    auto scene = Scene::create();
    auto layer = MenuScene::create();

    scene->addChild(layer);
    return scene;
}

void MenuScene::addBackGroundSprite()
{

    auto menuSpriteLogo = Sprite::create("logo.png");
    menuSpriteLogo->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2+200));
    menuSpriteLogo->setAnchorPoint(Vec2(0.5, 1));
    //menuSpriteLogo->setScale(0.6f);
    addChild(menuSpriteLogo);
    // add rainbow
    auto rainbow = Sprite::create("rainbow.png");
    rainbow->setPosition(Vec2(5, visibleSize.height - 20));
    rainbow->setAnchorPoint(Vec2(0, 1));
    rainbow->setScale(0.5f);
    addChild(rainbow);
    // make the rainbow activity
    MoveBy *rainbowAction = MoveBy::create(1, Vec2(8, 0));
    MoveBy *rainbowReverse = rainbowAction->reverse();
    Sequence *rainbowActions = Sequence::create(rainbowAction, rainbowReverse, NULL);
    rainbow->runAction(RepeatForever::create(rainbowActions));
}


void MenuScene::addMenuSprites()
{
    auto btnNormal = Scale9Sprite::create("normal_menu.png");
    auto btnPress = Scale9Sprite::create("press_menu.png");
    
    Size preferredSize(222, 50);
    
    ////single game
    auto singleGameTTF = LabelTTF::create("Single Game", "Marker Felt", 20);
    auto singleGameBtn = ControlButton::create(singleGameTTF, btnNormal);
    singleGameBtn->setBackgroundSpriteForState(btnPress, Control::State::HIGH_LIGHTED);
    singleGameBtn->setPosition(Vec2(visibleSize.width/2, visibleSize.height -340));
    singleGameBtn->setPreferredSize(preferredSize);
    singleGameBtn->addTargetWithActionForControlEvents(this,
                                                       cccontrol_selector(MenuScene::menuTouchDown),
                                                       Control::EventType::TOUCH_DOWN);

    singleGameBtn->setTag(SINGILE_GAME_TAG);
    addChild(singleGameBtn);

    ////////Multi game
    btnNormal = Scale9Sprite::create("normal_menu.png");
    btnPress = Scale9Sprite::create("press_menu.png");

    auto multiGameTTF = LabelTTF::create("Multi Game", "monospace", 20);
    auto multiGameBtn = ControlButton::create(multiGameTTF, btnNormal);
    multiGameBtn->setBackgroundSpriteForState(btnPress, Control::State::SELECTED);
    multiGameBtn->setPosition(Vec2(visibleSize.width/2, visibleSize.height - 400));
    multiGameBtn->setPreferredSize(preferredSize);
    multiGameBtn->addTargetWithActionForControlEvents(this,
                                                      cccontrol_selector(MenuScene::menuTouchDown),
                                                      Control::EventType::TOUCH_DOWN);
    multiGameBtn->setTag(MULTI_GAME_TAG);
    addChild(multiGameBtn);
    //// music menu
    btnNormal = Scale9Sprite::create("normal_menu.png");
    btnPress = Scale9Sprite::create("press_menu.png");
    bool music_on = UserDefault::getInstance()->getBoolForKey("MUSIC_ON_KEY", true);

    TTFConfig ttfConf("fonts/Marker Felt.ttf", 20);
    Label* musicOptionTTF;
    if(music_on){
        musicOptionTTF = Label::createWithTTF(ttfConf,"Music On", TextHAlignment::LEFT);
    }else{
        musicOptionTTF = Label::createWithTTF(ttfConf,"Music Off", TextHAlignment::LEFT);
    }
    log("line 90");
    auto musicBtn = ControlButton::create(musicOptionTTF, btnNormal);
    musicBtn->setBackgroundSpriteForState(btnPress, Control::State::SELECTED);
    musicBtn->setPreferredSize(preferredSize);
    musicBtn->setPosition(Vec2(visibleSize.width/2, visibleSize.height - 460));
    musicBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene::menuTouchDown),
                                                  Control::EventType::TOUCH_DOWN);
    musicBtn->setTag(MUSIC_GAME_TAG);
    addChild(musicBtn);

    /// Quit Game
    btnNormal = Scale9Sprite::create("normal_menu.png");
    btnPress = Scale9Sprite::create("press_menu.png");

    auto quitGameTTF = LabelTTF::create("Quit Game", "Marker Felt", 20);
    auto quitGameBtn = ControlButton::create(quitGameTTF, btnNormal);
    quitGameBtn->setBackgroundSpriteForState(btnPress, Control::State::SELECTED);
    quitGameBtn->setPosition(Vec2(visibleSize.width/2, visibleSize.height-520));
    quitGameBtn->setPreferredSize(preferredSize);
    quitGameBtn->addTargetWithActionForControlEvents(this,
                                                     cccontrol_selector(MenuScene::menuTouchDown),
                                                     Control::EventType::TOUCH_DOWN);
    quitGameBtn->setTag(GAME_QUIT);
    addChild(quitGameBtn);

}
void MenuScene::popupLayer()
{
    PopupLayer *popDialog = PopupLayer::create("popuplayer/dialog_bg.png");
    popDialog->setContentSize(Size(400, 220));
    popDialog->setTitle("Alert Message");
    popDialog->setContentText("Do you want to quit ?",
                              20, 60, 250);
    popDialog->setCallbackFunc(this,
                               callfuncN_selector(MenuScene::quitButtonCallback));
    popDialog->addButton("popuplayer/button_bg1.png",
                         "popuplayer/button_bg3.png",
                         "Ok",
                         GAME_QUIT_OK);

    popDialog->addButton("popuplayer/button_bg2.png",
                         "popuplayer/button_bg3.png",
                         "Cancel",
                         GAME_QUIT_CANCEL);

    addChild(popDialog);

}


void MenuScene::quitButtonCallback(Node *pNode)
{
    log("Clicked %d",pNode->getTag());
}


void MenuScene::menuTouchDown(Ref* pSender, Control::EventType event)
{
    ControlButton* button = static_cast<ControlButton*>(pSender);
    int tag = button->getTag();
    log("single touched %d", tag);
    switch(tag)
    {
        case MUSIC_GAME_TAG:
            {
                bool music_on = UserDefault::getInstance()->getBoolForKey("MUSIC_ON_KEY", true);
                if(music_on)
                {
                    UserDefault::getInstance()->setBoolForKey("MUSIC_ON_KEY", false);
                    button->setTitleForState("Music Off", Control::State::NORMAL);
                }
                else
                {
                    UserDefault::getInstance()->setBoolForKey("MUSIC_ON_KEY", true);
                    button->setTitleForState("Music On", Control::State::NORMAL);
                }

            }
            break;
        case SINGILE_GAME_TAG:
            log("singlegamebuttong clicked");
            Director::getInstance()->pushScene(MapChooseScene::createScene());
            break;
        case MULTI_GAME_TAG:
            log("multi game button clicked");
            break;
        case GAME_QUIT:
            log("game quit ");
            popupLayer();
            break;

        default:
            break;
    }
}
