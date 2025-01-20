#include <Geode/Geode.hpp>

#include "headers/UnlockProgressionPopup.hpp"

using namespace geode::prelude;

#include <Geode/modify/GJGarageLayer.hpp>
class $modify(MyGJGarageLayer, GJGarageLayer) {

	bool init() {
        
		if (!GJGarageLayer::init()) {
			return false;
		}

        auto myButton = CCMenuItemSpriteExtra::create(
			CCSprite::createWithSpriteFrameName("GJ_statsBtn_001.png"),
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
		// Show the custom popup with a sample message
		auto popup = UnlockProgressionPopup::create("Icon progression");
		if (popup) {
			
			popup->show();
		}
	}
};