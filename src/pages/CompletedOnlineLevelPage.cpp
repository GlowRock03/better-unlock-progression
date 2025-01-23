#pragma once

#include <Geode/Geode.hpp>
#include <Geode/utils/cocos.hpp>

#include "UnlockProgressionPopup.cpp"
#include "../modify/ItemInfoPopup.cpp"

using namespace geode::prelude;

class CompletedOnlineLevelPage : public CCObject {
private:

    struct UnlockData : public cocos2d::CCObject {
        std::string numberString;
        int unlockId;
        IconType iconType;
        std::string colorType;

        UnlockData(const std::string& num, int id, const std::string& type) : numberString(num), unlockId(id), colorType(type) {}
        UnlockData(const std::string& num, int id, IconType type) : numberString(num), unlockId(id), iconType(type) {}
    };

    struct UnlockInfo : public cocos2d::CCObject {
        int iconId;
        IconType unlockType;
        std::string colorType;                      //I dont think colours are in icon type so this is a string to identify when I want to display a colour
                                                    //also it hurts me to not use a u in colour :sob:
        UnlockInfo(int id, std::string type) : iconId(id), colorType(type) {}
        UnlockInfo(int id, IconType type) : iconId(id), unlockType(type), colorType("") {}
    };

    GJEffectManager* effectManager;
    GameManager* gameManager;

    FLAlertLayer* popupLayer;

    CCNode* pageContainer;
    CCMenu* buttonMenu;

    float pageWidth;

    CCArray* tierPages;
    int currentPage;
    
    CCNode* tier1Page;
    CCNode* tier2Page;

    CCMenuItemSpriteExtra* tier1Button = nullptr;
    CCMenuItemSpriteExtra* tier2Button = nullptr;

    CCSprite* page1Selected = nullptr;
    CCSprite* page2Selected = nullptr;
    CCSprite* page1Deselected = nullptr;
    CCSprite* page2Deselected = nullptr;

    bool togglePlayerColours;

    UnlockData* unlockData0 = nullptr;
    UnlockData* unlockData1 = nullptr;
    UnlockData* unlockData2 = nullptr;
    UnlockData* unlockData3 = nullptr;
    UnlockData* unlockData4 = nullptr;
    UnlockData* unlockData5 = nullptr;
    UnlockData* unlockData6 = nullptr;
    UnlockData* unlockData7 = nullptr;
    UnlockData* unlockData8 = nullptr;
    UnlockData* unlockData9 = nullptr;
    UnlockData* unlockData10 = nullptr;
    UnlockData* unlockData11 = nullptr;
    UnlockData* unlockData12 = nullptr;
    UnlockData* unlockData13 = nullptr;
    UnlockData* unlockData14 = nullptr;

public:
    CompletedOnlineLevelPage(FLAlertLayer* parentPopup) {

        effectManager = GJEffectManager::create();
        gameManager = GameManager::sharedState();
        popupLayer = parentPopup;
        tierPages = CCArray::create();
        tierPages->retain();
        buttonMenu = CCMenu::create();
        page1Selected = CCSprite::create("GJ_square03-uhd.png");
        page2Selected = CCSprite::create("GJ_square03-uhd.png");
        page2Selected->setVisible(false);
        page1Deselected = CCSprite::create("GJ_square01-uhd.png");
        page1Deselected->setVisible(false);
        page2Deselected = CCSprite::create("GJ_square01-uhd.png");
        togglePlayerColours = Mod::get()->getSettingValue<bool>("toggle-player-colors");

        unlockData0 = new UnlockData("0", 1, IconType::Cube); unlockData0->autorelease();
        
        unlockData1 = new UnlockData("1", 11, "main"); unlockData1->autorelease();
        unlockData2 = new UnlockData("10", 12, IconType::Cube); unlockData2->autorelease();
        unlockData3 = new UnlockData("50", 36, IconType::Cube); unlockData3->autorelease();
        unlockData4 = new UnlockData("100", 13, IconType::Ship); unlockData4->autorelease();
        unlockData5 = new UnlockData("200", 19, "main"); unlockData5->autorelease();
        unlockData6 = new UnlockData("300", 40, IconType::Cube); unlockData6->autorelease();
        unlockData7 = new UnlockData("500", 15, IconType::Ship); unlockData7->autorelease();
        unlockData8 = new UnlockData("1000", 17, IconType::Ship); unlockData8->autorelease();
        unlockData9 = new UnlockData("1500", 148, IconType::Ship); unlockData9->autorelease();
        unlockData10 = new UnlockData("2000", 164, IconType::Cube); unlockData10->autorelease();

        unlockData11 = new UnlockData("2500", 60, "main"); unlockData11->autorelease();
        unlockData12 = new UnlockData("3000", 161, IconType::Cube); unlockData12->autorelease();
        unlockData13 = new UnlockData("4000", 200, IconType::Cube); unlockData13->autorelease();
        unlockData14 = new UnlockData("5000", 108, IconType::Ufo); unlockData14->autorelease();
    }

    CCNode* createCompleteOnlinePage(int completedOnline) {

        pageContainer = CCNode::create();
        pageContainer->setPosition({0, 0});
        buttonMenu->setPosition({147, -200});
        pageContainer->addChild(buttonMenu);

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        pageWidth = winSize.width * 0.75f;

        currentPage = 0;

        auto labelSpr = CCSprite::create("completed_online_spr.png"_spr);
        labelSpr->setPosition({227.5f, 185});
        labelSpr->setScale(0.65f);
        pageContainer->addChild(labelSpr);

        auto player = SimplePlayer::create(1);
        player->updatePlayerFrame(gameManager->m_playerFrame, IconType::Cube);
        player->setColors(gameManager->colorForIdx(gameManager->getPlayerColor()), gameManager->colorForIdx(gameManager->getPlayerColor2()));
        if (gameManager->m_playerGlow) {
            player->setGlowOutline(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
        }
        player->setPosition({228, 200});
        player->setScale(1.35f);
        pageContainer->addChild(player);

        auto labelTopSpr = CCSprite::create("completed_online_top_spr.png"_spr);
        labelTopSpr->setPosition({228.25f, 175});
        labelTopSpr->setScale(0.5f);
        pageContainer->addChild(labelTopSpr);

        tier1Page = createTier1(completedOnline);
        tier1Page->retain();
        pageContainer->addChild(tier1Page);
        tierPages->addObject(tier1Page);
        tier1Page->setVisible(true);

        tier2Page = createTier2(completedOnline);
        tier2Page->retain();
        pageContainer->addChild(tier2Page);
        tierPages->addObject(tier2Page);
        tier2Page->setVisible(false);

        createNavigationButtons();

        pageContainer->setPosition({pageWidth * 0.5f, 0});

        return pageContainer;
    }

    ~CompletedOnlineLevelPage() {
        if (tierPages) {
            tierPages->release();
        }
    }

private:
    void createNavigationButtons() {

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        float popupHeight = winSize.height * 0.8f;

        CCSprite* tier1ButtonSpr = CCSprite::createWithSpriteFrameName("rankIcon_top500_001.png");
        CCSprite* tier2ButtonSpr = CCSprite::createWithSpriteFrameName("rankIcon_top200_001.png");

        tier1ButtonSpr->setScale(0.9f);
        tier2ButtonSpr->setScale(0.82f);

        auto tier1Button = CCMenuItemSpriteExtra::create(
            tier1ButtonSpr,
            this,
            menu_selector(CompletedOnlineLevelPage::onTierButton)
        );
        tier1Button->setTag(0);
        tier1Button->setAnchorPoint({.5f, .5f});
        tier1Button->setPosition({67, 220});

        page1Deselected->setAnchorPoint({.5f, 0});
        page1Deselected->setPosition({67, 208});
        page1Deselected->setScale(.3f);
        page1Deselected->setZOrder(-2);

        page1Selected->setAnchorPoint({.5f, 0});
        page1Selected->setPosition({67, 208});
        page1Selected->setScale(.3f);
        page1Selected->setZOrder(-2);

        buttonMenu->addChild(tier1Button);
        buttonMenu->addChild(page1Deselected);
        buttonMenu->addChild(page1Selected);

        tier2Button = CCMenuItemSpriteExtra::create(
            tier2ButtonSpr,
            this,
            menu_selector(CompletedOnlineLevelPage::onTierButton)
        );
        tier2Button->setTag(1);
        tier2Button->setAnchorPoint({.5f, .5f});
        tier2Button->setPosition({94, 220});

        page2Deselected->setAnchorPoint({.5f, 0});
        page2Deselected->setPosition({94, 208});
        page2Deselected->setScale(.3f);
        page2Deselected->setZOrder(-2);

        page2Selected->setAnchorPoint({.5f, 0});
        page2Selected->setPosition({94, 208});
        page2Selected->setScale(.3f);
        page2Selected->setZOrder(-2);

        buttonMenu->addChild(tier2Button);
        buttonMenu->addChild(page2Deselected);
        buttonMenu->addChild(page2Selected);
    }

    void onTierButton(CCObject* sender) {

        auto button = static_cast<CCMenuItemSpriteExtra*>(sender);
        int tag = button->getTag();
        currentPage = tag;
        updatePageVisibility(tag);
    }

    void openUnlockInfo(CCObject* sender) {
        auto button = static_cast<CCMenuItemSpriteExtra*>(sender);
        auto unlockInfo = dynamic_cast<UnlockInfo*>(button->getUserObject());

        if (unlockInfo->colorType.empty()) {
            auto popup = MyItemInfoPopup::createWithCustomizations(
                unlockInfo->iconId,
                GameManager::sharedState()->iconTypeToUnlockType(unlockInfo->unlockType)
            );
            popupLayer->addChild(popup);
        } else if (unlockInfo->colorType == "main") {
            popupLayer->addChild(MyItemInfoPopup::createWithCustomizations(
                unlockInfo->iconId, UnlockType::Col1
            ));
        } else if (unlockInfo->colorType == "secondary") {
            popupLayer->addChild(MyItemInfoPopup::createWithCustomizations(
                unlockInfo->iconId, UnlockType::Col2
            ));
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
            page1Deselected->setVisible(false);
            page2Deselected->setVisible(true);
        } else if (tag == 1) {

            page1Selected->setVisible(false);
            page2Selected->setVisible(true);
            page1Deselected->setVisible(true);
            page2Deselected->setVisible(false);
        } else if (tag == 2) {

            page1Selected->setVisible(false);
            page2Selected->setVisible(false);
            page1Deselected->setVisible(true);
            page2Deselected->setVisible(true);
        } else {

            page1Selected->setVisible(false);
            page2Selected->setVisible(false);
            page1Deselected->setVisible(true);
            page2Deselected->setVisible(true);
        }
    }

    const char* addCommas(const char* number) {
        std::string str(number);
        int len = str.length();
        int commaCount = (len - 1) / 3;

        std::string result;
        int count = 0;

        for (int i = len - 1; i >= 0; --i) {
            result.push_back(str[i]);
            count++;
            if (count % 3 == 0 && i != 0) {
                result.push_back(',');
            }
        }

        std::reverse(result.begin(), result.end());

        char* resultCStr = new char[result.length() + 1];
        std::copy(result.begin(), result.end(), resultCStr);
        resultCStr[result.length()] = '\0';

        return resultCStr;
    }

    CCNode* createTier1(int completedOnline) {
        auto tierContainer = CCNode::create();
        tierContainer->setPosition({0, 0});
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        pageWidth = winSize.width * 0.75f;
        CCMenu* tierMenu = CCMenu::create();

        /* Tier's Content */

        /* Moving Progress Text */
        auto currentProgressText = CCLabelBMFont::create("", "bigFont-uhd.fnt");
        currentProgressText->setScale(0.35f);

        /* Completion Stars */
        auto tierCompletedStar1 = CCSprite::createWithSpriteFrameName("GJ_bigStar_001.png");
        auto tierCompletedStarGlow1 = CCSprite::createWithSpriteFrameName("GJ_bigStar_glow_001.png");
        tierCompletedStarGlow1->setAnchorPoint({0, 0});
        tierCompletedStarGlow1->setPosition({-11, -11});
        tierCompletedStarGlow1->setZOrder(-1);
        tierCompletedStar1->addChild(tierCompletedStarGlow1);

        auto tierCompletedStar2 = CCSprite::createWithSpriteFrameName("GJ_bigStar_001.png");
        auto tierCompletedStarGlow2 = CCSprite::createWithSpriteFrameName("GJ_bigStar_glow_001.png");
        tierCompletedStarGlow2->setAnchorPoint({0, 0});
        tierCompletedStarGlow2->setPosition({-11, -11});
        tierCompletedStarGlow2->setZOrder(-1);
        tierCompletedStar2->addChild(tierCompletedStarGlow2);

        /* First Row */
        auto sliderOutlineSpr1 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr1 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio1 = (float)(completedOnline - std::stoi(unlockData0->numberString)) / (float)(std::stoi(unlockData1->numberString) - std::stoi(unlockData0->numberString));
        float scale1 = ratio1 >= 0.98f ? sliderBarSpr1->getContentSize().width * 0.98f : sliderBarSpr1->getContentSize().width * ratio1;
        sliderBarSpr1->setTextureRect(CCRectMake(0, 0, scale1, sliderBarSpr1->getContentSize().height));

        auto unlockText1 = CCLabelBMFont::create(addCommas(unlockData1->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo1 = new UnlockInfo(unlockData1->unlockId, unlockData1->colorType);
        unlockInfo1->autorelease();
        auto unlock1 = ColorChannelSprite::create();
        auto lock1 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr2 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr2 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio2 = (float)(completedOnline - std::stoi(unlockData1->numberString)) / (float)(std::stoi(unlockData2->numberString) - std::stoi(unlockData1->numberString));
        float scale2 = ratio2 >= 0.98f ? sliderBarSpr2->getContentSize().width * 0.98f : sliderBarSpr2->getContentSize().width * ratio2;
        sliderBarSpr2->setTextureRect(CCRectMake(0, 0, scale2, sliderBarSpr2->getContentSize().height)); 

        auto unlockText2 = CCLabelBMFont::create(addCommas(unlockData2->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo2 = new UnlockInfo(unlockData2->unlockId, unlockData2->iconType);
        unlockInfo2->autorelease();
        auto unlock2 = SimplePlayer::create(1);
        auto lock2 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr3 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr3 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio3 = (float)(completedOnline - std::stoi(unlockData2->numberString)) / (float)(std::stoi(unlockData3->numberString) - std::stoi(unlockData2->numberString));
        float scale3 = ratio3 >= 0.98f ? sliderBarSpr3->getContentSize().width * 0.98f : sliderBarSpr3->getContentSize().width * ratio3;
        sliderBarSpr3->setTextureRect(CCRectMake(0, 0, scale3, sliderBarSpr3->getContentSize().height));  

        auto unlockText3 = CCLabelBMFont::create(addCommas(unlockData3->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo3 = new UnlockInfo(unlockData3->unlockId, unlockData3->iconType);
        unlockInfo3->autorelease();
        auto unlock3 = SimplePlayer::create(1);
        auto lock3 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr4 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr4 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio4 = (float)(completedOnline - std::stoi(unlockData3->numberString)) / (float)(std::stoi(unlockData4->numberString) - std::stoi(unlockData3->numberString));
        float scale4 = ratio4 >= 0.98f ? sliderBarSpr4->getContentSize().width * 0.98f : sliderBarSpr4->getContentSize().width * ratio4;
        sliderBarSpr4->setTextureRect(CCRectMake(0, 0, scale4, sliderBarSpr4->getContentSize().height));

        auto unlockText4 = CCLabelBMFont::create(addCommas(unlockData4->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo4 = new UnlockInfo(unlockData4->unlockId, unlockData4->iconType);
        unlockInfo4->autorelease();
        auto unlock4 = SimplePlayer::create(1);
        auto lock4 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr5 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr5 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio5 = (float)(completedOnline - std::stoi(unlockData4->numberString)) / (float)(std::stoi(unlockData5->numberString) - std::stoi(unlockData4->numberString));
        float scale5 = ratio5 >= 0.98f ? sliderBarSpr5->getContentSize().width * 0.98f : sliderBarSpr5->getContentSize().width * ratio5;
        sliderBarSpr5->setTextureRect(CCRectMake(0, 0, scale5, sliderBarSpr5->getContentSize().height));

        auto unlockText5 = CCLabelBMFont::create(addCommas(unlockData5->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo5 = new UnlockInfo(unlockData5->unlockId, unlockData5->colorType);
        unlockInfo5->autorelease();
        auto unlock5 = ColorChannelSprite::create();
        auto lock5 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        /* second row */
        auto sliderOutlineSpr6 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr6 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio6 = (float)(completedOnline - std::stoi(unlockData5->numberString)) / (float)(std::stoi(unlockData6->numberString) - std::stoi(unlockData5->numberString));
        float scale6 = ratio6 >= 0.98f ? sliderBarSpr6->getContentSize().width * 0.98f : sliderBarSpr6->getContentSize().width * ratio6;
        sliderBarSpr6->setTextureRect(CCRectMake(0, 0, scale6, sliderBarSpr6->getContentSize().height));

        auto unlockText6 = CCLabelBMFont::create(addCommas(unlockData6->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo6 = new UnlockInfo(unlockData6->unlockId, unlockData6->iconType);
        unlockInfo6->autorelease();
        auto unlock6 = SimplePlayer::create(1);
        auto lock6 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr7 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr7 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio7 = (float)(completedOnline - std::stoi(unlockData6->numberString)) / (float)(std::stoi(unlockData7->numberString) - std::stoi(unlockData6->numberString));
        float scale7 = ratio7 >= 0.98f ? sliderBarSpr7->getContentSize().width * 0.98f : sliderBarSpr7->getContentSize().width * ratio7;
        sliderBarSpr7->setTextureRect(CCRectMake(0, 0, scale7, sliderBarSpr7->getContentSize().height));

        auto unlockText7 = CCLabelBMFont::create(addCommas(unlockData7->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo7 = new UnlockInfo(unlockData7->unlockId, unlockData7->iconType);
        unlockInfo7->autorelease();
        auto unlock7 = SimplePlayer::create(1);
        auto lock7 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr8 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr8 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio8 = (float)(completedOnline - std::stoi(unlockData7->numberString)) / (float)(std::stoi(unlockData8->numberString) - std::stoi(unlockData7->numberString));
        float scale8 = ratio8 >= 0.98f ? sliderBarSpr8->getContentSize().width * 0.98f : sliderBarSpr8->getContentSize().width * ratio8;
        sliderBarSpr8->setTextureRect(CCRectMake(0, 0, scale8, sliderBarSpr8->getContentSize().height));

        auto unlockText8 = CCLabelBMFont::create(addCommas(unlockData8->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo8 = new UnlockInfo(unlockData8->unlockId, unlockData8->iconType);
        unlockInfo8->autorelease();
        auto unlock8 = SimplePlayer::create(1);
        auto lock8 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr9 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr9 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio9 = (float)(completedOnline - std::stoi(unlockData8->numberString)) / (float)(std::stoi(unlockData9->numberString) - std::stoi(unlockData8->numberString));
        float scale9 = ratio9 >= 0.98f ? sliderBarSpr9->getContentSize().width * 0.98f : sliderBarSpr9->getContentSize().width * ratio9;
        sliderBarSpr9->setTextureRect(CCRectMake(0, 0, scale9, sliderBarSpr9->getContentSize().height));

        auto unlockText9 = CCLabelBMFont::create(addCommas(unlockData9->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo9 = new UnlockInfo(unlockData9->unlockId, unlockData9->iconType);
        unlockInfo9->autorelease();
        auto unlock9 = SimplePlayer::create(1);
        auto lock9 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr10 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr10 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio10 = (float)(completedOnline - std::stoi(unlockData9->numberString)) / (float)(std::stoi(unlockData9->numberString) - std::stoi(unlockData8->numberString));
        float scale10 = ratio10 >= 0.98f ? sliderBarSpr10->getContentSize().width * 0.98f : sliderBarSpr10->getContentSize().width * ratio10;
        sliderBarSpr10->setTextureRect(CCRectMake(0, 0, scale10, sliderBarSpr10->getContentSize().height));

        auto unlockText10 = CCLabelBMFont::create(addCommas(unlockData10->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo10 = new UnlockInfo(unlockData10->unlockId, unlockData10->iconType);
        unlockInfo10->autorelease();
        auto unlock10 = SimplePlayer::create(1);
        auto lock10 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        /* Set Progress Text */
        bool isInTier =  completedOnline >= std::stoi(unlockData0->numberString) && completedOnline < std::stoi(unlockData10->numberString);
        if (ratio1 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(completedOnline).c_str()));
            currentProgressText->setPosition({-185, 138});
            tierContainer->addChild(currentProgressText);
        } else if (ratio2 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(completedOnline).c_str()));
            currentProgressText->setPosition({-99, 138});
            tierContainer->addChild(currentProgressText);
        } else if (ratio3 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(completedOnline).c_str()));
            currentProgressText->setPosition({-12.5f, 138});
            tierContainer->addChild(currentProgressText);
        } else if (ratio4 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(completedOnline).c_str()));
            currentProgressText->setPosition({77, 138});
            tierContainer->addChild(currentProgressText);
        } else if (ratio5 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(completedOnline).c_str()));
            currentProgressText->setPosition({167.5f, 138});
            tierContainer->addChild(currentProgressText);
        } else if (ratio6 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(completedOnline).c_str()));
            currentProgressText->setPosition({-185, 73});
            tierContainer->addChild(currentProgressText);
        } else if (ratio7 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(completedOnline).c_str()));
            currentProgressText->setPosition({-99, 73});
            tierContainer->addChild(currentProgressText);
        } else if (ratio8 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(completedOnline).c_str()));
            currentProgressText->setPosition({-12.5f, 73});
            tierContainer->addChild(currentProgressText);
        } else if (ratio9 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(completedOnline).c_str()));
            currentProgressText->setPosition({77, 73});
            tierContainer->addChild(currentProgressText);
        } else if (ratio10 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(completedOnline).c_str()));
            currentProgressText->setPosition({167.5f, 73});
            tierContainer->addChild(currentProgressText);
        } 
        if (ratio10 >= 1.f) {
            tierCompletedStar1->setAnchorPoint({0, 0});
            tierCompletedStar2->setAnchorPoint({0, 0});
            tierCompletedStar1->setPosition({-72, 8});
            tierCompletedStar2->setPosition({77, 8});
            tierCompletedStar1->setScale(0.5f);
            tierCompletedStar2->setScale(0.5f);
            tierContainer->addChild(tierCompletedStar1);
            tierContainer->addChild(tierCompletedStar2);
        }

        /* Colour Init */
        auto p1Unlocked = ccc3(190, 190, 190);
        auto p2Unlocked = ccc3(245, 245, 245);
        auto p1Grey = ccc3(30, 30, 30);
        auto p2Grey = ccc3(80, 80, 80);

        /* First Row */
        togglePlayerColours ? sliderBarSpr1->setColor(gameManager->colorForIdx(gameManager->getPlayerColor())) : void();

        unlock1->setColor(gameManager->colorForIdx(unlockInfo1->iconId));
        if (ratio1 >= 1.f) {
            lock1->setVisible(false);
        }
        
        togglePlayerColours ? sliderBarSpr2->setColor(gameManager->colorForIdx(gameManager->getPlayerColor())) : void();

        unlock2->updatePlayerFrame(unlockInfo2->iconId, unlockInfo2->unlockType);
        if (ratio2 >= 1.f) {
            lock2->setVisible(false);
            if (togglePlayerColours) {
                unlock2->setColors(gameManager->colorForIdx(gameManager->getPlayerColor()), gameManager->colorForIdx(gameManager->getPlayerColor2()));
                if (gameManager->m_playerGlow) {
                    unlock2->setGlowOutline(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
                }
            } else {
                unlock2->setColors(p1Unlocked, p2Unlocked);
                unlock2->disableGlowOutline();
            }
        } else {
            unlock2->setColors(p1Grey, p2Grey);
            unlock2->disableGlowOutline();
        }

        togglePlayerColours ? sliderBarSpr3->setColor(gameManager->colorForIdx(gameManager->getPlayerColor())) : void();

        unlock3->updatePlayerFrame(unlockInfo3->iconId, unlockInfo3->unlockType);
        if (ratio3 >= 1.f) {
            lock3->setVisible(false);
            if (togglePlayerColours) {
                unlock3->setColors(gameManager->colorForIdx(gameManager->getPlayerColor()), gameManager->colorForIdx(gameManager->getPlayerColor2()));
                if (gameManager->m_playerGlow) {
                    unlock3->setGlowOutline(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
                }
            } else {
                unlock3->setColors(p1Unlocked, p2Unlocked);
                unlock3->disableGlowOutline();
            }
        } else {
            unlock3->setColors(p1Grey, p2Grey);
            unlock3->disableGlowOutline();
        }

        togglePlayerColours ? sliderBarSpr4->setColor(gameManager->colorForIdx(gameManager->getPlayerColor())) : void();

        unlock4->updatePlayerFrame(unlockInfo4->iconId, unlockInfo4->unlockType);
        if (ratio4 >= 1.f) {
            lock4->setVisible(false);
            if (togglePlayerColours) {
                unlock4->setColors(gameManager->colorForIdx(gameManager->getPlayerColor()), gameManager->colorForIdx(gameManager->getPlayerColor2()));
                if (gameManager->m_playerGlow) {
                    unlock4->setGlowOutline(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
                }
            } else {
                unlock4->setColors(p1Unlocked, p2Unlocked);
                unlock4->disableGlowOutline();
            }
        } else {
            unlock4->setColors(p1Grey, p2Grey);
            unlock4->disableGlowOutline();
        }

        togglePlayerColours ? sliderBarSpr5->setColor(gameManager->colorForIdx(gameManager->getPlayerColor())) : void();

        unlock5->setColor(gameManager->colorForIdx(unlockInfo5->iconId));
        if (ratio5 >= 1.f) {
            lock5->setVisible(false);
        }

        /* Second Row */
        togglePlayerColours ? sliderBarSpr6->setColor(gameManager->colorForIdx(gameManager->getPlayerColor())) : void();

        unlock6->updatePlayerFrame(unlockInfo6->iconId, unlockInfo6->unlockType);
        if (ratio6 >= 1.f) {
            lock6->setVisible(false);
            if (togglePlayerColours) {
                unlock6->setColors(gameManager->colorForIdx(gameManager->getPlayerColor()), gameManager->colorForIdx(gameManager->getPlayerColor2()));
                if (gameManager->m_playerGlow) {
                    unlock6->setGlowOutline(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
                }
            } else {
                unlock6->setColors(p1Unlocked, p2Unlocked);
                unlock6->disableGlowOutline();
            }
        } else {
            unlock6->setColors(p1Grey, p2Grey);
            unlock6->disableGlowOutline();
        }

        togglePlayerColours ? sliderBarSpr7->setColor(gameManager->colorForIdx(gameManager->getPlayerColor())) : void();

        unlock7->updatePlayerFrame(unlockInfo7->iconId, unlockInfo7->unlockType);
        if (ratio7 >= 1.f) {
            lock7->setVisible(false);
            if (togglePlayerColours) {
                unlock7->setColors(gameManager->colorForIdx(gameManager->getPlayerColor()), gameManager->colorForIdx(gameManager->getPlayerColor2()));
                if (gameManager->m_playerGlow) {
                    unlock7->setGlowOutline(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
                }
            } else {
                unlock7->setColors(p1Unlocked, p2Unlocked);
                unlock7->disableGlowOutline();
            }
        } else {
            unlock7->setColors(p1Grey, p2Grey);
            unlock7->disableGlowOutline();
        }

        togglePlayerColours ? sliderBarSpr8->setColor(gameManager->colorForIdx(gameManager->getPlayerColor())) : void();

        unlock8->updatePlayerFrame(unlockInfo8->iconId, unlockInfo8->unlockType);
        if (ratio8 >= 1.f) {
            lock8->setVisible(false);
            if (togglePlayerColours) {
                unlock8->setColors(gameManager->colorForIdx(gameManager->getPlayerColor()), gameManager->colorForIdx(gameManager->getPlayerColor2()));
                if (gameManager->m_playerGlow) {
                    unlock8->setGlowOutline(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
                }
            } else {
                unlock8->setColors(p1Unlocked, p2Unlocked);
                unlock8->disableGlowOutline();
            }
        } else {
            unlock8->setColors(p1Grey, p2Grey);
            unlock8->disableGlowOutline();
        }

        togglePlayerColours ? sliderBarSpr9->setColor(gameManager->colorForIdx(gameManager->getPlayerColor())) : void();

        unlock9->updatePlayerFrame(unlockInfo9->iconId, unlockInfo9->unlockType);
        if (ratio9 >= 1.f) {
            lock9->setVisible(false);
            if (togglePlayerColours) {
                unlock9->setColors(gameManager->colorForIdx(gameManager->getPlayerColor()), gameManager->colorForIdx(gameManager->getPlayerColor2()));
                if (gameManager->m_playerGlow) {
                    unlock9->setGlowOutline(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
                }
            } else {
                unlock9->setColors(p1Unlocked, p2Unlocked);
                unlock9->disableGlowOutline();
            }
        } else {
            unlock9->setColors(p1Grey, p2Grey);
            unlock9->disableGlowOutline();
        }

        togglePlayerColours ? sliderBarSpr10->setColor(gameManager->colorForIdx(gameManager->getPlayerColor())) : void();

        unlock10->updatePlayerFrame(unlockInfo10->iconId, unlockInfo10->unlockType);
        if (ratio10 >= 1.f) {
            lock10->setVisible(false);
            if (togglePlayerColours) {
                unlock10->setColors(gameManager->colorForIdx(gameManager->getPlayerColor()), gameManager->colorForIdx(gameManager->getPlayerColor2()));
                if (gameManager->m_playerGlow) {
                    unlock10->setGlowOutline(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
                }
            } else {
                unlock10->setColors(p1Unlocked, p2Unlocked);
                unlock10->disableGlowOutline();
            }
        } else {
            unlock10->setColors(p1Grey, p2Grey);
            unlock10->disableGlowOutline();
        }

        /* First Row */
        sliderBarSpr1->setAnchorPoint({ 0, .5f }); sliderBarSpr1->setZOrder({-1}); sliderBarSpr1->setPosition({-201, 150});
        sliderOutlineSpr1->setAnchorPoint({ 0, .5f }); sliderOutlineSpr1->setScaleX({1.1f}); sliderOutlineSpr1->setPosition({-203, 150});      
        lock1->setPosition({17.75f, 18.25f}); lock1->setZOrder(1);
        unlockText1->setScale(.5f); unlockText1->setPosition({-142.5f, 120});
        sliderBarSpr2->setAnchorPoint({ 0, .5f }); sliderBarSpr2->setZOrder({-1}); sliderBarSpr2->setPosition({-115, 150}); 
        sliderOutlineSpr2->setAnchorPoint({ 0, .5f }); sliderOutlineSpr2->setScaleX({1.1f}); sliderOutlineSpr2->setPosition({-117, 150}); 
        lock2->setZOrder(1);
        unlockText2->setScale(.5f); unlockText2->setPosition({-55.5f, 120});
        sliderBarSpr3->setAnchorPoint({ 0, .5f }); sliderBarSpr3->setZOrder({-1}); sliderBarSpr3->setPosition({-28.5f, 150});
        sliderOutlineSpr3->setAnchorPoint({ 0, .5f }); sliderOutlineSpr3->setScaleX({1.1f}); sliderOutlineSpr3->setPosition({-30.5f, 150});
        lock3->setZOrder(1);
        unlockText3->setScale(.5f); unlockText3->setPosition({33, 120});
        sliderBarSpr4->setAnchorPoint({ 0, .5f }); sliderBarSpr4->setZOrder({-1}); sliderBarSpr4->setPosition({61, 150});
        sliderOutlineSpr4->setAnchorPoint({ 0, .5f }); sliderOutlineSpr4->setScaleX({1.1f}); sliderOutlineSpr4->setPosition({59, 150});
        lock4->setZOrder(1);
        unlockText4->setScale(.5f); unlockText4->setPosition({122, 120});
        sliderBarSpr5->setAnchorPoint({ 0, .5f }); sliderBarSpr5->setZOrder({-1}); sliderBarSpr5->setPosition({151, 150});
        sliderOutlineSpr5->setAnchorPoint({ 0, .5f }); sliderOutlineSpr5->setScaleX({1.1f}); sliderOutlineSpr5->setPosition({149, 150});
        lock5->setPosition({17.75f, 18.25f}); lock5->setZOrder(1);
        unlockText5->setScale(.5f); unlockText5->setPosition({211.5f, 120});

        /* Second Row */
        sliderBarSpr6->setAnchorPoint({ 0, .5f }); sliderBarSpr6->setZOrder({-1}); sliderBarSpr6->setPosition({-201, 85});
        sliderOutlineSpr6->setAnchorPoint({ 0, .5f }); sliderOutlineSpr6->setScaleX({1.1f}); sliderOutlineSpr6->setPosition({-203, 85});
        lock6->setZOrder(1);
        unlockText6->setScale(.5f); unlockText6->setPosition({-142, 55});
        sliderBarSpr7->setAnchorPoint({ 0, .5f }); sliderBarSpr7->setZOrder({-1}); sliderBarSpr7->setPosition({-115, 85});
        sliderOutlineSpr7->setAnchorPoint({ 0, .5f }); sliderOutlineSpr7->setScaleX({1.1f}); sliderOutlineSpr7->setPosition({-117, 85});
        lock7->setZOrder(1);
        unlockText7->setScale(.5f); unlockText7->setPosition({-55.5f, 55});
        sliderBarSpr8->setAnchorPoint({ 0, .5f }); sliderBarSpr8->setZOrder({-1}); sliderBarSpr8->setPosition({-28.5f, 85});
        sliderOutlineSpr8->setAnchorPoint({ 0, .5f }); sliderOutlineSpr8->setScaleX({1.1f}); sliderOutlineSpr8->setPosition({-30.5f, 85});
        lock8->setZOrder(1);
        unlockText8->setScale(.5f); unlockText8->setPosition({33, 55});
        sliderBarSpr9->setAnchorPoint({ 0, .5f }); sliderBarSpr9->setZOrder({-1}); sliderBarSpr9->setPosition({61, 85});
        sliderOutlineSpr9->setAnchorPoint({ 0, .5f }); sliderOutlineSpr9->setScaleX({1.1f}); sliderOutlineSpr9->setPosition({59, 85});
        lock9->setZOrder(1);
        unlockText9->setScale(.5f); unlockText9->setPosition({122, 55});
        sliderBarSpr10->setAnchorPoint({ 0, .5f }); sliderBarSpr10->setZOrder({-1}); sliderBarSpr10->setPosition({151, 85});
        sliderOutlineSpr10->setAnchorPoint({ 0, .5f }); sliderOutlineSpr10->setScaleX({1.1f}); sliderOutlineSpr10->setPosition({149, 85});
        lock10->setZOrder(1);
        unlockText10->setScale(.5f); unlockText10->setPosition({211.5f, 55});

        /* First Row */
        unlock1->addChild(lock1);
        unlock2->addChild(lock2);
        unlock3->addChild(lock3);
        unlock4->addChild(lock4);
        unlock5->addChild(lock5);

        /* Second Row */
        unlock6->addChild(lock6);
        unlock7->addChild(lock7);
        unlock8->addChild(lock8);
        unlock9->addChild(lock9);
        unlock10->addChild(lock10);

        /* First Row */
        auto unlockButton1 = CCMenuItemSpriteExtra::create(
			unlock1,
			this,
			menu_selector(CompletedOnlineLevelPage::openUnlockInfo)
		);
        unlockButton1->setUserObject(unlockInfo1);

        auto unlockButton2 = CCMenuItemSpriteExtra::create(
			unlock2,
			this,
			menu_selector(CompletedOnlineLevelPage::openUnlockInfo)
		);
        unlockButton2->setUserObject(unlockInfo2);
        unlockButton2->setContentSize({unlock2->m_firstLayer->getContentSize().width, unlock2->m_firstLayer->getContentSize().height});
        auto innerSpr2 = static_cast<cocos2d::CCSprite*>(unlockButton2->getNormalImage());
        innerSpr2->setPosition({unlock2->m_firstLayer->getContentSize().width / 2.f, unlock2->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton3 = CCMenuItemSpriteExtra::create(
			unlock3,
			this,
			menu_selector(CompletedOnlineLevelPage::openUnlockInfo)
		);
        unlockButton3->setUserObject(unlockInfo3);
        unlockButton3->setContentSize({unlock3->m_firstLayer->getContentSize().width, unlock3->m_firstLayer->getContentSize().height});
        auto innerSpr3 = static_cast<cocos2d::CCSprite*>(unlockButton3->getNormalImage());
        innerSpr3->setPosition({unlock3->m_firstLayer->getContentSize().width / 2.f, unlock3->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton4 = CCMenuItemSpriteExtra::create(
			unlock4,
			this,
			menu_selector(CompletedOnlineLevelPage::openUnlockInfo)
		);
        unlockButton4->setUserObject(unlockInfo4);
        unlockButton4->setContentSize({unlock4->m_firstLayer->getContentSize().width, unlock4->m_firstLayer->getContentSize().height});
        auto innerSpr4 = static_cast<cocos2d::CCSprite*>(unlockButton4->getNormalImage());
        innerSpr4->setPosition({unlock4->m_firstLayer->getContentSize().width / 2.f, unlock4->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton5 = CCMenuItemSpriteExtra::create(
			unlock5,
			this,
			menu_selector(CompletedOnlineLevelPage::openUnlockInfo)
		);
        unlockButton5->setUserObject(unlockInfo5);

        /* Second Row */
        auto unlockButton6 = CCMenuItemSpriteExtra::create(
			unlock6,
			this,
			menu_selector(CompletedOnlineLevelPage::openUnlockInfo)
		);
        unlockButton6->setUserObject(unlockInfo6);
        unlockButton6->setContentSize({unlock6->m_firstLayer->getContentSize().width, unlock6->m_firstLayer->getContentSize().height});
        auto innerSpr6 = static_cast<cocos2d::CCSprite*>(unlockButton6->getNormalImage());
        innerSpr6->setPosition({unlock6->m_firstLayer->getContentSize().width / 2.f, unlock6->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton7 = CCMenuItemSpriteExtra::create(
			unlock7,
			this,
			menu_selector(CompletedOnlineLevelPage::openUnlockInfo)
		);
        unlockButton7->setUserObject(unlockInfo7);
        unlockButton7->setContentSize({unlock7->m_firstLayer->getContentSize().width, unlock7->m_firstLayer->getContentSize().height});
        auto innerSpr7 = static_cast<cocos2d::CCSprite*>(unlockButton7->getNormalImage());
        innerSpr7->setPosition({unlock7->m_firstLayer->getContentSize().width / 2.f, unlock7->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton8 = CCMenuItemSpriteExtra::create(
			unlock8,
			this,
			menu_selector(CompletedOnlineLevelPage::openUnlockInfo)
		);
        unlockButton8->setUserObject(unlockInfo8);
        unlockButton8->setContentSize({unlock8->m_firstLayer->getContentSize().width, unlock8->m_firstLayer->getContentSize().height});
        auto innerSpr8 = static_cast<cocos2d::CCSprite*>(unlockButton8->getNormalImage());
        innerSpr8->setPosition({unlock8->m_firstLayer->getContentSize().width / 2.f, unlock8->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton9 = CCMenuItemSpriteExtra::create(
			unlock9,
			this,
			menu_selector(CompletedOnlineLevelPage::openUnlockInfo)
		);
        unlockButton9->setUserObject(unlockInfo9);
        unlockButton9->setContentSize({unlock9->m_firstLayer->getContentSize().width, unlock9->m_firstLayer->getContentSize().height});
        auto innerSpr9 = static_cast<cocos2d::CCSprite*>(unlockButton9->getNormalImage());
        innerSpr9->setPosition({unlock9->m_firstLayer->getContentSize().width / 2.f, unlock9->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton10 = CCMenuItemSpriteExtra::create(
			unlock10,
			this,
			menu_selector(CompletedOnlineLevelPage::openUnlockInfo)
		);
        unlockButton10->setUserObject(unlockInfo10);
        unlockButton10->setContentSize({unlock10->m_firstLayer->getContentSize().width, unlock10->m_firstLayer->getContentSize().height});
        auto innerSpr10 = static_cast<cocos2d::CCSprite*>(unlockButton10->getNormalImage());
        innerSpr10->setPosition({unlock10->m_firstLayer->getContentSize().width / 2.f, unlock10->m_firstLayer->getContentSize().height / 2.f});

        /* First Row */
        unlockButton1->setPosition({-427, -10});
        unlockButton2->setPosition({-340.5f, -10});
        unlockButton3->setPosition({-252, -10});
        unlockButton4->setPosition({-163, -10});
        unlockButton5->setPosition({-73, -10});

        /* Second Row */
        unlockButton6->setPosition({-427, -75});
        unlockButton7->setPosition({-340.5f, -75});
        unlockButton8->setPosition({-252, -75});
        unlockButton9->setPosition({-163, -75});
        unlockButton10->setPosition({-73, -75});

        /* First Row */
        tierContainer->addChild(sliderBarSpr1);
        tierContainer->addChild(sliderOutlineSpr1);
        tierMenu->addChild(unlockButton1);
        tierContainer->addChild(unlockText1);
        tierContainer->addChild(sliderBarSpr2);
        tierContainer->addChild(sliderOutlineSpr2);
        tierMenu->addChild(unlockButton2);
        tierContainer->addChild(unlockText2);
        tierContainer->addChild(sliderBarSpr3);
        tierContainer->addChild(sliderOutlineSpr3);
        tierMenu->addChild(unlockButton3);
        tierContainer->addChild(unlockText3);
        tierContainer->addChild(sliderBarSpr4);
        tierContainer->addChild(sliderOutlineSpr4);
        tierMenu->addChild(unlockButton4);
        tierContainer->addChild(unlockText4);
        tierContainer->addChild(sliderBarSpr5);
        tierContainer->addChild(sliderOutlineSpr5);
        tierMenu->addChild(unlockButton5);
        tierContainer->addChild(unlockText5);

        /* Second Row */
        tierContainer->addChild(sliderBarSpr6);
        tierContainer->addChild(sliderOutlineSpr6);
        tierMenu->addChild(unlockButton6);
        tierContainer->addChild(unlockText6);
        tierContainer->addChild(sliderBarSpr7);
        tierContainer->addChild(sliderOutlineSpr7);
        tierMenu->addChild(unlockButton7);
        tierContainer->addChild(unlockText7);
        tierContainer->addChild(sliderBarSpr8);
        tierContainer->addChild(sliderOutlineSpr8);
        tierMenu->addChild(unlockButton8);
        tierContainer->addChild(unlockText8);
        tierContainer->addChild(sliderBarSpr9);
        tierContainer->addChild(sliderOutlineSpr9);
        tierMenu->addChild(unlockButton9);
        tierContainer->addChild(unlockText9);
        tierContainer->addChild(sliderBarSpr10);
        tierContainer->addChild(sliderOutlineSpr10);
        tierMenu->addChild(unlockButton10);
        tierContainer->addChild(unlockText10);

        tierContainer->addChild(tierMenu);

        /* End of Tier's Content */

        tierContainer->setPosition({pageWidth * 0.5f, 0});
        return tierContainer;
    }

    CCNode* createTier2(int completedOnline) {
        auto tierContainer = CCNode::create();
        tierContainer->setPosition({0, 0});
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        pageWidth = winSize.width * 0.75f;
        CCMenu* tierMenu = CCMenu::create();

        /* Tier's Content */

        /* Moving Progress Text */
        auto currentProgressText = CCLabelBMFont::create("", "bigFont-uhd.fnt");
        currentProgressText->setScale(0.35f);

        /* Completion Stars */
        auto tierCompletedStar1 = CCSprite::createWithSpriteFrameName("GJ_bigStar_001.png");
        auto tierCompletedStarGlow1 = CCSprite::createWithSpriteFrameName("GJ_bigStar_glow_001.png");
        tierCompletedStarGlow1->setAnchorPoint({0, 0});
        tierCompletedStarGlow1->setPosition({-11, -11});
        tierCompletedStarGlow1->setZOrder(-1);
        tierCompletedStar1->addChild(tierCompletedStarGlow1);

        auto tierCompletedStar2 = CCSprite::createWithSpriteFrameName("GJ_bigStar_001.png");
        auto tierCompletedStarGlow2 = CCSprite::createWithSpriteFrameName("GJ_bigStar_glow_001.png");
        tierCompletedStarGlow2->setAnchorPoint({0, 0});
        tierCompletedStarGlow2->setPosition({-11, -11});
        tierCompletedStarGlow2->setZOrder(-1);
        tierCompletedStar2->addChild(tierCompletedStarGlow2);

        /* First Row */
        auto sliderOutlineSpr1 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr1 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio1 = (float)(completedOnline - std::stoi(unlockData10->numberString)) / (float)(std::stoi(unlockData11->numberString) - std::stoi(unlockData10->numberString));
        float scale1 = ratio1 >= 0.98f ? sliderBarSpr1->getContentSize().width * 0.98f : sliderBarSpr1->getContentSize().width * ratio1;
        sliderBarSpr1->setTextureRect(CCRectMake(0, 0, scale1, sliderBarSpr1->getContentSize().height));

        auto unlockText1 = CCLabelBMFont::create(addCommas(unlockData11->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo1 = new UnlockInfo(unlockData11->unlockId, unlockData11->colorType);
        unlockInfo1->autorelease();
        auto unlock1 = ColorChannelSprite::create();
        auto lock1 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr2 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr2 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio2 = (float)(completedOnline - std::stoi(unlockData11->numberString)) / (float)(std::stoi(unlockData12->numberString) - std::stoi(unlockData11->numberString));
        float scale2 = ratio2 >= 0.98f ? sliderBarSpr2->getContentSize().width * 0.98f : sliderBarSpr2->getContentSize().width * ratio2;
        sliderBarSpr2->setTextureRect(CCRectMake(0, 0, scale2, sliderBarSpr2->getContentSize().height)); 

        auto unlockText2 = CCLabelBMFont::create(addCommas(unlockData12->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo2 = new UnlockInfo(unlockData12->unlockId, unlockData12->iconType);
        unlockInfo2->autorelease();
        auto unlock2 = SimplePlayer::create(1);
        auto lock2 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr3 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr3 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio3 = (float)(completedOnline - std::stoi(unlockData12->numberString)) / (float)(std::stoi(unlockData13->numberString) - std::stoi(unlockData12->numberString));
        float scale3 = ratio3 >= 0.98f ? sliderBarSpr3->getContentSize().width * 0.98f : sliderBarSpr3->getContentSize().width * ratio3;
        sliderBarSpr3->setTextureRect(CCRectMake(0, 0, scale3, sliderBarSpr3->getContentSize().height));  

        auto unlockText3 = CCLabelBMFont::create(addCommas(unlockData13->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo3 = new UnlockInfo(unlockData13->unlockId, unlockData13->iconType);
        unlockInfo3->autorelease();
        auto unlock3 = SimplePlayer::create(1);
        auto lock3 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr4 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr4 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio4 = (float)(completedOnline - std::stoi(unlockData13->numberString)) / (float)(std::stoi(unlockData14->numberString) - std::stoi(unlockData13->numberString));
        float scale4 = ratio4 >= 0.98f ? sliderBarSpr4->getContentSize().width * 0.98f : sliderBarSpr4->getContentSize().width * ratio4;
        sliderBarSpr4->setTextureRect(CCRectMake(0, 0, scale4, sliderBarSpr4->getContentSize().height));

        auto unlockText4 = CCLabelBMFont::create(addCommas(unlockData14->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo4 = new UnlockInfo(unlockData14->unlockId, unlockData14->iconType);
        unlockInfo4->autorelease();
        auto unlock4 = SimplePlayer::create(1);
        auto lock4 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        /* Set Progress Text */
        bool isInTier =  completedOnline >= std::stoi(unlockData10->numberString) && completedOnline < std::stoi(unlockData14->numberString);
        if (ratio1 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(completedOnline).c_str()));
            currentProgressText->setPosition({-99, 138});
            tierContainer->addChild(currentProgressText);
        } else if (ratio2 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(completedOnline).c_str()));
            currentProgressText->setPosition({-12.5f, 138});
            tierContainer->addChild(currentProgressText);
        } else if (ratio3 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(completedOnline).c_str()));
            currentProgressText->setPosition({77, 138});
            tierContainer->addChild(currentProgressText);
        } else if (ratio4 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(completedOnline).c_str()));
            currentProgressText->setPosition({-12.5f, 73});
            tierContainer->addChild(currentProgressText);
        }
        if (ratio4 >= 1.f) {
            tierCompletedStar1->setAnchorPoint({0, 0});
            tierCompletedStar2->setAnchorPoint({0, 0});
            tierCompletedStar1->setPosition({-72, 8});
            tierCompletedStar2->setPosition({77, 8});
            tierCompletedStar1->setScale(0.5f);
            tierCompletedStar2->setScale(0.5f);
            tierContainer->addChild(tierCompletedStar1);
            tierContainer->addChild(tierCompletedStar2);
        }

        /* Colour Init */
        auto p1Unlocked = ccc3(190, 190, 190);
        auto p2Unlocked = ccc3(245, 245, 245);
        auto p1Grey = ccc3(30, 30, 30);
        auto p2Grey = ccc3(80, 80, 80);

        /* First Row */
        togglePlayerColours ? sliderBarSpr1->setColor(gameManager->colorForIdx(gameManager->getPlayerColor())) : void();

        unlock1->setColor(gameManager->colorForIdx(unlockInfo1->iconId));
        if (ratio1 >= 1.f) {
            lock1->setVisible(false);
        }
        
        togglePlayerColours ? sliderBarSpr2->setColor(gameManager->colorForIdx(gameManager->getPlayerColor())) : void();

        unlock2->updatePlayerFrame(unlockInfo2->iconId, unlockInfo2->unlockType);
        if (ratio2 >= 1.f) {
            lock2->setVisible(false);
            if (togglePlayerColours) {
                unlock2->setColors(gameManager->colorForIdx(gameManager->getPlayerColor()), gameManager->colorForIdx(gameManager->getPlayerColor2()));
                if (gameManager->m_playerGlow) {
                    unlock2->setGlowOutline(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
                }
            } else {
                unlock2->setColors(p1Unlocked, p2Unlocked);
                unlock2->disableGlowOutline();
            }
        } else {
            unlock2->setColors(p1Grey, p2Grey);
            unlock2->disableGlowOutline();
        }

        togglePlayerColours ? sliderBarSpr3->setColor(gameManager->colorForIdx(gameManager->getPlayerColor())) : void();

        unlock3->updatePlayerFrame(unlockInfo3->iconId, unlockInfo3->unlockType);
        if (ratio3 >= 1.f) {
            lock3->setVisible(false);
            if (togglePlayerColours) {
                unlock3->setColors(gameManager->colorForIdx(gameManager->getPlayerColor()), gameManager->colorForIdx(gameManager->getPlayerColor2()));
                if (gameManager->m_playerGlow) {
                    unlock3->setGlowOutline(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
                }
            } else {
                unlock3->setColors(p1Unlocked, p2Unlocked);
                unlock3->disableGlowOutline();
            }
        } else {
            unlock3->setColors(p1Grey, p2Grey);
            unlock3->disableGlowOutline();
        }

        togglePlayerColours ? sliderBarSpr4->setColor(gameManager->colorForIdx(gameManager->getPlayerColor())) : void();

        unlock4->updatePlayerFrame(unlockInfo4->iconId, unlockInfo4->unlockType);
        if (ratio4 >= 1.f) {
            lock4->setVisible(false);
            if (togglePlayerColours) {
                unlock4->setColors(gameManager->colorForIdx(gameManager->getPlayerColor()), gameManager->colorForIdx(gameManager->getPlayerColor2()));
                if (gameManager->m_playerGlow) {
                    unlock4->setGlowOutline(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
                }
            } else {
                unlock4->setColors(p1Unlocked, p2Unlocked);
                unlock4->disableGlowOutline();
            }
        } else {
            unlock4->setColors(p1Grey, p2Grey);
            unlock4->disableGlowOutline();
        }

        /* First Row */
        sliderBarSpr1->setAnchorPoint({ 0, .5f }); sliderBarSpr1->setZOrder({-1}); sliderBarSpr1->setPosition({-115, 150});
        sliderOutlineSpr1->setAnchorPoint({ 0, .5f }); sliderOutlineSpr1->setScaleX({1.1f}); sliderOutlineSpr1->setPosition({-117, 150});      
        lock1->setPosition({17.75f, 18.25f}); lock1->setZOrder(1);
        unlockText1->setScale(.5f); unlockText1->setPosition({-55.5f, 120});
        sliderBarSpr2->setAnchorPoint({ 0, .5f }); sliderBarSpr2->setZOrder({-1}); sliderBarSpr2->setPosition({-28.5f, 150}); 
        sliderOutlineSpr2->setAnchorPoint({ 0, .5f }); sliderOutlineSpr2->setScaleX({1.1f}); sliderOutlineSpr2->setPosition({-30.5f, 150}); 
        lock2->setZOrder(1);
        unlockText2->setScale(.5f); unlockText2->setPosition({33, 120});
        sliderBarSpr3->setAnchorPoint({ 0, .5f }); sliderBarSpr3->setZOrder({-1}); sliderBarSpr3->setPosition({61, 150});
        sliderOutlineSpr3->setAnchorPoint({ 0, .5f }); sliderOutlineSpr3->setScaleX({1.1f}); sliderOutlineSpr3->setPosition({59, 150});
        lock3->setZOrder(1);
        unlockText3->setScale(.5f); unlockText3->setPosition({122, 120});
        sliderBarSpr4->setAnchorPoint({ 0, .5f }); sliderBarSpr4->setZOrder({-1}); sliderBarSpr4->setPosition({-28.5f, 85});
        sliderOutlineSpr4->setAnchorPoint({ 0, .5f }); sliderOutlineSpr4->setScaleX({1.1f}); sliderOutlineSpr4->setPosition({-30.5f, 85});
        lock4->setZOrder(1);
        unlockText4->setScale(.5f); unlockText4->setPosition({33, 55});

        /* First Row */
        unlock1->addChild(lock1);
        unlock2->addChild(lock2);
        unlock3->addChild(lock3);
        unlock4->addChild(lock4);

        /* First Row */
        auto unlockButton1 = CCMenuItemSpriteExtra::create(
			unlock1,
			this,
			menu_selector(CompletedOnlineLevelPage::openUnlockInfo)
		);
        unlockButton1->setUserObject(unlockInfo1);

        auto unlockButton2 = CCMenuItemSpriteExtra::create(
			unlock2,
			this,
			menu_selector(CompletedOnlineLevelPage::openUnlockInfo)
		);
        unlockButton2->setUserObject(unlockInfo2);
        unlockButton2->setContentSize({unlock2->m_firstLayer->getContentSize().width, unlock2->m_firstLayer->getContentSize().height});
        auto innerSpr2 = static_cast<cocos2d::CCSprite*>(unlockButton2->getNormalImage());
        innerSpr2->setPosition({unlock2->m_firstLayer->getContentSize().width / 2.f, unlock2->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton3 = CCMenuItemSpriteExtra::create(
			unlock3,
			this,
			menu_selector(CompletedOnlineLevelPage::openUnlockInfo)
		);
        unlockButton3->setUserObject(unlockInfo3);
        unlockButton3->setContentSize({unlock3->m_firstLayer->getContentSize().width, unlock3->m_firstLayer->getContentSize().height});
        auto innerSpr3 = static_cast<cocos2d::CCSprite*>(unlockButton3->getNormalImage());
        innerSpr3->setPosition({unlock3->m_firstLayer->getContentSize().width / 2.f, unlock3->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton4 = CCMenuItemSpriteExtra::create(
			unlock4,
			this,
			menu_selector(CompletedOnlineLevelPage::openUnlockInfo)
		);
        unlockButton4->setUserObject(unlockInfo4);
        unlockButton4->setContentSize({unlock4->m_firstLayer->getContentSize().width, unlock4->m_firstLayer->getContentSize().height});
        auto innerSpr4 = static_cast<cocos2d::CCSprite*>(unlockButton4->getNormalImage());
        innerSpr4->setPosition({unlock4->m_firstLayer->getContentSize().width / 2.f, unlock4->m_firstLayer->getContentSize().height / 2.f});

        /* First Row */
        unlockButton1->setPosition({-340.5f, -10});
        unlockButton2->setPosition({-252, -10});
        unlockButton3->setPosition({-163, -10});
        unlockButton4->setPosition({-252, -75});

        /* First Row */
        tierContainer->addChild(sliderBarSpr1);
        tierContainer->addChild(sliderOutlineSpr1);
        tierMenu->addChild(unlockButton1);
        tierContainer->addChild(unlockText1);
        tierContainer->addChild(sliderBarSpr2);
        tierContainer->addChild(sliderOutlineSpr2);
        tierMenu->addChild(unlockButton2);
        tierContainer->addChild(unlockText2);
        tierContainer->addChild(sliderBarSpr3);
        tierContainer->addChild(sliderOutlineSpr3);
        tierMenu->addChild(unlockButton3);
        tierContainer->addChild(unlockText3);
        tierContainer->addChild(sliderBarSpr4);
        tierContainer->addChild(sliderOutlineSpr4);
        tierMenu->addChild(unlockButton4);
        tierContainer->addChild(unlockText4);

        tierContainer->addChild(tierMenu);

        /* End of Tier's Content */

        tierContainer->setPosition({pageWidth * 0.5f, 0});
        return tierContainer;
    }
};