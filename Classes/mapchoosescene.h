#ifndef MAPCHOOSESCENE_H
#define MAPCHOOSESCENE_H

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class MapChooseScene: public Layer, public ScrollViewDelegate
{
  public:
    MapChooseScene();
    ~MapChooseScene();
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MapChooseScene);
  private:
    static const int MAP_COUNT = 3;
    static const int TOUCH_DISTANCE = 50;
    Size visibleSize;
    Layer* spriteContainer;
    int currentPage;
    Point beginTouchPoint;
    ScrollView *scrollView;

    void singleTouchDown(Ref* pSender, Control::EventType event);
    void addBackGroundSprite();
    void addScrollView();
    // reimplement
    void scrollViewDidScroll(ScrollView* view);
    void scrollViewDidZoom(ScrollView* view);
    void scrollViewMoveOver(ScrollView* view);

    void adjustScrollView(float distance);
    void onTouchEnded(Touch *touch, Event *unusedEvent);
    bool onTouchBegan(Touch *touch, Event *unusedEvent);
    void onTouchMoved(Touch *touch, Event *unusedEvent);
};


#endif /* MAPCHOOSESCENE_H */
