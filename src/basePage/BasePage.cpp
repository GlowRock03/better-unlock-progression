#include "BasePage.hpp"

BasePage::BasePage(FLAlertLayer* parentPopup) {

    util = Utilities::getInstance();
    popupLayer = parentPopup;

    pageContainer = CCNode::create();
    buttonMenu = CCMenu::create();

    pageWidth = 213.375f;
    tierPages = CCArray::create();
    tierPages->retain();
    currentPage = 0;
    
    page1Selected = CCSprite::create("GJ_square03.png");
    page2Selected = CCSprite::create("GJ_square03.png");
    page2Selected->setVisible(false);
    page3Selected = CCSprite::create("GJ_square03.png");
    page3Selected->setVisible(false);
    page4Selected = CCSprite::create("GJ_square03.png");
    page4Selected->setVisible(false);
    page1Deselected = CCSprite::create("GJ_square01.png");
    page1Deselected->setVisible(false);
    page2Deselected = CCSprite::create("GJ_square01.png");
    page3Deselected = CCSprite::create("GJ_square01.png");
    page4Deselected = CCSprite::create("GJ_square01.png");
}

BasePage::~BasePage() {

    if (tierPages) {
        tierPages->release();
        tierPages = nullptr;
    }
}

void BasePage::createTitle(const char* title, CCNode* pageContainer) {

    //base icon only
    if (std::string(title).compare("stars_spr.png"_spr) == 0 ||
        std::string(title).compare("moons_spr.png"_spr) == 0 ||
        std::string(title).compare("secret_coins_spr.png"_spr) == 0 ||
        std::string(title).compare("user_coins_spr.png"_spr) == 0 ||
        std::string(title).compare("diamonds_spr.png"_spr) == 0 ||
        std::string(title).compare("diamonds_spr.png"_spr) == 0) {

        
        auto labelSpr = CCSprite::createWithSpriteFrameName(title);
        labelSpr->setID("Page-Title-Sprite");
        labelSpr->setPosition({227.5f, 185});
        labelSpr->setScale(0.65f);
        pageContainer->addChild(labelSpr);

        auto player = SimplePlayer::create(1);
        player->setID("Title-Player");
        player->updatePlayerFrame(util->gameManager->m_playerFrame, IconType::Cube);
        player->setColors(util->gameManager->colorForIdx(util->gameManager->getPlayerColor()), util->gameManager->colorForIdx(util->gameManager->getPlayerColor2()));
        if (util->gameManager->m_playerGlow) {
            player->setGlowOutline(util->gameManager->colorForIdx(util->gameManager->getPlayerGlowColor()));
        }
        player->setPosition({228, 200});
        player->setScale(1.35f);
        pageContainer->addChild(player);

    } else if (std::string(title).compare("follow_creators_spr.png"_spr) == 0 ||
                std::string(title).compare("like_dislike_spr.png"_spr) == 0 ||
                std::string(title).compare("rate_stars_spr.png"_spr) == 0 ||
                std::string(title).compare("completed_insanes_spr.png"_spr) == 0 ||
                std::string(title).compare("completed_demons_spr.png"_spr) == 0 ||
                std::string(title).compare("completed_online_spr.png"_spr) == 0 ||
                std::string(title).compare("completed_daily_spr.png"_spr) == 0 ||
                std::string(title).compare("completed_map_packs_spr.png"_spr) == 0 ||
                std::string(title).compare("completed_gauntlets_spr.png"_spr) == 0 ||
                std::string(title).compare("completed_lists_spr.png"_spr) == 0 ||
                std::string(title).compare("most_liked_spr.png"_spr) == 0 ||
                std::string(title).compare("creator_points_spr.png"_spr) == 0) {  //single types


                auto labelSpr = CCSprite::createWithSpriteFrameName(title);
                labelSpr->setID("Page-Title-Sprite");
                labelSpr->setPosition({227.5f, 185});
                labelSpr->setScale(0.65f);
                pageContainer->addChild(labelSpr);
        
                auto player = SimplePlayer::create(1);
                player->setID("Title-Player");
                player->updatePlayerFrame(util->gameManager->m_playerFrame, IconType::Cube);
                player->setColors(util->gameManager->colorForIdx(util->gameManager->getPlayerColor()), util->gameManager->colorForIdx(util->gameManager->getPlayerColor2()));
                if (util->gameManager->m_playerGlow) {
                    player->setGlowOutline(util->gameManager->colorForIdx(util->gameManager->getPlayerGlowColor()));
                }
                player->setPosition({228, 200});
                player->setScale(1.35f);
                pageContainer->addChild(player);
                
                CCSprite* labelTopSpr;
                if (std::string(title).compare("follow_creators_spr.png"_spr) == 0) {

                    labelTopSpr = CCSprite::createWithSpriteFrameName("GJ_sFollowedIcon_001.png");
                    labelTopSpr->setScale(1.2f);
                } else if (std::string(title).compare("like_dislike_spr.png"_spr) == 0) {

                    labelTopSpr = CCSprite::createWithSpriteFrameName("GJ_like2Btn_001.png");
                    labelTopSpr->setScale(0.38f);
                } else if (std::string(title).compare("rate_stars_spr.png"_spr) == 0) {

                    labelTopSpr = CCSprite::createWithSpriteFrameName("GJ_rateDiffBtn_001.png");
                    labelTopSpr->setScale(0.38f);
                } else if (std::string(title).compare("completed_insanes_spr.png"_spr) == 0) {

                    labelTopSpr = CCSprite::createWithSpriteFrameName("diffIcon_05_btn_001.png");
                    labelTopSpr->setScale(0.58f);
                } else if (std::string(title).compare("completed_demons_spr.png"_spr) == 0) {

                    labelTopSpr = CCSprite::createWithSpriteFrameName("GJ_demonIcon_001.png");
                    labelTopSpr->setScale(0.75f);
                } else if (std::string(title).compare("completed_online_spr.png"_spr) == 0) {

                    labelTopSpr = CCSprite::createWithSpriteFrameName("accountBtn_myLevels_001.png");
                    labelTopSpr->setScale(0.4f);
                } else if (std::string(title).compare("completed_daily_spr.png"_spr) == 0) {

                    labelTopSpr = CCSprite::createWithSpriteFrameName("GJ_dailyRewardBtn_001.png");
                    labelTopSpr->setScale(0.4f);
                } else if (std::string(title).compare("completed_map_packs_spr.png"_spr) == 0) {

                    labelTopSpr = CCSprite::createWithSpriteFrameName("folderIcon_001.png");
                    labelTopSpr->setScale(0.5f);
                } else if (std::string(title).compare("completed_gauntlets_spr.png"_spr) == 0) {

                    labelTopSpr = CCSprite::createWithSpriteFrameName("completed_gauntlets_top_spr.png"_spr);
                    labelTopSpr->setScale(0.52f);
                    labelTopSpr->setPosition({228.25f, 174});
                } else if (std::string(title).compare("completed_lists_spr.png"_spr) == 0) {

                    labelTopSpr = CCSprite::createWithSpriteFrameName("accountBtn_myLists_001.png");
                    labelTopSpr->setScale(0.4f);
                } else if (std::string(title).compare("most_liked_spr.png"_spr) == 0) {

                    labelTopSpr = CCSprite::createWithSpriteFrameName("GJ_likeBtn_001.png");
                    labelTopSpr->setScale(0.38f);
                } else {

                    labelTopSpr = CCSprite::createWithSpriteFrameName("GJ_editBtn_001.png");
                    labelTopSpr->setScale(0.22f);
                }

                if (std::string(title).compare("completed_gauntlets_spr.png"_spr) != 0) {
                    labelTopSpr->setPosition({228.25f, 180});
                }
                
                labelTopSpr->setID("Title-Top-Sprite");
                pageContainer->addChild(labelTopSpr);

    } else if (std::string(title).compare("jumps_spr.png"_spr) == 0) {  //jump page

        auto labelSpr = CCSprite::createWithSpriteFrameName(title);
        labelSpr->setID("Page-Title-Sprite");
        labelSpr->setPosition({227.5f, 185});
        labelSpr->setScale(0.65f);
        pageContainer->addChild(labelSpr);

        auto player = SimplePlayer::create(1);
        player->setID("Title-Player");
        player->updatePlayerFrame(util->gameManager->m_playerFrame, IconType::Cube);
        player->setColors(util->gameManager->colorForIdx(util->gameManager->getPlayerColor()), util->gameManager->colorForIdx(util->gameManager->getPlayerColor2()));
        if (util->gameManager->m_playerGlow) {
            player->setGlowOutline(util->gameManager->colorForIdx(util->gameManager->getPlayerGlowColor()));
        }
        player->setPosition({215.5, 208});
        player->setRotation(18.f);
        player->setScale(0.85f);
        pageContainer->addChild(player);

    } else if (std::string(title).compare("attempts_spr.png"_spr) == 0) {  //attempt page

        auto labelSpr = CCSprite::createWithSpriteFrameName(title);
        labelSpr->setID("Page-Title-Sprite");
        labelSpr->setPosition({227.5f, 185});
        labelSpr->setScale(0.65f);
        pageContainer->addChild(labelSpr);

        auto player = SimplePlayer::create(1);
        player->setID("Title-Player");
        player->updatePlayerFrame(util->gameManager->m_playerFrame, IconType::Cube);
        player->setColors(util->gameManager->colorForIdx(util->gameManager->getPlayerColor()), util->gameManager->colorForIdx(util->gameManager->getPlayerColor2()));
        if (util->gameManager->m_playerGlow) {
            player->setGlowOutline(util->gameManager->colorForIdx(util->gameManager->getPlayerGlowColor()));
        }
        player->setPosition({221, 193});
        player->setScale(0.77f);
        pageContainer->addChild(player);

        auto label2Spr = CCSprite::createWithSpriteFrameName("spike_01_001.png");
        label2Spr->setID("Title-Spike");
        label2Spr->setPosition({236, 192.5f});
        label2Spr->setScale(0.8f);
        pageContainer->addChild(label2Spr);

        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("PlayerExplosion_02.plist");
        auto label3Spr = CCSprite::createWithSpriteFrameName("playerExplosion_02_003.png");
        label3Spr->setID("Title-Death");
        label3Spr->setPosition({222, 194});
        label3Spr->setScale(0.4f);
        label3Spr->setOpacity(220.f);
        pageContainer->addChild(label3Spr);

    } else if (std::string(title).compare("destroyed_players_spr.png"_spr) == 0) {  //destoryed players page

        auto labelSpr = CCSprite::createWithSpriteFrameName(title);
        labelSpr->setID("Page-Title-Sprite");
        labelSpr->setPosition({227.5f, 185});
        labelSpr->setScale(0.65f);
        pageContainer->addChild(labelSpr);

        auto player = SimplePlayer::create(1);
        player->setID("Title-Player");
        player->updatePlayerFrame(util->gameManager->m_playerFrame, IconType::Cube);
        player->setColors(util->gameManager->colorForIdx(util->gameManager->getPlayerColor()), util->gameManager->colorForIdx(util->gameManager->getPlayerColor2()));
        if (util->gameManager->m_playerGlow) {
            player->setGlowOutline(util->gameManager->colorForIdx(util->gameManager->getPlayerGlowColor()));
        }
        player->setPosition({227.5f, 195});
        player->setScale(0.77f);
        pageContainer->addChild(player);

        auto label2Spr = CCSprite::createWithSpriteFrameName("destroyed_players_cursor_spr.png"_spr);  //some top image
        label2Spr->setID("Title-Cursor");
        label2Spr->setPosition({228, 188});
        label2Spr->setScale(0.5f);
        pageContainer->addChild(label2Spr);

        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("PlayerExplosion_02.plist");
        auto label3Spr = CCSprite::createWithSpriteFrameName("playerExplosion_02_003.png");   //some top image
        label3Spr->setID("Title-Death");
        label3Spr->setPosition({228.5f, 196});
        label3Spr->setOpacity(220.f);
        label3Spr->setScale(0.4f);
        pageContainer->addChild(label3Spr);

    } else if (std::string(title).compare("friends_spr.png"_spr) == 0) {  //friend page

        auto labelSpr = CCSprite::createWithSpriteFrameName(title);
        labelSpr->setID("Page-Title-Sprite");
        labelSpr->setPosition({227.5f, 185});
        labelSpr->setScale(0.65f);
        pageContainer->addChild(labelSpr);

        auto player = SimplePlayer::create(1);
        player->setID("Title-Player-1");
        player->updatePlayerFrame(util->gameManager->m_playerFrame, IconType::Cube);
        player->setColors(util->gameManager->colorForIdx(util->gameManager->getPlayerColor()), util->gameManager->colorForIdx(util->gameManager->getPlayerColor2()));
        if (util->gameManager->m_playerGlow) {
            player->setGlowOutline(util->gameManager->colorForIdx(util->gameManager->getPlayerGlowColor()));
        }
        player->setPosition({189, 200});
        player->setScale(1.35f);
        pageContainer->addChild(player);

        auto player2 = SimplePlayer::create(1);
        player2->setID("Title-Player-2");
        player2->updatePlayerFrame(47, IconType::Cube);
        player2->setColors(ccc3(175, 175, 175), ccc3(253, 212, 206));
        player2->setGlowOutline(ccc3(253, 212, 206));
        player2->setPosition({227.5f, 201});
        player2->setScale(0.8f);
        pageContainer->addChild(player2);
        
        /*
        if (util->gameManager->m_playerUserID == 42195651) { //dev mode

            auto player3 = SimplePlayer::create(1);
            player3->setID("Title-Player-3");
            player3->updatePlayerFrame(1, IconType::Cube);
            player3->setColors(ccc3(0, 0, 0), ccc3(0, 0, 0));
            player3->setGlowOutline(ccc3(0, 0, 0));
            player3->setPosition({266, 200});
            player3->setScale(1.35f);
            pageContainer->addChild(player3);

        } else {    //waiting on unerve to tell me his colours (I am colourblind)
        */
            auto player3 = SimplePlayer::create(1);
            player3->setID("Title-Player-3");
            player3->updatePlayerFrame(122, IconType::Cube);
            player3->setColors(ccc3(255, 0, 0), ccc3(0, 125, 255));
            player3->setGlowOutline(ccc3(0, 125, 255));
            player3->setPosition({266, 200});
            player3->setScale(1.35f);
            pageContainer->addChild(player3);
        //}
    }
}

void BasePage::createNavigationButtons(int tierAmount) {

    tempTierAmount = tierAmount;
    float popupHeight = winSize.height * 0.8f;

    std::vector<std::pair<const char*, float>> tierData = {
        {"rankIcon_all_001.png", 1.05f},
        {"rankIcon_top1000_001.png", 0.94f},
        {"rankIcon_top500_001.png", 0.9f},
        {"rankIcon_top200_001.png", 0.82f}
    };

    tierAmount = std::min(tierAmount, static_cast<int>(tierData.size()));

    std::vector<CCSprite*> pageSelected = {page1Selected, page2Selected, page3Selected, page4Selected};
    std::vector<CCSprite*> pageDeselected = {page1Deselected, page2Deselected, page3Deselected, page4Deselected};

    pageSelected.resize(tierAmount);
    pageDeselected.resize(tierAmount);

    std::vector<CCMenuItemSpriteExtra*> tierButtons(tierAmount);
    std::vector<CCSprite*> tierButtonSprites(tierAmount);

    for (int i = 0; i < tierAmount; i++) {

        float xPos;

        switch (tierAmount) {
            case 1:
                xPos = 40 + (1.5f * 27);
                break;
            case 2:
                xPos = 40 + ((i + 1) * 27);
                break;
            case 3:
                xPos = 40 + ((i + 0.5f) * 27);
                break;
            default:
                xPos = 40 + (i * 27);
        }

        int tierDataIndex = tierData.size() - tierAmount + i;

        tierButtonSprites[i] = CCSprite::createWithSpriteFrameName(tierData[tierDataIndex].first);
        tierButtonSprites[i]->setID("Tier-Sprite");
        tierButtonSprites[i]->setScale(tierData[tierDataIndex].second);

        tierButtons[i] = CCMenuItemSpriteExtra::create(
            tierButtonSprites[i],
            this,
            menu_selector(BasePage::onTierButton)
        );
        tierButtons[i]->setID("Tier-Button");
        tierButtons[i]->setTag(i);
        tierButtons[i]->setAnchorPoint({.5f, .5f});
        tierButtons[i]->setPosition({xPos, 220});
        buttonMenu->addChild(tierButtons[i]);

        pageDeselected[i]->setID("Tier-Deselected");
        pageDeselected[i]->setAnchorPoint({.5f, 0});
        pageDeselected[i]->setPosition({xPos, 208});
        pageDeselected[i]->setScale(.3f);
        pageDeselected[i]->setZOrder(-2);
        buttonMenu->addChild(pageDeselected[i]);

        pageSelected[i]->setID("Tier-Selected");
        pageSelected[i]->setAnchorPoint({.5f, 0});
        pageSelected[i]->setPosition({xPos, 208});
        pageSelected[i]->setScale(.3f);
        pageSelected[i]->setZOrder(-2);
        buttonMenu->addChild(pageSelected[i]);
    }
}

void BasePage::onTierButton(CCObject* sender) {

    auto button = static_cast<CCMenuItemSpriteExtra*>(sender);
    int tag = button->getTag();
    currentPage = tag;
    updatePageVisibility(tag);
}

void BasePage::updatePageVisibility(int tag) {

    for (int i = 0; i < tierPages->count(); ++i) {

        auto page = static_cast<CCNode*>(tierPages->objectAtIndex(i));
        page->setVisible(i == currentPage);
    }
    updateButtonBackground(tag);
}

void BasePage::updateButtonBackground(int tag) {

    auto setVisibility = [this](int index, bool selected) {
        if (index == 0) {
            page1Selected->setVisible(selected);
            page1Deselected->setVisible(!selected);
        } else if (index == 1) {
            page2Selected->setVisible(selected);
            page2Deselected->setVisible(!selected);
        } else if (index == 2) {
            page3Selected->setVisible(selected);
            page3Deselected->setVisible(!selected);
        } else if (index == 3) {
            page4Selected->setVisible(selected);
            page4Deselected->setVisible(!selected);
        }
    };

    for (int i = 0; i < tempTierAmount; ++i) {
        setVisibility(i, i == tag);
    }
}