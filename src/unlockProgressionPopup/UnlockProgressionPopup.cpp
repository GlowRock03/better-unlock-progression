#include "UnlockProgressionPopup.hpp"

UnlockProgressionPopup* UnlockProgressionPopup::create(std::string const& text) {

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    auto ret = new UnlockProgressionPopup();
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
    m_pageContainer->setPosition({0, 0});
    m_buttonMenu->addChild(m_pageContainer);

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
    showFriendPage = Mod::get()->getSettingValue<bool>("show-friend-page");                             //has to be a class member due to friend refresh bug
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
        CCNode* starPageContainer = starPage->createPage(m_playerStats.stars);
        starPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(starPageContainer);
        m_pages->addObject(starPageContainer);
        starPageContainer->setVisible(true);
    }

    if (showMoonPage) {

        UnlockPage* moonPage = new UnlockPage(this, util->moonUnlockDataList, "moons_spr.png"_spr);
        CCNode* moonPageContainer = moonPage->createPage(m_playerStats.moons);
        moonPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(moonPageContainer);
        m_pages->addObject(moonPageContainer);
        moonPageContainer->setVisible(false);
    }


    if (showSecretCoinPage) {

        UnlockPage* secretCoinsPage = new UnlockPage(this, util->secretCoinUnlockDataList, "secret_coins_spr.png"_spr);
        CCNode* secretCoinsPageContainer = secretCoinsPage->createPage(m_playerStats.secretCoins);
        secretCoinsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(secretCoinsPageContainer);
        m_pages->addObject(secretCoinsPageContainer);
        secretCoinsPageContainer->setVisible(false);
    }

    if (showUserCoinPage) {

        UnlockPage* userCoinsPage = new UnlockPage(this, util->userCoinUnlockDataList, "user_coins_spr.png"_spr);
        CCNode* userCoinsPageContainer = userCoinsPage->createPage(m_playerStats.userCoins);
        userCoinsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(userCoinsPageContainer);
        m_pages->addObject(userCoinsPageContainer);
        userCoinsPageContainer->setVisible(false);
    }


    if (showDiamondPage) {

        UnlockPage* diamondsPage = new UnlockPage(this, util->diamondUnlockDataList, "diamonds_spr.png"_spr);
        CCNode* diamondsPageContainer = diamondsPage->createPage(m_playerStats.diamonds);
        diamondsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(diamondsPageContainer);
        m_pages->addObject(diamondsPageContainer);
        diamondsPageContainer->setVisible(false);
    }

    if (showJumpPage) {

        UnlockPage* jumpPage = new UnlockPage(this, util->jumpsUnlockDataList, "jumps_spr.png"_spr);
        CCNode* jumpPageContainer = jumpPage->createPage(m_playerStats.jumps);
        jumpPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(jumpPageContainer);
        m_pages->addObject(jumpPageContainer);
        jumpPageContainer->setVisible(false);
    }

    if (showAttemptPage) {

        UnlockPage* attemptPage = new UnlockPage(this, util->attemptsUnlockDataList, "attempts_spr.png"_spr);
        CCNode* attemptPageContainer = attemptPage->createPage(m_playerStats.attempts);
        attemptPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(attemptPageContainer);
        m_pages->addObject(attemptPageContainer);
        attemptPageContainer->setVisible(false);
    }

    if (showDestroyedPlayerPage) {

        UnlockPage* destroyedPlayersPage = new UnlockPage(this, util->destroyedPlayersUnlockDataList, "destroyed_players_spr.png"_spr);
        CCNode* destroyedPlayersPageContainer = destroyedPlayersPage->createPage(m_playerStats.destoryedPlayers);
        destroyedPlayersPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(destroyedPlayersPageContainer);
        m_pages->addObject(destroyedPlayersPageContainer);
        destroyedPlayersPageContainer->setVisible(false);
    }

    if (showFriendPage) {

        UnlockPage* friendsPage = new UnlockPage(this, util->followCreatorsUnlockDataList, "friends_spr.png"_spr);
        CCNode* friendsPageContainer = friendsPage->createPage(m_playerStats.friends);
        friendsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(friendsPageContainer);
        m_pages->addObject(friendsPageContainer);
        friendsPageContainer->setVisible(false);
    }

    if (showFollowCreatorPage) {

        UnlockPage* followCreatorsPage = new UnlockPage(this, util->followCreatorsUnlockDataList, "follow_creators_spr.png"_spr);
        CCNode* followCreatorsPageContainer = followCreatorsPage->createPage(m_playerStats.followedCreators);
        followCreatorsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(followCreatorsPageContainer);
        m_pages->addObject(followCreatorsPageContainer);
        followCreatorsPageContainer->setVisible(false);
    }


    if (showLikeDislikePage) {

        UnlockPage* likeDislikeLevelsPage = new UnlockPage(this, util->likeDislikeUnlockDataList, "like_dislike_spr.png"_spr);
        CCNode* likeDislikeLevelsPageContainer = likeDislikeLevelsPage->createPage(m_playerStats.likesAndDislikes);
        likeDislikeLevelsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(likeDislikeLevelsPageContainer);
        m_pages->addObject(likeDislikeLevelsPageContainer);
        likeDislikeLevelsPageContainer->setVisible(false);
    }

    if (showRateStarsPage) {

        UnlockPage* rateStarsOfLevelsPage = new UnlockPage(this, util->rateStarsUnlockDataList, "rate_stars_spr.png"_spr);
        CCNode* rateStarsOfLevelsPageContainer = rateStarsOfLevelsPage->createPage(m_playerStats.rateStarsOnLevels);
        rateStarsOfLevelsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(rateStarsOfLevelsPageContainer);
        m_pages->addObject(rateStarsOfLevelsPageContainer);
        rateStarsOfLevelsPageContainer->setVisible(false);
    }

    if (showInsanePage) {

        UnlockPage* insaneLevelsPage = new UnlockPage(this, util->completedInsaneUnlockDataList, "completed_insanes_spr.png"_spr);
        CCNode* insaneLevelsPageContainer = insaneLevelsPage->createPage(m_playerStats.completedInsanes);
        insaneLevelsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(insaneLevelsPageContainer);
        m_pages->addObject(insaneLevelsPageContainer);
        insaneLevelsPageContainer->setVisible(false);
    }

    if (showDemonPage) {

        UnlockPage* demonLevelsPage = new UnlockPage(this, util->completedDemonUnlockDataList, "completed_demons_spr.png"_spr);
        CCNode* demonLevelsPageContainer = demonLevelsPage->createPage(m_playerStats.completedDemons);
        demonLevelsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(demonLevelsPageContainer);
        m_pages->addObject(demonLevelsPageContainer);
        demonLevelsPageContainer->setVisible(false);
    }

    if (showOnlinePage) {

        UnlockPage* completedOnlineLevelsPage = new UnlockPage(this, util->completedOnlineUnlockDataList, "completed_online_spr.png"_spr);
        CCNode* completedOnlineLevelsPageContainer = completedOnlineLevelsPage->createPage(m_playerStats.completedOnline);
        completedOnlineLevelsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(completedOnlineLevelsPageContainer);
        m_pages->addObject(completedOnlineLevelsPageContainer);
        completedOnlineLevelsPageContainer->setVisible(false);
    }

    if (showDailyPage) {

        UnlockPage* completedDailyLevelsPage = new UnlockPage(this, util->completedDailyUnlockDataList, "completed_daily_spr.png"_spr);
        CCNode* completedDailyLevelsPageContainer = completedDailyLevelsPage->createPage(m_playerStats.completedDaily);
        completedDailyLevelsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(completedDailyLevelsPageContainer);
        m_pages->addObject(completedDailyLevelsPageContainer);
        completedDailyLevelsPageContainer->setVisible(false);
    }


    if (showMapPackPage) {

        UnlockPage* completedMapPacksPage = new UnlockPage(this, util->completedMapPacksUnlockDataList, "completed_map_packs_spr.png"_spr);
        CCNode* completedMapPacksPageContainer = completedMapPacksPage->createPage(m_playerStats.completedMapPacks);
        completedMapPacksPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(completedMapPacksPageContainer);
        m_pages->addObject(completedMapPacksPageContainer);
        completedMapPacksPageContainer->setVisible(false);
    }

    if (showGauntletPage) {

        UnlockPage* completedGauntletsPage = new UnlockPage(this, util->completedGauntletsUnlockDataList, "completed_gauntlets_spr.png"_spr);
        CCNode* completedGauntletsPageContainer = completedGauntletsPage->createPage(m_playerStats.completedGauntlets);
        completedGauntletsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(completedGauntletsPageContainer);
        m_pages->addObject(completedGauntletsPageContainer);
        completedGauntletsPageContainer->setVisible(false);
    }

    if (showListPage) {

        UnlockPage* completedListsPage = new UnlockPage(this, util->completedListsUnlockDataList, "completed_lists_spr.png"_spr);
        CCNode* completedListsPageContainer = completedListsPage->createPage(m_playerStats.completedLists);
        completedListsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(completedListsPageContainer);
        m_pages->addObject(completedListsPageContainer);
        completedListsPageContainer->setVisible(false);
    }

    if (showMostLikedPage) {

        UnlockPage* likesOnYourLevelPage = new UnlockPage(this, util->likesOnYourLevelUnlockDataList, "most_liked_spr.png"_spr);
        CCNode* likesOnYourLevelPageContainer = likesOnYourLevelPage->createPage(0);
        likesOnYourLevelPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(likesOnYourLevelPageContainer);
        m_pages->addObject(likesOnYourLevelPageContainer);
        likesOnYourLevelPageContainer->setVisible(false);
    }

    if (showRatedLevelPage) {

        UnlockPage* ratedLevelPage = new UnlockPage(this, util->creatorPointsUnlockDataList, "creator_points_spr.png"_spr);
        CCNode* ratedLevelPageContainer = ratedLevelPage->createPage(0);
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
    titleSpr->setPosition({75, 25});
    titleSpr->setScale(.4f);
    m_buttonMenu->addChild(titleSpr);
    
    auto creatorTitle = CCLabelBMFont::create("By GlowRock", "goldFont-uhd.fnt");
    creatorTitle->setScale(.4f);
    auto creatorTitleButton = CCMenuItemSpriteExtra::create(
        creatorTitle,
        this,
        menu_selector(UnlockProgressionPopup::openProfile)
    );
    creatorTitleButton->setPosition({373, 13});
    m_buttonMenu->addChild(creatorTitleButton);

    auto topLeftCornerSpr = CCSprite::createWithSpriteFrameName("dailyLevelCorner_001.png");
    topLeftCornerSpr->setAnchorPoint({0, 0});
    topLeftCornerSpr->setFlipY(true);
    auto topLeftNode = CCNode::create();
    topLeftNode->setPosition({0, 207});
    topLeftNode->setZOrder(-1);
    topLeftNode->addChild(topLeftCornerSpr);
    m_buttonMenu->addChild(topLeftNode);


    auto bottomRightCornerSpr = CCSprite::createWithSpriteFrameName("dailyLevelCorner_001.png");
    bottomRightCornerSpr->setAnchorPoint({0, 0});
    bottomRightCornerSpr->setFlipX(true);
    auto bottomRightNode = CCNode::create();
    bottomRightNode->setPosition({417.5f, 0});
    bottomRightNode->setZOrder(-1);
    bottomRightNode->addChild(bottomRightCornerSpr);
    m_buttonMenu->addChild(bottomRightNode);

    auto topRightCornerSpr = CCSprite::createWithSpriteFrameName("dailyLevelCorner_001.png");
    topRightCornerSpr->setAnchorPoint({0, 0});
    topRightCornerSpr->setFlipY(true);
    topRightCornerSpr->setFlipX(true);
    auto topRightNode = CCNode::create();
    topRightNode->setPosition({417.5f, 207});
    topRightNode->setZOrder(-1);
    topRightNode->addChild(topRightCornerSpr);
    m_buttonMenu->addChild(topRightNode);
}

void UnlockProgressionPopup::createNavigationButtons() {

    auto winSize = CCDirector::sharedDirector()->getWinSize();
    float popupHeight = 256;

    auto prevArrowSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    auto nextArrowSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    nextArrowSpr->setFlipX(true);

    m_prevButton = CCMenuItemSpriteExtra::create(
        prevArrowSpr,
        this,
        menu_selector(UnlockProgressionPopup::onPrevPage)
    );
    m_prevButton->setPosition({winSize.width * -0.05f + 2, popupHeight * 0.5f});
    m_buttonMenu->addChild(m_prevButton);

    m_nextButton = CCMenuItemSpriteExtra::create(
        nextArrowSpr,
        this,
        menu_selector(UnlockProgressionPopup::onNextPage)
    );
    m_nextButton->setPosition({winSize.width * 0.85f + 9.35f, popupHeight * 0.5f});
    m_buttonMenu->addChild(m_nextButton);
}

void UnlockProgressionPopup::createBottomNavigationButtons() {

    float popupHeight = 256;

    auto bgSpr = CCSprite::createWithSpriteFrameName("whiteSquare20_001.png");
    bgSpr->setPosition({285, 150});
    bgSpr->setScale(200.f);
    bgSpr->setZOrder(-10);
    bgSpr->setOpacity(100);
    bgSpr->setColor(ccc3(0, 0, 0));
    this->addChild(bgSpr);

    auto navContainer = CCMenu::create();

    navDotOnSpr = CCSprite::createWithSpriteFrameName("gj_navDotBtn_on_001.png");
    navDotOffSpr = CCSprite::createWithSpriteFrameName("gj_navDotBtn_off_001.png");

    const float y = -175;
    const float spacing = 24;

    float totalWidth = m_totalPages * spacing;

    float startX = -51 - (totalWidth / 2) + (spacing / 2);

    for (int i = 0; i < m_totalPages; ++i) {
        auto button = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName(i == 0 ? "gj_navDotBtn_on_001.png" : "gj_navDotBtn_off_001.png"),
            this,
            menu_selector(UnlockProgressionPopup::onPageBtn)
        );
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

    m_playerStats.stars = gameStatsManager->getStat("6");
    m_playerStats.moons = gameStatsManager->getStat("28");
    m_playerStats.secretCoins = gameStatsManager->getStat("8");
    m_playerStats.userCoins = gameStatsManager->getStat("12");
    m_playerStats.diamonds = gameStatsManager->getStat("13");
    m_playerStats.jumps = gameStatsManager->getStat("1");
    m_playerStats.attempts = gameStatsManager->getStat("2");
    m_playerStats.destoryedPlayers = gameStatsManager->getStat("9");
    m_playerStats.friends = 0; //m_playerStats.friends = processFriends.fetchFriendCount(); 
    m_playerStats.followedCreators = gameLevelManager->m_followedCreators->count();
    m_playerStats.likesAndDislikes = gameStatsManager->getStat("10");
    m_playerStats.rateStarsOnLevels = gameStatsManager->getStat("11");
    m_playerStats.completedInsanes = gameStatsManager->getStat("42");
    m_playerStats.completedDemons = gameStatsManager->getStat("5");
    m_playerStats.completedOnline = gameStatsManager->getStat("4");
    m_playerStats.completedDaily = gameStatsManager->getStat("15");
    m_playerStats.completedMapPacks = gameStatsManager->getStat("7");
    m_playerStats.completedGauntlets = gameStatsManager->getStat("40");
    m_playerStats.completedLists = gameStatsManager->getStat("41");
    m_playerStats.maxLikes = -1;                //assigned at a refresh button due to api rate limiting
    m_playerStats.ratedLevels = -1;             //assigned at a refresh button due to api rate limiting

    /*
    m_playerStats.stars = 0;
    m_playerStats.moons = 0;
    m_playerStats.secretCoins = 0;
    m_playerStats.userCoins = 0;
    m_playerStats.diamonds = 0;
    m_playerStats.jumps = 0;
    m_playerStats.attempts = 0;
    m_playerStats.destoryedPlayers = 0;
    m_playerStats.friends = 0;
    m_playerStats.followedCreators = 0;
    m_playerStats.likesAndDislikes = 0;
    m_playerStats.rateStarsOnLevels = 0;
    m_playerStats.completedInsanes = 0;
    m_playerStats.completedDemons = 0;
    m_playerStats.completedOnline = 0;
    m_playerStats.completedDaily = 0;
    m_playerStats.completedMapPacks = 0;
    m_playerStats.completedGauntlets = 0;
    m_playerStats.completedLists = 0;
    m_playerStats.maxLikes = 0;
    m_playerStats.ratedLevels = 0;
    */
}