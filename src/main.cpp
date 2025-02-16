#include <Geode/Geode.hpp>

#include "unlockProgressionPopup/UnlockProgressionPopup.hpp"

using namespace geode::prelude;

#include <Geode/modify/GJGarageLayer.hpp>
class $modify(MyGJGarageLayer, GJGarageLayer) {

	bool init() {
        
		if (!GJGarageLayer::init()) {
			return false;
		}

        auto myButton = CCMenuItemSpriteExtra::create(
			CCSprite::createWithSpriteFrameName("modButton.png"_spr),
			this,
			menu_selector(MyGJGarageLayer::onMyButton)
		);

		auto menu = this->getChildByID("shards-menu");
		menu->addChild(myButton);
		myButton->setID("IconProgressionBtn"_spr);
		menu->updateLayout();
        
		return true;
	}

	void onMyButton(CCObject*) {

		auto popup = UnlockProgressionPopup::create("Icon progression");
		popup->setID("Better-Unlock-Progression"_spr);
		if (popup) {
			
			popup->show();
		}
	}
};