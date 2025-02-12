#include "UnlockPage.hpp"

UnlockPage::UnlockPage(FLAlertLayer* parentPopup, std::vector<Utilities::UnlockData*> unlockList, const char* iconSprName) : BasePage(parentPopup), unlockList(unlockList), iconSprName(iconSprName) {
    
    unlockCount = (int)unlockList.size() - 1;
    tierCount = (unlockCount + 9) / 10;
}

UnlockPage::~UnlockPage() {}

CCNode* UnlockPage::createPage(int value) {

    pageContainer->setPosition({0, 0});
    buttonMenu->setPosition({147, -200});
    pageContainer->addChild(buttonMenu);

    auto labelSpr = CCSprite::createWithSpriteFrameName(iconSprName);
    labelSpr->setPosition({227.5f, 185});
    labelSpr->setScale(0.65f);
    pageContainer->addChild(labelSpr);

    auto player = SimplePlayer::create(1);
    player->updatePlayerFrame(util->gameManager->m_playerFrame, IconType::Cube);
    player->setColors(util->gameManager->colorForIdx(util->gameManager->getPlayerColor()), util->gameManager->colorForIdx(util->gameManager->getPlayerColor2()));
    if (util->gameManager->m_playerGlow) {
        player->setGlowOutline(util->gameManager->colorForIdx(util->gameManager->getPlayerGlowColor()));
    }
    player->setPosition({228, 200});
    player->setScale(1.35f);
    pageContainer->addChild(player);

    //add speical refreshes for friend page, most liked level, and creator points
    if (std::string(iconSprName).compare("friends_spr.png"_spr) == 0 || std::string(iconSprName).compare("most_liked_spr.png"_spr) == 0 || std::string(iconSprName).compare("creator_points_spr.png"_spr) == 0) {

        createRefreshButton();
    }

    for (int i = 0; i < tierCount; ++i) {
        auto tierPage = createTier(i, value);
        tierPage->retain();
        pageContainer->addChild(tierPage);
        tierPages->addObject(tierPage);
        tierPage->setVisible(i == 0);
    }

    createNavigationButtons(tierCount);

    pageContainer->setPosition({pageWidth, 0});

    return pageContainer;
}

void UnlockPage::createRefreshButton() {

    CCSprite* refreshSpr = CCSprite::createWithSpriteFrameName("GJ_replayBtn_001.png");
    refreshSpr->setScale(.75f);

    CCMenuItemSpriteExtra* refreshButton = nullptr;
    if (std::string(iconSprName).compare("friends_spr.png"_spr) == 0) {

        refreshButton = CCMenuItemSpriteExtra::create(
            refreshSpr,
            this,
            menu_selector(UnlockPage::refreshFriends)
        );
    } else if (std::string(iconSprName).compare("most_liked_spr.png"_spr) == 0) {

        refreshButton = CCMenuItemSpriteExtra::create(
            refreshSpr,
            this,
            menu_selector(UnlockPage::refreshMaxLikes)
        );
    } else {

        refreshButton = CCMenuItemSpriteExtra::create(
            refreshSpr,
            this,
            menu_selector(UnlockPage::refreshCreatorPoints)
        );
    }

    refreshButton->setAnchorPoint({.5f, .5f});
    refreshButton->setPosition({270, 245});

    buttonMenu->addChild(refreshButton);
}

CCNode* UnlockPage::createTier(int tier, int value) {
    
    auto tierContainer = CCNode::create();
    tierContainer->setPosition({0, 0});
    CCMenu* tierMenu = CCMenu::create();
    float tierXPos = 284.5f; float tierYPos = 160.f;
    tierMenu->setPosition({tierXPos, tierYPos});

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

    int startIdx;
    int endIdx;

    if (strcmp(iconSprName, "jumps_spr.png"_spr) == 0) {

        startIdx = tier * 8;
        endIdx = (tier == tierCount - 1) ? unlockCount : std::min(startIdx + 8, unlockCount);
    } else {

        startIdx = tier * 10;
        endIdx = (tier == tierCount - 1) ? unlockCount : std::min(startIdx + 10, unlockCount);
    }


    bool progressPlaced = false;
    for (int i = startIdx; i < endIdx; ++i) {
        
        progressPlaced = util->placeUnlockable(this, value, currentProgressText, 
                                            progressPlaced, tierContainer, tierMenu, 
                                            unlockList[i], unlockList[i + 1], 
                                            unlockList[startIdx], unlockList[endIdx]);
    }

    if (value >= std::stoi(unlockList[endIdx]->numberString)) {
        tierCompletedStar1->setAnchorPoint({0, 0});
        tierCompletedStar2->setAnchorPoint({0, 0});
        tierCompletedStar1->setPosition({-72, 8});
        tierCompletedStar2->setPosition({77, 8});
        tierCompletedStar1->setScale(0.5f);
        tierCompletedStar2->setScale(0.5f);
        tierContainer->addChild(tierCompletedStar1);
        tierContainer->addChild(tierCompletedStar2);
    }

    tierContainer->addChild(tierMenu);


    /* End of Tier's Content */

    tierContainer->setPosition({pageWidth, 0});
    return tierContainer;
}

void UnlockPage::refreshFriends(CCObject* sender) {

    int num = processFriendCount();
    num = processFriendCount();
    log::info("result: {}", num);
    makeInfoPopup("Friends");
}

void UnlockPage::refreshMaxLikes(CCObject* sender) {

    makeInfoPopup("Your Most Liked Level");
}

void UnlockPage::refreshCreatorPoints(CCObject* sender) {

    makeInfoPopup("Creator Points");
}

void UnlockPage::makeInfoPopup(std::string type) {

    if (type.compare("Friends") != 0) {

        FLAlertLayer::create(
            "Refresh Complete",
            std::format("Your '{}' statistic has been fetched via <cl>web requests</c>. <cr>DO NOT SPAM THIS BUTTON!</c> That will result in an <cr>API Rate Limit</c>.", type),
            "Ok"
        )->show(); 
    } else {

        FLAlertLayer::create(
            "Refreshing",
            "<co>If this is the first time you pressed this button</c>, <cy>press this button again</c>. Then your 'Friends' will be refreshed.",
            "Ok"
        )->show(); 
    }
}

int UnlockPage::processFriendCount() {

    FriendsProfilePage* m_friendsPage = FriendsProfilePage::create(UserListType::Friends);
            
    int friendCount = -1;

    for (auto node : CCArrayExt<CCNode*>(m_friendsPage->m_mainLayer->getChildren())) {

        if (auto label = typeinfo_cast<CCLabelBMFont*>(node)) {                

            std::string nodeText = label->getString();             
            if (nodeText.find("Total friends:") != std::string::npos) {

                std::string number = nodeText.substr(
                    nodeText.find(":") + 2, 
                    nodeText.length() - nodeText.find(":") - 2
                );
                friendCount = std::atoi(number.c_str());
                break;
            }
        }
    }

    m_friendsPage->removeFromParentAndCleanup(true);
    m_friendsPage->release();
    m_friendsPage = nullptr;

    return friendCount;
}