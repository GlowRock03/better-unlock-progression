#pragma once

#include <Geode/Geode.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/utils/web.hpp>
#include <Geode/loader/Event.hpp>

#include "../classes/LevelsJson.cpp"
#include "../classes/ProcessTotalFriends.cpp"
#include "../WebRequests/RequestLevelsForMaxLikedLevel.cpp"
#include "../WebRequests/RequestCreatorPoints.cpp"
#include "../headers/StarPage.cpp"

using namespace geode::prelude;

class UnlockProgressionPopup : public geode::Popup<std::string const&> {
protected:

    CCNode* m_pageContainer = nullptr;
    float m_pageWidth;
    CCArray* m_pages = nullptr;
    int m_currentPage = 0;
    const int m_totalPages = 21;
    CCMenuItemSpriteExtra* m_prevButton = nullptr;
    CCMenuItemSpriteExtra* m_nextButton = nullptr;

    GameStatsManager* gameStatsManager;
    GameLevelManager* gameLevelManager;

    ProcessTotalFriends processFriends;
    RequestLevelsForMaxLikedLevel requestLevels;
    RequestCreatorPoints requestCreatorPoints;
    int creatorPoints;

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

    bool setup(std::string const& text) override {

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        m_pageWidth = winSize.width * 0.75f;

        m_pageContainer = CCNode::create();
        //m_pageContainer->setPosition({winSize.width * 0.5f - m_pageWidth * 0.5f, winSize.height * 0.5f});
        m_pageContainer->setPosition({0, 0});
        m_buttonMenu->addChild(m_pageContainer);

        m_pages = CCArray::create();
        m_pages->retain();

        createBackgroundUI();

        getAllStats();



        //create all progression pages

        StarPage* starPage = new StarPage(this);
        CCNode* starPageContainer = starPage->createStarPage(m_playerStats.stars);
        starPageContainer->setPosition({0, 0});
        m_pageContainer->addChild(starPageContainer);
        m_pages->addObject(starPageContainer);
        starPageContainer->setVisible(true);
       /*
        auto moonPage = createMoonPage();
        m_pageContainer->addChild(moonPage);
        m_pages->addObject(moonPage);
        moonPage->setVisible(false);


        auto secretCoinsPage = createSecretCoinsPage();
        m_pageContainer->addChild(secretCoinsPage);
        m_pages->addObject(secretCoinsPage);
        secretCoinsPage->setVisible(false);

        auto userCoinsPage = createUserCoinsPage();
        m_pageContainer->addChild(userCoinsPage);
        m_pages->addObject(userCoinsPage);
        userCoinsPage->setVisible(false);

        auto diamondsPage = createDiamondsPage();
        m_pageContainer->addChild(diamondsPage);
        m_pages->addObject(diamondsPage);
        diamondsPage->setVisible(false);


        auto jumpsPage = createJumpsPage();
        m_pageContainer->addChild(jumpsPage);
        m_pages->addObject(jumpsPage);
        jumpsPage->setVisible(false);

        auto attemptsPage = createAttemptsPage();
        m_pageContainer->addChild(attemptsPage);
        m_pages->addObject(attemptsPage);
        attemptsPage->setVisible(false);


        auto destroyedPlayersPage = createDestroyedPlayersPage();
        m_pageContainer->addChild(destroyedPlayersPage);
        m_pages->addObject(destroyedPlayersPage);
        destroyedPlayersPage->setVisible(false);

        auto friendsPage = createFriendsPage();
        m_pageContainer->addChild(friendsPage);
        m_pages->addObject(friendsPage);
        friendsPage->setVisible(false);

        auto followCreatorsPage = createFollowCreatorsPage();
        m_pageContainer->addChild(followCreatorsPage);
        m_pages->addObject(followCreatorsPage);
        followCreatorsPage->setVisible(false);


        auto likeDislikeLevelsPage = createLikeDislikeLevelsPage();
        m_pageContainer->addChild(likeDislikeLevelsPage);
        m_pages->addObject(likeDislikeLevelsPage);
        likeDislikeLevelsPage->setVisible(false);

        auto rateStarsOfLevelsPage = createRateStarsOfLevelsPage();
        m_pageContainer->addChild(rateStarsOfLevelsPage);
        m_pages->addObject(rateStarsOfLevelsPage);
        rateStarsOfLevelsPage->setVisible(false);


        auto insaneLevelsPage = createInsaneLevelsPage();
        m_pageContainer->addChild(insaneLevelsPage);
        m_pages->addObject(insaneLevelsPage);
        insaneLevelsPage->setVisible(false);

        auto demonLevelsPage = createDemonLevelsPage();
        m_pageContainer->addChild(demonLevelsPage);
        m_pages->addObject(demonLevelsPage);
        demonLevelsPage->setVisible(false);


        auto completedOnlineLevelsPage = createCompletedOnlineLevelsPage();
        m_pageContainer->addChild(completedOnlineLevelsPage);
        m_pages->addObject(completedOnlineLevelsPage);
        completedOnlineLevelsPage->setVisible(false);

        auto completedDailyLevelsPage = createCompletedDailyLevelsPage();
        m_pageContainer->addChild(completedDailyLevelsPage);
        m_pages->addObject(completedDailyLevelsPage);
        completedDailyLevelsPage->setVisible(false);

        auto completedMapPacksPage = createCompletedMapPacksPage();
        m_pageContainer->addChild(completedMapPacksPage);
        m_pages->addObject(completedMapPacksPage);
        completedMapPacksPage->setVisible(false);

        auto completedGauntletsPage = createCompletedGauntletsPage();
        m_pageContainer->addChild(completedGauntletsPage);
        m_pages->addObject(completedGauntletsPage);
        completedGauntletsPage->setVisible(false);

        auto completedListsPage = createCompletedListsPage();
        m_pageContainer->addChild(completedListsPage);
        m_pages->addObject(completedListsPage);
        completedListsPage->setVisible(false);


        auto likesOnYourLevelPage = createLikesOnYourLevelPage();
        m_pageContainer->addChild(likesOnYourLevelPage);
        m_pages->addObject(likesOnYourLevelPage);
        likesOnYourLevelPage->setVisible(false);

        auto ratedLevelPage = createRatedLevelPage();
        m_pageContainer->addChild(ratedLevelPage);
        m_pages->addObject(ratedLevelPage);
        ratedLevelPage->setVisible(false);
        */

        createNavigationButtons();

        return true;
    }

    void createBackgroundUI() {

        auto titleSpr = CCSprite::create("Better_Unlock_Progression.png"_spr);
        titleSpr->setPosition({228, 227});
        titleSpr->setScale(.65f);
        m_buttonMenu->addChild(titleSpr);

        auto bottomLeftCornerSpr = CCSprite::createWithSpriteFrameName("dailyLevelCorner_001.png");
        bottomLeftCornerSpr->setAnchorPoint({0, 0});
        //do flip here on topLeftCornerSprite
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
        bottomRightNode->setPosition({405, 0});
        bottomRightNode->setZOrder(-1);
        bottomRightNode->addChild(bottomRightCornerSpr);
        m_buttonMenu->addChild(bottomRightNode);

        auto topRightCornerSpr = CCSprite::createWithSpriteFrameName("dailyLevelCorner_001.png");
        topRightCornerSpr->setAnchorPoint({0, 0});
        topRightCornerSpr->setFlipY(true);
        topRightCornerSpr->setFlipX(true);
        auto topRightNode = CCNode::create();
        topRightNode->setPosition({405, 207});
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
        m_prevButton->setPosition({winSize.width * -0.05f, popupHeight * 0.5f});
        m_buttonMenu->addChild(m_prevButton);
        m_prevButton->setVisible(false);

        m_nextButton = CCMenuItemSpriteExtra::create(
            nextArrowSpr,
            this,
            menu_selector(UnlockProgressionPopup::onNextPage)
        );
        m_nextButton->setPosition({winSize.width * 0.85f, popupHeight * 0.5f});
        m_buttonMenu->addChild(m_nextButton);
    }

    void onPrevPage(CCObject*) {
        if (m_currentPage > 0) {
            m_currentPage--;
            updatePageVisibility();
        }
    }

    void onNextPage(CCObject*) {
        if (m_currentPage < m_totalPages - 1) {
            m_currentPage++;
            updatePageVisibility();
        }
        m_playerStats.friends = processFriends.fetchFriendCount();    //dumb edge case :)
        /*
            friends page isn't loaded initially
            friend count requires a second call to get the real value
            theres another way to fix this but lazy coding!
            runtime is slightly worse because of this hotfix
            I may fix this in the future
        */
    }

    void updatePageVisibility() {
        for (int i = 0; i < m_pages->count(); ++i) {
            auto page = static_cast<CCNode*>(m_pages->objectAtIndex(i));
            page->setVisible(i == m_currentPage);
        }
        updateButtonVisibility();
    }

    void updateButtonVisibility() {
        m_prevButton->setVisible(m_currentPage > 0);
        m_nextButton->setVisible(m_currentPage < m_totalPages - 1);
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

        log::info("Stars: {}", m_playerStats.stars);
        log::info("Moons: {}", m_playerStats.moons);
        log::info("Secret Coins: {}", m_playerStats.secretCoins);
        log::info("User Coins: {}", m_playerStats.userCoins);
        log::info("Diamonds: {}", m_playerStats.diamonds);
        log::info("Jumps: {}", m_playerStats.jumps);
        log::info("Attempts: {}", m_playerStats.attempts);
        log::info("Destroyed Players: {}", m_playerStats.destoryedPlayers);
        log::info("Friends: {}", m_playerStats.friends);
        log::info("Followed Creators: {}", m_playerStats.followedCreators);
        log::info("Likes/Dislikes: {}", m_playerStats.likesAndDislikes);
        log::info("Rated Stars on Levels: {}", m_playerStats.rateStarsOnLevels);
        log::info("Completed Insane Levels: {}", m_playerStats.completedInsanes);
        log::info("Completed Demon Levels: {}", m_playerStats.completedDemons);
        log::info("Completed Online Levels: {}", m_playerStats.completedOnline);
        log::info("Completed Daily Levels: {}", m_playerStats.completedDaily);
        log::info("Completed Map Packs: {}", m_playerStats.completedMapPacks);
        log::info("Completed Gauntlets: {}", m_playerStats.completedGauntlets);
        log::info("Completed Lists: {}", m_playerStats.completedLists);
        log::info("Max Likes: {}", m_playerStats.maxLikes);
        log::info("Rated Levels: {}", m_playerStats.ratedLevels);
    }

public:
    static UnlockProgressionPopup* create(std::string const& text) {
        auto winSize = CCDirector::sharedDirector()->getWinSize();

        auto ret = new UnlockProgressionPopup();
        if (ret->initAnchored(winSize.width * 0.8f, winSize.height * 0.8f, text)) {
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
};
