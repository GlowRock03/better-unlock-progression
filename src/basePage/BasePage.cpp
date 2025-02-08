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
    
    page1Selected = CCSprite::create("GJ_square03-uhd.png");
    page2Selected = CCSprite::create("GJ_square03-uhd.png");
    page2Selected->setVisible(false);
    page3Selected = CCSprite::create("GJ_square03-uhd.png");
    page3Selected->setVisible(false);
    page4Selected = CCSprite::create("GJ_square03-uhd.png");
    page4Selected->setVisible(false);
    page1Deselected = CCSprite::create("GJ_square01-uhd.png");
    page1Deselected->setVisible(false);
    page2Deselected = CCSprite::create("GJ_square01-uhd.png");
    page3Deselected = CCSprite::create("GJ_square01-uhd.png");
    page4Deselected = CCSprite::create("GJ_square01-uhd.png");
}

BasePage::~BasePage() {

    if (tierPages) {
        tierPages->release();
        tierPages = nullptr;
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
        tierButtonSprites[i]->setScale(tierData[tierDataIndex].second);

        tierButtons[i] = CCMenuItemSpriteExtra::create(
            tierButtonSprites[i],
            this,
            menu_selector(BasePage::onTierButton)
        );
        tierButtons[i]->setTag(i);
        tierButtons[i]->setAnchorPoint({.5f, .5f});
        tierButtons[i]->setPosition({xPos, 220});
        buttonMenu->addChild(tierButtons[i]);

        pageDeselected[i]->setAnchorPoint({.5f, 0});
        pageDeselected[i]->setPosition({xPos, 208});
        pageDeselected[i]->setScale(.3f);
        pageDeselected[i]->setZOrder(-2);
        buttonMenu->addChild(pageDeselected[i]);

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