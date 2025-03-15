#include <Geode/Geode.hpp>

#include "unlockProgressionPopup/UnlockProgressionPopup.hpp"

using namespace geode::prelude;

#include <Geode/modify/GJGarageLayer.hpp>
class $modify(MyGJGarageLayer, GJGarageLayer) {

	bool init() {
        
		if (!GJGarageLayer::init()) {
			return false;
		}

		bool toggleLegacySprite = Mod::get()->getSettingValue<bool>("toggle-legacy-sprite");
		auto modSprite = toggleLegacySprite ? CCSprite::createWithSpriteFrameName("modButton.png"_spr) : CCSprite::createWithSpriteFrameName("modButtonNew.png"_spr);

        auto myButton = CCMenuItemSpriteExtra::create(
			modSprite,
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
		popup->setZOrder(95);
		if (popup) {
			
			popup->show();
		}
	}
};