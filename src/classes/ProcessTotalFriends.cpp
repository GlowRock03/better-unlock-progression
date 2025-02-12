#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class ProcessTotalFriends {

public:
    FriendsProfilePage* m_friendsPage = nullptr;

    int fetchFriendCount() {

        m_friendsPage = FriendsProfilePage::create(UserListType::Friends);
        //m_friendsPage->retain();

        int friendCount = processFriendCount();

        m_friendsPage = nullptr;

        return friendCount;
    }

    int processFriendCount() {
 
        FriendsProfilePage* m_friendsPage = FriendsProfilePage::create(UserListType::Friends);
        
        int friendCount = -1;

        for (auto node : CCArrayExt<CCNode*>(m_friendsPage->m_mainLayer->getChildren())) {

            if (auto label = typeinfo_cast<CCLabelBMFont*>(node)) {                

                std::string nodeText = label->getString();             
                if (nodeText.find("Total friends:") != std::string::npos) {

                    std::string number = nodeText.substr(
                        nodeText.find(":") + 2, 
                        nodeText.length() - nodeText.find(":") - 2
                    );
                    friendCount = std::atoi(number.c_str());
                    break;
                }
            }
        }

        m_friendsPage->removeFromParentAndCleanup(true);
        m_friendsPage->release();
        m_friendsPage = nullptr;

        return friendCount;
    }
};