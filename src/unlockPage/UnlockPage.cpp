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
    buttonMenu->setID("Page-Menu");
    pageContainer->addChild(buttonMenu);

    createTitle(iconSprName, pageContainer);

    if (std::string(iconSprName).compare("friends_spr.png"_spr) == 0 || std::string(iconSprName).compare("most_liked_spr.png"_spr) == 0 || std::string(iconSprName).compare("creator_points_spr.png"_spr) == 0) {

        createRefreshButton();
    }

    for (int i = 0; i < tierCount; ++i) {
        auto tierPage = createTier(i, value);
        tierPage->setID("Tier-Node");
        tierPage->retain();
        pageContainer->addChild(tierPage);
        tierPages->addObject(tierPage);
        tierPage->setVisible(i == 0);
    }

    createNavigationButtons(tierCount);

    pageContainer->setPosition({pageWidth, 0});
    pageNode = pageContainer;
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
    auto currentProgressText = CCLabelBMFont::create("", "bigFont.fnt");
    currentProgressText->setScale(0.35f);
    currentProgressText->setID("Progress-Text");

    /* Completion Stars */
    auto tierCompletedStar1 = CCSprite::createWithSpriteFrameName("GJ_bigStar_001.png");
    tierCompletedStar1->setID("Tier-Complete-Top");
    auto tierCompletedStarGlow1 = CCSprite::createWithSpriteFrameName("GJ_bigStar_glow_001.png");
    tierCompletedStarGlow1->setID("Tier-Complete-Bottom");
    tierCompletedStarGlow1->setAnchorPoint({0, 0});
    tierCompletedStarGlow1->setPosition({-11, -11});
    tierCompletedStarGlow1->setZOrder(-1);
    tierCompletedStar1->addChild(tierCompletedStarGlow1);

    auto tierCompletedStar2 = CCSprite::createWithSpriteFrameName("GJ_bigStar_001.png");
    tierCompletedStar2->setID("Tier-Complete-Top");
    auto tierCompletedStarGlow2 = CCSprite::createWithSpriteFrameName("GJ_bigStar_glow_001.png");
    tierCompletedStarGlow2->setID("Tier-Complete-Bottom");
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

        std::string specialPlacement = "";
        if (std::string(iconSprName).compare("stars_spr.png"_spr) == 0 && unlockList[i + 1]->numberString.compare("700") == 0) {

            specialPlacement = "star-700";
        } else if (std::string(iconSprName).compare("stars_spr.png"_spr) == 0 && unlockList[i + 1]->numberString.compare("7000") == 0) {

            specialPlacement = "star-7000";
        } else if (std::string(iconSprName).compare("diamonds_spr.png"_spr) == 0 && unlockList[i + 1]->numberString.compare("2500") == 0) {

            specialPlacement = "diamond-2500";
        } else if (std::string(iconSprName).compare("completed_demons_spr.png"_spr) == 0 && unlockList[i + 1]->numberString.compare("60") == 0) {

            specialPlacement = "demon-60";
        }
        
        progressPlaced = util->placeUnlockable(this, value, currentProgressText, 
                                            progressPlaced, tierContainer, tierMenu, 
                                            unlockList[i], unlockList[i + 1], 
                                            unlockList[startIdx], unlockList[endIdx], specialPlacement);
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
    refreshSpr->setID("Refresh-Sprite");
    refreshSpr->setScale(.75f);

    CCMenuItemSpriteExtra* refreshButton;
    CCMenuItemSpriteExtra* supportMeButton;
    CCLabelBMFont* refreshText = CCLabelBMFont::create("Refresh", "bigFont.fnt");
    if (std::string(iconSprName).compare("friends_spr.png"_spr) == 0) {

        refreshButton = CCMenuItemSpriteExtra::create(
            refreshSpr,
            this,
            menu_selector(UnlockPage::refreshFriends)
        );
    } else if (std::string(iconSprName).compare("most_liked_spr.png"_spr) == 0) {

        CCSprite* supportSpr = CCSprite::createWithSpriteFrameName("GJ_plainBtn_001.png");
        supportSpr->setID("Support-Plain-Sprite");
        supportSpr->setScale(0.99f);

        CCSprite* supportLikeSpr = CCSprite::createWithSpriteFrameName("GJ_likesIcon_001.png");
        supportLikeSpr->setID("Support-Like-Sprite");
        supportLikeSpr->setPosition({23.5f, 31});
        supportLikeSpr->setScale(0.7f);
        supportSpr->addChild(supportLikeSpr);

        auto supportText1 = CCLabelBMFont::create("Support", "bigFont.fnt");
        supportText1->setID("Support-Test-1");
        supportText1->setPosition({23.5f, 19});
        supportText1->setScale(0.225f);
        supportSpr->addChild(supportText1);

        auto supportText2 = CCLabelBMFont::create("Me", "bigFont.fnt");
        supportText2->setID("Support-Test-2");
        supportText2->setPosition({23.5f, 12});
        supportText2->setScale(0.225f);
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

        supportMeButton->setID("Support-Button");
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
    refreshText->setID("Refresh-Text");
    refreshText->setAnchorPoint({.5f, .5f});
    refreshText->setScale(.4f);
    refreshText->setPosition({270, 275});
    refreshButton->setID("Refresh-Button");
    refreshButton->setAnchorPoint({.5f, .5f});
    refreshButton->setPosition({270, 245});

    buttonMenu->addChild(refreshText);
    buttonMenu->addChild(refreshButton);
}

void UnlockPage::openSupportMeLevel(CCObject* sender) {

    int id = 122518349; //Iris by me: 114471227, my niece's level: 122518349
    GameLevelManager::get()->m_levelManagerDelegate = MyLevelDownloadDelegate::get();
    GameLevelManager::sharedState()->getOnlineLevels(GJSearchObject::create(SearchType::Search, std::to_string(id)));
}

void UnlockPage::refreshFriends(CCObject* sender) {

    int num = processFriendCount();
    util->updatePage(num, pageNode, util->friendsUnlockDataList, iconSprName);
    makeInfoPopup("Friends");
}

void UnlockPage::refreshMaxLikes(CCObject* sender) {

    requestMostLiked(0);
}

void UnlockPage::refreshCreatorPoints(CCObject* sender) {

    requestCreatorPoints();
}

void UnlockPage::makeInfoPopup(std::string type) {

    if (type.compare("Friends") == 0) {

        FLAlertLayer::create(
            "Refreshing",
            "<co>If this is the first time you pressed this button</c>, <cy>press this button again</c>. Then your 'Friends' will be refreshed.",
            "Ok"
        )->show();
    } else if (type.compare("Bad Response") == 0) {

        FLAlertLayer::create(
            "Web Request Failed",
            "The <cl>web requests</c> <cr>FAILED</c>. Please check your internet connect.",
            "Ok"
        )->show();
    } else if (type.compare("No Response") == 0) {

        FLAlertLayer::create(
            "Web Request Failed",
            "The <cl>web requests</c> <cr>FAILED</c>. This is likely because you do not have any public levels.",
            "Ok"
        )->show();
    } else if (type.compare("Unexpected") == 0) {

        FLAlertLayer::create(
            "Error",
            "An unexpected error has occured. The <cl>web requests</c> has been <cr>CANCELLED</c>.",
            "Ok"
        )->show();
    } else if (type.compare("Rate Limit") == 0) {  

        FLAlertLayer::create(
            "Rate Limit",
            "You have been <cr>API Rate Limited</c>. Please try again later (~1 hour)",
            "Ok"
        )->show();
    } else {

        FLAlertLayer::create(
            "Refresh Complete",
            fmt::format("Your '{}' statistic has been fetched via <cl>web requests</c>. <cr>DO NOT SPAM THIS BUTTON!</c> That will result in an <cr>API Rate Limit</c>.", type),
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

    Mod::get()->setSavedValue<int>(fmt::format("friends-{}", userId), friendCount);

    return friendCount;
}


void UnlockPage::requestMostLiked(int page) {

    log::info("Entered web request method");

    web::WebRequest req;
    req.userAgent("");
    req.bodyString(fmt::format("secret=Wmfd2893gb7&type=5&page={}&str={}", page, userId));

    req.onProgress([page](const web::WebProgress& progress) {
    if (auto p = progress.downloadProgress()) {
        log::info("Fetching page {} in progress... {}%", page, int(*p * 100));
    }
    });

    mostLikedListener.spawn(
        req.post("http://www.boomlings.com/database/getGJLevels21.php"), [this, page](web::WebResponse value) mutable {

            if (value.cancelled() || value.error()) {
                log::warn("Request failed or cancelled (code {})", value.code());
                makeInfoPopup("Unexpected");
                return;
            }

            auto result = value.string();
            if (!result) {
                log::error("Failed to decode response: {}", result.unwrapErr());
                makeInfoPopup("Bad Response");
                return;
            }

            auto str = result.unwrap();
            log::info("Response for Page {}: {}", page, str);

            if (str == "Curl failed: Couldn't resolve host name") {

                log::warn("No levels found!");
                makeInfoPopup("Bad Response");
                return;
            } else if (str == "-1") {

                log::warn("No levels found!");
                makeInfoPopup("No Response");
                return;   
            } else if (value.code() == 1015) {

                log::warn("Rate Limit!");
                makeInfoPopup("Rate Limit");
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

                util->updatePage(maxLikes, pageNode, util->likesOnYourLevelUnlockDataList, iconSprName);

                makeInfoPopup("Most Liked");
            }
        }
    );
}

/*
void UnlockPage::requestMostLiked(int page) {

    log::info("Entered web request method");

    // Send initial request to get total levels from server

    mostLikedListener.bind([this, page](web::WebTask::Event* e) mutable {

        if (web::WebResponse* value = e->getValue()) {
            auto str = value->string().unwrap();
            log::info("Response for Page {}: {}", page, str);

            if (str == "Curl failed: Couldn't resolve host name") {

                log::warn("No levels found!");
                makeInfoPopup("Bad Response");
                return;
            } else if (str == "-1") {

                log::warn("No levels found!");
                makeInfoPopup("No Response");
                return;   
            } else if (value->code() == 1015) {

                log::warn("Rate Limit!");
                makeInfoPopup("Rate Limit");
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

                util->updatePage(maxLikes, pageNode, util->likesOnYourLevelUnlockDataList, iconSprName);

                makeInfoPopup("Most Liked");
            }

        } else if (e->getProgress()) {
            log::info("Fetching page {} in progress...", page);

        } else if (e->isCancelled()) {
            log::warn("Request for page {} was cancelled.", page);
            makeInfoPopup("Unexpected");
        }
    });

    // Send request for the given page
    auto req = web::WebRequest().userAgent("").bodyString(fmt::format("secret=Wmfd2893gb7&type=5&page={}&str={}", page, userId));
    auto task = req.post("http://www.boomlings.com/database/getGJLevels21.php");
    mostLikedListener.setFilter(task);
} */

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

    log::info("Requesting creator points");

    web::WebRequest req;
    req.userAgent("");
    req.bodyString(fmt::format("secret=Wmfd2893gb7&targetAccountID={}", accountId));

    // Optional progress logging
    req.onProgress([](const web::WebProgress& progress) {
        if (auto p = progress.downloadProgress()) {
            log::info("Creator points request progress: {}%", int(*p * 100));
        }
    });

    creatorPointsListener.spawn(
        req.post("http://www.boomlings.com/database/getGJUserInfo20.php"),
        [this](web::WebResponse value) {

            if (value.cancelled() || value.error()) {
                log::warn("Request failed or cancelled (code {})", value.code());
                makeInfoPopup("Unexpected");
                return;
            }

            auto result = value.string();
            if (!result) {
                log::error("Failed to decode response: {}", result.unwrapErr());
                makeInfoPopup("Bad Response");
                return;
            }

            auto str = result.unwrap();
            log::info("Response: {}", str);

            // server-side errors
            if (str == "Curl failed: Couldn't resolve host name") {
                log::warn("No creator points found!");
                makeInfoPopup("Bad Response");
                return;
            }
            else if (value.code() == 1015) {
                log::warn("Rate Limit!");
                makeInfoPopup("Rate Limit");
                return;
            }

            // parse creator points
            int creatorPoints = findCreatorPoints(str);
            log::info("Extracted Creator Points: {}", creatorPoints);

            Mod::get()->setSavedValue<int>(
                fmt::format("creator-points-{}", accountId),
                creatorPoints
            );

            util->updatePage(creatorPoints, pageNode, util->creatorPointsUnlockDataList, iconSprName);

            makeInfoPopup("Creator Points");
        }
    );
}
/*
void UnlockPage::requestCreatorPoints() {

    creatorPointsListener.bind([this](web::WebTask::Event* e) {

        if (web::WebResponse* value = e->getValue()) {
            auto str = value->string().unwrap();        //I totally check this value before unwrapping :)
            log::info("Response: {}", str);

            if (str == "Curl failed: Couldn't resolve host name") {

                log::warn("No creator points found!");
                makeInfoPopup("Bad Response");
                return;
            } else if (value->code() == 1015) {

                log::warn("Rate Limit!");
                makeInfoPopup("Rate Limit");
                return;
            }

            int creatorPoints = findCreatorPoints(str);
            log::info("Extracted Creator Points: {}", creatorPoints);

            Mod::get()->setSavedValue<int>(fmt::format("creator-points-{}", accountId), creatorPoints);

            util->updatePage(creatorPoints, pageNode, util->creatorPointsUnlockDataList, iconSprName);

            makeInfoPopup("Creator Points");

        } else if (web::WebProgress* progress = e->getProgress()) {
            log::info("{}", "progress");
        } else if (e->isCancelled()) {
            log::info("{}", "fail");
            makeInfoPopup("Unexpected");
        }
    });

    auto req = web::WebRequest().userAgent("").bodyString(fmt::format("secret=Wmfd2893gb7&targetAccountID={}", accountId));
    auto task = req.post("http://www.boomlings.com/database/getGJUserInfo20.php");
    creatorPointsListener.setFilter(task);
} */

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