#ifndef BASEPAGE_HPP
#define BASEPAGE_HPP

#include <Geode/Geode.hpp>
#include <Geode/utils/cocos.hpp>

#include "../utility/Utilities.hpp"
#include "../modify/MyItemInfoPopup.hpp"

using namespace geode::prelude;

class BasePage : public CCObject {
protected:

    Utilities* util;
    FLAlertLayer* popupLayer;

    CCNode* pageContainer;
    CCMenu* buttonMenu;

    CCSize winSize;
    float pageWidth;
    CCArray* tierPages;
    int currentPage;

    CCSprite* page1Selected;
    CCSprite* page2Selected;
    CCSprite* page3Selected;
    CCSprite* page4Selected;
    CCSprite* page1Deselected;
    CCSprite* page2Deselected;
    CCSprite* page3Deselected;
    CCSprite* page4Deselected;

    int tempTierAmount;

public:

    BasePage(FLAlertLayer* parentPopup);
    ~BasePage();

    void createTitle(const char* title, CCNode* pageContainer);
    void createNavigationButtons(int tierAmount);
    void onTierButton(CCObject* sender);
    void updatePageVisibility(int tag);
    void updateButtonBackground(int tag);
    virtual CCNode* createPage(int value) = 0;
    virtual CCNode* createTier(int tier, int value) = 0;
};

#endif