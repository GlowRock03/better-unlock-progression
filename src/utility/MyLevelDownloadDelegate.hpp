#pragma once

#ifndef MYLEVELDOWNLOADDELEGATE_HPP
#define MYLEVELDOWNLOADDELEGATE_HPP

#include <Geode/Geode.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/binding/GameLevelManager.hpp>

using namespace geode::prelude;

#include <Geode/binding/LevelDownloadDelegate.hpp>
class MyLevelDownloadDelegate : public LevelDownloadDelegate {
private:

    int id = 114471227;
public:

    static MyLevelDownloadDelegate* get() {

        static MyLevelDownloadDelegate instance;
        return &instance;
    }

    void levelDownloadFinished(GJGameLevel* level) override;
    void levelDownloadFailed(int id) override;
};

#endif