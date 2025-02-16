#include "UnlockProgressionPopup.hpp"

UnlockProgressionPopup* UnlockProgressionPopup::create(std::string const& text) {

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    auto ret = new UnlockProgressionPopup();
    ret->setID("Popup-Layer");
    if (ret->initAnchored(466.58f, 256, text)) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

UnlockProgressionPopup::~UnlockProgressionPopup() {

    if (m_pages) {
        m_pages->release();
    }
}

bool UnlockProgressionPopup::setup(std::string const& text) {

    util = Utilities::getInstance();

    auto winSize = CCDirector::sharedDirector()->getWinSize();
    m_pageWidth = 466.58f;

    m_pageContainer = CCNode::create();
    m_pageContainer->setID("Progression-Container");
    m_pageContainer->setPosition({0, 0});
    m_buttonMenu->addChild(m_pageContainer);
    m_buttonMenu->setID("Mod Container");

    m_pages = CCArray::create();
    m_pages->retain();

    createBackgroundUI();

    getAllStats();

    auto showStarPage = Mod::get()->getSettingValue<bool>("show-star-page");
    auto showMoonPage = Mod::get()->getSettingValue<bool>("show-moon-page");
    auto showSecretCoinPage = Mod::get()->getSettingValue<bool>("show-secret-coin-page");
    auto showUserCoinPage = Mod::get()->getSettingValue<bool>("show-user-coin-page");
    auto showDiamondPage = Mod::get()->getSettingValue<bool>("show-diamond-page");
    auto showJumpPage = Mod::get()->getSettingValue<bool>("show-jump-page");
    auto showAttemptPage = Mod::get()->getSettingValue<bool>("show-attempts-page");
    auto showDestroyedPlayerPage = Mod::get()->getSettingValue<bool>("show-destroyed-players-page");
    auto showFriendPage = Mod::get()->getSettingValue<bool>("show-friend-page");
    auto showFollowCreatorPage = Mod::get()->getSettingValue<bool>("show-follow-creator-page");
    auto showLikeDislikePage = Mod::get()->getSettingValue<bool>("show-like-dislike-page");
    auto showRateStarsPage = Mod::get()->getSettingValue<bool>("show-rate-stars-page");
    auto showInsanePage = Mod::get()->getSettingValue<bool>("show-insane-page");
    auto showDemonPage = Mod::get()->getSettingValue<bool>("show-demon-page");
    auto showOnlinePage = Mod::get()->getSettingValue<bool>("show-online-page");
    auto showDailyPage = Mod::get()->getSettingValue<bool>("show-daily-page");
    auto showMapPackPage = Mod::get()->getSettingValue<bool>("show-map-pack-page");
    auto showGauntletPage = Mod::get()->getSettingValue<bool>("show-gauntlet-page");
    auto showListPage = Mod::get()->getSettingValue<bool>("show-list-page");
    auto showMostLikedPage = Mod::get()->getSettingValue<bool>("show-most-liked-level-page");
    auto showRatedLevelPage = Mod::get()->getSettingValue<bool>("show-rated-level-page");

    std::vector<std::string> modSettingKeys = {
        "show-star-page", "show-moon-page", "show-secret-coin-page", "show-user-coin-page",
        "show-diamond-page", "show-jump-page", "show-attempts-page", "show-destroyed-players-page",
        "show-friend-page", "show-follow-creator-page", "show-like-dislike-page", "show-rate-stars-page",
        "show-insane-page", "show-demon-page", "show-online-page", "show-daily-page",
        "show-map-pack-page", "show-gauntlet-page", "show-list-page", "show-most-liked-level-page", "show-rated-level-page"
    };

    int disabledSettings = 0;
    for (const auto& key : modSettingKeys) {
        if (!Mod::get()->getSettingValue<bool>(key)) {
            ++disabledSettings;
        }
    }
    m_totalPages = 21 - disabledSettings;

    //create all progression pages

    bool disableArrows = false;

    if (! (showStarPage || showMoonPage || showSecretCoinPage || showUserCoinPage || showDiamondPage || showJumpPage
        || showAttemptPage || showDestroyedPlayerPage || showFriendPage || showFollowCreatorPage || showLikeDislikePage
        || showRateStarsPage || showInsanePage || showDemonPage && showOnlinePage || showDailyPage || showMapPackPage
        || showGauntletPage || showMostLikedPage || showRatedLevelPage))  {

        auto disableText = CCLabelBMFont::create("You have disabled every page in the mod. Please enable a page to see something.", "bigFont-uhd.fnt");
        disableText->setScale(0.3f);
        disableText->setPosition({233, 130});
        m_pageContainer->addChild(disableText);
        disableArrows = true;
    }


    if (showStarPage) {
        
        UnlockPage* starPage = new UnlockPage(this, util->starUnlockDataList, "stars_spr.png"_spr);
        CCNode* starPageContainer = starPage->createPage(util->m_playerStats.stars);
        starPageContainer->setID("Stars-Progression");
        starPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(starPageContainer);
        m_pages->addObject(starPageContainer);
        starPageContainer->setVisible(true);
    }

    if (showMoonPage) {

        UnlockPage* moonPage = new UnlockPage(this, util->moonUnlockDataList, "moons_spr.png"_spr);
        CCNode* moonPageContainer = moonPage->createPage(util->m_playerStats.moons);
        moonPageContainer->setID("Moons-Progression");
        moonPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(moonPageContainer);
        m_pages->addObject(moonPageContainer);
        moonPageContainer->setVisible(false);
    }


    if (showSecretCoinPage) {

        UnlockPage* secretCoinsPage = new UnlockPage(this, util->secretCoinUnlockDataList, "secret_coins_spr.png"_spr);
        CCNode* secretCoinsPageContainer = secretCoinsPage->createPage(util->m_playerStats.secretCoins);
        secretCoinsPageContainer->setID("Secret-Coin-Progression");
        secretCoinsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(secretCoinsPageContainer);
        m_pages->addObject(secretCoinsPageContainer);
        secretCoinsPageContainer->setVisible(false);
    }

    if (showUserCoinPage) {

        UnlockPage* userCoinsPage = new UnlockPage(this, util->userCoinUnlockDataList, "user_coins_spr.png"_spr);
        CCNode* userCoinsPageContainer = userCoinsPage->createPage(util->m_playerStats.userCoins);
        userCoinsPageContainer->setID("User-Coin-Progression");
        userCoinsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(userCoinsPageContainer);
        m_pages->addObject(userCoinsPageContainer);
        userCoinsPageContainer->setVisible(false);
    }


    if (showDiamondPage) {

        UnlockPage* diamondsPage = new UnlockPage(this, util->diamondUnlockDataList, "diamonds_spr.png"_spr);
        CCNode* diamondsPageContainer = diamondsPage->createPage(util->m_playerStats.diamonds);
        diamondsPageContainer->setID("Diamond-Progression");
        diamondsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(diamondsPageContainer);
        m_pages->addObject(diamondsPageContainer);
        diamondsPageContainer->setVisible(false);
    }

    if (showJumpPage) {

        UnlockPage* jumpPage = new UnlockPage(this, util->jumpsUnlockDataList, "jumps_spr.png"_spr);
        CCNode* jumpPageContainer = jumpPage->createPage(util->m_playerStats.jumps);
        jumpPageContainer->setID("Jump-Progression");
        jumpPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(jumpPageContainer);
        m_pages->addObject(jumpPageContainer);
        jumpPageContainer->setVisible(false);
    }

    if (showAttemptPage) {

        UnlockPage* attemptPage = new UnlockPage(this, util->attemptsUnlockDataList, "attempts_spr.png"_spr);
        CCNode* attemptPageContainer = attemptPage->createPage(util->m_playerStats.attempts);
        attemptPageContainer->setID("Attempt-Progression");
        attemptPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(attemptPageContainer);
        m_pages->addObject(attemptPageContainer);
        attemptPageContainer->setVisible(false);
    }

    if (showDestroyedPlayerPage) {

        UnlockPage* destroyedPlayersPage = new UnlockPage(this, util->destroyedPlayersUnlockDataList, "destroyed_players_spr.png"_spr);
        CCNode* destroyedPlayersPageContainer = destroyedPlayersPage->createPage(util->m_playerStats.destoryedPlayers);
        destroyedPlayersPageContainer->setID("Destroyed-Players-Progression");
        destroyedPlayersPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(destroyedPlayersPageContainer);
        m_pages->addObject(destroyedPlayersPageContainer);
        destroyedPlayersPageContainer->setVisible(false);
    }

    if (showFriendPage) {

        UnlockPage* friendsPage = new UnlockPage(this, util->friendsUnlockDataList, "friends_spr.png"_spr);
        CCNode* friendsPageContainer = friendsPage->createPage(util->m_playerStats.friends);
        friendsPageContainer->setID("Friend-Progression");
        friendsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(friendsPageContainer);
        m_pages->addObject(friendsPageContainer);
        friendsPageContainer->setVisible(false);
    }

    if (showFollowCreatorPage) {

        UnlockPage* followCreatorsPage = new UnlockPage(this, util->followCreatorsUnlockDataList, "follow_creators_spr.png"_spr);
        CCNode* followCreatorsPageContainer = followCreatorsPage->createPage(util->m_playerStats.followedCreators);
        followCreatorsPageContainer->setID("Followed-Creators-Progression");
        followCreatorsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(followCreatorsPageContainer);
        m_pages->addObject(followCreatorsPageContainer);
        followCreatorsPageContainer->setVisible(false);
    }


    if (showLikeDislikePage) {

        UnlockPage* likeDislikeLevelsPage = new UnlockPage(this, util->likeDislikeUnlockDataList, "like_dislike_spr.png"_spr);
        CCNode* likeDislikeLevelsPageContainer = likeDislikeLevelsPage->createPage(util->m_playerStats.likesAndDislikes);
        likeDislikeLevelsPageContainer->setID("Like-Dislike-Progression");
        likeDislikeLevelsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(likeDislikeLevelsPageContainer);
        m_pages->addObject(likeDislikeLevelsPageContainer);
        likeDislikeLevelsPageContainer->setVisible(false);
    }

    if (showRateStarsPage) {

        UnlockPage* rateStarsOfLevelsPage = new UnlockPage(this, util->rateStarsUnlockDataList, "rate_stars_spr.png"_spr);
        CCNode* rateStarsOfLevelsPageContainer = rateStarsOfLevelsPage->createPage(util->m_playerStats.rateStarsOnLevels);
        rateStarsOfLevelsPageContainer->setID("Rate-Stars-Progression");
        rateStarsOfLevelsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(rateStarsOfLevelsPageContainer);
        m_pages->addObject(rateStarsOfLevelsPageContainer);
        rateStarsOfLevelsPageContainer->setVisible(false);
    }

    if (showInsanePage) {

        UnlockPage* insaneLevelsPage = new UnlockPage(this, util->completedInsaneUnlockDataList, "completed_insanes_spr.png"_spr);
        CCNode* insaneLevelsPageContainer = insaneLevelsPage->createPage(util->m_playerStats.completedInsanes);
        insaneLevelsPageContainer->setID("Completed-Insanes-Progression");
        insaneLevelsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(insaneLevelsPageContainer);
        m_pages->addObject(insaneLevelsPageContainer);
        insaneLevelsPageContainer->setVisible(false);
    }

    if (showDemonPage) {

        UnlockPage* demonLevelsPage = new UnlockPage(this, util->completedDemonUnlockDataList, "completed_demons_spr.png"_spr);
        CCNode* demonLevelsPageContainer = demonLevelsPage->createPage(util->m_playerStats.completedDemons);
        demonLevelsPageContainer->setID("Completed-Demons-Progression");
        demonLevelsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(demonLevelsPageContainer);
        m_pages->addObject(demonLevelsPageContainer);
        demonLevelsPageContainer->setVisible(false);
    }

    if (showOnlinePage) {

        UnlockPage* completedOnlineLevelsPage = new UnlockPage(this, util->completedOnlineUnlockDataList, "completed_online_spr.png"_spr);
        CCNode* completedOnlineLevelsPageContainer = completedOnlineLevelsPage->createPage(util->m_playerStats.completedOnline);
        completedOnlineLevelsPageContainer->setID("Completed-Online-Progression");
        completedOnlineLevelsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(completedOnlineLevelsPageContainer);
        m_pages->addObject(completedOnlineLevelsPageContainer);
        completedOnlineLevelsPageContainer->setVisible(false);
    }

    if (showDailyPage) {

        UnlockPage* completedDailyLevelsPage = new UnlockPage(this, util->completedDailyUnlockDataList, "completed_daily_spr.png"_spr);
        CCNode* completedDailyLevelsPageContainer = completedDailyLevelsPage->createPage(util->m_playerStats.completedDaily);
        completedDailyLevelsPageContainer->setID("Completed-Daily-Progression");
        completedDailyLevelsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(completedDailyLevelsPageContainer);
        m_pages->addObject(completedDailyLevelsPageContainer);
        completedDailyLevelsPageContainer->setVisible(false);
    }


    if (showMapPackPage) {

        UnlockPage* completedMapPacksPage = new UnlockPage(this, util->completedMapPacksUnlockDataList, "completed_map_packs_spr.png"_spr);
        CCNode* completedMapPacksPageContainer = completedMapPacksPage->createPage(util->m_playerStats.completedMapPacks);
        completedMapPacksPageContainer->setID("Completed-Map-Packs-Progression");
        completedMapPacksPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(completedMapPacksPageContainer);
        m_pages->addObject(completedMapPacksPageContainer);
        completedMapPacksPageContainer->setVisible(false);
    }

    if (showGauntletPage) {

        UnlockPage* completedGauntletsPage = new UnlockPage(this, util->completedGauntletsUnlockDataList, "completed_gauntlets_spr.png"_spr);
        CCNode* completedGauntletsPageContainer = completedGauntletsPage->createPage(util->m_playerStats.completedGauntlets);
        completedGauntletsPageContainer->setID("Completed-Gauntlets-Progression");
        completedGauntletsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(completedGauntletsPageContainer);
        m_pages->addObject(completedGauntletsPageContainer);
        completedGauntletsPageContainer->setVisible(false);
    }

    if (showListPage) {

        UnlockPage* completedListsPage = new UnlockPage(this, util->completedListsUnlockDataList, "completed_lists_spr.png"_spr);
        CCNode* completedListsPageContainer = completedListsPage->createPage(util->m_playerStats.completedLists);
        completedListsPageContainer->setID("Completed-Lists-Progression");
        completedListsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(completedListsPageContainer);
        m_pages->addObject(completedListsPageContainer);
        completedListsPageContainer->setVisible(false);
    }

    if (showMostLikedPage) {

        UnlockPage* likesOnYourLevelPage = new UnlockPage(this, util->likesOnYourLevelUnlockDataList, "most_liked_spr.png"_spr);
        CCNode* likesOnYourLevelPageContainer = likesOnYourLevelPage->createPage(util->m_playerStats.maxLikes);
        likesOnYourLevelPageContainer->setID("Most-Liked-Progression");
        likesOnYourLevelPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(likesOnYourLevelPageContainer);
        m_pages->addObject(likesOnYourLevelPageContainer);
        likesOnYourLevelPageContainer->setVisible(false);
    }

    if (showRatedLevelPage) {

        UnlockPage* ratedLevelPage = new UnlockPage(this, util->creatorPointsUnlockDataList, "creator_points_spr.png"_spr);
        CCNode* ratedLevelPageContainer = ratedLevelPage->createPage(util->m_playerStats.ratedLevels);
        ratedLevelPageContainer->setID("Creator-Point-Progression");
        ratedLevelPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(ratedLevelPageContainer);
        m_pages->addObject(ratedLevelPageContainer);
        ratedLevelPageContainer->setVisible(false);
    }

    if (! disableArrows) {

        if (m_totalPages != 1) {
            createNavigationButtons();
        }
        createBottomNavigationButtons();
    }

    setupInitialPage();

    return true;
}

void UnlockProgressionPopup::createBackgroundUI() {

    auto titleSpr = CCSprite::createWithSpriteFrameName("betterUnlockProgressionTitle.png"_spr);
    titleSpr->setID("Title-Sprite");
    titleSpr->setPosition({75, 25});
    titleSpr->setScale(.4f);
    m_buttonMenu->addChild(titleSpr);
    
    auto creatorTitle = CCLabelBMFont::create("By GlowRock", "goldFont-uhd.fnt");
    creatorTitle->setID("Water-Mark-Label");
    creatorTitle->setScale(.4f);
    auto creatorTitleButton = CCMenuItemSpriteExtra::create(
        creatorTitle,
        this,
        menu_selector(UnlockProgressionPopup::openProfile)
    );
    creatorTitleButton->setID("Water-Mark-Button");
    creatorTitleButton->setPosition({373, 13});
    m_buttonMenu->addChild(creatorTitleButton);

    auto topLeftCornerSpr = CCSprite::createWithSpriteFrameName("dailyLevelCorner_001.png");
    topLeftCornerSpr->setID("Corner-Sprite");
    topLeftCornerSpr->setAnchorPoint({0, 0});
    topLeftCornerSpr->setFlipY(true);
    auto topLeftNode = CCNode::create();
    topLeftNode->setID("Corner-Node");
    topLeftNode->setPosition({0, 207});
    topLeftNode->setZOrder(-1);
    topLeftNode->addChild(topLeftCornerSpr);
    m_buttonMenu->addChild(topLeftNode);


    auto bottomRightCornerSpr = CCSprite::createWithSpriteFrameName("dailyLevelCorner_001.png");
    bottomRightCornerSpr->setID("Corner-Sprite");
    bottomRightCornerSpr->setAnchorPoint({0, 0});
    bottomRightCornerSpr->setFlipX(true);
    auto bottomRightNode = CCNode::create();
    bottomRightNode->setID("Corner-Node");
    bottomRightNode->setPosition({417.5f, 0});
    bottomRightNode->setZOrder(-1);
    bottomRightNode->addChild(bottomRightCornerSpr);
    m_buttonMenu->addChild(bottomRightNode);

    auto topRightCornerSpr = CCSprite::createWithSpriteFrameName("dailyLevelCorner_001.png");
    topRightCornerSpr->setID("Corner-Sprite");
    topRightCornerSpr->setAnchorPoint({0, 0});
    topRightCornerSpr->setFlipY(true);
    topRightCornerSpr->setFlipX(true);
    auto topRightNode = CCNode::create();
    topRightNode->setID("Corner-Node");
    topRightNode->setPosition({417.5f, 207});
    topRightNode->setZOrder(-1);
    topRightNode->addChild(topRightCornerSpr);
    m_buttonMenu->addChild(topRightNode);
}

void UnlockProgressionPopup::createNavigationButtons() {

    auto winSize = CCDirector::sharedDirector()->getWinSize();
    float popupHeight = 256;

    auto prevArrowSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    prevArrowSpr->setID("Left-Arrow-Sprite");
    auto nextArrowSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    prevArrowSpr->setID("Right-Arrow-Sprite");
    nextArrowSpr->setFlipX(true);

    m_prevButton = CCMenuItemSpriteExtra::create(
        prevArrowSpr,
        this,
        menu_selector(UnlockProgressionPopup::onPrevPage)
    );
    m_prevButton->setPosition({winSize.width * -0.05f + 2, popupHeight * 0.5f});
    m_prevButton->setID("Left-Arrow-Button");
    m_buttonMenu->addChild(m_prevButton);

    m_nextButton = CCMenuItemSpriteExtra::create(
        nextArrowSpr,
        this,
        menu_selector(UnlockProgressionPopup::onNextPage)
    );
    m_nextButton->setPosition({winSize.width * 0.85f + 9.35f, popupHeight * 0.5f});
    m_nextButton->setID("Right-Arrow-Button");
    m_buttonMenu->addChild(m_nextButton);
}

void UnlockProgressionPopup::createBottomNavigationButtons() {

    float popupHeight = 256;

    auto bgSpr = CCSprite::createWithSpriteFrameName("whiteSquare20_001.png");
    bgSpr->setID("Dim-Sprite");
    bgSpr->setPosition({285, 150});
    bgSpr->setScale(200.f);
    bgSpr->setZOrder(-10);
    bgSpr->setOpacity(100);
    bgSpr->setColor(ccc3(0, 0, 0));
    this->addChild(bgSpr);

    auto navContainer = CCMenu::create();
    navContainer->setID("Page-Navigation");



    navContainer->setPosition({284.5f, 160});


    navDotOnSpr = CCSprite::createWithSpriteFrameName("gj_navDotBtn_on_001.png");
    navDotOnSpr->setID("Page-Selected");
    navDotOffSpr = CCSprite::createWithSpriteFrameName("gj_navDotBtn_off_001.png");
    navDotOffSpr->setID("Page-Deselected");

    const float y = -175;
    const float spacing = 24;

    float totalWidth = m_totalPages * spacing;

    //auto winSize = CCDirector::sharedDirector()->getWinSize();
    //log::info("width: {}", winSize.width);

    //float offset = (float) winSize.width / -11.1568f;

    float startX = -51 - (totalWidth / 2) + (spacing / 2);

    for (int i = 0; i < m_totalPages; ++i) {
        auto button = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName(i == 0 ? "gj_navDotBtn_on_001.png" : "gj_navDotBtn_off_001.png"),
            this,
            menu_selector(UnlockProgressionPopup::onPageBtn)
        );
        button->setID("Page-Selector");
        button->setTag(i);
        button->setPosition({startX + i * spacing, y});
        navDots.push_back(button);
        navContainer->addChild(button);
    }

    m_buttonMenu->addChild(navContainer);
}

void UnlockProgressionPopup::openProfile(CCObject*) {

    this->addChild(ProfilePage::create(7472440, false));
}

void UnlockProgressionPopup::onPageBtn(CCObject* sender) {

    auto button = static_cast<CCMenuItemSpriteExtra*>(sender);
    m_currentPage = button->getTag();
    updatePageVisibility();
}

void UnlockProgressionPopup::setupInitialPage() {

    m_currentPage = 0;

    // Find the first enabled page
    for (int i = 0; i < m_pages->count(); ++i) {
        if (isPageEnabled(i)) {
            m_currentPage = i;
            break;
        }
    }

    updatePageVisibility();
}

bool UnlockProgressionPopup::isPageEnabled(int index) {

    if (index < 0 || index >= m_pages->count()) {
        return false;
    }
    auto page = static_cast<CCNode*>(m_pages->objectAtIndex(index));
    return page != nullptr && page->isVisible();
}

void UnlockProgressionPopup::onPrevPage(CCObject*) {

    m_currentPage = (m_currentPage == 0) ? m_totalPages - 1 : m_currentPage - 1;
    updatePageVisibility();
}

void UnlockProgressionPopup::onNextPage(CCObject*) {

    m_currentPage = (m_currentPage == m_totalPages - 1) ? 0 : m_currentPage + 1;
    updatePageVisibility();
}

void UnlockProgressionPopup::updatePageVisibility() {

    /*
        friends page isn't loaded initially because of retrival method
        friend count requires a second call to get the real value
        theres another way to fix this but lazy coding wins!
        runtime is *slightly* worse because of this hotfix
        I may fix this in the future
    
    if (m_playerStats.friends == -1 && showFriendPage) {
        m_playerStats.friends = processFriends.fetchFriendCount();
        friendsPage->updateFriendCount(m_playerStats.friends);
    } */
    if (m_pages->count() == 0) {
        return;
    }
    if (m_currentPage >= m_pages->count()) {
        m_currentPage = 0;
    }
    for (int i = 0; i < m_pages->count(); ++i) {
        auto page = static_cast<CCNode*>(m_pages->objectAtIndex(i));
        page->setVisible(i == m_currentPage);
    }
    updateButtonVisibility();
}

void UnlockProgressionPopup::updateButtonVisibility() {

    for (int i = 0; i < navDots.size(); ++i) {
        auto dotSpr = CCSprite::createWithSpriteFrameName(
            i == m_currentPage ? "gj_navDotBtn_on_001.png" : "gj_navDotBtn_off_001.png"
        );
        navDots[i]->setNormalImage(dotSpr);
    }
}

void UnlockProgressionPopup::getAllStats() {

    gameStatsManager = GameStatsManager::sharedState();
    gameLevelManager = GameLevelManager::sharedState();

    int userId = util->gameManager->m_playerUserID;
    int accountId = GJAccountManager::sharedState()->m_accountID;

    util->m_playerStats.stars = gameStatsManager->getStat("6");
    util->m_playerStats.moons = gameStatsManager->getStat("28");
    util->m_playerStats.secretCoins = gameStatsManager->getStat("8");
    util->m_playerStats.userCoins = gameStatsManager->getStat("12");
    util->m_playerStats.diamonds = gameStatsManager->getStat("13");
    util->m_playerStats.jumps = gameStatsManager->getStat("1");
    util->m_playerStats.attempts = gameStatsManager->getStat("2");
    util->m_playerStats.destoryedPlayers = gameStatsManager->getStat("9");
    util->m_playerStats.friends = Mod::get()->getSavedValue<int>(fmt::format("friends-{}", userId));
    util->m_playerStats.followedCreators = gameLevelManager->m_followedCreators->count();
    util->m_playerStats.likesAndDislikes = gameStatsManager->getStat("10");
    util->m_playerStats.rateStarsOnLevels = gameStatsManager->getStat("11");
    util->m_playerStats.completedInsanes = gameStatsManager->getStat("42");
    util->m_playerStats.completedDemons = gameStatsManager->getStat("5");
    util->m_playerStats.completedOnline = gameStatsManager->getStat("4");
    util->m_playerStats.completedDaily = gameStatsManager->getStat("15");
    util->m_playerStats.completedMapPacks = gameStatsManager->getStat("7");
    util->m_playerStats.completedGauntlets = gameStatsManager->getStat("40");
    util->m_playerStats.completedLists = gameStatsManager->getStat("41");
    util->m_playerStats.maxLikes = Mod::get()->getSavedValue<int>(fmt::format("most-liked-{}", userId));
    util->m_playerStats.ratedLevels = Mod::get()->getSavedValue<int>(fmt::format("creator-points-{}", accountId));
}