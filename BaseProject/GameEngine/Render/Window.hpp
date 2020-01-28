//
//  Window.hpp
//  SFGameEngine
//
//  Created by Daniel Harvey on 27/05/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp


#include "imgui.h"
#include "imgui-SFML.h"
#include "FPS.hpp"
#include <SFML/Graphics.hpp>
#include "FileLogger.hpp"
#include <thread>
#include <queue>

class Window
{
public:
    Window(std::shared_ptr<ige::FileLogger> LOG);
    void Start(const std::string& windowName,sf::Vector2u WindowSize,bool Fullscreen = false);
    void Update();
    void BeginDraw(sf::Color colour = sf::Color::Magenta);
    void draw(const sf::Drawable& drawable);
    void EndDraw();
    void Close();
    void SetSize(sf::Vector2u size);
    void SetVsync(bool Vsync);
    void SetTitle(std::string &title);
    bool IsOpen() const;

    float getDT();
    int GetFPS();
    
    sf::Event GetEvent();
    sf::Vector2u GetSize();
    sf::Vector2u GetCentre();
    sf::Vector2i GetMouse();
    
    sf::RenderWindow window;
    
    bool RenderToTexture = false;
    
    std::queue<sf::Event> events;
    
private:
    void CalculateDT();

    sf::RenderTexture rendertexture;
    sf::Sprite windowtexture;
    sf::Clock clock;
    sf::Event event;
    
    FPS fps;
    float deltatime;

    std::shared_ptr<ige::FileLogger> log;
};


#endif /* Window_hpp */

