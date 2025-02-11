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

    //auto labelName = fmt::format("glowrock.better_unlock_progression/{}", iconSprName);         //was having issues with _spr and a variable, so a manual solution works
    //auto labelSpr = CCSprite::create(labelName.c_str());
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