//
//  Menu.hpp
//  BaseProject
//
//  Created by Daniel Harvey on 13/09/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#ifndef Menu_hpp
#define Menu_hpp

#include "WindowHolder.hpp"
#include <stdio.h>

class Menu : public WindowHolder
{
public:
    Menu(std::shared_ptr<ige::FileLogger> LOG,std::shared_ptr<SettingsManager> SM);
    ~Menu(){};
        
    virtual void Start() override;
    virtual void Input(std::queue<sf::Event> &events, float dt) override;
    virtual void Render(std::shared_ptr<Window> window) override;
    virtual void UI() override;
    virtual void EarlyUpdate() override;
    virtual void LateUpdate() override;
    virtual void FixedUpdate(float dt) override;
    
protected:
    virtual void StartScreen();
    virtual void ProgramSettingsMenu();
    virtual void GameSettingsMenu();
    virtual void GameSettingsMenuTWO();
private:
    sf::Texture StartTexture,SettingsTexture,ExitTexture;
};
#endif /* Menu_hpp */
