#pragma once

#include <Geode/Geode.hpp>
using namespace geode::prelude;
#include <Geode/modify/ItemInfoPopup.hpp>

class $modify(MyItemInfoPopup, ItemInfoPopup) {
public:
    static MyItemInfoPopup* createWithCustomizations(int iconId, UnlockType unlockType) {
        // Call the original create method
        auto popup = ItemInfoPopup::create(iconId, unlockType);
        if (!popup) {
            log::warn("Failed to create ItemInfoPopup.");
            return nullptr;
        }

        // Cast to MyItemInfoPopup to access custom methods if needed
        auto customPopup = static_cast<MyItemInfoPopup*>(popup);

        // Apply customizations
        customPopup->applyCustomizations();

        return customPopup;
    }

private:
    void applyCustomizations() {
        log::info("Applying customizations to ItemInfoPopup.");

        auto mainLayer = this->getChildByID("main-layer");
        if (!mainLayer) {
            log::warn("Main layer not found in ItemInfoPopup.");
            return;
        }

        auto itemIcon = mainLayer->getChildByID("item-icon");
        if (!itemIcon) {
            log::warn("GJItemIcon 'item-icon' not found in ItemInfoPopup.");
            return;
        }

        log::info("itemicon type: {}", typeid(*itemIcon).name());

        // Iterate through children of itemIcon
        CCArray* children = itemIcon->getChildren();
        if (!children) {
            log::warn("ItemIcon has no children.");
            return;
        }

        for (int i = 0; i < children->count(); ++i) {
            auto child = children->objectAtIndex(i);

            // Safely dynamic_cast to SimplePlayer
            auto simplePlayer = dynamic_cast<SimplePlayer*>(child);
            if (simplePlayer) {
                log::info("Found SimplePlayer instance within GJItemIcon.");

                // Determine whether to use player colors
                bool togglePlayerColors = Mod::get()->getSettingValue<bool>("toggle-player-colors");
                auto gameManager = GameManager::sharedState();

                if (togglePlayerColors) {
                    // Set the player's primary and secondary colors
                    simplePlayer->setColors(
                        gameManager->colorForIdx(gameManager->getPlayerColor()),
                        gameManager->colorForIdx(gameManager->getPlayerColor2())
                    );

                    // Set the glow outline if enabled
                    if (gameManager->m_playerGlow) {
                        simplePlayer->setGlowOutline(
                            gameManager->colorForIdx(gameManager->getPlayerGlowColor())
                        );
                    }
                } else {
                    // Set default colors and disable glow
                    simplePlayer->setColors(ccc3(190, 190, 190), ccc3(245, 245, 245));
                    simplePlayer->disableGlowOutline();
                }
            }
        }
    }
};