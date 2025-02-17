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

    std::vector<bool> showList(21);
    std::vector<std::string> modSettingKeys = {
        "show-star-page", "show-moon-page", "show-secret-coin-page", "show-user-coin-page",
        "show-diamond-page", "show-jump-page", "show-attempts-page", "show-destroyed-players-page",
        "show-friend-page", "show-follow-creator-page", "show-like-dislike-page", "show-rate-stars-page",
        "show-insane-page", "show-demon-page", "show-online-page", "show-daily-page",
        "show-map-pack-page", "show-gauntlet-page", "show-list-page", "show-most-liked-level-page", "show-rated-level-page"
    };
    std::vector<std::vector<Utilities::UnlockData*>> allUnlocksList = {
        util->starUnlockDataList, util->moonUnlockDataList, util->secretCoinUnlockDataList,
        util->userCoinUnlockDataList, util->diamondUnlockDataList, util->jumpsUnlockDataList,
        util->attemptsUnlockDataList, util->destroyedPlayersUnlockDataList, util->friendsUnlockDataList,
        util->followCreatorsUnlockDataList, util->likeDislikeUnlockDataList, util->rateStarsUnlockDataList,
        util->completedInsaneUnlockDataList, util->completedDemonUnlockDataList, util->completedOnlineUnlockDataList,
        util->completedDailyUnlockDataList, util->completedMapPacksUnlockDataList, util->completedGauntletsUnlockDataList,
        util->completedListsUnlockDataList, util->likesOnYourLevelUnlockDataList, util->creatorPointsUnlockDataList
    };
    std::vector<const char*> allTitleSprites = {
        "stars_spr.png"_spr, "moons_spr.png"_spr, "secret_coins_spr.png"_spr, "user_coins_spr.png"_spr,
        "diamonds_spr.png"_spr, "jumps_spr.png"_spr, "attempts_spr.png"_spr, "destroyed_players_spr.png"_spr,
        "friends_spr.png"_spr, "follow_creators_spr.png"_spr, "like_dislike_spr.png"_spr, "rate_stars_spr.png"_spr,
        "completed_insanes_spr.png"_spr, "completed_demons_spr.png"_spr, "completed_online_spr.png"_spr,
        "completed_daily_spr.png"_spr, "completed_map_packs_spr.png"_spr, "completed_gauntlets_spr.png"_spr,
        "completed_lists_spr.png"_spr, "most_liked_spr.png"_spr, "creator_points_spr.png"_spr
    };
    std::vector<int> statsList(21);
    statsList = {
        util->m_playerStats.stars, util->m_playerStats.moons, util->m_playerStats.secretCoins, util->m_playerStats.userCoins,
        util->m_playerStats.diamonds, util->m_playerStats.jumps, util->m_playerStats.attempts, util->m_playerStats.destoryedPlayers,
        util->m_playerStats.friends, util->m_playerStats.followedCreators, util->m_playerStats.likesAndDislikes, util->m_playerStats.rateStarsOnLevels,
        util->m_playerStats.completedInsanes, util->m_playerStats.completedDemons, util->m_playerStats.completedOnline, util->m_playerStats.completedDaily,
        util->m_playerStats.completedMapPacks, util->m_playerStats.completedGauntlets, util->m_playerStats.completedLists, util->m_playerStats.maxLikes,
        util->m_playerStats.ratedLevels
    };
    std::vector<std::string> pageIdList = {
        "Stars-Progression", "Moons-Progression", "Secret-Coin-Progression", "User-Coin-Progression", "Diamond-Progression",
        "Jump-Progression", "Attempt-Progression", "Destroyed-Players-Progression", "Friend-Progression", "Followed-Creators-Progression",
        "Like-Dislike-Progression", "Rate-Stars-Progression", "Completed-Insanes-Progression", "Completed-Demons-Progression",
        "Completed-Online-Progression", "Completed-Daily-Progression", "Completed-Map-Packs-Progression", "Completed-Gauntlets-Progression",
        "Completed-Lists-Progression", "Most-Liked-Progression", "Creator-Point-Progression"
    };

    int disabledSettings = 0;
    int j = 0;
    for (const auto& key : modSettingKeys) {

        bool value = Mod::get()->getSettingValue<bool>(key);
        showList[j] = value;
        if (!value) {
            ++disabledSettings;
        }
        ++j;
    }

    for (int i = 0; i < 21; ++i) {
        if (showList[i]) {
            UnlockPage* page = new UnlockPage(this, allUnlocksList[i], allTitleSprites[i]);
            CCNode* pageContainer = page->createPage(statsList[i]);
            pageContainer->setID(pageIdList[i]);
            pageContainer->setPosition({5.75f, 0});
            m_pageContainer->addChild(pageContainer);
            m_pages->addObject(pageContainer);
            pageContainer->setVisible(m_pages->count() == 1);
        }
    }

    m_totalPages = 21 - disabledSettings;

    bool disableArrows = false;

    if (m_totalPages == 0)  {

        auto disableText = CCLabelBMFont::create("You have disabled every page in the mod. Please enable a page.", "bigFont-uhd.fnt");
        disableText->setScale(0.3f);
        disableText->setPosition({233, 130});
        m_pageContainer->addChild(disableText);
        disableArrows = true;
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
    nextArrowSpr->setID("Right-Arrow-Sprite");
    nextArrowSpr->setFlipX(true);

    m_prevButton = CCMenuItemSpriteExtra::create(
        prevArrowSpr,
        this,
        menu_selector(UnlockProgressionPopup::onPrevPage)
    );
    //m_prevButton->setPosition({winSize.width * -0.05f + 2, popupHeight * 0.5f});
    m_prevButton->setPosition({-26.45f, popupHeight * 0.5f});
    m_prevButton->setID("Left-Arrow-Button");
    m_buttonMenu->addChild(m_prevButton);

    m_nextButton = CCMenuItemSpriteExtra::create(
        nextArrowSpr,
        this,
        menu_selector(UnlockProgressionPopup::onNextPage)
    );
    //-26.45f
    //493
    //m_nextButton->setPosition({winSize.width * 0.85f + 9.35f, popupHeight * 0.5f});
    m_nextButton->setPosition({493, popupHeight * 0.5f});
    m_nextButton->setID("Right-Arrow-Button");
    m_buttonMenu->addChild(m_nextButton);
}

void UnlockProgressionPopup::createBottomNavigationButtons() {

    float popupHeight = 256;
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    log::info("width: {}", winSize.width);

    auto bgSpr = CCSprite::createWithSpriteFrameName("whiteSquare20_001.png");
    bgSpr->setID("Dim-Sprite");
    bgSpr->setPosition({winSize.width / 2, 150});
    bgSpr->setScale(500.f);
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