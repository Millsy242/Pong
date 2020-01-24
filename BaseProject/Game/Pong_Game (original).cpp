//
//  MyGame.cpp
//  BaseProject
//
//  Created by Daniel Harvey on 03/11/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#include "Pong_Game.hpp"
#include <iostream>
Pong_Game::Pong_Game(ige::FileLogger *LOG,SettingsManager *SM) : Game(LOG, SM)
{
    
}

void Pong_Game::Start()
{
    *log << "Game Start";
    ball.Start();
    ball.SetPosition({static_cast<float>(window->GetSize().x)/2,static_cast<float>(window->GetSize().y)/2},true);
    ball.Reset(true);
    lastTouched = 1;
    
    Paddle p1;
    p1.Start();
    p1.SetPosition({40,static_cast<float>(window->GetSize().y)/2},true);
    Paddle p2;
    p2.Start();
    p2.SetPosition({static_cast<float>(window->GetSize().x)-30,static_cast<float>(window->GetSize().y)/2},true);
    
    paddles[0] = p1;
    paddles[1] = p2;
    
    font.loadFromFile("PINGPONG.TTF");
    
    Player1Scores.setPosition({static_cast<float>(window->GetSize().x)*0.25f,40});
    Player1Scores.setCharacterSize(220);
    Player1Scores.setFont(font);
    Player1Scores.setString(std::to_string(paddles[0].score));
    Player1Scores.setFillColor(sf::Color(255,255,255,50));
    Player1Scores.setOrigin(Player1Scores.getLocalBounds().width/2, Player1Scores.getLocalBounds().height/2);
    
    Player2Scores.setPosition({static_cast<float>(window->GetSize().x)*0.75f,40});
    Player2Scores.setCharacterSize(220);
    Player2Scores.setFont(font);
    Player2Scores.setString(std::to_string(paddles[1].score));
    Player2Scores.setFillColor(sf::Color(255,255,255,50));
    Player2Scores.setOrigin(Player2Scores.getLocalBounds().width/2, Player2Scores.getLocalBounds().height/2);
    
    ghostball.setFillColor(sf::Color(255,0,255,50));
    ghostball.setSize({6,6});
    ghostball.setOrigin(3,3);
    ghostball.setPosition(-10, -10);
}
void Pong_Game::Input(std::queue<sf::Event> &events)
{
    static float PaddleSpeed = 400.f;
    *log << "Game Input";

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        paddles[0].Move(0, -PaddleSpeed, window->getDT());

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        paddles[0].Move(0, PaddleSpeed, window->getDT());
    
    if(lastTouched != 1)
    {
        float tempX{ball.GetPosition().x},tempY{ball.GetPosition().y};
        float tempVX{ball.GetVelocity().x}, tempVY{ball.GetVelocity().y};
        int i = 0;
        while (tempX < paddles[1].GetPosition().x)
        {
            tempX += tempVX * window->getDT()*1;
            tempY += tempVY * window->getDT()*1;
            
            if(tempY<=0 || tempY >= window->GetSize().y)
                tempVY = -tempVY;
            
            if(i > 0)
                break;
            i++;
        }
        if(tempY > paddles[1].GetPosition().y)
            paddles[1].Move(0, PaddleSpeed, window->getDT());
        if(tempY < paddles[1].GetPosition().y)
            paddles[1].Move(0, -PaddleSpeed, window->getDT());
        
        ghostball.setPosition(paddles[!lastTouched].GetPosition().x, tempY);
    }
//Use this when varying AI difficulty, use paddlespeed_modifier to vary difficult. disable for lower difficulty
//Also for lower difficulty, lower ball speed and ai reaction time
    /*
    if(lastTouched == 1)
    {
        int paddlespeed_modifier = 4;
        if(window->GetSize().y/2 > paddles[1].GetPosition().y)
            paddles[1].Move(0, PaddleSpeed/paddlespeed_modifier, window->getDT());
        if(window->GetSize().y/2 < paddles[1].GetPosition().y)
            paddles[1].Move(0, -PaddleSpeed/paddlespeed_modifier, window->getDT());
    }
*/
    for(int i{0}; i<paddles.size();i++)
    {
        if(paddles[i].GetPosition().y - paddles[i].GetSize().y/2 < 0)
            paddles[i].SetPosition({paddles[i].GetPosition().x,paddles[i].GetSize().y/2});
        if(paddles[i].GetPosition().y + paddles[i].GetSize().y/2 > window->GetSize().y)
        paddles[i].SetPosition({paddles[i].GetPosition().x,window->GetSize().y - paddles[i].GetSize().y/2});
    }
     
}
void Pong_Game::Render(Window *window)
{
    *log << "Game Render";
    window->BeginDraw(sf::Color::Black);
    window->draw(Player1Scores);
    window->draw(Player2Scores);
    
    paddles[0].Render(window);
    paddles[1].Render(window);
    window->draw(ghostball);
    ball.Render(window);
    window->EndDraw();
}
void Pong_Game::UI()
{
    *log << "UI";
    Game::GameUI();
}
void Pong_Game::EarlyUpdate()
{
    *log << "Game Early Update";

}
void Pong_Game::LateUpdate()
{
    *log << "Game Late Update";
    oldlastTouched = lastTouched;
    touch = false;
    if(paddles[0].CollwithBall(&ball))
    {
        lastTouched = 0;
        touch = true;
    }
    if(paddles[1].CollwithBall(&ball))
    {
        lastTouched = 1;
        touch = true;
    }
    
    if(touch && oldlastTouched == lastTouched)
    {
        Reset(false);
    }
    
    if(ball.GetPosition().x < 0)
    {
        paddles[1].score++;
        Reset(true);
        Player2Scores.setString(std::to_string(paddles[1].score));
    }

    if(ball.GetPosition().x > window->GetSize().x)
    {
        paddles[0].score++;
        Reset(true);
        Player1Scores.setString(std::to_string(paddles[0].score));
    }
    
    if((ball.GetPosition().y >= window->GetSize().y) || (ball.GetPosition().y <= 0))
        ball.Collide();
    
    if((ball.GetPosition().y > window->GetSize().y+10) || (ball.GetPosition().y < -10))
        ball.Reset(lastTouched);
    
     ball.Move(window->getDT());
}
void Pong_Game::Reset(bool scored)
{
    paddles[0].ResetPosition();
    paddles[1].ResetPosition();
    
    if(scored)
    {
        ball.Reset(!lastTouched);
        lastTouched = !lastTouched;
        if(paddles[0].score >= settings->MaxScore || paddles[1].score >= settings->MaxScore)
        {
            if(paddles[0].score > paddles[1].score)
            {
                if(paddles[0].score - settings->WinMargin > paddles[1].score)
                {
                    Player1Scores.setString("WIN");
                    Player2Scores.setString("LOSE");
                    Pause = true;
                }
            }
            else if(paddles[0].score < paddles[1].score)
            {
                if(paddles[1].score - settings->WinMargin > paddles[0].score)
                {
                    Player2Scores.setString("WIN");
                    Player1Scores.setString("LOSE");
                    Pause = true;
                }
            }
        }
    }
    else
    {
        ball.Reset(lastTouched);
    }
}
