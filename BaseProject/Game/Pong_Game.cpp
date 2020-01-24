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
    
    paddles[0] = std::make_shared<ComputerPaddle>();
    
    paddles[0]->Start();
    paddles[0]->SetPosition({40,static_cast<float>(window->GetSize().y)/2},true);
    paddles[0]->GiveWindowSize(sf::Vector2f(window->GetSize()));
    paddles[0]->SetSide(true);
    
    paddles[1] = std::make_shared<ComputerPaddle>();
    paddles[1]->Start();
    paddles[1]->SetPosition({static_cast<float>(window->GetSize().x)-30,static_cast<float>(window->GetSize().y)/2},true);
    paddles[1]->GiveWindowSize(sf::Vector2f(window->GetSize()));
    paddles[1]->SetSide(false);
    
    font.loadFromFile("PINGPONG.TTF");
    
    Player1Scores.setPosition({static_cast<float>(window->GetSize().x)*0.25f,40});
    Player1Scores.setCharacterSize(220);
    Player1Scores.setFont(font);
    Player1Scores.setString(std::to_string(paddles[0]->score));
    Player1Scores.setFillColor(sf::Color(255,255,255,50));
    Player1Scores.setOrigin(Player1Scores.getLocalBounds().width/2, Player1Scores.getLocalBounds().height/2);
    
    Player2Scores.setPosition({static_cast<float>(window->GetSize().x)*0.75f,40});
    Player2Scores.setCharacterSize(220);
    Player2Scores.setFont(font);
    Player2Scores.setString(std::to_string(paddles[1]->score));
    Player2Scores.setFillColor(sf::Color(255,255,255,50));
    Player2Scores.setOrigin(Player2Scores.getLocalBounds().width/2, Player2Scores.getLocalBounds().height/2);
    
    ghostball.setFillColor(sf::Color(255,0,255,255));
    ghostball.setSize({6,6});
    ghostball.setOrigin(3,3);
    ghostball.setPosition(-10, -10);
}
void Pong_Game::Input(std::queue<sf::Event> &events, float dt)
{
    
    *log << "Game Input";
    for(int i{0}; i<paddles.size();i++)
    {
        paddles[i]->setlastTouched(lastTouched == i);
        paddles[i]->Giveballdetails(ball.GetPosition(), ball.GetVelocity());
        paddles[i]->Input(events, dt);
        paddles[i]->Update(); //stop paddles leaving screen
    }
    

    

}
void Pong_Game::Render(Window *window)
{
    
    *log << "Game Render";
    window->BeginDraw(sf::Color::Black);
    window->draw(Player1Scores);
    window->draw(Player2Scores);
    
    paddles[0]->Render(window);
    paddles[1]->Render(window);
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
void Pong_Game::FixedUpdate(float dt)
{
    *log << "Game Fixed Update";
    
    //ghost ball
    //move this to fixedupdate
    float tempX{ball.GetPosition().x},tempY{ball.GetPosition().y};
    float tempVX{ball.GetVelocity().x}, tempVY{ball.GetVelocity().y};
    float wy{(float)window->GetSize().y};
    
    int i = 0;
    
    auto predictballpos = [&] ()
    {
        tempX += tempVX * dt;
        tempY += tempVY * dt;
        
        if(tempY <= 0 || tempY >= wy)
            tempVY = -tempVY;

        i++;
    };

    if(paddles[!lastTouched]->GetPosition().x > window->GetSize().x/2)
        while (tempX < paddles[!lastTouched]->GetPosition().x)
        {
            predictballpos();
            if(i>100)
                break;
        }
    else
        while (tempX > paddles[!lastTouched]->GetPosition().x)
        {
            predictballpos();
            if(i>100)
                break;
        }
    ghostball.setPosition(paddles[!lastTouched]->GetPosition().x, tempY);
    
}
void Pong_Game::LateUpdate()
{
    *log << "Game Late Update";

    oldlastTouched = lastTouched;
    touch = false;
    if(paddles[0]->CollwithBall(&ball))
    {
        lastTouched = 0;
        touch = true;
    }
    if(paddles[1]->CollwithBall(&ball))
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
        paddles[1]->score++;
        Reset(true);
        Player2Scores.setString(std::to_string(paddles[1]->score));
    }

    if(ball.GetPosition().x > window->GetSize().x)
    {
        paddles[0]->score++;
        Reset(true);
        Player1Scores.setString(std::to_string(paddles[0]->score));
    }
    
    if((ball.GetPosition().y >= window->GetSize().y) || (ball.GetPosition().y <= 0))
        ball.Collide();
    
    if((ball.GetPosition().y > window->GetSize().y+10) || (ball.GetPosition().y < -10))
        ball.Reset(lastTouched);
    
     ball.Move(window->getDT());
    

}
void Pong_Game::Reset(bool scored)
{
    paddles[0]->ResetPosition();
    paddles[1]->ResetPosition();
    
    if(scored)
    {
        ball.Reset(!lastTouched);
        lastTouched = !lastTouched;
        if(paddles[0]->score >= settings->MaxScore || paddles[1]->score >= settings->MaxScore)
        {
            if(paddles[0]->score > paddles[1]->score)
            {
                if(paddles[0]->score - settings->WinMargin > paddles[1]->score)
                {
                    Player1Scores.setString("WIN");
                    Player2Scores.setString("LOSE");
                    Pause = true;
                }
            }
            else if(paddles[0]->score < paddles[1]->score)
            {
                if(paddles[1]->score - settings->WinMargin > paddles[0]->score)
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
