#pragma once

#ifndef UNLOCKPROGRESSIONPOPUP_HPP
#define UNLOCKPROGRESSIONPOPUP_HPP

#include <Geode/Geode.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/utils/web.hpp>
#include <Geode/loader/Event.hpp>
#include <Geode/binding/ProfilePage.hpp>

#include "../utility/Utilities.hpp" 
#include "../unlockPage/UnlockPage.hpp"

using namespace geode::prelude;

class UnlockProgressionPopup : public geode::Popup<std::string const&> {
private:

    GameStatsManager* gameStatsManager;
    GameLevelManager* gameLevelManager;

    CCNode* m_pageContainer = nullptr;
    float m_pageWidth;
    CCArray* m_pages = nullptr;
    int m_currentPage = 0;
    int m_totalPages = 21;

    CCMenuItemSpriteExtra* m_prevButton = nullptr;
    CCMenuItemSpriteExtra* m_nextButton = nullptr;
    CCSprite* navDotOnSpr = nullptr;
    CCSprite* navDotOffSpr = nullptr;
    std::vector<CCMenuItemSpriteExtra*> navDots;

    Utilities* util;

public:

    static UnlockProgressionPopup* create(std::string const& text);
    ~UnlockProgressionPopup();
    bool setup(std::string const& text) override;
    void createBackgroundUI();
    void createNavigationButtons();
    void createBottomNavigationButtons();
    void openProfile(CCObject*);
    void onPageBtn(CCObject* sender);
    void setupInitialPage();
    bool isPageEnabled(int index);
    void onPrevPage(CCObject*);
    void onNextPage(CCObject*);
    void updatePageVisibility();
    void updateButtonVisibility();
    void getAllStats();
};

#endif