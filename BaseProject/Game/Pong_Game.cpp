//
//  MyGame.cpp
//  BaseProject
//
//  Created by Daniel Harvey on 03/11/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#include "Pong_Game.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Yaml.hpp"
Pong_Game::Pong_Game(std::shared_ptr<ige::FileLogger> LOG,std::shared_ptr<SettingsManager> SM) : Game(LOG, SM)
{
    
}

void Pong_Game::Start()
{
    *log << "Game Start";
    GameArea = sf::IntRect(100,200,900,700);
    
    GameAreaShape.setSize(sf::Vector2f(GameArea.width-GameArea.left,GameArea.height-GameArea.top));
    GameAreaShape.setPosition(GameArea.left,GameArea.top);
    GameAreaShape.setFillColor(sf::Color::Black);
    GameAreaShape.setOutlineColor(sf::Color(70,70,70));
    GameAreaShape.setOutlineThickness(2);
    
    ball.Start();
    ball.SetPosition({static_cast<float>(GameArea.left + ((GameArea.width-GameArea.left)/2)),static_cast<float>(GameArea.top + ((GameArea.height-GameArea.top)/2))},true);
    ball.Reset(true);
    lastTouched = 1;
    
    if(settings->Player1AI)
    {
        paddles[0] = std::make_shared<ComputerPaddle>();
        paddles[0]->SetAIDifficulty(settings->AIDifficultyP1);
    }
    else
        paddles[0] = std::make_shared<PlayerPaddle>();
    paddles[0]->Start();
    paddles[0]->SetSize({settings->PaddleSize/8,settings->PaddleSize});
    paddles[0]->SetPosition({static_cast<float>(GameArea.left + 40),static_cast<float>(GameArea.top + ((GameArea.height-GameArea.top)/2))},true);
    
    paddles[0]->GiveGameArea(GameArea);
    paddles[0]->SetSide(true);
    paddles[0]->SetPaddleSpeed(settings->paddleSpeed);
    
    if(settings->Player2AI)
    {
        paddles[1] = std::make_shared<ComputerPaddle>();
        paddles[1]->SetAIDifficulty(settings->AIDifficultyP2);
    }
    else
    {
        paddles[1] = std::make_shared<PlayerPaddle>();
    }
    paddles[1]->Start();
    paddles[1]->SetSize({settings->PaddleSize/8,settings->PaddleSize});
    paddles[1]->SetPosition({static_cast<float>(GameArea.width)-30,static_cast<float>(GameArea.top + ((GameArea.height-GameArea.top)/2))},true);
    paddles[1]->GiveGameArea(GameArea);
    paddles[1]->SetSide(false);
    paddles[1]->SetPaddleSpeed(settings->paddleSpeed);
    
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
    
    ghostball.setFillColor(sf::Color(255,0,255,128));
    ghostball.setSize({6,6});
    ghostball.setOrigin(3,3);
    ghostball.setPosition(-10, -10);
}
void Pong_Game::Input(std::queue<sf::Event> &events, float dt)
{
    *log << "Game Input";
    if(!Pause)
    {
        for(int i{0}; i<paddles.size();i++)
        {
            paddles[i]->setlastTouched(lastTouched == i);
            paddles[i]->Giveballdetails(ball.GetPosition(), ball.GetVelocity());
            paddles[i]->Input(events, dt);
            paddles[i]->Move(dt);
            paddles[i]->Update(); //stop paddles leaving screen
        }
    }
}
void Pong_Game::Render(std::shared_ptr<Window> window)
{
    *log << "Game Render";
    window->BeginDraw(sf::Color(108,108,108));
    window->draw(GameAreaShape);
    window->draw(Player1Scores);
    window->draw(Player2Scores);
    
    paddles[0]->Render(window);
    paddles[1]->Render(window);
    if(settings->showBallPrediction)
        window->draw(ghostball);
    
    ball.Render(window);
    window->EndDraw();
    if(!Pause)
        AddSave();
}
void Pong_Game::UI()
{
    static bool show_data = false;
    static bool Play = false;
    static int scale = 1;
    static int current_scaled_frame = 0;
    *log << "UI";
    Game::GameUI();
    if(!PongSaves.empty() && Pause)
    {
        ImGui::Begin("Struct");
        if(ImGui::Button("LoadFromFile"))
        {
            //use filemanager
            LoadSaveFromFile("savetest.yml");
        }
        ImGui::Checkbox("Play", &Play);
        if(Play)
        {
            if(SelectedSave > PongSaves.size()-1)
                SelectedSave = 0;
            
            if(scale == 1 || SelectedSave == PongSaves.size()-1)
            {
                LoadSave(PongSaves[SelectedSave]);
                SelectedSave++;
            }
            else
            {
                LoadSave(scaleSave(PongSaves[SelectedSave], PongSaves[SelectedSave+1], scale, current_scaled_frame));
                if(current_scaled_frame >= scale)
                {
                    current_scaled_frame = 0;
                    SelectedSave++;
                }
                else
                    current_scaled_frame++;
            }
        }
        ImGui::SliderInt("ScaleSlider", &scale, 1, 25);
        if(ImGui::SliderInt("SaveSlider", &SelectedSave, 0, frame-1))
        {
            LoadSave(PongSaves[SelectedSave]);
        }
        ImGui::End();
    }
    if(!Pause)
    {
        frame++;
        Play = false;
    }
}
void Pong_Game::EarlyUpdate()
{
    *log << "Game Early Update";

}
void Pong_Game::FixedUpdate(float dt)
{
    *log << "Game Fixed Update";
    
    //ghost ball
    float tempX{ball.GetPosition().x},tempY{ball.GetPosition().y};
    float tempVX{ball.GetVelocity().x}, tempVY{ball.GetVelocity().y};
    int i = 0;
    
    auto predictballpos = [&] ()
    {
        tempX += tempVX * dt;
        tempY += tempVY * dt;
        
        if(tempY <= GameArea.top || tempY >= GameArea.height)
            tempVY = -tempVY;

        i++;
    };

    if(paddles[!lastTouched]->getOnLeft())
    {
        while (tempX > paddles[!lastTouched]->GetPosition().x)
        {
            predictballpos();
            if(i>(1/dt) * (100/60))
                break;
        }
    }
    else
    {
        while (tempX < paddles[!lastTouched]->GetPosition().x)
        {
            predictballpos();
            if(i>(1/dt) * (100/60))
                break;
        }
    }
    ghostball.setPosition(paddles[!lastTouched]->GetPosition().x, tempY);
    ball.Move(window->getDT());
}
void Pong_Game::LateUpdate()
{
    *log << "Game Late Update";

    oldlastTouched = lastTouched;
    touch = false;
    if(paddles[!lastTouched]->CollwithBall(&ball))
    {
        lastTouched = !lastTouched;
        touch = true;
    }
    else if(ball.GetPosition().x < GameArea.left)
    {
        paddles[1]->score++;
        Reset(true);
        Player2Scores.setString(std::to_string(paddles[1]->score));
    }
    else if(ball.GetPosition().x > GameArea.width)
    {
        paddles[0]->score++;
        Reset(true);
        Player1Scores.setString(std::to_string(paddles[0]->score));
    }
    else if((ball.GetPosition().y >= GameArea.height-(ball.GetSize().x/2)) || (ball.GetPosition().y <= (GameArea.top + ball.GetSize().x/2)))
    {
        ball.Collide();
    }
    else if((ball.GetPosition().y > GameArea.height+(ball.GetSize().x*6)) || (ball.GetPosition().y < GameArea.top-(ball.GetSize().x*6)))
    {
        Reset(lastTouched);
    }
    else
        return;
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
void Pong_Game::AddSave()
{
    PongSaveStruct PSS;
    PSS.P1PosX = paddles[0]->GetPosition().x;
    PSS.P1PosY = paddles[0]->GetPosition().y;
    PSS.P1VelX = paddles[0]->GetVelocity().x;
    PSS.P1VelY = paddles[0]->GetVelocity().y;
    PSS.P1SizeX = paddles[0]->GetSize().x;
    PSS.P1SizeY = paddles[0]->GetSize().y;
    PSS.P2PosX = paddles[1]->GetPosition().x;
    PSS.P2PosY = paddles[1]->GetPosition().y;
    PSS.P2VelX = paddles[1]->GetVelocity().x;
    PSS.P2VelY = paddles[1]->GetVelocity().y;
    PSS.P2SizeX = paddles[1]->GetSize().x;
    PSS.P2SizeY = paddles[1]->GetSize().y;
    PSS.BPosX = ball.GetPosition().x;
    PSS.BPosY = ball.GetPosition().y;
    PSS.BVelX = ball.GetVelocity().x;
    PSS.BVelY = ball.GetVelocity().y;
    PSS.BSizeX = ball.GetSize().x;
    PSS.BSizeY = ball.GetSize().y;
    PSS.P1Score = paddles[0]->score;
    PSS.P2Score = paddles[1]->score;
    PSS.SaveID = frame;
    PSS.BLastTouched = lastTouched;
    PongSaves.push_back(PSS);
}
void Pong_Game::saveSavestofile()
{
    Yaml::Node root;
    std::stringstream data;
    
    data << "AmountofSaves: " << frame << "\n\n";
    
    for(auto &PSS : PongSaves)
    {
        data << "Save_" << PSS.SaveID << ":\n - P1PosX: " << PSS.P1PosX << "\n   P1PosY: " << PSS.P1PosY << "\n   P1VelX: " << PSS.P1VelX << "\n   P1VelY: " << PSS.P1VelY << "\n   P1SizeX: " << PSS.P1SizeX << "\n   P1SizeY: " << PSS.P1SizeY <<
                "\n   P2PosX: " << PSS.P2PosX << "\n   P2PosY: " << PSS.P2PosY << "\n   P2VelX: " << PSS.P2VelX << "\n   P2VelY: " << PSS.P2VelY << "\n   P2SizeX: " << PSS.P2SizeX << "\n   P2SizeY: " << PSS.P2SizeY <<
                "\n   BPosX: " << PSS.BPosX << "\n   BPosY: " << PSS.BPosY << "\n   BVelX: " << PSS.BVelX << "\n   BVelY: " << PSS.BVelY << "\n   BSizeX: " << PSS.BSizeX << "\n   BSizeY: " << PSS.BSizeY <<
                "\n   P1Score: " << PSS.P1Score << "\n   P2Score: " << PSS.P2Score <<  "\n   LastTouched: " << PSS.BLastTouched << "\n   SaveID: " << PSS.SaveID << "\n\n";
    }
    Yaml::Parse(root, data);
    Yaml::Serialize(root, "savetest.yml");
}
void Pong_Game::LoadSave(PongSaveStruct PSS)
{
    paddles[0]->SetPosition({PSS.P1PosX,PSS.P1PosY});
    paddles[0]->SetVelocity({PSS.P1VelX,PSS.P1VelY});
    paddles[0]->SetSize({PSS.P1SizeX,PSS.P1SizeY});
    paddles[0]->score = PSS.P1Score;
    paddles[1]->SetPosition({PSS.P2PosX,PSS.P2PosY});
    paddles[1]->SetVelocity({PSS.P2VelX,PSS.P2VelY});
    paddles[1]->SetSize({PSS.P2SizeX,PSS.P2SizeY});
    paddles[1]->score = PSS.P2Score;
    ball.SetPosition({PSS.BPosX,PSS.BPosY});
    ball.SetVelocity({PSS.BVelX,PSS.BVelY});
    ball.SetSize({PSS.BSizeX,PSS.BSizeY});
    lastTouched = PSS.BLastTouched;
    
    Player1Scores.setString(std::to_string(paddles[0]->score));
    Player2Scores.setString(std::to_string(paddles[1]->score));
}
PongSaveStruct Pong_Game::scaleSave(PongSaveStruct PSS1,PongSaveStruct PSS2,int scale,int current)
{
    PongSaveStruct newPSS = PSS1;
    auto getDifferenceAndReturnScaledValue_single = [&](float val_1, float val_2)
    {
        if(val_1 != val_2)
        {
            float diff = val_2 - val_1;
            float scaleDiff = diff/scale;
            return val_1 + (scaleDiff*current);
        }
        else
            return val_1;
    };

    if(current < scale)
    {
        newPSS.P1PosX = getDifferenceAndReturnScaledValue_single(PSS1.P1PosX,PSS2.P1PosX);
        newPSS.P1PosY = getDifferenceAndReturnScaledValue_single(PSS1.P1PosY,PSS2.P1PosY);
        newPSS.P1VelX = getDifferenceAndReturnScaledValue_single(PSS1.P1VelX,PSS2.P1VelX);
        newPSS.P1VelY = getDifferenceAndReturnScaledValue_single(PSS1.P1VelY,PSS2.P1VelY);
        newPSS.P1SizeX = getDifferenceAndReturnScaledValue_single(PSS1.P1SizeX,PSS2.P1SizeX);
        newPSS.P1SizeY = getDifferenceAndReturnScaledValue_single(PSS1.P1SizeY,PSS2.P1SizeY);
        newPSS.P2PosX = getDifferenceAndReturnScaledValue_single(PSS1.P2PosX,PSS2.P2PosX);
        newPSS.P2PosY = getDifferenceAndReturnScaledValue_single(PSS1.P2PosY,PSS2.P2PosY);
        newPSS.P2VelX = getDifferenceAndReturnScaledValue_single(PSS1.P2VelX,PSS2.P2VelX);
        newPSS.P2VelY = getDifferenceAndReturnScaledValue_single(PSS1.P2VelY,PSS2.P2VelY);
        newPSS.P2SizeX = getDifferenceAndReturnScaledValue_single(PSS1.P2SizeX,PSS2.P2SizeX);
        newPSS.P2SizeY = getDifferenceAndReturnScaledValue_single(PSS1.P2SizeY,PSS2.P2SizeY);
        newPSS.BPosX = getDifferenceAndReturnScaledValue_single(PSS1.BPosX,PSS2.BPosX);
        newPSS.BPosY = getDifferenceAndReturnScaledValue_single(PSS1.BPosY,PSS2.BPosY);
        newPSS.BVelX = getDifferenceAndReturnScaledValue_single(PSS1.BVelX,PSS2.BVelX);
        newPSS.BVelY = getDifferenceAndReturnScaledValue_single(PSS1.BVelY,PSS2.BVelY);
        newPSS.BSizeX = getDifferenceAndReturnScaledValue_single(PSS1.BSizeX,PSS2.BSizeX);
        newPSS.BSizeY = getDifferenceAndReturnScaledValue_single(PSS1.BSizeY,PSS2.BSizeY);
    }
    else
        newPSS = PSS2;
    return newPSS;
}
void Pong_Game::LoadSaveFromFile(std::string filename)
{
    Yaml::Parse(loadROOT, filename.c_str());
    PongSaves.clear();
    frame = loadROOT["AmountofSaves"].As<int>();
    PongSaveStruct PSS;
    for(int i{0}; i<frame;i++)
    {
        PSS.P1PosX = loadROOT["Save_" + std::to_string(i)][0]["P1PosX"].As<float>();
        PSS.P1PosY = loadROOT["Save_" + std::to_string(i)][0]["P1PosY"].As<float>();
        PSS.P1VelX = loadROOT["Save_" + std::to_string(i)][0]["P1VelX"].As<float>();
        PSS.P1VelY = loadROOT["Save_" + std::to_string(i)][0]["P1VelY"].As<float>();
        PSS.P1SizeX = loadROOT["Save_" + std::to_string(i)][0]["P1SizeX"].As<float>();
        PSS.P1SizeY = loadROOT["Save_" + std::to_string(i)][0]["P1SizeY"].As<float>();
        PSS.P2PosX = loadROOT["Save_" + std::to_string(i)][0]["P2PosX"].As<float>();
        PSS.P2PosY = loadROOT["Save_" + std::to_string(i)][0]["P2PosY"].As<float>();
        PSS.P2VelX = loadROOT["Save_" + std::to_string(i)][0]["P2VelX"].As<float>();
        PSS.P2VelY = loadROOT["Save_" + std::to_string(i)][0]["P2VelY"].As<float>();
        PSS.P2SizeX = loadROOT["Save_" + std::to_string(i)][0]["P2SizeX"].As<float>();
        PSS.P2SizeY = loadROOT["Save_" + std::to_string(i)][0]["P2SizeY"].As<float>();
        PSS.BPosX = loadROOT["Save_" + std::to_string(i)][0]["BPosX"].As<float>();
        PSS.BPosY = loadROOT["Save_" + std::to_string(i)][0]["BPosY"].As<float>();
        PSS.BVelX = loadROOT["Save_" + std::to_string(i)][0]["BVelX"].As<float>();
        PSS.BVelY = loadROOT["Save_" + std::to_string(i)][0]["BVelY"].As<float>();
        PSS.BSizeX = loadROOT["Save_" + std::to_string(i)][0]["BSizeX"].As<float>();
        PSS.BSizeY = loadROOT["Save_" + std::to_string(i)][0]["BSizeY"].As<float>();
        PSS.P1Score = loadROOT["Save_" + std::to_string(i)][0]["P1Score"].As<int>();
        PSS.P2Score = loadROOT["Save_" + std::to_string(i)][0]["P2Score"].As<int>();
        PSS.SaveID = loadROOT["Save_" + std::to_string(i)][0]["SaveID"].As<int>();
        PSS.BLastTouched = loadROOT["Save_" + std::to_string(i)][0]["LastTouched"].As<int>();
        PongSaves.push_back(PSS);
    }
}
/*
 ImGui::Checkbox("ShowSaveData", &show_data);
 if(show_data)
 {
     ImGui::Text("Size of List = %i", (int)PongSaves.size());
     ImGui::Text("P1PosX:%f\nP1PosY:%f\nP1VelX:%f\nP1VelY:%f\nP1SizeX:%f\nP1SizeY:%f\nP2PosX:%f\nP2PosY:%f\nP2VelX:%f\nP2VelY:%f\nP2SizeX:%f\nP2SizeY:%f\nBPosX:%f\nBPosY:%f\nBVelX:%f\nBVelY:%f\nBSizeX:%f\nBSizeY:%f\nP1Score:%i\nP2Score:%i\nSaveID:%i",
     PongSaves[frame].P1PosX,
     PongSaves[frame].P1PosY,
     PongSaves[frame].P1VelX,
     PongSaves[frame].P1VelY,
     PongSaves[frame].P1SizeX,
     PongSaves[frame].P1SizeY,
     PongSaves[frame].P2PosX,
     PongSaves[frame].P2PosY,
     PongSaves[frame].P2VelX,
     PongSaves[frame].P2VelY,
     PongSaves[frame].P2SizeX,
     PongSaves[frame].P2SizeY,
     PongSaves[frame].BPosX,
     PongSaves[frame].BPosY,
     PongSaves[frame].BVelX,
     PongSaves[frame].BVelY,
     PongSaves[frame].BSizeX,
     PongSaves[frame].BSizeY,
     PongSaves[frame].P1Score,
     PongSaves[frame].P2Score,
     PongSaves[frame].SaveID);
     if(ImGui::Button("save"))
         saveSavestofile();
 }
 */
