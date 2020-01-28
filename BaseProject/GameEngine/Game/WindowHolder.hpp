//
//  Game.hpp
//  BaseProject
//
//  Created by Daniel Harvey on 15/06/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#ifndef WindowHolder_hpp
#define WindowHolder_hpp
#include "Base.hpp"

#include "Window.hpp"
#include "FileLogger.hpp"
#include "SettingsManager.hpp"
class WindowHolder : public Base
{
public:
    
    virtual ~WindowHolder(){};
    virtual void Start()override;
    virtual void Update()override;
    virtual void EarlyUpdate() = 0;
    virtual void LateUpdate() = 0;
    virtual void FixedUpdate(float dt) override = 0;
    virtual void Render(std::shared_ptr<Window> window) override= 0;
    virtual void Input(std::queue<sf::Event> &events, float dt) override = 0;
    
    virtual void Exit() override;
    void Stats();
    void GiveWindow(std::shared_ptr<Window> w);
    bool Continue = true;
    
protected:
    bool Pause = false;
    bool Active = true;
    bool Debug{false},DebugMetrics{false},DebugUserGuide{false},DebugStyleSel{false},DebugStyleEditer{false};
    std::shared_ptr<Window> window;
    std::shared_ptr<ige::FileLogger> log;
    std::shared_ptr<SettingsManager> settings;
private:
    sf::Clock c;
    const sf::Time TimePerFrame = sf::seconds(1.f/60.f);
    sf::Time elapsedTime;
    sf::Time OverallPlayerLapTime;
    sf::Time mStatisticsUpdateTime;
    sf::Time TotalTime;
    sf::Time timeSinceLastUpdate;
};

#endif /* WindowHolder_hpp */

