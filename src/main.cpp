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
			CCSprite::create("mod_button.png"_spr),
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
		if (popup) {
			
			popup->show();
		}
	}
};