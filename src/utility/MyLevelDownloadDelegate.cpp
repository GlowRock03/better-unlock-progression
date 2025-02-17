#include "MyLevelDownloadDelegate.hpp"

void MyLevelDownloadDelegate::levelDownloadFinished(GJGameLevel* level) {

    GameLevelManager::get()->m_levelDownloadDelegate = nullptr;
    log::info("level downloaded, delegate complete");
    //level = GameLevelManager::sharedState()->getSavedLevel(id);
    auto levelLayer = LevelInfoLayer::create(level, false);
    auto scene = CCScene::create();
    scene->addChild(levelLayer);
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5, scene));
}

void MyLevelDownloadDelegate::levelDownloadFailed(int id) {

    GameLevelManager::get()->m_levelDownloadDelegate = nullptr;
    log::info("level failed to download, delegate complete");
    FLAlertLayer::create(
        "Rate Limit",
        "Level download failed. Please try again later",
        "Ok"
    )->show();
}