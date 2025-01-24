#pragma once

#include <Geode/Geode.hpp>
#include <Geode/utils/cocos.hpp>

#include "../modify/ItemInfoPopup.cpp"

using namespace geode::prelude;

class SecretCoinPage : public CCObject {
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

    GameManager* gameManager;

    FLAlertLayer* popupLayer;

    CCNode* pageContainer;
    CCMenu* buttonMenu;

    float pageWidth;

    CCArray* tierPages;
    int currentPage;
    
    CCNode* tier1Page;
    CCNode* tier2Page;
    CCNode* tier3Page;

    CCMenuItemSpriteExtra* tier1Button = nullptr;
    CCMenuItemSpriteExtra* tier2Button = nullptr;
    CCMenuItemSpriteExtra* tier3Button = nullptr;

    CCSprite* page1Selected = nullptr;
    CCSprite* page2Selected = nullptr;
    CCSprite* page3Selected = nullptr;
    CCSprite* page1Deselected = nullptr;
    CCSprite* page2Deselected = nullptr;
    CCSprite* page3Deselected = nullptr;

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
    UnlockData* unlockData15 = nullptr;
    UnlockData* unlockData16 = nullptr;
    UnlockData* unlockData17 = nullptr;
    UnlockData* unlockData18 = nullptr;
    UnlockData* unlockData19 = nullptr;
    UnlockData* unlockData20 = nullptr;
    UnlockData* unlockData21 = nullptr;
    UnlockData* unlockData22 = nullptr;
    UnlockData* unlockData23 = nullptr;
    UnlockData* unlockData24 = nullptr;
    UnlockData* unlockData25 = nullptr;
    UnlockData* unlockData26 = nullptr;
    UnlockData* unlockData27 = nullptr;
    UnlockData* unlockData28 = nullptr;

public:
    SecretCoinPage(FLAlertLayer* parentPopup) {

        gameManager = GameManager::sharedState();
        popupLayer = parentPopup;
        tierPages = CCArray::create();
        tierPages->retain();
        buttonMenu = CCMenu::create();
        page1Selected = CCSprite::create("GJ_square03-uhd.png");
        page2Selected = CCSprite::create("GJ_square03-uhd.png");
        page2Selected->setVisible(false);
        page3Selected = CCSprite::create("GJ_square03-uhd.png");
        page3Selected->setVisible(false);
        page1Deselected = CCSprite::create("GJ_square01-uhd.png");
        page1Deselected->setVisible(false);
        page2Deselected = CCSprite::create("GJ_square01-uhd.png");
        page3Deselected = CCSprite::create("GJ_square01-uhd.png");
        togglePlayerColours = Mod::get()->getSettingValue<bool>("toggle-player-colors");

        unlockData0 = new UnlockData("0", 1, IconType::Cube); unlockData0->autorelease();

        unlockData1 = new UnlockData("5", 31, IconType::Cube); unlockData1->autorelease();
        unlockData2 = new UnlockData("10", 2, IconType::Ball); unlockData2->autorelease();
        unlockData3 = new UnlockData("15", 16, "secondary"); unlockData3->autorelease();
        unlockData4 = new UnlockData("20", 3, IconType::Ufo); unlockData4->autorelease();
        unlockData5 = new UnlockData("25", 32, IconType::Cube); unlockData5->autorelease();
        unlockData6 = new UnlockData("30", 15, "main"); unlockData6->autorelease();
        unlockData7 = new UnlockData("35", 3, IconType::Ball); unlockData7->autorelease();
        unlockData8 = new UnlockData("40", 34, IconType::Cube); unlockData8->autorelease();
        unlockData9 = new UnlockData("45", 4, IconType::Ufo); unlockData9->autorelease();
        unlockData10 = new UnlockData("50", 4, IconType::Ball); unlockData10->autorelease();

        unlockData11 = new UnlockData("55", 14, IconType::Ship); unlockData11->autorelease();
        unlockData12 = new UnlockData("60", 38, IconType::Cube); unlockData12->autorelease();
        unlockData13 = new UnlockData("65", 6, IconType::Ufo); unlockData13->autorelease();
        unlockData14 = new UnlockData("70", 6, IconType::Ball); unlockData14->autorelease();
        unlockData15 = new UnlockData("75", 12, IconType::Ship); unlockData15->autorelease();
        unlockData16 = new UnlockData("80", 7, IconType::Ufo); unlockData16->autorelease();
        unlockData17 = new UnlockData("85", 8, IconType::Ufo); unlockData17->autorelease();
        unlockData18 = new UnlockData("90", 16, IconType::Ship); unlockData18->autorelease();
        unlockData19 = new UnlockData("95", 43, IconType::Cube); unlockData19->autorelease();
        unlockData20 = new UnlockData("100", 9, IconType::Ufo); unlockData20->autorelease();

        unlockData21 = new UnlockData("105", 14, IconType::Ball); unlockData21->autorelease();
        unlockData22 = new UnlockData("110", 56, IconType::Cube); unlockData22->autorelease();
        unlockData23 = new UnlockData("115", 24, IconType::Ship); unlockData23->autorelease();
        unlockData24 = new UnlockData("120", 18, IconType::Ufo); unlockData24->autorelease();
        unlockData25 = new UnlockData("130", 88, IconType::Cube); unlockData25->autorelease();
        unlockData26 = new UnlockData("140", 36, IconType::Wave); unlockData26->autorelease();
        unlockData27 = new UnlockData("150", 34, IconType::Swing); unlockData27->autorelease();
        unlockData28 = new UnlockData("160", 88, IconType::Ship); unlockData28->autorelease();
    }

    CCNode* createSecretCoinPage(int secretCoins) {

        pageContainer = CCNode::create();
        pageContainer->setPosition({0, 0});
        buttonMenu->setPosition({147, -200});
        pageContainer->addChild(buttonMenu);

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        pageWidth = winSize.width * 0.75f;

        currentPage = 0;

        auto labelSpr = CCSprite::create("secret_coins_spr.png"_spr);
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

        tier1Page = createTier1(secretCoins);
        tier1Page->retain();
        pageContainer->addChild(tier1Page);
        tierPages->addObject(tier1Page);
        tier1Page->setVisible(true);

        tier2Page = createTier2(secretCoins);
        tier2Page->retain();
        pageContainer->addChild(tier2Page);
        tierPages->addObject(tier2Page);
        tier2Page->setVisible(false);

        tier3Page = createTier3(secretCoins);
        tier3Page->retain();
        pageContainer->addChild(tier3Page);
        tierPages->addObject(tier3Page);
        tier3Page->setVisible(false);

        createNavigationButtons();

        pageContainer->setPosition({pageWidth * 0.5f, 0});

        return pageContainer;
    }

    ~SecretCoinPage() {
        if (tierPages) {
            tierPages->release();
        }
    }

private:
    void createNavigationButtons() {

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        float popupHeight = winSize.height * 0.8f;

        CCSprite* tier1ButtonSpr = CCSprite::createWithSpriteFrameName("rankIcon_top1000_001.png");
        CCSprite* tier2ButtonSpr = CCSprite::createWithSpriteFrameName("rankIcon_top500_001.png");
        CCSprite* tier3ButtonSpr = CCSprite::createWithSpriteFrameName("rankIcon_top200_001.png");

        tier1ButtonSpr->setScale(0.94f);
        tier2ButtonSpr->setScale(0.9f);
        tier3ButtonSpr->setScale(0.82f);

        auto tier1Button = CCMenuItemSpriteExtra::create(
            tier1ButtonSpr,
            this,
            menu_selector(SecretCoinPage::onTierButton)
        );
        tier1Button->setTag(0);
        tier1Button->setAnchorPoint({.5f, .5f});
        tier1Button->setPosition({53.5f, 220});

        page1Deselected->setAnchorPoint({.5f, 0});
        page1Deselected->setPosition({53.5f, 208});
        page1Deselected->setScale(.3f);
        page1Deselected->setZOrder(-2);

        page1Selected->setAnchorPoint({.5f, 0});
        page1Selected->setPosition({53.5f, 208});
        page1Selected->setScale(.3f);
        page1Selected->setZOrder(-2);

        buttonMenu->addChild(tier1Button);
        buttonMenu->addChild(page1Deselected);
        buttonMenu->addChild(page1Selected);

        tier2Button = CCMenuItemSpriteExtra::create(
            tier2ButtonSpr,
            this,
            menu_selector(SecretCoinPage::onTierButton)
        );
        tier2Button->setTag(1);
        tier2Button->setAnchorPoint({.5f, .5f});
        tier2Button->setPosition({80.5f, 220});

        page2Deselected->setAnchorPoint({.5f, 0});
        page2Deselected->setPosition({80.5f, 208});
        page2Deselected->setScale(.3f);
        page2Deselected->setZOrder(-2);

        page2Selected->setAnchorPoint({.5f, 0});
        page2Selected->setPosition({80.5f, 208});
        page2Selected->setScale(.3f);
        page2Selected->setZOrder(-2);

        buttonMenu->addChild(tier2Button);
        buttonMenu->addChild(page2Deselected);
        buttonMenu->addChild(page2Selected);

        tier3Button = CCMenuItemSpriteExtra::create(
            tier3ButtonSpr,
            this,
            menu_selector(SecretCoinPage::onTierButton)
        );
        tier3Button->setTag(2);
        tier3Button->setAnchorPoint({.5f, .5f});
        tier3Button->setPosition({107.5f, 220});

        page3Deselected->setAnchorPoint({.5f, 0});
        page3Deselected->setPosition({107.5f, 208});
        page3Deselected->setScale(.3f);
        page3Deselected->setZOrder(-2);

        page3Selected->setAnchorPoint({.5f, 0});
        page3Selected->setPosition({107.5f, 208});
        page3Selected->setScale(.3f);
        page3Selected->setZOrder(-2);

        buttonMenu->addChild(tier3Button);
        buttonMenu->addChild(page3Deselected);
        buttonMenu->addChild(page3Selected);
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
            page3Selected->setVisible(false);
            page1Deselected->setVisible(false);
            page2Deselected->setVisible(true);
            page3Deselected->setVisible(true);
        } else if (tag == 1) {

            page1Selected->setVisible(false);
            page2Selected->setVisible(true);
            page3Selected->setVisible(false);
            page1Deselected->setVisible(true);
            page2Deselected->setVisible(false);
            page3Deselected->setVisible(true);
        } else if (tag == 2) {

            page1Selected->setVisible(false);
            page2Selected->setVisible(false);
            page3Selected->setVisible(true);
            page1Deselected->setVisible(true);
            page2Deselected->setVisible(true);
            page3Deselected->setVisible(false);
        } else {

            page1Selected->setVisible(false);
            page2Selected->setVisible(false);
            page3Selected->setVisible(false);
            page1Deselected->setVisible(true);
            page2Deselected->setVisible(true);
            page3Deselected->setVisible(true);
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

    CCNode* createTier1(int secretCoins) {
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
        float ratio1 = (float)(secretCoins - std::stoi(unlockData0->numberString)) / (float)(std::stoi(unlockData1->numberString) - std::stoi(unlockData0->numberString));
        float scale1 = ratio1 >= 0.98f ? sliderBarSpr1->getContentSize().width * 0.98f : sliderBarSpr1->getContentSize().width * ratio1;
        sliderBarSpr1->setTextureRect(CCRectMake(0, 0, scale1, sliderBarSpr1->getContentSize().height));

        auto unlockText1 = CCLabelBMFont::create(addCommas(unlockData1->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo1 = new UnlockInfo(unlockData1->unlockId, unlockData1->iconType);
        unlockInfo1->autorelease();
        auto unlock1 = SimplePlayer::create(1);
        auto lock1 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr2 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr2 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio2 = (float)(secretCoins - std::stoi(unlockData1->numberString)) / (float)(std::stoi(unlockData2->numberString) - std::stoi(unlockData1->numberString));
        float scale2 = ratio2 >= 0.98f ? sliderBarSpr2->getContentSize().width * 0.98f : sliderBarSpr2->getContentSize().width * ratio2;
        sliderBarSpr2->setTextureRect(CCRectMake(0, 0, scale2, sliderBarSpr2->getContentSize().height)); 

        auto unlockText2 = CCLabelBMFont::create(addCommas(unlockData2->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo2 = new UnlockInfo(unlockData2->unlockId, unlockData2->iconType);
        unlockInfo2->autorelease();
        auto unlock2 = SimplePlayer::create(1);
        auto lock2 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr3 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr3 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio3 = (float)(secretCoins - std::stoi(unlockData2->numberString)) / (float)(std::stoi(unlockData3->numberString) - std::stoi(unlockData2->numberString));
        float scale3 = ratio3 >= 0.98f ? sliderBarSpr3->getContentSize().width * 0.98f : sliderBarSpr3->getContentSize().width * ratio3;
        sliderBarSpr3->setTextureRect(CCRectMake(0, 0, scale3, sliderBarSpr3->getContentSize().height));  

        auto unlockText3 = CCLabelBMFont::create(addCommas(unlockData3->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo3 = new UnlockInfo(unlockData3->unlockId, unlockData3->colorType);
        unlockInfo3->autorelease();
        auto unlock3 = ColorChannelSprite::create();
        auto lock3 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr4 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr4 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio4 = (float)(secretCoins - std::stoi(unlockData3->numberString)) / (float)(std::stoi(unlockData4->numberString) - std::stoi(unlockData3->numberString));
        float scale4 = ratio4 >= 0.98f ? sliderBarSpr4->getContentSize().width * 0.98f : sliderBarSpr4->getContentSize().width * ratio4;
        sliderBarSpr4->setTextureRect(CCRectMake(0, 0, scale4, sliderBarSpr4->getContentSize().height));

        auto unlockText4 = CCLabelBMFont::create(addCommas(unlockData4->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo4 = new UnlockInfo(unlockData4->unlockId, unlockData4->iconType);
        unlockInfo4->autorelease();
        auto unlock4 = SimplePlayer::create(1);
        auto lock4 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr5 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr5 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio5 = (float)(secretCoins - std::stoi(unlockData4->numberString)) / (float)(std::stoi(unlockData5->numberString) - std::stoi(unlockData4->numberString));
        float scale5 = ratio5 >= 0.98f ? sliderBarSpr5->getContentSize().width * 0.98f : sliderBarSpr5->getContentSize().width * ratio5;
        sliderBarSpr5->setTextureRect(CCRectMake(0, 0, scale5, sliderBarSpr5->getContentSize().height));

        auto unlockText5 = CCLabelBMFont::create(addCommas(unlockData5->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo5 = new UnlockInfo(unlockData5->unlockId, unlockData5->iconType);
        unlockInfo5->autorelease();
        auto unlock5 = SimplePlayer::create(1);
        auto lock5 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        /* second row */
        auto sliderOutlineSpr6 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr6 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio6 = (float)(secretCoins - std::stoi(unlockData5->numberString)) / (float)(std::stoi(unlockData6->numberString) - std::stoi(unlockData5->numberString));
        float scale6 = ratio6 >= 0.98f ? sliderBarSpr6->getContentSize().width * 0.98f : sliderBarSpr6->getContentSize().width * ratio6;
        sliderBarSpr6->setTextureRect(CCRectMake(0, 0, scale6, sliderBarSpr6->getContentSize().height));

        auto unlockText6 = CCLabelBMFont::create(addCommas(unlockData6->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo6 = new UnlockInfo(unlockData6->unlockId, unlockData6->colorType);
        unlockInfo6->autorelease();
        auto unlock6 = ColorChannelSprite::create();
        auto lock6 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr7 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr7 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio7 = (float)(secretCoins - std::stoi(unlockData6->numberString)) / (float)(std::stoi(unlockData7->numberString) - std::stoi(unlockData6->numberString));
        float scale7 = ratio7 >= 0.98f ? sliderBarSpr7->getContentSize().width * 0.98f : sliderBarSpr7->getContentSize().width * ratio7;
        sliderBarSpr7->setTextureRect(CCRectMake(0, 0, scale7, sliderBarSpr7->getContentSize().height));

        auto unlockText7 = CCLabelBMFont::create(addCommas(unlockData7->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo7 = new UnlockInfo(unlockData7->unlockId, unlockData7->iconType);
        unlockInfo7->autorelease();
        auto unlock7 = SimplePlayer::create(1);
        auto lock7 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr8 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr8 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio8 = (float)(secretCoins - std::stoi(unlockData7->numberString)) / (float)(std::stoi(unlockData8->numberString) - std::stoi(unlockData7->numberString));
        float scale8 = ratio8 >= 0.98f ? sliderBarSpr8->getContentSize().width * 0.98f : sliderBarSpr8->getContentSize().width * ratio8;
        sliderBarSpr8->setTextureRect(CCRectMake(0, 0, scale8, sliderBarSpr8->getContentSize().height));

        auto unlockText8 = CCLabelBMFont::create(addCommas(unlockData8->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo8 = new UnlockInfo(unlockData8->unlockId, unlockData8->iconType);
        unlockInfo8->autorelease();
        auto unlock8 = SimplePlayer::create(1);
        auto lock8 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr9 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr9 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio9 = (float)(secretCoins - std::stoi(unlockData8->numberString)) / (float)(std::stoi(unlockData9->numberString) - std::stoi(unlockData8->numberString));
        float scale9 = ratio9 >= 0.98f ? sliderBarSpr9->getContentSize().width * 0.98f : sliderBarSpr9->getContentSize().width * ratio9;
        sliderBarSpr9->setTextureRect(CCRectMake(0, 0, scale9, sliderBarSpr9->getContentSize().height));

        auto unlockText9 = CCLabelBMFont::create(addCommas(unlockData9->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo9 = new UnlockInfo(unlockData9->unlockId, unlockData9->iconType);
        unlockInfo9->autorelease();
        auto unlock9 = SimplePlayer::create(1);
        auto lock9 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr10 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr10 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio10 = (float)(secretCoins - std::stoi(unlockData9->numberString)) / (float)(std::stoi(unlockData9->numberString) - std::stoi(unlockData8->numberString));
        float scale10 = ratio10 >= 0.98f ? sliderBarSpr10->getContentSize().width * 0.98f : sliderBarSpr10->getContentSize().width * ratio10;
        sliderBarSpr10->setTextureRect(CCRectMake(0, 0, scale10, sliderBarSpr10->getContentSize().height));

        auto unlockText10 = CCLabelBMFont::create(addCommas(unlockData10->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo10 = new UnlockInfo(unlockData10->unlockId, unlockData10->iconType);
        unlockInfo10->autorelease();
        auto unlock10 = SimplePlayer::create(1);
        auto lock10 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        /* Set Progress Text */
        bool isInTier =  secretCoins >= std::stoi(unlockData0->numberString) && secretCoins < std::stoi(unlockData10->numberString);
        if (ratio1 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(secretCoins).c_str()));
            currentProgressText->setPosition({-185, 138});
            tierContainer->addChild(currentProgressText);
        } else if (ratio2 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(secretCoins).c_str()));
            currentProgressText->setPosition({-99, 138});
            tierContainer->addChild(currentProgressText);
        } else if (ratio3 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(secretCoins).c_str()));
            currentProgressText->setPosition({-12.5f, 138});
            tierContainer->addChild(currentProgressText);
        } else if (ratio4 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(secretCoins).c_str()));
            currentProgressText->setPosition({77, 138});
            tierContainer->addChild(currentProgressText);
        } else if (ratio5 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(secretCoins).c_str()));
            currentProgressText->setPosition({167.5f, 138});
            tierContainer->addChild(currentProgressText);
        } else if (ratio6 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(secretCoins).c_str()));
            currentProgressText->setPosition({-185, 73});
            tierContainer->addChild(currentProgressText);
        } else if (ratio7 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(secretCoins).c_str()));
            currentProgressText->setPosition({-99, 73});
            tierContainer->addChild(currentProgressText);
        } else if (ratio8 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(secretCoins).c_str()));
            currentProgressText->setPosition({-12.5f, 73});
            tierContainer->addChild(currentProgressText);
        } else if (ratio9 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(secretCoins).c_str()));
            currentProgressText->setPosition({77, 73});
            tierContainer->addChild(currentProgressText);
        } else if (ratio10 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(secretCoins).c_str()));
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

        unlock1->updatePlayerFrame(unlockInfo1->iconId, unlockInfo1->unlockType);
        if (ratio1 >= 1.f) {        //unlocked
            lock1->setVisible(false);
            
            if (togglePlayerColours) {
                unlock1->setColors(gameManager->colorForIdx(gameManager->getPlayerColor()), gameManager->colorForIdx(gameManager->getPlayerColor2()));
                if (gameManager->m_playerGlow) {
                    unlock1->setGlowOutline(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
                }
            } else {
                unlock1->setColors(p1Unlocked, p2Unlocked);
                unlock1->disableGlowOutline();
            }
        } else {                        //locked
            unlock1->setColors(p1Grey, p2Grey);
            unlock1->disableGlowOutline();
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

        unlock3->setColor(gameManager->colorForIdx(unlockInfo3->iconId));
        if (ratio3 >= 1.f) {
            lock3->setVisible(false);
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

        unlock5->updatePlayerFrame(unlockInfo5->iconId, unlockInfo5->unlockType);
        if (ratio5 >= 1.f) {
            lock5->setVisible(false);
            if (togglePlayerColours) {
                unlock5->setColors(gameManager->colorForIdx(gameManager->getPlayerColor()), gameManager->colorForIdx(gameManager->getPlayerColor2()));
                if (gameManager->m_playerGlow) {
                    unlock5->setGlowOutline(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
                }
            } else {
                unlock5->setColors(p1Unlocked, p2Unlocked);
                unlock5->disableGlowOutline();
            }
        } else {
            unlock5->setColors(p1Grey, p2Grey);
            unlock5->disableGlowOutline();
        }

        /* Second Row */
        togglePlayerColours ? sliderBarSpr6->setColor(gameManager->colorForIdx(gameManager->getPlayerColor())) : void();

        unlock6->setColor(gameManager->colorForIdx(unlockInfo6->iconId));
        if (ratio6 >= 1.f) {
            lock6->setVisible(false);
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
        lock1->setZOrder(1);
        unlockText1->setScale(.5f); unlockText1->setPosition({-142.5f, 120});
        sliderBarSpr2->setAnchorPoint({ 0, .5f }); sliderBarSpr2->setZOrder({-1}); sliderBarSpr2->setPosition({-115, 150}); 
        sliderOutlineSpr2->setAnchorPoint({ 0, .5f }); sliderOutlineSpr2->setScaleX({1.1f}); sliderOutlineSpr2->setPosition({-117, 150}); 
        lock2->setZOrder(1);
        unlockText2->setScale(.5f); unlockText2->setPosition({-55.5f, 120});
        sliderBarSpr3->setAnchorPoint({ 0, .5f }); sliderBarSpr3->setZOrder({-1}); sliderBarSpr3->setPosition({-28.5f, 150});
        sliderOutlineSpr3->setAnchorPoint({ 0, .5f }); sliderOutlineSpr3->setScaleX({1.1f}); sliderOutlineSpr3->setPosition({-30.5f, 150});
        lock3->setPosition({17.75f, 18.25f}); lock3->setZOrder(1);
        unlockText3->setScale(.5f); unlockText3->setPosition({33, 120});
        sliderBarSpr4->setAnchorPoint({ 0, .5f }); sliderBarSpr4->setZOrder({-1}); sliderBarSpr4->setPosition({61, 150});
        sliderOutlineSpr4->setAnchorPoint({ 0, .5f }); sliderOutlineSpr4->setScaleX({1.1f}); sliderOutlineSpr4->setPosition({59, 150});
        lock4->setZOrder(1);
        unlockText4->setScale(.5f); unlockText4->setPosition({122, 120});
        sliderBarSpr5->setAnchorPoint({ 0, .5f }); sliderBarSpr5->setZOrder({-1}); sliderBarSpr5->setPosition({151, 150});
        sliderOutlineSpr5->setAnchorPoint({ 0, .5f }); sliderOutlineSpr5->setScaleX({1.1f}); sliderOutlineSpr5->setPosition({149, 150});
        lock5->setZOrder(1);
        unlockText5->setScale(.5f); unlockText5->setPosition({211.5f, 120});

        /* Second Row */
        sliderBarSpr6->setAnchorPoint({ 0, .5f }); sliderBarSpr6->setZOrder({-1}); sliderBarSpr6->setPosition({-201, 85});
        sliderOutlineSpr6->setAnchorPoint({ 0, .5f }); sliderOutlineSpr6->setScaleX({1.1f}); sliderOutlineSpr6->setPosition({-203, 85});
        lock6->setPosition({17.75f, 18.25f}); lock6->setZOrder(1);
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
			menu_selector(SecretCoinPage::openUnlockInfo)
		);
        unlockButton1->setUserObject(unlockInfo1);
        unlockButton1->setContentSize({unlock1->m_firstLayer->getContentSize().width, unlock1->m_firstLayer->getContentSize().height});
        auto innerSpr1 = static_cast<cocos2d::CCSprite*>(unlockButton1->getNormalImage());
        innerSpr1->setPosition({unlock1->m_firstLayer->getContentSize().width / 2.f, unlock1->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton2 = CCMenuItemSpriteExtra::create(
			unlock2,
			this,
			menu_selector(SecretCoinPage::openUnlockInfo)
		);
        unlockButton2->setUserObject(unlockInfo2);
        unlockButton2->setContentSize({unlock2->m_firstLayer->getContentSize().width, unlock2->m_firstLayer->getContentSize().height});
        auto innerSpr2 = static_cast<cocos2d::CCSprite*>(unlockButton2->getNormalImage());
        innerSpr2->setPosition({unlock2->m_firstLayer->getContentSize().width / 2.f, unlock2->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton3 = CCMenuItemSpriteExtra::create(
			unlock3,
			this,
			menu_selector(SecretCoinPage::openUnlockInfo)
		);
        unlockButton3->setUserObject(unlockInfo3);

        auto unlockButton4 = CCMenuItemSpriteExtra::create(
			unlock4,
			this,
			menu_selector(SecretCoinPage::openUnlockInfo)
		);
        unlockButton4->setUserObject(unlockInfo4);
        unlockButton4->setContentSize({unlock4->m_firstLayer->getContentSize().width, unlock4->m_firstLayer->getContentSize().height});
        auto innerSpr4 = static_cast<cocos2d::CCSprite*>(unlockButton4->getNormalImage());
        innerSpr4->setPosition({unlock4->m_firstLayer->getContentSize().width / 2.f, unlock4->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton5 = CCMenuItemSpriteExtra::create(
			unlock5,
			this,
			menu_selector(SecretCoinPage::openUnlockInfo)
		);
        unlockButton5->setUserObject(unlockInfo5);
        unlockButton5->setContentSize({unlock5->m_firstLayer->getContentSize().width, unlock5->m_firstLayer->getContentSize().height});
        auto innerSpr5 = static_cast<cocos2d::CCSprite*>(unlockButton5->getNormalImage());
        innerSpr5->setPosition({unlock5->m_firstLayer->getContentSize().width / 2.f, unlock5->m_firstLayer->getContentSize().height / 2.f});

        /* Second Row */
        auto unlockButton6 = CCMenuItemSpriteExtra::create(
			unlock6,
			this,
			menu_selector(SecretCoinPage::openUnlockInfo)
		);
        unlockButton6->setUserObject(unlockInfo6);

        auto unlockButton7 = CCMenuItemSpriteExtra::create(
			unlock7,
			this,
			menu_selector(SecretCoinPage::openUnlockInfo)
		);
        unlockButton7->setUserObject(unlockInfo7);
        unlockButton7->setContentSize({unlock7->m_firstLayer->getContentSize().width, unlock7->m_firstLayer->getContentSize().height});
        auto innerSpr7 = static_cast<cocos2d::CCSprite*>(unlockButton7->getNormalImage());
        innerSpr7->setPosition({unlock7->m_firstLayer->getContentSize().width / 2.f, unlock7->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton8 = CCMenuItemSpriteExtra::create(
			unlock8,
			this,
			menu_selector(SecretCoinPage::openUnlockInfo)
		);
        unlockButton8->setUserObject(unlockInfo8);
        unlockButton8->setContentSize({unlock8->m_firstLayer->getContentSize().width, unlock8->m_firstLayer->getContentSize().height});
        auto innerSpr8 = static_cast<cocos2d::CCSprite*>(unlockButton8->getNormalImage());
        innerSpr8->setPosition({unlock8->m_firstLayer->getContentSize().width / 2.f, unlock8->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton9 = CCMenuItemSpriteExtra::create(
			unlock9,
			this,
			menu_selector(SecretCoinPage::openUnlockInfo)
		);
        unlockButton9->setUserObject(unlockInfo9);
        unlockButton9->setContentSize({unlock9->m_firstLayer->getContentSize().width, unlock9->m_firstLayer->getContentSize().height});
        auto innerSpr9 = static_cast<cocos2d::CCSprite*>(unlockButton9->getNormalImage());
        innerSpr9->setPosition({unlock9->m_firstLayer->getContentSize().width / 2.f, unlock9->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton10 = CCMenuItemSpriteExtra::create(
			unlock10,
			this,
			menu_selector(SecretCoinPage::openUnlockInfo)
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

    CCNode* createTier2(int secretCoins) {
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
        float ratio1 = (float)(secretCoins - std::stoi(unlockData10->numberString)) / (float)(std::stoi(unlockData11->numberString) - std::stoi(unlockData10->numberString));
        float scale1 = ratio1 >= 0.98f ? sliderBarSpr1->getContentSize().width * 0.98f : sliderBarSpr1->getContentSize().width * ratio1;
        sliderBarSpr1->setTextureRect(CCRectMake(0, 0, scale1, sliderBarSpr1->getContentSize().height));

        auto unlockText1 = CCLabelBMFont::create(addCommas(unlockData11->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo1 = new UnlockInfo(unlockData11->unlockId, unlockData11->iconType);
        unlockInfo1->autorelease();
        auto unlock1 = SimplePlayer::create(1);
        auto lock1 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr2 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr2 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio2 = (float)(secretCoins - std::stoi(unlockData11->numberString)) / (float)(std::stoi(unlockData12->numberString) - std::stoi(unlockData11->numberString));
        float scale2 = ratio2 >= 0.98f ? sliderBarSpr2->getContentSize().width * 0.98f : sliderBarSpr2->getContentSize().width * ratio2;
        sliderBarSpr2->setTextureRect(CCRectMake(0, 0, scale2, sliderBarSpr2->getContentSize().height)); 

        auto unlockText2 = CCLabelBMFont::create(addCommas(unlockData12->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo2 = new UnlockInfo(unlockData12->unlockId, unlockData12->iconType);
        unlockInfo2->autorelease();
        auto unlock2 = SimplePlayer::create(1);
        auto lock2 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr3 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr3 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio3 = (float)(secretCoins - std::stoi(unlockData12->numberString)) / (float)(std::stoi(unlockData13->numberString) - std::stoi(unlockData12->numberString));
        float scale3 = ratio3 >= 0.98f ? sliderBarSpr3->getContentSize().width * 0.98f : sliderBarSpr3->getContentSize().width * ratio3;
        sliderBarSpr3->setTextureRect(CCRectMake(0, 0, scale3, sliderBarSpr3->getContentSize().height));  

        auto unlockText3 = CCLabelBMFont::create(addCommas(unlockData13->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo3 = new UnlockInfo(unlockData13->unlockId, unlockData13->iconType);
        unlockInfo3->autorelease();
        auto unlock3 = SimplePlayer::create(1);
        auto lock3 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr4 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr4 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio4 = (float)(secretCoins - std::stoi(unlockData13->numberString)) / (float)(std::stoi(unlockData14->numberString) - std::stoi(unlockData13->numberString));
        float scale4 = ratio4 >= 0.98f ? sliderBarSpr4->getContentSize().width * 0.98f : sliderBarSpr4->getContentSize().width * ratio4;
        sliderBarSpr4->setTextureRect(CCRectMake(0, 0, scale4, sliderBarSpr4->getContentSize().height));

        auto unlockText4 = CCLabelBMFont::create(addCommas(unlockData14->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo4 = new UnlockInfo(unlockData14->unlockId, unlockData14->iconType);
        unlockInfo4->autorelease();
        auto unlock4 = SimplePlayer::create(1);
        auto lock4 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr5 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr5 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio5 = (float)(secretCoins - std::stoi(unlockData14->numberString)) / (float)(std::stoi(unlockData15->numberString) - std::stoi(unlockData14->numberString));
        float scale5 = ratio5 >= 0.98f ? sliderBarSpr5->getContentSize().width * 0.98f : sliderBarSpr5->getContentSize().width * ratio5;
        sliderBarSpr5->setTextureRect(CCRectMake(0, 0, scale5, sliderBarSpr5->getContentSize().height));

        auto unlockText5 = CCLabelBMFont::create(addCommas(unlockData15->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo5 = new UnlockInfo(unlockData15->unlockId, unlockData15->iconType);
        unlockInfo5->autorelease();
        auto unlock5 = SimplePlayer::create(1);
        auto lock5 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        /* second row */
        auto sliderOutlineSpr6 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr6 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio6 = (float)(secretCoins - std::stoi(unlockData15->numberString)) / (float)(std::stoi(unlockData16->numberString) - std::stoi(unlockData15->numberString));
        float scale6 = ratio6 >= 0.98f ? sliderBarSpr6->getContentSize().width * 0.98f : sliderBarSpr6->getContentSize().width * ratio6;
        sliderBarSpr6->setTextureRect(CCRectMake(0, 0, scale6, sliderBarSpr6->getContentSize().height));

        auto unlockText6 = CCLabelBMFont::create(addCommas(unlockData16->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo6 = new UnlockInfo(unlockData16->unlockId, unlockData16->iconType);
        unlockInfo6->autorelease();
        auto unlock6 = SimplePlayer::create(1);
        auto lock6 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr7 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr7 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio7 = (float)(secretCoins - std::stoi(unlockData16->numberString)) / (float)(std::stoi(unlockData17->numberString) - std::stoi(unlockData16->numberString));
        float scale7 = ratio7 >= 0.98f ? sliderBarSpr7->getContentSize().width * 0.98f : sliderBarSpr7->getContentSize().width * ratio7;
        sliderBarSpr7->setTextureRect(CCRectMake(0, 0, scale7, sliderBarSpr7->getContentSize().height));

        auto unlockText7 = CCLabelBMFont::create(addCommas(unlockData17->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo7 = new UnlockInfo(unlockData17->unlockId, unlockData17->iconType);
        unlockInfo7->autorelease();
        auto unlock7 = SimplePlayer::create(1);
        auto lock7 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr8 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr8 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio8 = (float)(secretCoins - std::stoi(unlockData17->numberString)) / (float)(std::stoi(unlockData18->numberString) - std::stoi(unlockData17->numberString));
        float scale8 = ratio8 >= 0.98f ? sliderBarSpr8->getContentSize().width * 0.98f : sliderBarSpr8->getContentSize().width * ratio8;
        sliderBarSpr8->setTextureRect(CCRectMake(0, 0, scale8, sliderBarSpr8->getContentSize().height));

        auto unlockText8 = CCLabelBMFont::create(addCommas(unlockData18->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo8 = new UnlockInfo(unlockData18->unlockId, unlockData18->iconType);
        unlockInfo8->autorelease();
        auto unlock8 = SimplePlayer::create(1);
        auto lock8 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr9 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr9 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio9 = (float)(secretCoins - std::stoi(unlockData18->numberString)) / (float)(std::stoi(unlockData19->numberString) - std::stoi(unlockData18->numberString));
        float scale9 = ratio9 >= 0.98f ? sliderBarSpr9->getContentSize().width * 0.98f : sliderBarSpr9->getContentSize().width * ratio9;
        sliderBarSpr9->setTextureRect(CCRectMake(0, 0, scale9, sliderBarSpr9->getContentSize().height));

        auto unlockText9 = CCLabelBMFont::create(addCommas(unlockData19->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo9 = new UnlockInfo(unlockData19->unlockId, unlockData19->iconType);
        unlockInfo9->autorelease();
        auto unlock9 = SimplePlayer::create(1);
        auto lock9 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr10 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr10 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio10 = (float)(secretCoins - std::stoi(unlockData19->numberString)) / (float)(std::stoi(unlockData20->numberString) - std::stoi(unlockData19->numberString));
        float scale10 = ratio10 >= 0.98f ? sliderBarSpr10->getContentSize().width * 0.98f : sliderBarSpr10->getContentSize().width * ratio10;
        sliderBarSpr10->setTextureRect(CCRectMake(0, 0, scale10, sliderBarSpr10->getContentSize().height));

        auto unlockText10 = CCLabelBMFont::create(addCommas(unlockData20->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo10 = new UnlockInfo(unlockData20->unlockId, unlockData20->iconType);
        unlockInfo10->autorelease();
        auto unlock10 = SimplePlayer::create(1);
        auto lock10 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        /* Set Progress Text */
        bool isInTier =  secretCoins >= std::stoi(unlockData10->numberString) && secretCoins < std::stoi(unlockData20->numberString);
        if (ratio1 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(secretCoins).c_str()));
            currentProgressText->setPosition({-185, 138});
            tierContainer->addChild(currentProgressText);
        } else if (ratio2 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(secretCoins).c_str()));
            currentProgressText->setPosition({-99, 138});
            tierContainer->addChild(currentProgressText);
        } else if (ratio3 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(secretCoins).c_str()));
            currentProgressText->setPosition({-12.5f, 138});
            tierContainer->addChild(currentProgressText);
        } else if (ratio4 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(secretCoins).c_str()));
            currentProgressText->setPosition({77, 138});
            tierContainer->addChild(currentProgressText);
        } else if (ratio5 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(secretCoins).c_str()));
            currentProgressText->setPosition({167.5f, 138});
            tierContainer->addChild(currentProgressText);
        } else if (ratio6 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(secretCoins).c_str()));
            currentProgressText->setPosition({-185, 73});
            tierContainer->addChild(currentProgressText);
        } else if (ratio7 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(secretCoins).c_str()));
            currentProgressText->setPosition({-99, 73});
            tierContainer->addChild(currentProgressText);
        } else if (ratio8 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(secretCoins).c_str()));
            currentProgressText->setPosition({-12.5f, 73});
            tierContainer->addChild(currentProgressText);
        } else if (ratio9 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(secretCoins).c_str()));
            currentProgressText->setPosition({77, 73});
            tierContainer->addChild(currentProgressText);
        } else if (ratio10 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(secretCoins).c_str()));
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

        unlock1->updatePlayerFrame(unlockInfo1->iconId, unlockInfo1->unlockType);
        if (ratio1 >= 1.f) {        //unlocked
            lock1->setVisible(false);
            
            if (togglePlayerColours) {
                unlock1->setColors(gameManager->colorForIdx(gameManager->getPlayerColor()), gameManager->colorForIdx(gameManager->getPlayerColor2()));
                if (gameManager->m_playerGlow) {
                    unlock1->setGlowOutline(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
                }
            } else {
                unlock1->setColors(p1Unlocked, p2Unlocked);
                unlock1->disableGlowOutline();
            }
        } else {                        //locked
            unlock1->setColors(p1Grey, p2Grey);
            unlock1->disableGlowOutline();
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

        unlock5->updatePlayerFrame(unlockInfo5->iconId, unlockInfo5->unlockType);
        if (ratio5 >= 1.f) {
            lock5->setVisible(false);
            if (togglePlayerColours) {
                unlock5->setColors(gameManager->colorForIdx(gameManager->getPlayerColor()), gameManager->colorForIdx(gameManager->getPlayerColor2()));
                if (gameManager->m_playerGlow) {
                    unlock5->setGlowOutline(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
                }
            } else {
                unlock5->setColors(p1Unlocked, p2Unlocked);
                unlock5->disableGlowOutline();
            }
        } else {
            unlock5->setColors(p1Grey, p2Grey);
            unlock5->disableGlowOutline();
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
        lock1->setZOrder(1);
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
        lock5->setZOrder(1);
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
			menu_selector(SecretCoinPage::openUnlockInfo)
		);
        unlockButton1->setUserObject(unlockInfo1);
        unlockButton1->setContentSize({unlock1->m_firstLayer->getContentSize().width, unlock1->m_firstLayer->getContentSize().height});
        auto innerSpr1 = static_cast<cocos2d::CCSprite*>(unlockButton1->getNormalImage());
        innerSpr1->setPosition({unlock1->m_firstLayer->getContentSize().width / 2.f, unlock1->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton2 = CCMenuItemSpriteExtra::create(
			unlock2,
			this,
			menu_selector(SecretCoinPage::openUnlockInfo)
		);
        unlockButton2->setUserObject(unlockInfo2);
        unlockButton2->setContentSize({unlock2->m_firstLayer->getContentSize().width, unlock2->m_firstLayer->getContentSize().height});
        auto innerSpr2 = static_cast<cocos2d::CCSprite*>(unlockButton2->getNormalImage());
        innerSpr2->setPosition({unlock2->m_firstLayer->getContentSize().width / 2.f, unlock2->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton3 = CCMenuItemSpriteExtra::create(
			unlock3,
			this,
			menu_selector(SecretCoinPage::openUnlockInfo)
		);
        unlockButton3->setUserObject(unlockInfo3);
        unlockButton3->setContentSize({unlock3->m_firstLayer->getContentSize().width, unlock3->m_firstLayer->getContentSize().height});
        auto innerSpr3 = static_cast<cocos2d::CCSprite*>(unlockButton3->getNormalImage());
        innerSpr3->setPosition({unlock3->m_firstLayer->getContentSize().width / 2.f, unlock3->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton4 = CCMenuItemSpriteExtra::create(
			unlock4,
			this,
			menu_selector(SecretCoinPage::openUnlockInfo)
		);
        unlockButton4->setUserObject(unlockInfo4);
        unlockButton4->setContentSize({unlock4->m_firstLayer->getContentSize().width, unlock4->m_firstLayer->getContentSize().height});
        auto innerSpr4 = static_cast<cocos2d::CCSprite*>(unlockButton4->getNormalImage());
        innerSpr4->setPosition({unlock4->m_firstLayer->getContentSize().width / 2.f, unlock4->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton5 = CCMenuItemSpriteExtra::create(
			unlock5,
			this,
			menu_selector(SecretCoinPage::openUnlockInfo)
		);
        unlockButton5->setUserObject(unlockInfo5);
        unlockButton5->setContentSize({unlock5->m_firstLayer->getContentSize().width, unlock5->m_firstLayer->getContentSize().height});
        auto innerSpr5 = static_cast<cocos2d::CCSprite*>(unlockButton5->getNormalImage());
        innerSpr5->setPosition({unlock5->m_firstLayer->getContentSize().width / 2.f, unlock5->m_firstLayer->getContentSize().height / 2.f});

        /* Second Row */
        auto unlockButton6 = CCMenuItemSpriteExtra::create(
			unlock6,
			this,
			menu_selector(SecretCoinPage::openUnlockInfo)
		);
        unlockButton6->setUserObject(unlockInfo6);
        unlockButton6->setContentSize({unlock6->m_firstLayer->getContentSize().width, unlock6->m_firstLayer->getContentSize().height});
        auto innerSpr6 = static_cast<cocos2d::CCSprite*>(unlockButton6->getNormalImage());
        innerSpr6->setPosition({unlock6->m_firstLayer->getContentSize().width / 2.f, unlock6->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton7 = CCMenuItemSpriteExtra::create(
			unlock7,
			this,
			menu_selector(SecretCoinPage::openUnlockInfo)
		);
        unlockButton7->setUserObject(unlockInfo7);
        unlockButton7->setContentSize({unlock7->m_firstLayer->getContentSize().width, unlock7->m_firstLayer->getContentSize().height});
        auto innerSpr7 = static_cast<cocos2d::CCSprite*>(unlockButton7->getNormalImage());
        innerSpr7->setPosition({unlock7->m_firstLayer->getContentSize().width / 2.f, unlock7->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton8 = CCMenuItemSpriteExtra::create(
			unlock8,
			this,
			menu_selector(SecretCoinPage::openUnlockInfo)
		);
        unlockButton8->setUserObject(unlockInfo8);
        unlockButton8->setContentSize({unlock8->m_firstLayer->getContentSize().width, unlock8->m_firstLayer->getContentSize().height});
        auto innerSpr8 = static_cast<cocos2d::CCSprite*>(unlockButton8->getNormalImage());
        innerSpr8->setPosition({unlock8->m_firstLayer->getContentSize().width / 2.f, unlock8->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton9 = CCMenuItemSpriteExtra::create(
			unlock9,
			this,
			menu_selector(SecretCoinPage::openUnlockInfo)
		);
        unlockButton9->setUserObject(unlockInfo9);
        unlockButton9->setContentSize({unlock9->m_firstLayer->getContentSize().width, unlock9->m_firstLayer->getContentSize().height});
        auto innerSpr9 = static_cast<cocos2d::CCSprite*>(unlockButton9->getNormalImage());
        innerSpr9->setPosition({unlock9->m_firstLayer->getContentSize().width / 2.f, unlock9->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton10 = CCMenuItemSpriteExtra::create(
			unlock10,
			this,
			menu_selector(SecretCoinPage::openUnlockInfo)
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

    CCNode* createTier3(int secretCoins) {
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
        float ratio1 = (float)(secretCoins - std::stoi(unlockData20->numberString)) / (float)(std::stoi(unlockData21->numberString) - std::stoi(unlockData20->numberString));
        float scale1 = ratio1 >= 0.98f ? sliderBarSpr1->getContentSize().width * 0.98f : sliderBarSpr1->getContentSize().width * ratio1;
        sliderBarSpr1->setTextureRect(CCRectMake(0, 0, scale1, sliderBarSpr1->getContentSize().height));

        auto unlockText1 = CCLabelBMFont::create(addCommas(unlockData21->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo1 = new UnlockInfo(unlockData21->unlockId, unlockData21->iconType);
        unlockInfo1->autorelease();
        auto unlock1 = SimplePlayer::create(1);
        auto lock1 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr2 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr2 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio2 = (float)(secretCoins - std::stoi(unlockData21->numberString)) / (float)(std::stoi(unlockData22->numberString) - std::stoi(unlockData21->numberString));
        float scale2 = ratio2 >= 0.98f ? sliderBarSpr2->getContentSize().width * 0.98f : sliderBarSpr2->getContentSize().width * ratio2;
        sliderBarSpr2->setTextureRect(CCRectMake(0, 0, scale2, sliderBarSpr2->getContentSize().height)); 

        auto unlockText2 = CCLabelBMFont::create(addCommas(unlockData22->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo2 = new UnlockInfo(unlockData22->unlockId, unlockData22->iconType);
        unlockInfo2->autorelease();
        auto unlock2 = SimplePlayer::create(1);
        auto lock2 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr3 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr3 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio3 = (float)(secretCoins - std::stoi(unlockData22->numberString)) / (float)(std::stoi(unlockData23->numberString) - std::stoi(unlockData22->numberString));
        float scale3 = ratio3 >= 0.98f ? sliderBarSpr3->getContentSize().width * 0.98f : sliderBarSpr3->getContentSize().width * ratio3;
        sliderBarSpr3->setTextureRect(CCRectMake(0, 0, scale3, sliderBarSpr3->getContentSize().height));  

        auto unlockText3 = CCLabelBMFont::create(addCommas(unlockData23->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo3 = new UnlockInfo(unlockData23->unlockId, unlockData23->iconType);
        unlockInfo3->autorelease();
        auto unlock3 = SimplePlayer::create(1);
        auto lock3 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr4 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr4 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio4 = (float)(secretCoins - std::stoi(unlockData23->numberString)) / (float)(std::stoi(unlockData24->numberString) - std::stoi(unlockData23->numberString));
        float scale4 = ratio4 >= 0.98f ? sliderBarSpr4->getContentSize().width * 0.98f : sliderBarSpr4->getContentSize().width * ratio4;
        sliderBarSpr4->setTextureRect(CCRectMake(0, 0, scale4, sliderBarSpr4->getContentSize().height));

        auto unlockText4 = CCLabelBMFont::create(addCommas(unlockData24->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo4 = new UnlockInfo(unlockData24->unlockId, unlockData24->iconType);
        unlockInfo4->autorelease();
        auto unlock4 = SimplePlayer::create(1);
        auto lock4 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr5 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr5 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio5 = (float)(secretCoins - std::stoi(unlockData24->numberString)) / (float)(std::stoi(unlockData25->numberString) - std::stoi(unlockData24->numberString));
        float scale5 = ratio5 >= 0.98f ? sliderBarSpr5->getContentSize().width * 0.98f : sliderBarSpr5->getContentSize().width * ratio5;
        sliderBarSpr5->setTextureRect(CCRectMake(0, 0, scale5, sliderBarSpr5->getContentSize().height));

        auto unlockText5 = CCLabelBMFont::create(addCommas(unlockData25->numberString.c_str()), "bigFont-uhd.fnt");
        auto unlockInfo5 = new UnlockInfo(unlockData25->unlockId, unlockData25->iconType);
        unlockInfo5->autorelease();
        auto unlock5 = SimplePlayer::create(1);
        auto lock5 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        /* second row */
        auto sliderOutlineSpr6 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr6 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio6 = (float)(secretCoins - std::stoi(unlockData25->numberString)) / (float)(std::stoi(unlockData26->numberString) - std::stoi(unlockData25->numberString));
        float scale6 = ratio6 >= 0.98f ? sliderBarSpr6->getContentSize().width * 0.98f : sliderBarSpr6->getContentSize().width * ratio6;
        sliderBarSpr6->setTextureRect(CCRectMake(0, 0, scale6, sliderBarSpr6->getContentSize().height));

        auto unlockText6 = CCLabelBMFont::create(unlockData26->numberString.c_str(), "bigFont-uhd.fnt");
        auto unlockInfo6 = new UnlockInfo(unlockData26->unlockId, unlockData26->iconType);
        unlockInfo6->autorelease();
        auto unlock6 = SimplePlayer::create(1);
        auto lock6 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr7 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr7 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio7 = (float)(secretCoins - std::stoi(unlockData26->numberString)) / (float)(std::stoi(unlockData27->numberString) - std::stoi(unlockData26->numberString));
        float scale7 = ratio7 >= 0.98f ? sliderBarSpr7->getContentSize().width * 0.98f : sliderBarSpr7->getContentSize().width * ratio7;
        sliderBarSpr7->setTextureRect(CCRectMake(0, 0, scale7, sliderBarSpr7->getContentSize().height));

        auto unlockText7 = CCLabelBMFont::create(unlockData27->numberString.c_str(), "bigFont-uhd.fnt");
        auto unlockInfo7 = new UnlockInfo(unlockData27->unlockId, unlockData27->iconType);
        unlockInfo7->autorelease();
        auto unlock7 = SimplePlayer::create(1);
        auto lock7 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr8 = CCSprite::create("Progress_Outline.png"_spr);
        auto sliderBarSpr8 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio8 = (float)(secretCoins - std::stoi(unlockData27->numberString)) / (float)(std::stoi(unlockData28->numberString) - std::stoi(unlockData27->numberString));
        float scale8 = ratio8 >= 0.98f ? sliderBarSpr8->getContentSize().width * 0.98f : sliderBarSpr8->getContentSize().width * ratio8;
        sliderBarSpr8->setTextureRect(CCRectMake(0, 0, scale8, sliderBarSpr8->getContentSize().height));

        auto unlockText8 = CCLabelBMFont::create(unlockData28->numberString.c_str(), "bigFont-uhd.fnt");
        auto unlockInfo8 = new UnlockInfo(unlockData28->unlockId, unlockData28->iconType);
        unlockInfo8->autorelease();
        auto unlock8 = SimplePlayer::create(1);
        auto lock8 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        /* Set Progress Text */
        bool isInTier = secretCoins >= std::stoi(unlockData20->numberString) && secretCoins < std::stoi(unlockData28->numberString);
        if (ratio1 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(secretCoins).c_str()));
            currentProgressText->setPosition({-185, 138});
            tierContainer->addChild(currentProgressText);
        } else if (ratio2 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(secretCoins).c_str()));
            currentProgressText->setPosition({-99, 138});
            tierContainer->addChild(currentProgressText);
        } else if (ratio3 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(secretCoins).c_str()));
            currentProgressText->setPosition({-12.5f, 138});
            tierContainer->addChild(currentProgressText);
        } else if (ratio4 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(secretCoins).c_str()));
            currentProgressText->setPosition({77, 138});
            tierContainer->addChild(currentProgressText);
        } else if (ratio5 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(secretCoins).c_str()));
            currentProgressText->setPosition({167.5f, 138});
            tierContainer->addChild(currentProgressText);
        } else if (ratio6 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(secretCoins).c_str()));
            currentProgressText->setPosition({-99, 73});
            tierContainer->addChild(currentProgressText);
        } else if (ratio7 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(secretCoins).c_str()));
            currentProgressText->setPosition({-12.5f, 73});
            tierContainer->addChild(currentProgressText);
        } else if (ratio8 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(secretCoins).c_str()));
            currentProgressText->setPosition({77, 73});
            tierContainer->addChild(currentProgressText);
        } 
        if (ratio8 >= 1.f) {
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

        unlock1->updatePlayerFrame(unlockInfo1->iconId, unlockInfo1->unlockType);
        if (ratio1 >= 1.f) {
            lock1->setVisible(false);
            if (togglePlayerColours) {
                unlock1->setColors(gameManager->colorForIdx(gameManager->getPlayerColor()), gameManager->colorForIdx(gameManager->getPlayerColor2()));
                if (gameManager->m_playerGlow) {
                    unlock1->setGlowOutline(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
                }
            } else {
                unlock1->setColors(p1Unlocked, p2Unlocked);
                unlock1->disableGlowOutline();
            }
        } else {
            unlock1->setColors(p1Grey, p2Grey);
            unlock1->disableGlowOutline();
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

        unlock5->updatePlayerFrame(unlockInfo5->iconId, unlockInfo5->unlockType);
        if (ratio5 >= 1.f) {
            lock5->setVisible(false);
            if (togglePlayerColours) {
                unlock5->setColors(gameManager->colorForIdx(gameManager->getPlayerColor()), gameManager->colorForIdx(gameManager->getPlayerColor2()));
                if (gameManager->m_playerGlow) {
                    unlock5->setGlowOutline(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
                }
            } else {
                unlock5->setColors(p1Unlocked, p2Unlocked);
                unlock5->disableGlowOutline();
            }
        } else {
            unlock5->setColors(p1Grey, p2Grey);
            unlock5->disableGlowOutline();
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

        /* First Row */
        sliderBarSpr1->setAnchorPoint({ 0, .5f }); sliderBarSpr1->setZOrder({-1}); sliderBarSpr1->setPosition({-201, 150});
        sliderOutlineSpr1->setAnchorPoint({ 0, .5f }); sliderOutlineSpr1->setScaleX({1.1f}); sliderOutlineSpr1->setPosition({-203, 150});      
        lock1->setZOrder(1);
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
        lock5->setZOrder(1);
        unlockText5->setScale(.5f); unlockText5->setPosition({211.5f, 120});

        /* Second Row */
        sliderBarSpr6->setAnchorPoint({ 0, .5f }); sliderBarSpr6->setZOrder({-1}); sliderBarSpr6->setPosition({-115, 85});
        sliderOutlineSpr6->setAnchorPoint({ 0, .5f }); sliderOutlineSpr6->setScaleX({1.1f}); sliderOutlineSpr6->setPosition({-117, 85});
        lock6->setZOrder(1);
        unlockText6->setScale(.5f); unlockText6->setPosition({-55.5f, 55});
        sliderBarSpr7->setAnchorPoint({ 0, .5f }); sliderBarSpr7->setZOrder({-1}); sliderBarSpr7->setPosition({-28.5f, 85});
        sliderOutlineSpr7->setAnchorPoint({ 0, .5f }); sliderOutlineSpr7->setScaleX({1.1f}); sliderOutlineSpr7->setPosition({-30.5f, 85});
        lock7->setZOrder(1);
        unlockText7->setScale(.5f); unlockText7->setPosition({33, 55});
        sliderBarSpr8->setAnchorPoint({ 0, .5f }); sliderBarSpr8->setZOrder({-1}); sliderBarSpr8->setPosition({61, 85});
        sliderOutlineSpr8->setAnchorPoint({ 0, .5f }); sliderOutlineSpr8->setScaleX({1.1f}); sliderOutlineSpr8->setPosition({59, 85});
        lock8->setZOrder(1);
        unlockText8->setScale(.5f); unlockText8->setPosition({122, 55});

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

        /* First Row */
        auto unlockButton1 = CCMenuItemSpriteExtra::create(
			unlock1,
			this,
			menu_selector(SecretCoinPage::openUnlockInfo)
		);
        unlockButton1->setUserObject(unlockInfo1);
        unlockButton1->setContentSize({unlock1->m_firstLayer->getContentSize().width, unlock1->m_firstLayer->getContentSize().height});
        auto innerSpr1 = static_cast<cocos2d::CCSprite*>(unlockButton1->getNormalImage());
        innerSpr1->setPosition({unlock1->m_firstLayer->getContentSize().width / 2.f, unlock1->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton2 = CCMenuItemSpriteExtra::create(
			unlock2,
			this,
			menu_selector(SecretCoinPage::openUnlockInfo)
		);
        unlockButton2->setUserObject(unlockInfo2);
        unlockButton2->setContentSize({unlock2->m_firstLayer->getContentSize().width, unlock2->m_firstLayer->getContentSize().height});
        auto innerSpr2 = static_cast<cocos2d::CCSprite*>(unlockButton2->getNormalImage());
        innerSpr2->setPosition({unlock2->m_firstLayer->getContentSize().width / 2.f, unlock2->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton3 = CCMenuItemSpriteExtra::create(
			unlock3,
			this,
			menu_selector(SecretCoinPage::openUnlockInfo)
		);
        unlockButton3->setUserObject(unlockInfo3);
        unlockButton3->setContentSize({unlock3->m_firstLayer->getContentSize().width, unlock3->m_firstLayer->getContentSize().height});
        auto innerSpr3 = static_cast<cocos2d::CCSprite*>(unlockButton3->getNormalImage());
        innerSpr3->setPosition({unlock3->m_firstLayer->getContentSize().width / 2.f, unlock3->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton4 = CCMenuItemSpriteExtra::create(
			unlock4,
			this,
			menu_selector(SecretCoinPage::openUnlockInfo)
		);
        unlockButton4->setUserObject(unlockInfo4);
        unlockButton4->setContentSize({unlock4->m_firstLayer->getContentSize().width, unlock4->m_firstLayer->getContentSize().height});
        auto innerSpr4 = static_cast<cocos2d::CCSprite*>(unlockButton4->getNormalImage());
        innerSpr4->setPosition({unlock4->m_firstLayer->getContentSize().width / 2.f, unlock4->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton5 = CCMenuItemSpriteExtra::create(
			unlock5,
			this,
			menu_selector(SecretCoinPage::openUnlockInfo)
		);
        unlockButton5->setUserObject(unlockInfo5);
        unlockButton5->setContentSize({unlock5->m_firstLayer->getContentSize().width, unlock5->m_firstLayer->getContentSize().height});
        auto innerSpr5 = static_cast<cocos2d::CCSprite*>(unlockButton5->getNormalImage());
        innerSpr5->setPosition({unlock5->m_firstLayer->getContentSize().width / 2.f, unlock5->m_firstLayer->getContentSize().height / 2.f});

        /* Second Row */
        auto unlockButton6 = CCMenuItemSpriteExtra::create(
			unlock6,
			this,
			menu_selector(SecretCoinPage::openUnlockInfo)
		);
        unlockButton6->setUserObject(unlockInfo6);
        unlockButton6->setContentSize({unlock6->m_firstLayer->getContentSize().width, unlock6->m_firstLayer->getContentSize().height});
        auto innerSpr6 = static_cast<cocos2d::CCSprite*>(unlockButton6->getNormalImage());
        innerSpr6->setPosition({unlock6->m_firstLayer->getContentSize().width / 2.f, unlock6->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton7 = CCMenuItemSpriteExtra::create(
			unlock7,
			this,
			menu_selector(SecretCoinPage::openUnlockInfo)
		);
        unlockButton7->setUserObject(unlockInfo7);
        unlockButton7->setContentSize({unlock7->m_firstLayer->getContentSize().width, unlock7->m_firstLayer->getContentSize().height});
        auto innerSpr7 = static_cast<cocos2d::CCSprite*>(unlockButton7->getNormalImage());
        innerSpr7->setPosition({unlock7->m_firstLayer->getContentSize().width / 2.f, unlock7->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton8 = CCMenuItemSpriteExtra::create(
			unlock8,
			this,
			menu_selector(SecretCoinPage::openUnlockInfo)
		);
        unlockButton8->setUserObject(unlockInfo8);
        unlockButton8->setContentSize({unlock8->m_firstLayer->getContentSize().width, unlock8->m_firstLayer->getContentSize().height});
        auto innerSpr8 = static_cast<cocos2d::CCSprite*>(unlockButton8->getNormalImage());
        innerSpr8->setPosition({unlock8->m_firstLayer->getContentSize().width / 2.f, unlock8->m_firstLayer->getContentSize().height / 2.f});

        /* First Row */
        unlockButton1->setPosition({-427, -10});
        unlockButton2->setPosition({-340.5f, -10});
        unlockButton3->setPosition({-252, -10});
        unlockButton4->setPosition({-163, -10});
        unlockButton5->setPosition({-73, -10});

        /* Second Row */
        unlockButton6->setPosition({-340.5f, -75});
        unlockButton7->setPosition({-252, -75});
        unlockButton8->setPosition({-163, -75});

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

        tierContainer->addChild(currentProgressText);
        tierContainer->addChild(tierMenu);

        /* End of Tier's Content */

        tierContainer->setPosition({pageWidth * 0.5f, 0});
        return tierContainer;
    }
};