#include "UnlockPage.hpp"

UnlockPage::UnlockPage(FLAlertLayer* parentPopup, std::vector<Utilities::UnlockData*> unlockList, const char* iconSprName) : BasePage(parentPopup), unlockList(unlockList), iconSprName(iconSprName) {
    
    unlockCount = (int)unlockList.size() - 1;
    tierCount = (unlockCount + 9) / 10;
    userId = util->gameManager->m_playerUserID;
    accountId = GJAccountManager::sharedState()->m_accountID;
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


void UnlockPage::createRefreshButton() {

    CCSprite* refreshSpr = CCSprite::createWithSpriteFrameName("GJ_replayBtn_001.png");
    refreshSpr->setScale(.75f);

    CCMenuItemSpriteExtra* refreshButton;
    CCMenuItemSpriteExtra* supportMeButton;
    if (std::string(iconSprName).compare("friends_spr.png"_spr) == 0) {

        refreshButton = CCMenuItemSpriteExtra::create(
            refreshSpr,
            this,
            menu_selector(UnlockPage::refreshFriends)
        );
    } else if (std::string(iconSprName).compare("most_liked_spr.png"_spr) == 0) {

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

        refreshButton = CCMenuItemSpriteExtra::create(
            refreshSpr,
            this,
            menu_selector(UnlockPage::refreshMaxLikes)
        );
        supportMeButton = CCMenuItemSpriteExtra::create(
            supportSpr,
            this,
            menu_selector(UnlockPage::openSupportMeLevel)
        );

        supportMeButton->setAnchorPoint({.5f, .5f});
        supportMeButton->setPosition({220, 245});
        buttonMenu->addChild(supportMeButton);
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

void UnlockPage::openSupportMeLevel(CCObject* sender) {

    int id = 114471227;

    GameLevelManager::sharedState()->downloadLevel(id, false);

    GameLevelManager::get()->m_levelDownloadDelegate = MyLevelDownloadDelegate::get();

    //auto scheduler = CCDirector::sharedDirector()->getScheduler();
    //scheduler->scheduleSelector(schedule_selector(UnlockPage::checkLevelDownloaded), this, 0.2f, false);
}

void UnlockPage::checkLevelDownloaded(float dt) {

    auto level = GameLevelManager::sharedState()->getSavedLevel(114471227);
    if (level) {

        log::info("level is not null");
        bool downloadedRight = GameLevelManager::sharedState()->hasDownloadedLevel(114471227);
        log::info("Result: {}", downloadedRight);

        auto scheduler = CCDirector::sharedDirector()->getScheduler();
        scheduler->unscheduleSelector(schedule_selector(UnlockPage::checkLevelDownloaded), this);
        openLevel(level);
    }
}

void UnlockPage::openLevel(GJGameLevel* level) {

    auto levelLayer = LevelInfoLayer::create(level, false);
    auto scene = CCScene::create();
    scene->addChild(levelLayer);
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5, scene));
}

void UnlockPage::refreshFriends(CCObject* sender) {

    int num = processFriendCount();
    num = processFriendCount();
    log::info("result: {}", num);
    makeInfoPopup("Friends");
}

void UnlockPage::refreshMaxLikes(CCObject* sender) {

    requestMostLiked(0);
    makeInfoPopup("Your Most Liked Level");
}

void UnlockPage::refreshCreatorPoints(CCObject* sender) {

    requestCreatorPoints();
    makeInfoPopup("Creator Points");
}

void UnlockPage::makeInfoPopup(std::string type) {

    if (type.compare("Friends") != 0) {

        FLAlertLayer::create(
            "Refresh Complete",
            fmt::format("Your '{}' statistic has been fetched via <cl>web requests</c>. <cr>DO NOT SPAM THIS BUTTON!</c> That will result in an <cr>API Rate Limit</c>.", type),
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


void UnlockPage::requestMostLiked(int page) {

    log::info("Entered web request method");

    // Send initial request to get total levels from server

    mostLikedListener.bind([this, page](web::WebTask::Event* e) mutable {

        if (web::WebResponse* value = e->getValue()) {
            auto str = value->string().unwrap();
            log::info("Response for Page {}: {}", page, str);

            if (str == "-1") {
                log::warn("No levels found!");
                return;
            }

            // Parse response
            auto [levels, total, offset, amount] = parseResponse(str);

            log::info("Parsed Levels: {}", fmt::join(levels, ", "));
            log::info("Total: {}, Offset: {}, Amount: {}", total, offset, amount);

            processLevels(levels, userId);

            // Continue fetching pages if needed
            if (offset + amount < total) {

                log::info("Fetching next page... current size of vector is: {}", allLikes.size());
                requestMostLiked(page + 1);
            } else {
                log::info("All levels fetched: {}", allLikes.size());
                log::info("All likes: {}", fmt::join(allLikes, ", "));

                int maxLikes = findMaxLikes();
                log::info("The level with the most likes has {} likes.", maxLikes);
                
                Mod::get()->setSavedValue<int>(fmt::format("most-liked-{}", userId), maxLikes);

                //updateProgression(maxLikes);

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
    mostLikedListener.setFilter(task);
}

void UnlockPage::processLevels(const std::vector<std::string>& levelObjects, int userId) {

    std::vector<std::tuple<int, int>> levels;

    for (const auto& levelObject : levelObjects) {
        auto keyValuePairs = util->split(levelObject, ":");
        int levelId = 0;
        int likes = 0;

        // Iterate through the key-value pairs
        for (size_t i = 0; i < keyValuePairs.size(); i += 2) {
            if (i + 1 < keyValuePairs.size()) {
                int key = std::stoi(keyValuePairs[i]);
                if (key == 14) {
                    likes = std::stoi(keyValuePairs[i + 1]); // Key 14: Likes
                    break;
                }
            }
        }
        allLikes.push_back(likes);
    }
}

std::tuple<std::vector<std::string>, int, int, int> UnlockPage::parseResponse(const std::string& response) {
    // Split the response into parts
    auto parts = util->split(response, "#");

    // Extract levels
    auto levels = util->split(parts[0], "|");

    // Extract page info
    auto pageInfo = util->split(parts[3], ":");

    int total = std::stoi(pageInfo[0]);
    int offset = std::stoi(pageInfo[1]);
    int amount = std::stoi(pageInfo[2]);

    return {levels, total, offset, amount};
}

int UnlockPage::findMaxLikes() {

    return *max_element(allLikes.begin(), allLikes.end());
}


void UnlockPage::requestCreatorPoints() {

    creatorPointsListener.bind([this](web::WebTask::Event* e) {

        if (web::WebResponse* value = e->getValue()) {
            auto str = value->string().unwrap();        //I totally check this value before unwrapping :)
            log::info("Response: {}", str);

            int creatorPoints = findCreatorPoints(str);
            log::info("Extracted Creator Points: {}", creatorPoints);

            Mod::get()->setSavedValue<int>(fmt::format("creator-points-{}", accountId), creatorPoints);

            //updateProgression(creatorPoints);

        } else if (web::WebProgress* progress = e->getProgress()) {
            log::info("{}", "progress");
        } else if (e->isCancelled()) {
            log::info("{}", "fail");

            //call ui update
        }
    });

    auto req = web::WebRequest().userAgent("").bodyString(fmt::format("secret=Wmfd2893gb7&targetAccountID={}", accountId));
    auto task = req.post("http://www.boomlings.com/database/getGJUserInfo20.php");
    creatorPointsListener.setFilter(task);
}

int UnlockPage::findCreatorPoints(const std::string& fullResponse) {

    int creatorPoints = 0;
    auto keyValuePairs = util->split(fullResponse, ":");

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

    return creatorPoints;
}