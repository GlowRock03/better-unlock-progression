#pragma once

#include <Geode/Geode.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/web.hpp>
#include <Geode/loader/Event.hpp>

#include "../modify/ItemInfoPopup.cpp"

using namespace geode::prelude;

class RatedLevelPage : public CCObject {
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

    CCMenuItemSpriteExtra* tier1Button = nullptr;

    CCSprite* page1Selected = nullptr;
    CCSprite* page1Deselected = nullptr;

    bool togglePlayerColours;

    UnlockData* unlockData0 = nullptr;
    UnlockData* unlockData1 = nullptr;

    CCSprite* sliderBarSpr1;

    SimplePlayer* unlock1;

    CCSprite* lock1;

    CCLabelBMFont* currentProgressText;

    CCNode* tierContainer;

    UnlockInfo* unlockInfo1;

    bool starsAdd;

    EventListener<web::WebTask> m_listener;
    int accountId;

public:
    RatedLevelPage(FLAlertLayer* parentPopup) {

        gameManager = GameManager::sharedState();
        popupLayer = parentPopup;
        tierPages = CCArray::create();
        tierPages->retain();
        buttonMenu = CCMenu::create();
        page1Selected = CCSprite::create("GJ_square03-uhd.png");
        page1Deselected = CCSprite::create("GJ_square01-uhd.png");
        page1Deselected->setVisible(false);
        togglePlayerColours = Mod::get()->getSettingValue<bool>("toggle-player-colors");

        unlockData0 = new UnlockData("0", 1, IconType::Cube);
        
        unlockData1 = new UnlockData("1", 16, IconType::Ufo);

        starsAdd = false;
        accountId = GJAccountManager::sharedState()->m_accountID;
    }

    CCNode* createRatedLevelPage() {

        int ratedLevels = Mod::get()->getSavedValue<int>(fmt::format("creator-points-{}", accountId));

        pageContainer = CCNode::create();
        pageContainer->setPosition({0, 0});
        buttonMenu->setPosition({147, -200});
        pageContainer->addChild(buttonMenu);

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        pageWidth = winSize.width * 0.75f;

        currentPage = 0;

        auto labelSpr = CCSprite::create("creator_points_spr.png"_spr);
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

        auto labelTopSpr = CCSprite::create("creator_points_top_spr.png"_spr);
        labelTopSpr->setPosition({228.25f, 175});
        labelTopSpr->setScale(0.5f);
        pageContainer->addChild(labelTopSpr);

        tier1Page = createTier1(ratedLevels);
        tier1Page->retain();
        pageContainer->addChild(tier1Page);
        tierPages->addObject(tier1Page);
        tier1Page->setVisible(true);

        createNavigationButtons();

        createRefreshButton();

        pageContainer->setPosition({pageWidth * 0.5f, 0});

        return pageContainer;
    }

    ~RatedLevelPage() {
        if (tierPages) {
            tierPages->release();
        }
    }

private:
    void createNavigationButtons() {

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        float popupHeight = winSize.height * 0.8f;

        CCSprite* tier1ButtonSpr = CCSprite::createWithSpriteFrameName("rankIcon_top200_001.png");
        tier1ButtonSpr->setScale(0.82f);

        auto tier1Button = CCMenuItemSpriteExtra::create(
            tier1ButtonSpr,
            this,
            menu_selector(RatedLevelPage::onTierButton)
        );
        tier1Button->setTag(0);
        tier1Button->setAnchorPoint({.5f, .5f});
        tier1Button->setPosition({80.5f, 220});

        page1Deselected->setAnchorPoint({.5f, 0});
        page1Deselected->setPosition({80.5f, 208});
        page1Deselected->setScale(.3f);
        page1Deselected->setZOrder(-2);

        page1Selected->setAnchorPoint({.5f, 0});
        page1Selected->setPosition({80.5f, 208});
        page1Selected->setScale(.3f);
        page1Selected->setZOrder(-2);

        buttonMenu->addChild(tier1Button);
        buttonMenu->addChild(page1Deselected);
        buttonMenu->addChild(page1Selected);
    }

    void onTierButton(CCObject* sender) {

        auto button = static_cast<CCMenuItemSpriteExtra*>(sender);
        int tag = button->getTag();
        currentPage = tag;
        updatePageVisibility(tag);
    }

    void createRefreshButton() {

        CCSprite* refreshSpr = CCSprite::createWithSpriteFrameName("GJ_replayBtn_001.png");
        refreshSpr->setScale(.75f);

        CCSprite* infoBtnSPr = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
        infoBtnSPr->setScale(.7f);

        auto refreshButton = CCMenuItemSpriteExtra::create(
            refreshSpr,
            this,
            menu_selector(RatedLevelPage::refreshMaxLikes)
        );
        refreshButton->setAnchorPoint({.5f, .5f});
        refreshButton->setPosition({270, 245});

        buttonMenu->addChild(refreshButton);
    }

    void refreshMaxLikes(CCObject* sender) {

        makeWebRequest();
        makeInfoPopup();
    }

    void makeInfoPopup() {

        FLAlertLayer::create(
            "Refresh Complete",
            "Your 'Creator Points' statistic has been fetched via <cl>web requests</c>. <cr>DO NOT SPAM THIS BUTTON!</c> That will result in an <cr>API Rate Limit</c>.",
            "Ok"
        )->show(); 
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
            page1Deselected->setVisible(false);
        } else if (tag == 1) {

            page1Selected->setVisible(false);
            page1Deselected->setVisible(true);
        } else if (tag == 2) {

            page1Selected->setVisible(false);
            page1Deselected->setVisible(true);
        } else {

            page1Selected->setVisible(false);
            page1Deselected->setVisible(true);
        }
    }

    void makeWebRequest() {

        m_listener.bind([this](web::WebTask::Event* e) {

            if (web::WebResponse* value = e->getValue()) {
                auto str = value->string().unwrap();        //I totally check this value before unwrapping :)
                log::info("Response: {}", str);

                int creatorPoints = this->findCreatorPoints(str);
                log::info("Extracted Creator Points: {}", creatorPoints);

                Mod::get()->setSavedValue<int>(fmt::format("creator-points-{}", accountId), creatorPoints);

                updateProgression(creatorPoints);

            } else if (web::WebProgress* progress = e->getProgress()) {
                log::info("{}", "progress");
            } else if (e->isCancelled()) {
                log::info("{}", "fail");

                //call ui update
            }
        });

        auto req = web::WebRequest().userAgent("").bodyString(fmt::format("secret=Wmfd2893gb7&targetAccountID={}", accountId));
        auto task = req.post("http://www.boomlings.com/database/getGJUserInfo20.php");
        m_listener.setFilter(task);
    }

    int findCreatorPoints(const std::string& fullResponse) {
        int creatorPoints = 0;
        auto keyValuePairs = split(fullResponse, ":");

        try {
            for (size_t i = 0; i < keyValuePairs.size(); i += 2) {
                if (i + 1 < keyValuePairs.size()) {
                    int key = std::stoi(keyValuePairs[i]);
                    if (key == 8) {
                        creatorPoints = std::stoi(keyValuePairs[i + 1]);
                        break;
                    }
                }
            }
        } catch (const std::exception& e) {
            log::info("Error processing creator points: {}. Exception: {}", fullResponse, e.what());
        }

        if (creatorPoints == 0) {
            log::info("Creator points not found in data");
        }

        return creatorPoints;
    }

    std::vector<std::string> split(const std::string& str, const std::string& delimiter) {
        std::vector<std::string> tokens;
        size_t start = 0, end;
        while ((end = str.find(delimiter, start)) != std::string::npos) {
            tokens.push_back(str.substr(start, end - start));
            start = end + delimiter.length();
        }
        tokens.push_back(str.substr(start));
        return tokens;
    }

    void updateProgression(int creatorPointResult) {

        sliderBarSpr1->setTextureRect(CCRectMake(0, 0, 31.36f, sliderBarSpr1->getContentSize().height));

        float ratio1 = (float)(creatorPointResult - std::stoi(unlockData0->numberString)) / (float)(std::stoi(unlockData1->numberString) - std::stoi(unlockData0->numberString));
        float scale1 = ratio1 >= 0.98f ? sliderBarSpr1->getContentSize().width * 0.98f : sliderBarSpr1->getContentSize().width * ratio1;
        sliderBarSpr1->setTextureRect(CCRectMake(0, 0, scale1, sliderBarSpr1->getContentSize().height));

        CCSprite* tierCompletedStar1 = CCSprite::createWithSpriteFrameName("GJ_bigStar_001.png");
        CCSprite* tierCompletedStarGlow1 = CCSprite::createWithSpriteFrameName("GJ_bigStar_glow_001.png");
        tierCompletedStarGlow1->setAnchorPoint({0, 0});
        tierCompletedStarGlow1->setPosition({-11, -11});
        tierCompletedStarGlow1->setZOrder(-1);
        tierCompletedStar1->addChild(tierCompletedStarGlow1);

        CCSprite* tierCompletedStar2 = CCSprite::createWithSpriteFrameName("GJ_bigStar_001.png");
        CCSprite* tierCompletedStarGlow2 = CCSprite::createWithSpriteFrameName("GJ_bigStar_glow_001.png");
        tierCompletedStarGlow2->setAnchorPoint({0, 0});
        tierCompletedStarGlow2->setPosition({-11, -11});
        tierCompletedStarGlow2->setZOrder(-1);
        tierCompletedStar2->addChild(tierCompletedStarGlow2);

        bool isInTier =  creatorPointResult >= std::stoi(unlockData0->numberString) && creatorPointResult < std::stoi(unlockData1->numberString);
        if (ratio1 < 1.f && isInTier) {
            currentProgressText->setScale(0.35f);
            currentProgressText->setString(addCommas(std::to_string(creatorPointResult).c_str()));
            currentProgressText->setPosition({-12.5f, 110.5f});
            tierContainer->addChild(currentProgressText);
        }
        if (ratio1 >= 1.f) {
            currentProgressText->setString("");
            if (!starsAdd) {
                tierCompletedStar1->setAnchorPoint({0, 0});
                tierCompletedStar2->setAnchorPoint({0, 0});
                tierCompletedStar1->setPosition({-72, 8});
                tierCompletedStar2->setPosition({77, 8});
                tierCompletedStar1->setScale(0.5f);
                tierCompletedStar2->setScale(0.5f);
                tierContainer->addChild(tierCompletedStar1);
                tierContainer->addChild(tierCompletedStar2);
                starsAdd = true;
            }
        }

        auto p1Unlocked = ccc3(190, 190, 190);
        auto p2Unlocked = ccc3(245, 245, 245);
        auto p1Grey = ccc3(30, 30, 30);
        auto p2Grey = ccc3(80, 80, 80);

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
            lock1->setVisible(true);
            unlock1->setColors(p1Grey, p2Grey);
            unlock1->disableGlowOutline();
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

    CCNode* createTier1(int ratedLevels) {
        tierContainer = CCNode::create();
        tierContainer->setPosition({0, 0});
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        pageWidth = winSize.width * 0.75f;
        CCMenu* tierMenu = CCMenu::create();

        /* Tier's Content */

        /* Moving Progress Text */
        currentProgressText = CCLabelBMFont::create("", "bigFont-uhd.fnt");
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
        sliderBarSpr1 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio1 = (float)(ratedLevels - std::stoi(unlockData0->numberString)) / (float)(std::stoi(unlockData1->numberString) - std::stoi(unlockData0->numberString));
        float scale1 = ratio1 >= 0.98f ? sliderBarSpr1->getContentSize().width * 0.98f : sliderBarSpr1->getContentSize().width * ratio1;
        sliderBarSpr1->setTextureRect(CCRectMake(0, 0, scale1, sliderBarSpr1->getContentSize().height));

        auto unlockText1 = CCLabelBMFont::create(addCommas(unlockData1->numberString.c_str()), "bigFont-uhd.fnt");
        unlockInfo1 = new UnlockInfo(unlockData1->unlockId, unlockData1->iconType);
        unlockInfo1->autorelease();
        unlock1 = SimplePlayer::create(1);
        lock1 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        /* Set Progress Text */
        bool isInTier =  ratedLevels >= std::stoi(unlockData0->numberString) && ratedLevels < std::stoi(unlockData1->numberString);
        if (ratio1 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(ratedLevels).c_str()));
            currentProgressText->setPosition({-12.5f, 110.5f});
            tierContainer->addChild(currentProgressText);
        }
        if (ratio1 >= 1.f) {
            tierCompletedStar1->setAnchorPoint({0, 0});
            tierCompletedStar2->setAnchorPoint({0, 0});
            tierCompletedStar1->setPosition({-72, 8});
            tierCompletedStar2->setPosition({77, 8});
            tierCompletedStar1->setScale(0.5f);
            tierCompletedStar2->setScale(0.5f);
            tierContainer->addChild(tierCompletedStar1);
            tierContainer->addChild(tierCompletedStar2);
            starsAdd = true;
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
            lock1->setVisible(true);
            unlock1->setColors(p1Grey, p2Grey);
            unlock1->disableGlowOutline();
        }

        /* First Row */
        sliderBarSpr1->setAnchorPoint({ 0, .5f }); sliderBarSpr1->setZOrder(-1); sliderBarSpr1->setPosition({-28.5f, 122.5f});
        sliderOutlineSpr1->setAnchorPoint({ 0, .5f }); sliderOutlineSpr1->setScaleX(1.1f); sliderOutlineSpr1->setPosition({-30.5f, 122.5f});      
        lock1->setZOrder(1);
        unlockText1->setScale(.5f); unlockText1->setPosition({33, 92.5f});

        /* First Row */
        unlock1->addChild(lock1);

        /* First Row */
        auto unlockButton1 = CCMenuItemSpriteExtra::create(
			unlock1,
			this,
			menu_selector(RatedLevelPage::openUnlockInfo)
		);
        unlockButton1->setUserObject(unlockInfo1);
        unlockButton1->setContentSize({unlock1->m_firstLayer->getContentSize().width, unlock1->m_firstLayer->getContentSize().height});
        auto innerSpr1 = static_cast<cocos2d::CCSprite*>(unlockButton1->getNormalImage());
        innerSpr1->setPosition({unlock1->m_firstLayer->getContentSize().width / 2.f, unlock1->m_firstLayer->getContentSize().height / 2.f});

        /* First Row */
        unlockButton1->setPosition({-251, -37.5f});

        /* First Row */
        tierContainer->addChild(sliderBarSpr1);
        tierContainer->addChild(sliderOutlineSpr1);
        tierMenu->addChild(unlockButton1);
        tierContainer->addChild(unlockText1);

        tierContainer->addChild(tierMenu);

        /* End of Tier's Content */

        tierContainer->setPosition({pageWidth * 0.5f, 0});
        return tierContainer;
    }
};