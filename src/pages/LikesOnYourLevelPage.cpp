#pragma once

#include <Geode/Geode.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/binding/LevelInfoLayer.hpp>
#include <Geode/binding/GJGameLevel.hpp>

#include "../modify/ItemInfoPopup.cpp"

#include "../classes/ProcessLevelObjects.cpp"

using namespace geode::prelude;

class LikesOnYourLevelPage : public CCObject {
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
    UnlockData* unlockData2 = nullptr;
    UnlockData* unlockData3 = nullptr;
    UnlockData* unlockData4 = nullptr;
    UnlockData* unlockData5 = nullptr;

    CCSprite* sliderBarSpr1;
    CCSprite* sliderBarSpr2;
    CCSprite* sliderBarSpr3;
    CCSprite* sliderBarSpr4;
    CCSprite* sliderBarSpr5;

    SimplePlayer* unlock1;
    SimplePlayer* unlock2;
    SimplePlayer* unlock3;
    SimplePlayer* unlock4;
    SimplePlayer* unlock5;

    CCSprite* lock1;
    CCSprite* lock2;
    CCSprite* lock3;
    CCSprite* lock4;
    CCSprite* lock5;

    CCLabelBMFont* currentProgressText;

    CCNode* tierContainer;

    UnlockInfo* unlockInfo1;
    UnlockInfo* unlockInfo2;
    UnlockInfo* unlockInfo3;
    UnlockInfo* unlockInfo4;
    UnlockInfo* unlockInfo5;

    bool starsAdd;
    
    EventListener<web::WebTask> m_listener;
    int userId;
    ProcessLevelObjects exporter;

public:
    LikesOnYourLevelPage(FLAlertLayer* parentPopup) {

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
        
        unlockData1 = new UnlockData("50", 63, IconType::Cube);
        unlockData2 = new UnlockData("100", 46, IconType::Cube);
        unlockData3 = new UnlockData("250", 72, IconType::Ball);
        unlockData4 = new UnlockData("500", 238, IconType::Cube);
        unlockData5 = new UnlockData("1000", 275, IconType::Cube);

        starsAdd = false;
        userId = GameManager::sharedState()->m_playerUserID;
    }

    CCNode* createLikesOnYourLevelPage() {

        int maxLikes = Mod::get()->getSavedValue<int>(fmt::format("most-liked-{}", userId));

        pageContainer = CCNode::create();
        pageContainer->setPosition({0, 0});
        buttonMenu->setPosition({147, -200});
        pageContainer->addChild(buttonMenu);

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        pageWidth = winSize.width * 0.75f;

        currentPage = 0;

        auto labelSpr = CCSprite::create("most_liked_spr.png"_spr);
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

        auto labelTopSpr = CCSprite::create("most_liked_top_spr.png"_spr);
        labelTopSpr->setPosition({228.25f, 175});
        labelTopSpr->setScale(0.5f);
        pageContainer->addChild(labelTopSpr);

        tier1Page = createTier1(maxLikes);
        tier1Page->retain();
        pageContainer->addChild(tier1Page);
        tierPages->addObject(tier1Page);
        tier1Page->setVisible(true);

        createNavigationButtons();

        createRefreshButton();

        pageContainer->setPosition({pageWidth * 0.5f, 0});

        return pageContainer;
    }

    ~LikesOnYourLevelPage() {
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
            menu_selector(LikesOnYourLevelPage::onTierButton)
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

    void createRefreshButton() {

        CCSprite* refreshSpr = CCSprite::createWithSpriteFrameName("GJ_replayBtn_001.png");
        refreshSpr->setScale(.75f);

        CCSprite* supportSpr = CCSprite::create("support_me_spr.png"_spr);
        supportSpr->setScale(0.99f);
        supportSpr->setRotation(270.f);

        CCSprite* supportLikeSpr = CCSprite::createWithSpriteFrameName("GJ_likesIcon_001.png");
        supportLikeSpr->setPosition({33, 24});
        supportLikeSpr->setScale(0.7f);
        supportLikeSpr->setRotation(90.f);
        supportSpr->addChild(supportLikeSpr);

        auto supportText1 = CCLabelBMFont::create("Support", "bigFont-uhd.fnt");
        supportText1->setPosition({21, 24});
        supportText1->setScale(0.225f);
        supportText1->setRotation(90.f);
        supportSpr->addChild(supportText1);

        auto supportText2 = CCLabelBMFont::create("Me", "bigFont-uhd.fnt");
        supportText2->setPosition({14, 23.75f});
        supportText2->setScale(0.225f);
        supportText2->setRotation(90.f);
        supportSpr->addChild(supportText2);

        auto refreshButton = CCMenuItemSpriteExtra::create(
            refreshSpr,
            this,
            menu_selector(LikesOnYourLevelPage::refreshMaxLikes)
        );
        refreshButton->setAnchorPoint({.5f, .5f});
        refreshButton->setPosition({270, 245});

        auto supportButton = CCMenuItemSpriteExtra::create(
            supportSpr,
            this,
            menu_selector(LikesOnYourLevelPage::supportMe)
        );
        supportButton->setAnchorPoint({.5f, .5f});
        supportButton->setPosition({220, 244.25f});

        buttonMenu->addChild(refreshButton);
        buttonMenu->addChild(supportButton);
    }

    void supportMe(CCObject*) {

        GameLevelManager::sharedState()->downloadLevel(114471227, false);       //114471227 is my level
        auto level = GameLevelManager::sharedState()->getSavedLevel(114471227);
        auto levelLayer = LevelInfoLayer::create(level, false);

        auto scene = CCScene::create();
        scene->addChild(levelLayer);
        CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5, scene));
    }

    void refreshMaxLikes(CCObject* sender) {

        makeWebRequest(0);
        makeInfoPopup();
    }

    void makeInfoPopup() {

        FLAlertLayer::create(
            "Refresh Complete",
            "Your 'Most Liked Level' statistic has been fetched via <cl>web requests</c>. <cr>DO NOT SPAM THIS BUTTON!</c> That will result in an <cr>API Rate Limit</c>.",
            "Ok"
        )->show();
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

    void makeWebRequest(int page) {

        log::info("Entered web request method");

        // Send initial request to get total levels from server

        m_listener.bind([this, page](web::WebTask::Event* e) mutable {
            if (web::WebResponse* value = e->getValue()) {
                auto str = value->string().unwrap();
                log::info("Response for Page {}: {}", page, str);

                if (str == "-1") {
                    log::warn("No levels found!");
                    return;
                }

                // Parse response
                auto [levels, total, offset, amount] = this->parseResponse(str);

                log::info("Parsed Levels: {}", fmt::join(levels, ", "));
                log::info("Total: {}, Offset: {}, Amount: {}", total, offset, amount);

                exporter.processLevels(levels, userId);

                // Continue fetching pages if needed
                if (offset + amount < total) {
                    log::info("Fetching next page... current size of vector is: {}", exporter.getAllLikes().size());
                    makeWebRequest(page + 1);
                } else {
                    log::info("All levels fetched: {}", exporter.getAllLikes().size());
                    log::info("All likes: {}", fmt::join(exporter.getAllLikes(), ", "));

                    int maxLikes = exporter.findMaxLikes();
                    log::info("The level with the most likes has {} likes.", maxLikes);
                    
                    Mod::get()->setSavedValue<int>(fmt::format("most-liked-{}", userId), maxLikes);

                    updateProgression(maxLikes);

                }

            } else if (e->getProgress()) {
                log::info("Fetching page {} in progress...", page);

            } else if (e->isCancelled()) {
                log::warn("Request for page {} was cancelled.", page);
            }
        });

        // Send request for the given page
        auto req = web::WebRequest().userAgent("").bodyString(fmt::format("secret=Wmfd2893gb7&type=5&page={}&str={}", page, userId));
        auto task = req.post("http://www.boomlings.com/database/getGJLevels21.php");
        m_listener.setFilter(task);
    }

    std::tuple<std::vector<std::string>, int, int, int> parseResponse(const std::string& response) {
        // Split the response into parts
        auto parts = split(response, "#");

        // Extract levels
        auto levels = split(parts[0], "|");

        // Extract page info
        auto pageInfo = split(parts[3], ":");

        int total = std::stoi(pageInfo[0]);
        int offset = std::stoi(pageInfo[1]);
        int amount = std::stoi(pageInfo[2]);

        return {levels, total, offset, amount};
    }

    std::vector<std::string> split(const std::string& str, const std::string& delimiter) {
        std::vector<std::string> tokens;
        size_t start = 0, end = 0;
        while ((end = str.find(delimiter, start)) != std::string::npos) {
            tokens.push_back(str.substr(start, end - start));
            start = end + delimiter.length();
        }
        tokens.push_back(str.substr(start));
        return tokens;
    }

    void updateProgression(int maxLikes) {

        sliderBarSpr1->setTextureRect(CCRectMake(0, 0, 31.36f, sliderBarSpr1->getContentSize().height));
        sliderBarSpr2->setTextureRect(CCRectMake(0, 0, 31.36f, sliderBarSpr2->getContentSize().height));
        sliderBarSpr3->setTextureRect(CCRectMake(0, 0, 31.36f, sliderBarSpr3->getContentSize().height));
        sliderBarSpr4->setTextureRect(CCRectMake(0, 0, 31.36f, sliderBarSpr4->getContentSize().height));
        sliderBarSpr5->setTextureRect(CCRectMake(0, 0, 31.36f, sliderBarSpr5->getContentSize().height));

        float ratio1 = (float)(maxLikes - std::stoi(unlockData0->numberString)) / (float)(std::stoi(unlockData1->numberString) - std::stoi(unlockData0->numberString));
        float scale1 = ratio1 >= 0.98f ? sliderBarSpr1->getContentSize().width * 0.98f : sliderBarSpr1->getContentSize().width * ratio1;
        sliderBarSpr1->setTextureRect(CCRectMake(0, 0, scale1, sliderBarSpr1->getContentSize().height));

        float ratio2 = (float)(maxLikes - std::stoi(unlockData1->numberString)) / (float)(std::stoi(unlockData2->numberString) - std::stoi(unlockData1->numberString));
        float scale2 = ratio2 >= 0.98f ? sliderBarSpr2->getContentSize().width * 0.98f : sliderBarSpr2->getContentSize().width * ratio2;
        sliderBarSpr2->setTextureRect(CCRectMake(0, 0, scale2, sliderBarSpr2->getContentSize().height)); 

        float ratio3 = (float)(maxLikes - std::stoi(unlockData2->numberString)) / (float)(std::stoi(unlockData3->numberString) - std::stoi(unlockData2->numberString));
        float scale3 = ratio3 >= 0.98f ? sliderBarSpr3->getContentSize().width * 0.98f : sliderBarSpr3->getContentSize().width * ratio3;
        sliderBarSpr3->setTextureRect(CCRectMake(0, 0, scale3, sliderBarSpr3->getContentSize().height));  

        float ratio4 = (float)(maxLikes - std::stoi(unlockData3->numberString)) / (float)(std::stoi(unlockData4->numberString) - std::stoi(unlockData3->numberString));
        float scale4 = ratio4 >= 0.98f ? sliderBarSpr4->getContentSize().width * 0.98f : sliderBarSpr4->getContentSize().width * ratio4;
        sliderBarSpr4->setTextureRect(CCRectMake(0, 0, scale4, sliderBarSpr4->getContentSize().height));

        float ratio5 = (float)(maxLikes - std::stoi(unlockData4->numberString)) / (float)(std::stoi(unlockData5->numberString) - std::stoi(unlockData4->numberString));
        float scale5 = ratio5 >= 0.98f ? sliderBarSpr5->getContentSize().width * 0.98f : sliderBarSpr5->getContentSize().width * ratio5;
        sliderBarSpr5->setTextureRect(CCRectMake(0, 0, scale5, sliderBarSpr5->getContentSize().height));

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
        
        bool isInTier =  maxLikes >= std::stoi(unlockData0->numberString) && maxLikes < std::stoi(unlockData5->numberString);
        if (ratio1 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(maxLikes).c_str()));
            currentProgressText->setPosition({-99, 138});
            tierContainer->addChild(currentProgressText);
        } else if (ratio2 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(maxLikes).c_str()));
            currentProgressText->setPosition({-12.5f, 138});
            tierContainer->addChild(currentProgressText);
        } else if (ratio3 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(maxLikes).c_str()));
            currentProgressText->setPosition({77, 138});
            tierContainer->addChild(currentProgressText);
        } else if (ratio4 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(maxLikes).c_str()));
            currentProgressText->setPosition({-55.75f, 73});
            tierContainer->addChild(currentProgressText);
        } else if (ratio5 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(maxLikes).c_str()));
            currentProgressText->setPosition({30.75f, 73});
            tierContainer->addChild(currentProgressText);
        }
        if (ratio5 >= 1.f) {
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
            lock2->setVisible(true);
            unlock2->setColors(p1Grey, p2Grey);
            unlock2->disableGlowOutline();
        }

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
            lock3->setVisible(true);
            unlock3->setColors(p1Grey, p2Grey);
            unlock3->disableGlowOutline();
        }

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
            lock4->setVisible(true);
            unlock4->setColors(p1Grey, p2Grey);
            unlock4->disableGlowOutline();
        }

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
            lock5->setVisible(true);
            unlock5->setColors(p1Grey, p2Grey);
            unlock5->disableGlowOutline();
        }
    }

    CCNode* createTier1(int maxLikes) {
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
        float ratio1 = (float)(maxLikes - std::stoi(unlockData0->numberString)) / (float)(std::stoi(unlockData1->numberString) - std::stoi(unlockData0->numberString));
        float scale1 = ratio1 >= 0.98f ? sliderBarSpr1->getContentSize().width * 0.98f : sliderBarSpr1->getContentSize().width * ratio1;
        sliderBarSpr1->setTextureRect(CCRectMake(0, 0, scale1, sliderBarSpr1->getContentSize().height));

        auto unlockText1 = CCLabelBMFont::create(addCommas(unlockData1->numberString.c_str()), "bigFont-uhd.fnt");
        unlockInfo1 = new UnlockInfo(unlockData1->unlockId, unlockData1->iconType);
        unlockInfo1->autorelease();
        unlock1 = SimplePlayer::create(1);
        lock1 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr2 = CCSprite::create("Progress_Outline.png"_spr);
        sliderBarSpr2 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio2 = (float)(maxLikes - std::stoi(unlockData1->numberString)) / (float)(std::stoi(unlockData2->numberString) - std::stoi(unlockData1->numberString));
        float scale2 = ratio2 >= 0.98f ? sliderBarSpr2->getContentSize().width * 0.98f : sliderBarSpr2->getContentSize().width * ratio2;
        sliderBarSpr2->setTextureRect(CCRectMake(0, 0, scale2, sliderBarSpr2->getContentSize().height)); 

        auto unlockText2 = CCLabelBMFont::create(addCommas(unlockData2->numberString.c_str()), "bigFont-uhd.fnt");
        unlockInfo2 = new UnlockInfo(unlockData2->unlockId, unlockData2->iconType);
        unlockInfo2->autorelease();
        unlock2 = SimplePlayer::create(1);
        lock2 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr3 = CCSprite::create("Progress_Outline.png"_spr);
        sliderBarSpr3 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio3 = (float)(maxLikes - std::stoi(unlockData2->numberString)) / (float)(std::stoi(unlockData3->numberString) - std::stoi(unlockData2->numberString));
        float scale3 = ratio3 >= 0.98f ? sliderBarSpr3->getContentSize().width * 0.98f : sliderBarSpr3->getContentSize().width * ratio3;
        sliderBarSpr3->setTextureRect(CCRectMake(0, 0, scale3, sliderBarSpr3->getContentSize().height));  

        auto unlockText3 = CCLabelBMFont::create(addCommas(unlockData3->numberString.c_str()), "bigFont-uhd.fnt");
        unlockInfo3 = new UnlockInfo(unlockData3->unlockId, unlockData3->iconType);
        unlockInfo3->autorelease();
        unlock3 = SimplePlayer::create(1);
        lock3 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr4 = CCSprite::create("Progress_Outline.png"_spr);
        sliderBarSpr4 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio4 = (float)(maxLikes - std::stoi(unlockData3->numberString)) / (float)(std::stoi(unlockData4->numberString) - std::stoi(unlockData3->numberString));
        float scale4 = ratio4 >= 0.98f ? sliderBarSpr4->getContentSize().width * 0.98f : sliderBarSpr4->getContentSize().width * ratio4;
        sliderBarSpr4->setTextureRect(CCRectMake(0, 0, scale4, sliderBarSpr4->getContentSize().height));

        auto unlockText4 = CCLabelBMFont::create(addCommas(unlockData4->numberString.c_str()), "bigFont-uhd.fnt");
        unlockInfo4 = new UnlockInfo(unlockData4->unlockId, unlockData4->iconType);
        unlockInfo4->autorelease();
        unlock4 = SimplePlayer::create(1);
        lock4 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        auto sliderOutlineSpr5 = CCSprite::create("Progress_Outline.png"_spr);
        sliderBarSpr5 = togglePlayerColours ? CCSprite::create("sliderBar2-uhd.png") : CCSprite::create("sliderBar-uhd.png");
        float ratio5 = (float)(maxLikes - std::stoi(unlockData4->numberString)) / (float)(std::stoi(unlockData5->numberString) - std::stoi(unlockData4->numberString));
        float scale5 = ratio5 >= 0.98f ? sliderBarSpr5->getContentSize().width * 0.98f : sliderBarSpr5->getContentSize().width * ratio5;
        sliderBarSpr5->setTextureRect(CCRectMake(0, 0, scale5, sliderBarSpr5->getContentSize().height));

        auto unlockText5 = CCLabelBMFont::create(addCommas(unlockData5->numberString.c_str()), "bigFont-uhd.fnt");
        unlockInfo5 = new UnlockInfo(unlockData5->unlockId, unlockData5->iconType);
        unlockInfo5->autorelease();
        unlock5 = SimplePlayer::create(1);
        lock5 = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");

        /* Set Progress Text */
        bool isInTier =  maxLikes >= std::stoi(unlockData0->numberString) && maxLikes < std::stoi(unlockData5->numberString);
        if (ratio1 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(maxLikes).c_str()));
            currentProgressText->setPosition({-99, 138});
            tierContainer->addChild(currentProgressText);
        } else if (ratio2 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(maxLikes).c_str()));
            currentProgressText->setPosition({-12.5f, 138});
            tierContainer->addChild(currentProgressText);
        } else if (ratio3 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(maxLikes).c_str()));
            currentProgressText->setPosition({77, 138});
            tierContainer->addChild(currentProgressText);
        } else if (ratio4 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(maxLikes).c_str()));
            currentProgressText->setPosition({-55.75f, 73});
            tierContainer->addChild(currentProgressText);
        } else if (ratio5 < 1.f && isInTier) {
            currentProgressText->setString(addCommas(std::to_string(maxLikes).c_str()));
            currentProgressText->setPosition({30.75f, 73});
            tierContainer->addChild(currentProgressText);
        }
        if (ratio5 >= 1.f) {
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
            lock2->setVisible(true);
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
            lock3->setVisible(true);
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
            lock4->setVisible(true);
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
            lock5->setVisible(true);
            unlock5->setColors(p1Grey, p2Grey);
            unlock5->disableGlowOutline();
        }

        /* First Row */
        sliderBarSpr1->setAnchorPoint({ 0, .5f }); sliderBarSpr1->setZOrder(-1); sliderBarSpr1->setPosition({-115, 150}); 
        sliderOutlineSpr1->setAnchorPoint({ 0, .5f }); sliderOutlineSpr1->setScaleX(1.1f); sliderOutlineSpr1->setPosition({-117, 150}); 
        lock1->setZOrder(1);
        unlockText1->setScale(.5f); unlockText1->setPosition({-55.5f, 120});
        sliderBarSpr2->setAnchorPoint({ 0, .5f }); sliderBarSpr2->setZOrder(-1); sliderBarSpr2->setPosition({-28.5f, 150});
        sliderOutlineSpr2->setAnchorPoint({ 0, .5f }); sliderOutlineSpr2->setScaleX(1.1f); sliderOutlineSpr2->setPosition({-30.5f, 150});
        lock2->setZOrder(1);
        unlockText2->setScale(.5f); unlockText2->setPosition({33, 120});
        sliderBarSpr3->setAnchorPoint({ 0, .5f }); sliderBarSpr3->setZOrder(-1); sliderBarSpr3->setPosition({61, 150});
        sliderOutlineSpr3->setAnchorPoint({ 0, .5f }); sliderOutlineSpr3->setScaleX(1.1f); sliderOutlineSpr3->setPosition({59, 150});
        lock3->setZOrder(1);
        unlockText3->setScale(.5f); unlockText3->setPosition({122, 120});

        sliderBarSpr4->setAnchorPoint({ 0, .5f }); sliderBarSpr4->setZOrder(-1); sliderBarSpr4->setPosition({-71.75f, 85}); 
        sliderOutlineSpr4->setAnchorPoint({ 0, .5f }); sliderOutlineSpr4->setScaleX(1.1f); sliderOutlineSpr4->setPosition({-73.75f, 85}); 
        lock4->setZOrder(1);
        unlockText4->setScale(.5f); unlockText4->setPosition({-12.5f, 55});
        sliderBarSpr5->setAnchorPoint({ 0, .5f }); sliderBarSpr5->setZOrder(-1); sliderBarSpr5->setPosition({14.75f, 85});
        sliderOutlineSpr5->setAnchorPoint({ 0, .5f }); sliderOutlineSpr5->setScaleX(1.1f); sliderOutlineSpr5->setPosition({12.75f, 85});
        lock5->setZOrder(1);
        unlockText5->setScale(.5f); unlockText5->setPosition({76.25f, 55});

        /* First Row */
        unlock1->addChild(lock1);
        unlock2->addChild(lock2);
        unlock3->addChild(lock3);
        unlock4->addChild(lock4);
        unlock5->addChild(lock5);

        /* First Row */
        auto unlockButton1 = CCMenuItemSpriteExtra::create(
			unlock1,
			this,
			menu_selector(LikesOnYourLevelPage::openUnlockInfo)
		);
        unlockButton1->setUserObject(unlockInfo1);
        unlockButton1->setContentSize({unlock1->m_firstLayer->getContentSize().width, unlock1->m_firstLayer->getContentSize().height});
        auto innerSpr1 = static_cast<cocos2d::CCSprite*>(unlockButton1->getNormalImage());
        innerSpr1->setPosition({unlock1->m_firstLayer->getContentSize().width / 2.f, unlock1->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton2 = CCMenuItemSpriteExtra::create(
			unlock2,
			this,
			menu_selector(LikesOnYourLevelPage::openUnlockInfo)
		);
        unlockButton2->setUserObject(unlockInfo2);
        unlockButton2->setContentSize({unlock2->m_firstLayer->getContentSize().width, unlock2->m_firstLayer->getContentSize().height});
        auto innerSpr2 = static_cast<cocos2d::CCSprite*>(unlockButton2->getNormalImage());
        innerSpr2->setPosition({unlock2->m_firstLayer->getContentSize().width / 2.f, unlock2->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton3 = CCMenuItemSpriteExtra::create(
			unlock3,
			this,
			menu_selector(LikesOnYourLevelPage::openUnlockInfo)
		);
        unlockButton3->setUserObject(unlockInfo3);
        unlockButton3->setContentSize({unlock3->m_firstLayer->getContentSize().width, unlock3->m_firstLayer->getContentSize().height});
        auto innerSpr3 = static_cast<cocos2d::CCSprite*>(unlockButton3->getNormalImage());
        innerSpr3->setPosition({unlock3->m_firstLayer->getContentSize().width / 2.f, unlock3->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton4 = CCMenuItemSpriteExtra::create(
			unlock4,
			this,
			menu_selector(LikesOnYourLevelPage::openUnlockInfo)
		);
        unlockButton4->setUserObject(unlockInfo4);
        unlockButton4->setContentSize({unlock4->m_firstLayer->getContentSize().width, unlock4->m_firstLayer->getContentSize().height});
        auto innerSpr4 = static_cast<cocos2d::CCSprite*>(unlockButton4->getNormalImage());
        innerSpr4->setPosition({unlock4->m_firstLayer->getContentSize().width / 2.f, unlock4->m_firstLayer->getContentSize().height / 2.f});

        auto unlockButton5 = CCMenuItemSpriteExtra::create(
			unlock5,
			this,
			menu_selector(LikesOnYourLevelPage::openUnlockInfo)
		);
        unlockButton5->setUserObject(unlockInfo5);
        unlockButton5->setContentSize({unlock5->m_firstLayer->getContentSize().width, unlock5->m_firstLayer->getContentSize().height});
        auto innerSpr5 = static_cast<cocos2d::CCSprite*>(unlockButton5->getNormalImage());
        innerSpr5->setPosition({unlock5->m_firstLayer->getContentSize().width / 2.f, unlock5->m_firstLayer->getContentSize().height / 2.f});

        /* First Row */
        unlockButton1->setPosition({-340.5f, -10});
        unlockButton2->setPosition({-252, -10});
        unlockButton3->setPosition({-163, -10});

        unlockButton4->setPosition({-297.5f, -75});
        unlockButton5->setPosition({-208.5f, -75});

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

        tierContainer->addChild(tierMenu);

        /* End of Tier's Content */

        tierContainer->setPosition({pageWidth * 0.5f, 0});
        return tierContainer;
    }
};