//
//  Game.hpp
//  BaseProject
//
//  Created by Daniel Harvey on 13/09/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp
#include "WindowHolder.hpp"
#include "SelbaWard.hpp"
#include <stdio.h>
class Game : public WindowHolder
{
public:
    Game(ige::FileLogger *LOG,SettingsManager *SM);
    ~Game(){};
    
    virtual void Start() override;
    virtual void Input(std::queue<sf::Event> &events, float dt) override;
    virtual void Render(Window *window) override;
    virtual void UI() override;
    virtual void EarlyUpdate() override;
    virtual void LateUpdate() override;
    virtual void FixedUpdate(float dt) override;
    
   void GameUI();
protected:
    sf::Texture DebugTexture,ExitTexture,PauseTexture,SettingsTexture;
};
#endif /* Game_hpp */
