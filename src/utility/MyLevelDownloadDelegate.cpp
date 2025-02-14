#include "MyLevelDownloadDelegate.hpp"

void MyLevelDownloadDelegate::levelDownloadFinished(GJGameLevel* level) {

    GameLevelManager::get()->m_levelDownloadDelegate = nullptr;
    log::info("level downloaded, delegate complete");
}

void MyLevelDownloadDelegate::levelDownloadFailed(int id) {

    GameLevelManager::get()->m_levelDownloadDelegate = nullptr;
    log::info("level failed to download, delegate complete");
}