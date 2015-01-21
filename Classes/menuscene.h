#ifndef MENU_SCENE_H
#define MENU_SCENE_H

#include "cocos2d.h"
#include "ui/UIScale9Sprite.h"
#include "extensions/cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class MenuScene: public cocos2d::LayerColor
{
  public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void quitButtonCallback(Node *pNode);
    CREATE_FUNC(MenuScene);
  private:
    cocos2d::Size visibleSize;
    void menuTouchDown(Ref *pSender, Control::EventType event);
    void addBackGroundSprite();
    void addMenuSprites();
    void popupLayer();
  private:
    const static int SINGILE_GAME_TAG = 10001;
    const static int MULTI_GAME_TAG = 10002;
    const static int MUSIC_GAME_TAG = 10003;
    const static int GAME_QUIT = 10004;
    const static int GAME_QUIT_OK = 10005;
    const static int GAME_QUIT_CANCEL = 10006;
};


#endif //
