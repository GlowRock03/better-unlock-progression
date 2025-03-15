#include "MyLevelDownloadDelegate.hpp"

void MyLevelDownloadDelegate::loadLevelsFinished(CCArray* levels, const char* key, int) {
    if (levels->count() < 1) {
        loadLevelsFailed(key, 0);
        return;
    }
    GameLevelManager::get()->m_levelManagerDelegate = nullptr;
    log::info("level downloaded, delegate complete");
    //level = GameLevelManager::sharedState()->getSavedLevel(id);
    auto levelLayer = LevelInfoLayer::scene(static_cast<GJGameLevel*>(levels->objectAtIndex(0)), false);
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5, levelLayer));
}

void MyLevelDownloadDelegate::loadLevelsFailed(const char* key, int) {

    GameLevelManager::get()->m_levelManagerDelegate = nullptr;
    log::info("level failed to download, delegate complete");
    FLAlertLayer::create(
        "Rate Limit",
        "Level download failed. Please try again later",
        "Ok"
    )->show();
}