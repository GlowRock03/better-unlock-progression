#pragma once

#include <Geode/Geode.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/utils/web.hpp>
#include <Geode/loader/Event.hpp>

#include "classes/ProcessTotalFriends.cpp"

#include "pages/StarPage.cpp"
#include "pages/MoonPage.cpp"
#include "pages/SecretCoinPage.cpp"
#include "pages/UserCoinPage.cpp"
#include "pages/DiamondPage.cpp"
#include "pages/JumpPage.cpp"
#include "pages/AttemptPage.cpp"
#include "pages/DestroyedPlayerPage.cpp"
#include "pages/FriendPage.cpp" 
#include "pages/FollowCreatorPage.cpp" 
#include "pages/LikeDislikeLevelPage.cpp"
#include "pages/RateStarsOfLevelsPage.cpp" 
#include "pages/CompletedInsaneLevelPage.cpp"
#include "pages/CompletedDemonPage.cpp"
#include "pages/CompletedOnlineLevelPage.cpp"
#include "pages/CompletedDailies.cpp" 
#include "pages/CompletedMapPackPage.cpp"
#include "pages/CompletedGauntletPage.cpp"
#include "pages/CompletedListPage.cpp"
#include "pages/LikesOnYourLevelPage.cpp"
#include "pages/RatedLevelPage.cpp"

using namespace geode::prelude;

class UnlockProgressionPopup : public geode::Popup<std::string const&> {
protected:

    GameStatsManager* gameStatsManager;
    GameLevelManager* gameLevelManager;

    ProcessTotalFriends processFriends;
    FriendPage* friendsPage;

    CCNode* m_pageContainer = nullptr;
    float m_pageWidth;
    CCArray* m_pages = nullptr;
    int m_currentPage = 0;
    const int m_totalPages = 21;

    CCMenuItemSpriteExtra* m_prevButton = nullptr;
    CCMenuItemSpriteExtra* m_nextButton = nullptr;
    CCSprite* navDotOnSpr = nullptr;
    CCSprite* navDotOffSpr = nullptr;
    std::vector<CCMenuItemSpriteExtra*> navDots;

    struct PlayerStats {
        int stars;
        int moons;
        int secretCoins;
        int userCoins;
        int diamonds;
        int jumps;
        int attempts;
        int destoryedPlayers;
        int friends;
        int followedCreators;
        int likesAndDislikes;
        int rateStarsOnLevels;
        int completedInsanes;
        int completedDemons;
        int completedOnline;
        int completedDaily;
        int completedMapPacks;
        int completedGauntlets;
        int completedLists;
        int maxLikes;
        int ratedLevels;
    };
    PlayerStats m_playerStats;

public:
    static UnlockProgressionPopup* create(std::string const& text) {
        auto winSize = CCDirector::sharedDirector()->getWinSize();

        auto ret = new UnlockProgressionPopup();
        if (ret->initAnchored(winSize.width * 0.82f, winSize.height * 0.8f, text)) {
            ret->autorelease();
            return ret;
        }

        delete ret;
        return nullptr;
    }

    ~UnlockProgressionPopup() {
        if (m_pages) {
            m_pages->release();
        }
    }

private:
    bool setup(std::string const& text) override {

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        m_pageWidth = winSize.width * 0.80f;

        m_pageContainer = CCNode::create();
        m_pageContainer->setPosition({0, 0});
        m_buttonMenu->addChild(m_pageContainer);

        m_pages = CCArray::create();
        m_pages->retain();

        createBackgroundUI();

        getAllStats();

        auto showStarPage = Mod::get()->getSettingValue<bool>("show-star-page");

        //create all progression pages

        StarPage* starPage = new StarPage(this);
        CCNode* starPageContainer = starPage->createStarPage(m_playerStats.stars);
        starPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(starPageContainer);
        m_pages->addObject(starPageContainer);
        starPageContainer->setVisible(true);
       
        MoonPage* moonPage = new MoonPage(this);
        CCNode* moonPageContainer = moonPage->createMoonPage(m_playerStats.moons);
        moonPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(moonPageContainer);
        m_pages->addObject(moonPageContainer);
        moonPageContainer->setVisible(false);
        

        SecretCoinPage* secretCoinsPage = new SecretCoinPage(this);
        CCNode* secretCoinsPageContainer = secretCoinsPage->createSecretCoinPage(m_playerStats.secretCoins);
        secretCoinsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(secretCoinsPageContainer);
        m_pages->addObject(secretCoinsPageContainer);
        secretCoinsPageContainer->setVisible(false);

        UserCoinPage* userCoinsPage = new UserCoinPage(this);
        CCNode* userCoinsPageContainer = userCoinsPage->createUserCoinPage(m_playerStats.userCoins);
        userCoinsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(userCoinsPageContainer);
        m_pages->addObject(userCoinsPageContainer);
        userCoinsPageContainer->setVisible(false);

        DiamondPage* diamondsPage = new DiamondPage(this);
        CCNode* diamondsPageContainer = diamondsPage->createDiamondPage(m_playerStats.diamonds);
        diamondsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(diamondsPageContainer);
        m_pages->addObject(diamondsPageContainer);
        diamondsPageContainer->setVisible(false);


        JumpPage* jumpPage = new JumpPage(this);
        CCNode* jumpPageContainer = jumpPage->createJumpPage(m_playerStats.jumps);
        jumpPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(jumpPageContainer);
        m_pages->addObject(jumpPageContainer);
        jumpPageContainer->setVisible(false);

        AttemptPage* attemptPage = new AttemptPage(this);
        CCNode* attemptPageContainer = attemptPage->createAttemptPage(m_playerStats.attempts);
        attemptPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(attemptPageContainer);
        m_pages->addObject(attemptPageContainer);
        attemptPageContainer->setVisible(false);

        
        DestroyedPlayerPage* destroyedPlayersPage = new DestroyedPlayerPage(this);
        CCNode* destroyedPlayersPageContainer = destroyedPlayersPage->createDestroyedPlayersPage(m_playerStats.destoryedPlayers);
        destroyedPlayersPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(destroyedPlayersPageContainer);
        m_pages->addObject(destroyedPlayersPageContainer);
        destroyedPlayersPageContainer->setVisible(false);

        friendsPage = new FriendPage(this);
        CCNode* friendsPageContainer = friendsPage->createFriendPage(m_playerStats.friends);
        friendsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(friendsPageContainer);
        m_pages->addObject(friendsPageContainer);
        friendsPageContainer->setVisible(false);

        FollowCreatorPage* followCreatorsPage = new FollowCreatorPage(this);
        CCNode* followCreatorsPageContainer = followCreatorsPage->createFollowedCreatorPage(m_playerStats.followedCreators);
        followCreatorsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(followCreatorsPageContainer);
        m_pages->addObject(followCreatorsPageContainer);
        followCreatorsPageContainer->setVisible(false);


        LikeDislikeLevelPage* likeDislikeLevelsPage = new LikeDislikeLevelPage(this);
        CCNode* likeDislikeLevelsPageContainer = likeDislikeLevelsPage->createLikeDislikeLevelPage(m_playerStats.likesAndDislikes);
        likeDislikeLevelsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(likeDislikeLevelsPageContainer);
        m_pages->addObject(likeDislikeLevelsPageContainer);
        likeDislikeLevelsPageContainer->setVisible(false);

        RateStarsOfLevelsPage* rateStarsOfLevelsPage = new RateStarsOfLevelsPage(this);
        CCNode* rateStarsOfLevelsPageContainer = rateStarsOfLevelsPage->createRateStarsOfLevelPage(m_playerStats.rateStarsOnLevels);
        rateStarsOfLevelsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(rateStarsOfLevelsPageContainer);
        m_pages->addObject(rateStarsOfLevelsPageContainer);
        rateStarsOfLevelsPageContainer->setVisible(false);


        CompletedInsaneLevelPage* insaneLevelsPage = new CompletedInsaneLevelPage(this);
        CCNode* insaneLevelsPageContainer = insaneLevelsPage->createInsaneLevelPage(m_playerStats.completedInsanes);
        insaneLevelsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(insaneLevelsPageContainer);
        m_pages->addObject(insaneLevelsPageContainer);
        insaneLevelsPageContainer->setVisible(false);

        CompletedDemonPage* demonLevelsPage = new CompletedDemonPage(this);
        CCNode* demonLevelsPageContainer = demonLevelsPage->createDemonLevelPage(m_playerStats.completedDemons);
        demonLevelsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(demonLevelsPageContainer);
        m_pages->addObject(demonLevelsPageContainer);
        demonLevelsPageContainer->setVisible(false);

        CompletedOnlineLevelPage* completedOnlineLevelsPage = new CompletedOnlineLevelPage(this);
        CCNode* completedOnlineLevelsPageContainer = completedOnlineLevelsPage->createCompleteOnlinePage(m_playerStats.completedOnline);
        completedOnlineLevelsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(completedOnlineLevelsPageContainer);
        m_pages->addObject(completedOnlineLevelsPageContainer);
        completedOnlineLevelsPageContainer->setVisible(false);

        CompletedDailies* completedDailyLevelsPage = new CompletedDailies(this);
        CCNode* completedDailyLevelsPageContainer = completedDailyLevelsPage->createCompletedDailiesPage(m_playerStats.completedDaily);
        completedDailyLevelsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(completedDailyLevelsPageContainer);
        m_pages->addObject(completedDailyLevelsPageContainer);
        completedDailyLevelsPageContainer->setVisible(false);


        CompletedMapPackPage* completedMapPacksPage = new CompletedMapPackPage(this);
        CCNode* completedMapPacksPageContainer = completedMapPacksPage->createCompletedMapPackPage(m_playerStats.completedMapPacks);
        completedMapPacksPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(completedMapPacksPageContainer);
        m_pages->addObject(completedMapPacksPageContainer);
        completedMapPacksPageContainer->setVisible(false);

        CompletedGauntletPage* completedGauntletsPage = new CompletedGauntletPage(this);
        CCNode* completedGauntletsPageContainer = completedGauntletsPage->createCompletedGauntletPage(m_playerStats.completedGauntlets);
        completedGauntletsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(completedGauntletsPageContainer);
        m_pages->addObject(completedGauntletsPageContainer);
        completedGauntletsPageContainer->setVisible(false);

        CompletedListPage* completedListsPage = new CompletedListPage(this);
        CCNode* completedListsPageContainer = completedListsPage->createCompletedListPage(m_playerStats.completedLists);
        completedListsPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(completedListsPageContainer);
        m_pages->addObject(completedListsPageContainer);
        completedListsPageContainer->setVisible(false);


        LikesOnYourLevelPage* likesOnYourLevelPage = new LikesOnYourLevelPage(this);
        CCNode* likesOnYourLevelPageContainer = likesOnYourLevelPage->createLikesOnYourLevelPage();
        likesOnYourLevelPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(likesOnYourLevelPageContainer);
        m_pages->addObject(likesOnYourLevelPageContainer);
        likesOnYourLevelPageContainer->setVisible(false);

        RatedLevelPage* ratedLevelPage = new RatedLevelPage(this);
        CCNode* ratedLevelPageContainer = ratedLevelPage->createRatedLevelPage();
        ratedLevelPageContainer->setPosition({5.75f, 0});
        m_pageContainer->addChild(ratedLevelPageContainer);
        m_pages->addObject(ratedLevelPageContainer);
        ratedLevelPageContainer->setVisible(false);

        createNavigationButtons();

        createBottomNavigationButtons();

        return true;
    }

    void createBackgroundUI() {

        auto titleSpr = CCSprite::create("Better_Unlock_Progression.png"_spr);
        titleSpr->setPosition({234.5f, 227});
        titleSpr->setScale(.65f);
        m_buttonMenu->addChild(titleSpr);

        auto bottomLeftCornerSpr = CCSprite::createWithSpriteFrameName("dailyLevelCorner_001.png");
        bottomLeftCornerSpr->setAnchorPoint({0, 0});
        auto bottomLeftNode = CCNode::create();
        bottomLeftNode->setPosition({0, 0});
        bottomLeftNode->setZOrder(-1);
        bottomLeftNode->addChild(bottomLeftCornerSpr);
        m_buttonMenu->addChild(bottomLeftNode);

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

    void createNavigationButtons() {
        
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        float popupHeight = winSize.height * 0.8f;

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

    void createBottomNavigationButtons() {

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        float popupHeight = winSize.height * 0.8f;

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

        const float initialX = -291;
        const float y = -175;
        const float spacing = 24;

        for (int i = 0; i <= 20; ++i) {
            auto button = CCMenuItemSpriteExtra::create(
                CCSprite::createWithSpriteFrameName(i == 0 ? "gj_navDotBtn_on_001.png" : "gj_navDotBtn_off_001.png"),
                this,
                menu_selector(UnlockProgressionPopup::onPageBtn)
            );
            button->setTag(i);
            button->setPosition({initialX + i * spacing, y});
            navDots.push_back(button);
            navContainer->addChild(button);
        }

        m_buttonMenu->addChild(navContainer);
    }

    void onPageBtn(CCObject* sender) {

        auto button = static_cast<CCMenuItemSpriteExtra*>(sender);
        m_currentPage = button->getTag();
        updatePageVisibility();
    }

    void onPrevPage(CCObject*) {

        m_currentPage = (m_currentPage == 0) ? m_totalPages - 1 : m_currentPage - 1;
        updatePageVisibility();
    }

    void onNextPage(CCObject*) {

        m_currentPage = (m_currentPage == m_totalPages - 1) ? 0 : m_currentPage + 1;
        updatePageVisibility();
    }

    void updatePageVisibility() {
        /*
            friends page isn't loaded initially because of retrival method
            friend count requires a second call to get the real value
            theres another way to fix this but lazy coding wins!
            runtime is *slightly* worse because of this hotfix
            I may fix this in the future
        */
        if (m_playerStats.friends == -1) {
            m_playerStats.friends = processFriends.fetchFriendCount();
            friendsPage->updateFriendCount(m_playerStats.friends);
        }
        for (int i = 0; i < m_pages->count(); ++i) {
            auto page = static_cast<CCNode*>(m_pages->objectAtIndex(i));
            page->setVisible(i == m_currentPage);
        }
        updateButtonVisibility();
    }

    void updateButtonVisibility() {

        for (int i = 0; i < navDots.size(); ++i) {
            auto dotSpr = CCSprite::createWithSpriteFrameName(
                i == m_currentPage ? "gj_navDotBtn_on_001.png" : "gj_navDotBtn_off_001.png"
            );
            navDots[i]->setNormalImage(dotSpr);
        }
    }

    void getAllStats() {
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
        m_playerStats.friends = processFriends.fetchFriendCount();
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
        m_playerStats.maxLikes = 0;                //assigned at a refresh button due to api rate limiting
        m_playerStats.ratedLevels = 0;            //assigned at a refresh button due to api rate limiting
        */
    }
};
