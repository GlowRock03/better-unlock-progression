#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/ItemInfoPopup.hpp>

using namespace geode::prelude;

class $modify(MyItemInfoPopup, ItemInfoPopup) {
public:

    static MyItemInfoPopup* createWithCustomizations(int iconId, UnlockType unlockType);

private:

    void applyCustomizations();
};