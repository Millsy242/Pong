//
//  Entity.cpp
//  BaseProject
//
//  Created by Daniel Harvey on 13/09/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#include "Entity.hpp"

void Entity::LoadTexture(std::string filepath)
{
    Collision::CreateTextureAndBitmask(EntityTexture, filepath);
    EntitySprite.setTexture(EntityTexture);
}
void Entity::Render(std::shared_ptr<Window> window)
{
    if(Active)
        window->draw(EntitySprite);
}
sf::Vector2f Entity::GetPosition()
{
    return Position;
}
sf::Vector2f Entity::GetOldPosition()
{
    return OldPosition;
}
 void Entity::Update()
{
    OldPosition = Position;
    EntityUpdate();
}
void Entity::SetPosition(sf::Vector2f NewPosition)
{
    Position = NewPosition;
    EntitySprite.setPosition(Position);
}
void Entity::SetPosition(float x, float y)
{
    SetPosition(sf::Vector2f(x,y));
}
void Entity::ResetPosition()
{
    Position = OldPosition;
    SetPosition(OldPosition);
}
bool Entity::isCollision(sf::Sprite *sprite)
{
    return Collision::PixelPerfectTest(EntitySprite, *sprite);
}
sf::Sprite Entity::GetSprite()
{
    return EntitySprite;
}
void Entity::SetScale(sf::Vector2f scale)
{
    EntitySprite.setScale(scale);
}
void  Entity::FlipTexture(bool Vertical)
{
    sf::Image temp = EntityTexture.copyToImage();
    if(Vertical)
        temp.flipVertically();
    else
        temp.flipHorizontally();
    
    EntityTexture.loadFromImage(temp);
    Collision::CreateTextureAndBitmask(&EntityTexture);
    EntitySprite.setTexture(EntityTexture);
    
}
