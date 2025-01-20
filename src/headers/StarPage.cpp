#pragma once

#include <Geode/Geode.hpp>
#include <Geode/utils/cocos.hpp>
#include "UnlockProgressionPopup.hpp"
#include "../WebRequests/RequestCreatorPoints.cpp"

using namespace geode::prelude;

class StarPage : public CCObject {
private:

    FLAlertLayer* popupLayer;

    CCNode* starPageContainer;
    CCMenu* buttonMenu;

    float pageWidth;

    CCArray* tierPages;
    int currentPage;
    
    CCNode* tier1Page;
    CCNode* tier2Page;
    CCNode* tier3Page;
    CCNode* tier4Page;

    CCMenuItemSpriteExtra* tier1Button = nullptr;
    CCMenuItemSpriteExtra* tier2Button = nullptr;
    CCMenuItemSpriteExtra* tier3Button = nullptr;
    CCMenuItemSpriteExtra* tier4Button = nullptr;

    CCSprite* page1Selected = nullptr;
    CCSprite* page2Selected = nullptr;
    CCSprite* page3Selected = nullptr;
    CCSprite* page4Selected = nullptr;
    CCSprite* page1Deselected = nullptr;
    CCSprite* page2Deselected = nullptr;
    CCSprite* page3Deselected = nullptr;
    CCSprite* page4Deselected = nullptr;

    bool togglePlayerColours;

    struct UnlockInfo : public cocos2d::CCObject {
        int iconId;
        IconType unlockType;

        UnlockInfo(int id, IconType type) : iconId(id), unlockType(type) {}
    };

public:
    StarPage(FLAlertLayer* parentPopup) {

        popupLayer = parentPopup;
        tierPages = CCArray::create();
        tierPages->retain();
        buttonMenu = CCMenu::create();
        page1Selected = CCSprite::create("GJ_square03-uhd.png");
        page2Selected = CCSprite::create("GJ_square03-uhd.png");
        page2Selected->setVisible(false);
        page3Selected = CCSprite::create("GJ_square03-uhd.png");
        page3Selected->setVisible(false);
        page4Selected = CCSprite::create("GJ_square03-uhd.png");
        page4Selected->setVisible(false);
        page1Deselected = CCSprite::create("GJ_square01-uhd.png");
        page1Deselected->setVisible(false);
        page2Deselected = CCSprite::create("GJ_square01-uhd.png");
        page3Deselected = CCSprite::create("GJ_square01-uhd.png");
        page4Deselected = CCSprite::create("GJ_square01-uhd.png");
        togglePlayerColours = false;
    }

    CCNode* createStarPage(int stars) {

        starPageContainer = CCNode::create();
        starPageContainer->setPosition({0, 0});
        auto layout = geode::RowLayout::create();
        layout->setGap(10.f);
        layout->setAxisAlignment(geode::AxisAlignment::Start);
        layout->setCrossAxisAlignment(geode::AxisAlignment::Center);
        starPageContainer->setLayout(layout);
        buttonMenu->setPosition({147, -200});
        starPageContainer->addChild(buttonMenu);

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        pageWidth = winSize.width * 0.75f;

        currentPage = 0;


        auto labelSpr = CCSprite::create("Stars_Title.png"_spr);
        labelSpr->setPosition({227.5f, 193});
        labelSpr->setScale(.8f);
        starPageContainer->addChild(labelSpr);

        //page content would go here

        tier1Page = createTier1(stars);
        tier1Page->retain();
        starPageContainer->addChild(tier1Page);
        tierPages->addObject(tier1Page);
        tier1Page->setVisible(true);

        tier2Page = createTier2(stars);
        tier2Page->retain();
        starPageContainer->addChild(tier2Page);
        tierPages->addObject(tier2Page);
        tier2Page->setVisible(false);

        tier3Page = createTier3(stars);
        tier3Page->retain();
        starPageContainer->addChild(tier3Page);
        tierPages->addObject(tier3Page);
        tier3Page->setVisible(false);

        tier4Page = createTier4(stars);
        tier4Page->retain();
        starPageContainer->addChild(tier4Page);
        tierPages->addObject(tier4Page);
        tier4Page->setVisible(false);

        createNavigationButtons();


        starPageContainer->setPosition({pageWidth * 0.5f, 0});

        return starPageContainer;
    }

    ~StarPage() {
        if (tierPages) {
            tierPages->release();
        }
    }

private:
    void createNavigationButtons() {

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        float popupHeight = winSize.height * 0.8f;

        CCSprite* tier1ButtonSpr = CCSprite::createWithSpriteFrameName("rankIcon_all_001.png");
        CCSprite* tier2ButtonSpr = CCSprite::createWithSpriteFrameName("rankIcon_top1000_001.png");
        CCSprite* tier3ButtonSpr = CCSprite::createWithSpriteFrameName("rankIcon_top500_001.png");
        CCSprite* tier4ButtonSpr = CCSprite::createWithSpriteFrameName("rankIcon_top200_001.png");

        auto tier1Button = CCMenuItemSpriteExtra::create(
            tier1ButtonSpr,
            this,
            menu_selector(StarPage::onTierButton)
        );
        tier1Button->setTag(0);
        tier1Button->setAnchorPoint({.5f, .5f});
        tier1Button->setPosition({40, 220});

        page1Deselected->setAnchorPoint({.5f, 0});
        page1Deselected->setPosition({40, 208});
        page1Deselected->setScale(.3f);
        page1Deselected->setZOrder(-2);

        page1Selected->setAnchorPoint({.5f, 0});
        page1Selected->setPosition({40, 208});
        page1Selected->setScale(.3f);
        page1Selected->setZOrder(-2);

        buttonMenu->addChild(tier1Button);
        buttonMenu->addChild(page1Deselected);
        buttonMenu->addChild(page1Selected);

        tier2Button = CCMenuItemSpriteExtra::create(
            tier2ButtonSpr,
            this,
            menu_selector(StarPage::onTierButton)
        );
        tier2Button->setTag(1);
        tier2Button->setAnchorPoint({.5f, .5f});
        tier2Button->setPosition({67, 220});

        page2Deselected->setAnchorPoint({.5f, 0});
        page2Deselected->setPosition({67, 208});
        page2Deselected->setScale(.3f);
        page2Deselected->setZOrder(-2);

        page2Selected->setAnchorPoint({.5f, 0});
        page2Selected->setPosition({67, 208});
        page2Selected->setScale(.3f);
        page2Selected->setZOrder(-2);

        buttonMenu->addChild(tier2Button);
        buttonMenu->addChild(page2Deselected);
        buttonMenu->addChild(page2Selected);

        tier3Button = CCMenuItemSpriteExtra::create(
            tier3ButtonSpr,
            this,
            menu_selector(StarPage::onTierButton)
        );
        tier3Button->setTag(2);
        tier3Button->setAnchorPoint({.5f, .5f});
        tier3Button->setPosition({94, 220});

        page3Deselected->setAnchorPoint({.5f, 0});
        page3Deselected->setPosition({94, 208});
        page3Deselected->setScale(.3f);
        page3Deselected->setZOrder(-2);

        page3Selected->setAnchorPoint({.5f, 0});
        page3Selected->setPosition({94, 208});
        page3Selected->setScale(.3f);
        page3Selected->setZOrder(-2);

        buttonMenu->addChild(tier3Button);
        buttonMenu->addChild(page3Deselected);
        buttonMenu->addChild(page3Selected);

        tier4Button = CCMenuItemSpriteExtra::create(
            tier4ButtonSpr,
            this,
            menu_selector(StarPage::onTierButton)
        );
        tier4Button->setTag(3);
        tier4Button->setAnchorPoint({.5f, .5f});
        tier4Button->setPosition({121, 220});

        page4Deselected->setAnchorPoint({.5f, 0});
        page4Deselected->setPosition({121, 208});
        page4Deselected->setScale(.3f);
        page4Deselected->setZOrder(-2);

        page4Selected->setAnchorPoint({.5f, 0});
        page4Selected->setPosition({121, 208});
        page4Selected->setScale(.3f);
        page4Selected->setZOrder(-2);

        buttonMenu->addChild(tier4Button);
        buttonMenu->addChild(page4Deselected);
        buttonMenu->addChild(page4Selected);
    }

    void onTierButton(CCObject* sender) {

        auto button = static_cast<CCMenuItemSpriteExtra*>(sender);
        int tag = button->getTag();
        currentPage = tag;
        updatePageVisibility(tag);
    }

    UnlockType convertIconTypeToUnlockType(IconType iconType) {
        switch (iconType) {
            case IconType::Cube:
                return UnlockType::Cube;
            case IconType::Ship:
                return UnlockType::Ship;
            default: // IconType::Ball:
                return UnlockType::Ball;
            // Add cases for other IconType values as needed
            //default:
                // Handle unexpected IconType values appropriately
                //return nullptr; // Assuming 'Unknown' is a valid value in UnlockType
        }
    }

    void openUnlockInfo(CCObject* sender) {
        auto button = static_cast<CCMenuItemSpriteExtra*>(sender);
        auto unlockInfo = dynamic_cast<UnlockInfo*>(button->getUserObject());

        if (unlockInfo) {
            log::info("Button pressed: Icon ID = {}, Unlock Type = {}", unlockInfo->iconId, static_cast<int>(unlockInfo->unlockType));
            UnlockType unlockType = convertIconTypeToUnlockType(unlockInfo->unlockType);
            popupLayer->addChild(ItemInfoPopup::create(unlockInfo->iconId, unlockType));
        } else {
            log::warn("Unlock info not found!");
        }
    }

    void updatePageVisibility(int tag) {

        for (int i = 0; i < tierPages->count(); ++i) {

            auto page = static_cast<CCNode*>(tierPages->objectAtIndex(i));
            page->setVisible(i == currentPage);
        }
        updateButtonBackground(tag);
    }

    void updateButtonBackground(int tag) {
        
        //theres gotta be a better way to do this but I'm lazy
        if (tag == 0) {

            page1Selected->setVisible(true);
            page2Selected->setVisible(false);
            page3Selected->setVisible(false);
            page4Selected->setVisible(false);
            page1Deselected->setVisible(false);
            page2Deselected->setVisible(true);
            page3Deselected->setVisible(true);
            page4Deselected->setVisible(true);
        } else if (tag == 1) {

            page1Selected->setVisible(false);
            page2Selected->setVisible(true);
            page3Selected->setVisible(false);
            page4Selected->setVisible(false);
            page1Deselected->setVisible(true);
            page2Deselected->setVisible(false);
            page3Deselected->setVisible(true);
            page4Deselected->setVisible(true);
        } else if (tag == 2) {

            page1Selected->setVisible(false);
            page2Selected->setVisible(false);
            page3Selected->setVisible(true);
            page4Selected->setVisible(false);
            page1Deselected->setVisible(true);
            page2Deselected->setVisible(true);
            page3Deselected->setVisible(false);
            page4Deselected->setVisible(true);
        } else {

            page1Selected->setVisible(false);
            page2Selected->setVisible(false);
            page3Selected->setVisible(false);
            page4Selected->setVisible(true);
            page1Deselected->setVisible(true);
            page2Deselected->setVisible(true);
            page3Deselected->setVisible(true);
            page4Deselected->setVisible(false);
        }
    }

    CCNode* createTier1(int stars) {
        auto tier1Container = CCNode::create();
        tier1Container->setPosition({0, 0});
        auto layout = geode::RowLayout::create();
        layout->setGap(10.f);
        layout->setAxisAlignment(geode::AxisAlignment::Start);
        layout->setCrossAxisAlignment(geode::AxisAlignment::Center);
        tier1Container->setLayout(layout);
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        pageWidth = winSize.width * 0.75f;
        CCMenu* tierMenu = CCMenu::create();

        /* star of tier's content */

        /* first row */
        float ratioFrom0 = (float)stars / (float)100;

        auto unlock100 = SimplePlayer::create(1);
        auto unlockInfo100 = new UnlockInfo(23, IconType::Cube);
        unlockInfo100->autorelease();
        auto lock100 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");
        auto unlockText100 = CCLabelBMFont::create("100", "bigFont-uhd.fnt");
        auto sliderSpr1 = CCSprite::create("sliderBar2-uhd.png");
        float ratioFrom100 = (float)(stars - 100) / (float)100;
        float scale100 = ratioFrom100 >= 1.f ? sliderSpr1->getContentSize().width : sliderSpr1->getContentSize().width * ratioFrom100;
        sliderSpr1->setTextureRect(CCRectMake(0, 0, scale100, sliderSpr1->getContentSize().height)); 
        auto siderBgSpr1 = CCSprite::create("Progress_Outline.png"_spr);

        auto unlock200 = SimplePlayer::create(1);
        auto lock200 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");
        auto unlockText200 = CCLabelBMFont::create("200", "bigFont-uhd.fnt");
        auto sliderSpr2 = CCSprite::create("sliderBar2-uhd.png");
        float ratioFrom200 = (float)(stars - 200) / (float)100;
        float scale200 = ratioFrom200 >= 1.f ? sliderSpr2->getContentSize().width : sliderSpr2->getContentSize().width * ratioFrom200;
        sliderSpr2->setTextureRect(CCRectMake(0, 0, scale200, sliderSpr2->getContentSize().height));  
        auto siderBgSpr2 = CCSprite::create("Progress_Outline.png"_spr);

        auto unlock300 = SimplePlayer::create(1);
        auto lock300 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");
        auto unlockText300 = CCLabelBMFont::create("300", "bigFont-uhd.fnt");
        auto sliderSpr3 = CCSprite::create("sliderBar2-uhd.png");
        float ratioFrom300 = (float)(stars - 300) / (float)100;
        float scale300 = ratioFrom300 >= 1.f ? sliderSpr3->getContentSize().width : sliderSpr3->getContentSize().width * ratioFrom300;
        sliderSpr3->setTextureRect(CCRectMake(0, 0, scale300, sliderSpr3->getContentSize().height));
        auto siderBgSpr3 = CCSprite::create("Progress_Outline.png"_spr);

        auto unlock400 = SimplePlayer::create(1);
        auto lock400 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");
        auto unlockText400 = CCLabelBMFont::create("400", "bigFont-uhd.fnt");
        auto sliderSpr4 = CCSprite::create("sliderBar2-uhd.png");
        float ratioFrom400 = (float)(stars - 400) / (float)100;
        float scale400 = ratioFrom400 >= 1.f ? sliderSpr4->getContentSize().width : sliderSpr4->getContentSize().width * ratioFrom400;
        sliderSpr4->setTextureRect(CCRectMake(0, 0, scale400, sliderSpr4->getContentSize().height));
        auto siderBgSpr4 = CCSprite::create("Progress_Outline.png"_spr);

        auto unlock500 = SimplePlayer::create(1);
        auto lock500 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");
        auto unlockText500 = CCLabelBMFont::create("500", "bigFont-uhd.fnt");

        /* second row */
        float ratioFrom500 = (float)(stars - 500) / (float)100;

        auto unlock600 = SimplePlayer::create(1);
        auto lock600 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");
        auto unlockText600 = CCLabelBMFont::create("600", "bigFont-uhd.fnt");
        auto sliderSpr5 = CCSprite::create("sliderBar2-uhd.png");
        float ratioFrom600 = (float)(stars - 600) / (float)100;
        float scale600 = ratioFrom600 >= 1.f ? sliderSpr5->getContentSize().width : sliderSpr5->getContentSize().width * ratioFrom600;
        sliderSpr5->setTextureRect(CCRectMake(0, 0, scale600, sliderSpr5->getContentSize().height));
        auto siderBgSpr5 = CCSprite::create("Progress_Outline.png"_spr);

        auto unlock700 = SimplePlayer::create(1);
        auto lock700 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");
        auto unlockText700 = CCLabelBMFont::create("700", "bigFont-uhd.fnt");
        auto sliderSpr6 = CCSprite::create("sliderBar2-uhd.png");
        float ratioFrom700 = (float)(stars - 700) / (float)100;
        float scale700 = ratioFrom700 >= 1.f ? sliderSpr6->getContentSize().width : sliderSpr6->getContentSize().width * ratioFrom700;
        sliderSpr6->setTextureRect(CCRectMake(0, 0, scale700, sliderSpr6->getContentSize().height));
        auto siderBgSpr6 = CCSprite::create("Progress_Outline.png"_spr);

        auto unlock800 = SimplePlayer::create(1);
        auto lock800 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");
        auto unlockText800 = CCLabelBMFont::create("800", "bigFont-uhd.fnt");
        auto sliderSpr7 = CCSprite::create("sliderBar2-uhd.png");
        float ratioFrom800 = (float)(stars - 800) / (float)100;
        float scale800 = ratioFrom800 >= 1.f ? sliderSpr7->getContentSize().width : sliderSpr7->getContentSize().width * ratioFrom800;
        sliderSpr7->setTextureRect(CCRectMake(0, 0, scale800, sliderSpr7->getContentSize().height));
        auto siderBgSpr7 = CCSprite::create("Progress_Outline.png"_spr);

        auto unlock900 = SimplePlayer::create(1);
        auto lock900 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");
        auto unlockText900 = CCLabelBMFont::create("900", "bigFont-uhd.fnt");
        auto sliderSpr8 = CCSprite::create("sliderBar2-uhd.png");
        float ratioFrom900 = (float)(stars - 900) / (float)100;
        float scale900 = ratioFrom900 >= 1.f ? sliderSpr8->getContentSize().width : sliderSpr8->getContentSize().width * ratioFrom900;
        sliderSpr8->setTextureRect(CCRectMake(0, 0, scale900, sliderSpr8->getContentSize().height));
        auto siderBgSpr8 = CCSprite::create("Progress_Outline.png"_spr);

        auto unlock1000 = SimplePlayer::create(1);
        auto lock1000 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");
        auto unlockText1000 = CCLabelBMFont::create("1000", "bigFont-uhd.fnt");

        /* first row */
        unlock100->updatePlayerFrame(unlockInfo100->iconId, unlockInfo100->unlockType);
        if (ratioFrom0 >= 1.f) {        //unlocked
            lock100->setVisible(false);
            if (togglePlayerColours) {
                unlock100->setColors(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor()), GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor2()));
                unlock100->setGlowOutline(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerGlowColor()));
            } else {
                unlock100->setColors(ccc3(190, 190, 190), ccc3(245, 245, 245));
                unlock100->disableGlowOutline();
            }
        } else {                        //locked
            unlock100->setColors(ccc3(30, 30, 30), ccc3(80, 80, 80));
            unlock100->disableGlowOutline();
        }

        sliderSpr1->setColor(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor()));

        unlock200->updatePlayerFrame(24, IconType::Cube);
        if (ratioFrom100 >= 1.f) {
            lock200->setVisible(false);
            if (togglePlayerColours) {
                unlock200->setColors(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor()), GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor2()));
                unlock200->setGlowOutline(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerGlowColor()));
            } else {
                unlock200->setColors(ccc3(190, 190, 190), ccc3(245, 245, 245));
                unlock200->disableGlowOutline();
            }
        } else {
            unlock200->setColors(ccc3(30, 30, 30), ccc3(80, 80, 80));
            unlock200->disableGlowOutline();
        }

        sliderSpr2->setColor(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor()));

        unlock300->updatePlayerFrame(25, IconType::Cube);
        if (ratioFrom200 >= 1.f) {
            lock300->setVisible(false);
            if (togglePlayerColours) {
                unlock300->setColors(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor()), GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor2()));
                unlock300->setGlowOutline(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerGlowColor()));
            } else {
                unlock300->setColors(ccc3(190, 190, 190), ccc3(245, 245, 245));
                unlock300->disableGlowOutline();
            }
        } else {
            unlock300->setColors(ccc3(30, 30, 30), ccc3(80, 80, 80));
            unlock300->disableGlowOutline();
        }

        sliderSpr3->setColor(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor()));

        unlock400->updatePlayerFrame(26, IconType::Cube);
        if (ratioFrom300 >= 1.f) {
            lock400->setVisible(false);
            if (togglePlayerColours) {
                unlock400->setColors(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor()), GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor2()));
                unlock400->setGlowOutline(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerGlowColor()));
            } else {
                unlock400->setColors(ccc3(190, 190, 190), ccc3(245, 245, 245));
                unlock400->disableGlowOutline();
            }
        } else {
            unlock400->setColors(ccc3(30, 30, 30), ccc3(80, 80, 80));
            unlock400->disableGlowOutline();
        }

        sliderSpr4->setColor(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor()));

        unlock500->updatePlayerFrame(4, IconType::Ship);
        if (ratioFrom400 >= 1.f) {
            lock500->setVisible(false);
            if (togglePlayerColours) {
                unlock500->setColors(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor()), GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor2()));
                unlock500->setGlowOutline(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerGlowColor()));
            } else {
                unlock500->setColors(ccc3(190, 190, 190), ccc3(245, 245, 245));
                unlock500->disableGlowOutline();
            }
        } else {
            unlock500->setColors(ccc3(30, 30, 30), ccc3(80, 80, 80));
            unlock500->disableGlowOutline();
        }
        /* second row */
        unlock600->updatePlayerFrame(5, IconType::Ship);
        if (ratioFrom500 >= 1.f) {
            lock600->setVisible(false);
            if (togglePlayerColours) {
                unlock600->setColors(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor()), GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor2()));
                unlock600->setGlowOutline(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerGlowColor()));
            } else {
                unlock600->setColors(ccc3(190, 190, 190), ccc3(245, 245, 245));
                unlock600->disableGlowOutline();
            }
        } else {
            unlock600->setColors(ccc3(30, 30, 30), ccc3(80, 80, 80));
            unlock600->disableGlowOutline();
        }

        sliderSpr5->setColor(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor()));

        unlock700->updatePlayerFrame(7, IconType::Ship);
        if (ratioFrom600 >= 1.f) {
            lock700->setVisible(false);
            if (togglePlayerColours) {
                unlock700->setColors(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor()), GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor2()));
                unlock700->setGlowOutline(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerGlowColor()));
            } else {
                unlock700->setColors(ccc3(190, 190, 190), ccc3(245, 245, 245));
                unlock700->disableGlowOutline();
            }
        } else {
            unlock700->setColors(ccc3(30, 30, 30), ccc3(80, 80, 80));
            unlock700->disableGlowOutline();
        }

        sliderSpr6->setColor(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor()));

        unlock800->updatePlayerFrame(28, IconType::Cube);
        if (ratioFrom700 >= 1.f) {
            lock800->setVisible(false);
            if (togglePlayerColours) {
                unlock800->setColors(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor()), GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor2()));
                unlock800->setGlowOutline(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerGlowColor()));
            } else {
                unlock800->setColors(ccc3(190, 190, 190), ccc3(245, 245, 245));
                unlock800->disableGlowOutline();
            }
        } else {
            unlock800->setColors(ccc3(30, 30, 30), ccc3(80, 80, 80));
            unlock800->disableGlowOutline();
        }

        sliderSpr7->setColor(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor()));

        unlock900->updatePlayerFrame(29, IconType::Cube);
        if (ratioFrom800 >= 1.f) {
            lock900->setVisible(false);
            if (togglePlayerColours) {
                unlock900->setColors(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor()), GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor2()));
                unlock900->setGlowOutline(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerGlowColor()));
            } else {
                unlock900->setColors(ccc3(190, 190, 190), ccc3(245, 245, 245));
                unlock900->disableGlowOutline();
            }
        } else {
            unlock900->setColors(ccc3(30, 30, 30), ccc3(80, 80, 80));
            unlock900->disableGlowOutline();
        }

        sliderSpr8->setColor(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor()));

        unlock1000->updatePlayerFrame(30, IconType::Ship);
        if (ratioFrom900 >= 1.f) {
            lock1000->setVisible(false);
            if (togglePlayerColours) {
                unlock1000->setColors(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor()), GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor2()));
                unlock1000->setGlowOutline(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerGlowColor()));
            } else {
                unlock1000->setColors(ccc3(190, 190, 190), ccc3(245, 245, 245));
                unlock1000->disableGlowOutline();
            }
        } else {
            unlock1000->setColors(ccc3(30, 30, 30), ccc3(80, 80, 80));
            unlock1000->disableGlowOutline();
        }

        /* first row */
        unlock100->setPosition({-158, 150});
        lock100->setPosition({-158, 150}); lock100->setZOrder(1);
        unlockText100->setScale(.5f); unlockText100->setPosition({-158, 120});
        sliderSpr1->setAnchorPoint({ 0, .5f }); sliderSpr1->setZOrder({-1}); sliderSpr1->setPosition({-131, 150});
        siderBgSpr1->setAnchorPoint({ 0, .5f }); siderBgSpr1->setScaleX({1.1f}); siderBgSpr1->setPosition({-132.5f, 150});       
        unlock200->setPosition({-72, 150});
        lock200->setPosition({-72, 150}); lock200->setZOrder(1);
        unlockText200->setScale(.5f); unlockText200->setPosition({-72, 120});
        sliderSpr2->setAnchorPoint({ 0, .5f }); sliderSpr2->setZOrder({-1}); sliderSpr2->setPosition({-44, 150}); 
        siderBgSpr2->setAnchorPoint({ 0, .5f }); siderBgSpr2->setScaleX({1.1f}); siderBgSpr2->setPosition({-45.5f, 150});
        unlock300->setPosition({14, 150});
        lock300->setPosition({14, 150}); lock300->setZOrder(1);
        unlockText300->setScale(.5f); unlockText300->setPosition({14, 120});
        sliderSpr3->setAnchorPoint({ 0, .5f }); sliderSpr3->setZOrder({-1}); sliderSpr3->setPosition({42, 150});
        siderBgSpr3->setAnchorPoint({ 0, .5f }); siderBgSpr3->setScaleX({1.1f}); siderBgSpr3->setPosition({40.5f, 150});
        unlock400->setPosition({100, 150});
        lock400->setPosition({100, 150}); lock400->setZOrder(1);
        unlockText400->setScale(.5f); unlockText400->setPosition({100, 120});
        sliderSpr4->setAnchorPoint({ 0, .5f }); sliderSpr4->setZOrder({-1}); sliderSpr4->setPosition({128, 150});
        siderBgSpr4->setAnchorPoint({ 0, .5f }); siderBgSpr4->setScaleX({1.1f}); siderBgSpr4->setPosition({126.5f, 150});
        unlock500->setPosition({190, 150});         //186 for accurate, changed because ship is wide af
        lock500->setPosition({190, 150}); lock500->setZOrder(1);
        unlockText500->setScale(.5f); unlockText500->setPosition({190, 120});
        /* second row */
        unlock600->setPosition({-158, 85});
        lock600->setPosition({-158, 85}); lock600->setZOrder(1);
        unlockText600->setScale(.5f); unlockText600->setPosition({-158, 55});
        sliderSpr5->setAnchorPoint({ 0, .5f }); sliderSpr5->setZOrder({-1}); sliderSpr5->setPosition({-131, 85});
        siderBgSpr5->setAnchorPoint({ 0, .5f }); siderBgSpr5->setScaleX({1.1f}); siderBgSpr5->setPosition({-132.5f, 85});
        unlock700->setPosition({-72, 85});
        lock700->setPosition({-72, 85}); lock700->setZOrder(1);
        unlockText700->setScale(.5f); unlockText700->setPosition({-72, 55});
        sliderSpr6->setAnchorPoint({ 0, .5f }); sliderSpr6->setZOrder({-1}); sliderSpr6->setPosition({-44, 85});
        siderBgSpr6->setAnchorPoint({ 0, .5f }); siderBgSpr6->setScaleX({1.1f}); siderBgSpr6->setPosition({-45.5f, 85});
        unlock800->setPosition({14, 85});
        lock800->setPosition({14, 85}); lock800->setZOrder(1);
        unlockText800->setScale(.5f); unlockText800->setPosition({14, 55});
        sliderSpr7->setAnchorPoint({ 0, .5f }); sliderSpr7->setZOrder({-1}); sliderSpr7->setPosition({42, 85});
        siderBgSpr7->setAnchorPoint({ 0, .5f }); siderBgSpr7->setScaleX({1.1f}); siderBgSpr7->setPosition({40.5f, 85});
        unlock900->setPosition({100, 85});
        lock900->setPosition({100, 85}); lock900->setZOrder(1);
        unlockText900->setScale(.5f); unlockText900->setPosition({100, 55});
        sliderSpr8->setAnchorPoint({ 0, .5f }); sliderSpr8->setZOrder({-1}); sliderSpr8->setPosition({128, 85});
        siderBgSpr8->setAnchorPoint({ 0, .5f }); siderBgSpr8->setScaleX({1.1f}); siderBgSpr8->setPosition({126.5f, 85});
        unlock1000->setPosition({190, 85});         //186 for accurate, changed because ship is wide af
        lock1000->setPosition({190, 85}); lock1000->setZOrder(1);
        unlockText1000->setScale(.5f); unlockText1000->setPosition({190, 55});

        auto btn100 = CCMenuItemSpriteExtra::create(
			unlock100,
			this,
			menu_selector(StarPage::openUnlockInfo)
		);
        log::info("Width: {}, Height: {}", unlock100->m_firstLayer->getContentSize().width, unlock100->m_firstLayer->getContentSize().height);
        btn100->setUserObject(unlockInfo100);
        btn100->setContentSize({unlock100->m_firstLayer->getContentSize().width, unlock100->m_firstLayer->getContentSize().height});
        tierMenu->addChild(btn100);

        /* first row */
        //tier1Container->addChild(unlock100);
        tier1Container->addChild(tierMenu);
        tier1Container->addChild(lock100);
        tier1Container->addChild(unlockText100);
        tier1Container->addChild(sliderSpr1);
        tier1Container->addChild(siderBgSpr1);
        tier1Container->addChild(unlock200);
        tier1Container->addChild(lock200);
        tier1Container->addChild(unlockText200);
        tier1Container->addChild(sliderSpr2);
        tier1Container->addChild(siderBgSpr2);
        tier1Container->addChild(unlock300);
        tier1Container->addChild(lock300);
        tier1Container->addChild(unlockText300);
        tier1Container->addChild(sliderSpr3);
        tier1Container->addChild(siderBgSpr3);
        tier1Container->addChild(unlock400);
        tier1Container->addChild(lock400);
        tier1Container->addChild(unlockText400);
        tier1Container->addChild(sliderSpr4);
        tier1Container->addChild(siderBgSpr4);
        tier1Container->addChild(unlock500);
        tier1Container->addChild(lock500);
        tier1Container->addChild(unlockText500);
        /* second row */
        tier1Container->addChild(unlock600);
        tier1Container->addChild(lock600);
        tier1Container->addChild(unlockText600);
        tier1Container->addChild(sliderSpr5);
        tier1Container->addChild(siderBgSpr5);
        tier1Container->addChild(unlock700);
        tier1Container->addChild(lock700);
        tier1Container->addChild(unlockText700);
        tier1Container->addChild(sliderSpr6);
        tier1Container->addChild(siderBgSpr6);
        tier1Container->addChild(unlock800);
        tier1Container->addChild(lock800);
        tier1Container->addChild(unlockText800);
        tier1Container->addChild(sliderSpr7);
        tier1Container->addChild(siderBgSpr7);
        tier1Container->addChild(unlock900);
        tier1Container->addChild(lock900);
        tier1Container->addChild(unlockText900);
        tier1Container->addChild(sliderSpr8);
        tier1Container->addChild(siderBgSpr8);
        tier1Container->addChild(unlock1000);
        tier1Container->addChild(lock1000);
        tier1Container->addChild(unlockText1000);


        /* end of tier's content */
        tier1Container->setPosition({pageWidth * 0.5f, 0});
        return tier1Container;
    }

    CCNode* createTier2(int stars) {
        auto tier2Container = CCNode::create();
        tier2Container->setPosition({0, 0});
        auto layout = geode::RowLayout::create();
        layout->setGap(10.f);
        layout->setAxisAlignment(geode::AxisAlignment::Start);
        layout->setCrossAxisAlignment(geode::AxisAlignment::Center);
        tier2Container->setLayout(layout);
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        pageWidth = winSize.width * 0.75f;


        auto gameManager = GameManager::sharedState();

        auto cube = SimplePlayer::create(1);
        cube->setColors(gameManager->colorForIdx(gameManager->getPlayerColor()), gameManager->colorForIdx(gameManager->getPlayerColor2()));
        cube->setGlowOutline(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
        cube->updatePlayerFrame(122, IconType::Cube);
        cube->setAnchorPoint({ .5f, .5f });
        cube->setPosition({0, 120});
        tier2Container->addChild(cube);

        tier2Container->setPosition({pageWidth * 0.5f, 0});
        return tier2Container;
    }

    CCNode* createTier3(int stars) {
        auto tier3Container = CCNode::create();
        tier3Container->setPosition({0, 0});
        auto layout = geode::RowLayout::create();
        layout->setGap(10.f);
        layout->setAxisAlignment(geode::AxisAlignment::Start);
        layout->setCrossAxisAlignment(geode::AxisAlignment::Center);
        tier3Container->setLayout(layout);
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        pageWidth = winSize.width * 0.75f;


        auto gameManager = GameManager::sharedState();

        auto ship = SimplePlayer::create(1);
        ship->setColors(gameManager->colorForIdx(gameManager->getPlayerColor()), gameManager->colorForIdx(gameManager->getPlayerColor2()));
        ship->setGlowOutline(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
        ship->updatePlayerFrame(5, IconType::Ship);
        ship->setAnchorPoint({ .5f, .5f });
        ship->setPosition({0, 120});
        tier3Container->addChild(ship);


        tier3Container->setPosition({pageWidth * 0.5f, 0});
        return tier3Container;
    }

    CCNode* createTier4(int stars) {
        auto tier4Container = CCNode::create();
        tier4Container->setPosition({0, 0});
        auto layout = geode::RowLayout::create();
        layout->setGap(10.f);
        layout->setAxisAlignment(geode::AxisAlignment::Start);
        layout->setCrossAxisAlignment(geode::AxisAlignment::Center);
        tier4Container->setLayout(layout);
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        pageWidth = winSize.width * 0.75f;


        auto gameManager = GameManager::sharedState();

        auto ball = SimplePlayer::create(1);
        ball->setColors(gameManager->colorForIdx(gameManager->getPlayerColor()), gameManager->colorForIdx(gameManager->getPlayerColor2()));
        ball->setGlowOutline(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
        ball->updatePlayerFrame(5, IconType::Ball);
        ball->setAnchorPoint({ .5f, .5f });
        ball->setPosition({0, 120});
        tier4Container->addChild(ball);


        tier4Container->setPosition({pageWidth * 0.5f, 0});
        return tier4Container;
    }
};