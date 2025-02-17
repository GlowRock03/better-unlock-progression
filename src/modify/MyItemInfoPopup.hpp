#pragma once

#ifndef MYITEMINFOPOPUP_HPP
#define MYITEMINFOPOPUP_HPP

#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/ItemInfoPopup.hpp>
class $modify(MyItemInfoPopup, ItemInfoPopup) {
public:

    static MyItemInfoPopup* createWithCustomizations(int iconId, UnlockType unlockType);

private:

    void applyCustomizations();
};

#endif