#ifndef POPUPLAYER_H
#define POPUPLAYER_H
#include "cocos2d.h"
//#include "extensions/cocos-ext.h"
#include "ui/UISCale9Sprite.h"

USING_NS_CC;
//USING_NS_CC_EXT;
class PopupLayer: public Layer
{
  public:
    PopupLayer();
    ~PopupLayer();
    static PopupLayer *create(const char *bgImg);
    //static Scene* createScene();
    bool init();
    void setTitle(const char *title, int fontSize=10);
    void setContentText(const char *text, int fontSize=20,
                        int padding=50,
                        int paddingTo=100);
    bool addButton(const char* normalImg, const char* selectedImg,
                   const char* title,
                   int tag=0);

    void setCallbackFunc(Ref* target, SEL_CallFuncN callFun);
    virtual void onEnter();
    virtual void onExit();
    CREATE_FUNC(PopupLayer);
  private:
    int m_contentPadding;
    int m_contentPaddingTop;

    Ref *m_callbackListener;
    SEL_CallFuncN m_callback;

    void buttonCallback(Ref* pSender);
    CC_SYNTHESIZE_RETAIN(Menu*, m_pMenu, MenuButton);
    CC_SYNTHESIZE_RETAIN(ui::Scale9Sprite*, m_s9BackGround, Sprite9BackGround);
    CC_SYNTHESIZE_RETAIN(Sprite*, m_spBackGround, SpriteBackGround);
    CC_SYNTHESIZE_RETAIN(Label*, m_ltTitle, LabelTitle);
    CC_SYNTHESIZE_RETAIN(Label*, m_ltContentText, LabelContentText);

};

#endif /* POPUPLAYER_H */
