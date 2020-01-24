//
//  SettingsManager.hpp
//  BaseProject
//
//  Created by Daniel Harvey on 27/10/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#ifndef SettingsManager_hpp
#define SettingsManager_hpp

#include "SettingsParser.hpp"
#include <SFML/Graphics.hpp>

class SettingsManager
{
public:
    SettingsManager();
    ~SettingsManager();
    
    void Setup();
    void UpdateFile();
    
    sf::Vector2u MenuSize{400,600};
    sf::Vector2u GameSize{1920,1080};
    sf::Vector2u MenuApsectRatio{4,3};
    sf::Vector2u GameApsectRatio{16,9};
    bool Vsync = false;
    bool Fullscreen = false;
    
    int MaxScore = 7;
    int WinMargin = 1;
private:
    SettingsParser parse;
    std::string FileName = "Settings.txt";
    int SettingsVersion = 4; 

};

#endif /* SettingsManager_hpp */
