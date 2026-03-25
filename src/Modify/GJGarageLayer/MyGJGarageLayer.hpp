#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/GJGarageLayer.hpp>

#include "../../UnlockProgressionPopup/UnlockProgressionPopup.hpp"

using namespace geode::prelude;

class $modify(MyGJGarageLayer, GJGarageLayer) {
public:

    bool init();

private:

    void onPopup(CCObject*);
};