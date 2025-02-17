#include "MyItemInfoPopup.hpp"

using namespace geode::prelude;

MyItemInfoPopup* MyItemInfoPopup::createWithCustomizations(int iconId, UnlockType unlockType) {

    auto popup = ItemInfoPopup::create(iconId, unlockType);
    if (!popup) {
        return nullptr;
    }
    popup->setTouchPriority(-500);
    auto customPopup = static_cast<MyItemInfoPopup*>(popup);
    customPopup->applyCustomizations();
    
    return customPopup;
}

void MyItemInfoPopup::applyCustomizations() {

    auto mainLayer = this->getChildByID("main-layer");
    auto itemIcon = mainLayer->getChildByID("item-icon");
    CCArray* children = itemIcon->getChildren();

    for (int i = 0; i < children->count(); ++i) {

        auto child = children->objectAtIndex(i);
        auto simplePlayer = dynamic_cast<SimplePlayer*>(child);
        if (simplePlayer) {

            bool togglePlayerColors = Mod::get()->getSettingValue<bool>("toggle-player-colors");
            auto gameManager = GameManager::sharedState();

            if (togglePlayerColors) {

                simplePlayer->setColors(
                    gameManager->colorForIdx(gameManager->getPlayerColor()),
                    gameManager->colorForIdx(gameManager->getPlayerColor2())
                );

                if (gameManager->m_playerGlow) {
                    simplePlayer->setGlowOutline(
                        gameManager->colorForIdx(gameManager->getPlayerGlowColor())
                    );
                }
            } else {

                simplePlayer->setColors(ccc3(190, 190, 190), ccc3(245, 245, 245));
                simplePlayer->disableGlowOutline();
            }
        }
    }
}
