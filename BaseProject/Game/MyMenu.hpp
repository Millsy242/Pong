//
//  MyMenu.hpp
//  BaseProject
//
//  Created by Daniel Harvey on 03/11/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#ifndef MyMenu_hpp
#define MyMenu_hpp

#include <stdio.h>
#include "Menu.hpp"

class MyMenu : public Menu
{
public:
    MyMenu(std::shared_ptr<ige::FileLogger> LOG,std::shared_ptr<SettingsManager> SM);
    
    void GameSettingsMenu() override;
    void GameSettingsMenuTWO() override;
    void Input(std::queue<sf::Event> &events, float dt) override;
    void Render(std::shared_ptr<Window> window) override;
    
    void EarlyUpdate() override;
    void LateUpdate() override;
    
private:
};

#endif /* MyMenu_hpp */
