#include "MyGJGarageLayer.hpp"

bool MyGJGarageLayer::init() {
    
    if (!GJGarageLayer::init()) {
        return false;
    }

    bool toggleLegacySprite = Mod::get()->getSettingValue<bool>("toggle-legacy-sprite");
    auto modSprite = toggleLegacySprite ? CCSprite::createWithSpriteFrameName("modButton.png"_spr) : CCSprite::createWithSpriteFrameName("modButtonNew.png"_spr);

    auto myButton = CCMenuItemSpriteExtra::create(modSprite, this, menu_selector(MyGJGarageLayer::onPopup));

    auto menu = this->getChildByID("shards-menu");
    menu->addChild(myButton);
    myButton->setID("IconProgressionBtn"_spr);
    menu->updateLayout();
    
    return true;
}

void MyGJGarageLayer::onPopup(CCObject*) {

    auto popup = UnlockProgressionPopup::create("Icon progression");
    popup->setID("Better-Unlock-Progression"_spr);
    popup->setZOrder(95);
    if (popup) {
        
        popup->show();
    }
}