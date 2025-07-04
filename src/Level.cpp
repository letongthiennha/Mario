#include "Level.h"
#include "ResourceManager.h"
#include "Map.h"
#include "LevelState.h"
#include "SoundControoler.h"
Level::Level(int mapNumber,GameState* gamestate,const PlayerData& playerData):map(mapNumber),items(map.getItems()),gameState(gamestate),
player(map.getStartPositionForMario(),playerData),
interactiveTiles(map.getInteractiveTiles()),
state(LevelState::LEVEL_STATE_PLAYING)
{
        switch(mapNumber) {
            case 0:
                background = ResourceManager::getInstance().getTexture("BACKGROUND_0");
                backgroundColor = Color{0,96,184,255}; // Default color for level 0
                break;
            case 1:
                background = ResourceManager::getInstance().getTexture("BACKGROUND_LEVEL_1");
                backgroundColor = {0,96,184,255};

                break;
            case 2:
                background = ResourceManager::getInstance().getTexture("LEVEL_2_BACKGROUND");
                backgroundColor = WHITE;
                break;
        //     case 3:
        //         background = ResourceManager::getInstance().getTexture("LEVEL_3_BACKGROUND");
        //         backgroundColor = ResourceManager::getInstance().getColor("LEVEL_3_BACKGROUND_COLOR");
        //         break;
            default:
                // background = ResourceManager::getInstance().getTexture("DEFAULT_BACKGROUND");
                backgroundColor = WHITE;
        }
        player.addObserver(&gameState->getHUD());
        player.addCoin(0);
        player.addLives(0);
        player.addScore(0);

        camera.offset = Vector2{(float)GetScreenWidth()/2,(float) GetScreenHeight()/2};
        camera.target = player.getPosition();
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;


}


LevelState Level::getState() const
{
    return state;
}
bool Level::needReset() const
{
    return state == LevelState::LEVEL_STATE_NEED_RESET;
}
Level::~Level()
{
}

std::unique_ptr<PlayerData> Level::getPlayerData()
{
    return player.createMemento();
}

bool Level::IsCompleted()
{
    return this->state==LevelState::LEVEL_STATE_COMPLETED;
}

void Level::UpdateLevel()
{
        //Check collision when it is not in special state
        if(player.getState()!=ENTITY_STATE_DYING&&player.getState()!=ENTITY_STATE_TO_BE_REMOVED&&player.getState()!=ENTITY_STATE_VICTORY_DANCE) // If player falls off the screen, reset the level
        {
                if(player.getPosition().y>=GetScreenHeight()-32) // If player falls below the screen, reset the level
                {
                        player.die();
                        return;
                }
                for(auto const & tile : interactiveTiles)
                {
                        CollisionInfo playerCollision = player.CheckCollisionType(*tile);
                        if(playerCollision)
                        collisionMediator.HandleCollision(&player, tile);
                        
                        for(auto& fireball : *player.getFireballs())
                        {
                                CollisionInfo fireballCollision = fireball->CheckCollisionType(*tile);
                                if(fireballCollision)
                                {
                                        collisionMediator.HandleCollision(fireball, tile);
                                }

                        }
                };
        
                for (auto const & item : items)
                {
                        CollisionInfo playerCollision = player.CheckCollisionType(*item);
                        if(playerCollision)
                        {
                                collisionMediator.HandleCollision(&player, item);
                        }
		}

            for (auto const& item : items) {
                // Check collision with each interactive tile
                if (dynamic_cast<Coin*>(item) != nullptr) {
                    continue;
                }

                item->setOnGround(false);

                // Skip coins, as they are handled separately
                for (auto const& tile : interactiveTiles) {
                    CollisionInfo itemCollision = item->CheckCollisionType(*tile);

                    if (itemCollision) {
                        collisionMediator.HandleCollision(item, tile);
                    }
                }
            }
                if(player.getPosition().x<0)
                {
                        player.setPosition({0, player.getPosition().y}); // Prevent player from going off the left side of the screen
                }
                else if(player.getPosition().x>map.getMapWidth()-player.getSize().x)
                {
                        player.setPosition({map.getMapWidth()-player.getSize().x, player.getPosition().y}); // Prevent player from going off the right side of the screen
                }
        }
        

        for (auto const& item : items) {
            if(item->getState()==ItemState::IDLE)
                item->updateStateAndPhysic();
            if (item->getState() == ItemState::POP_UP)
                item->Activate();
        }

        if(player.getState() == ENTITY_STATE_TO_BE_REMOVED) // If player is dead, reset the level
        {
                if(player.getLives() > 0) // If player has lives left, reset the level
                {
                        state = LevelState::LEVEL_STATE_NEED_RESET;
                }
                else // If player has no lives left, game over
                {
                        state = LevelState::LEVEL_STATE_GAME_OVER;
                }
                return;
        }

        if(player.getPosition().x<=0) // If player is past the left edge of the screen, reset the level
        {
                player.setPosition(Vector2{0,player.getPosition().y});
        }
        else if(player.getPosition().x>=map.getMapWidth()-player.getSize().x) // If player is past the right edge of the screen, reset the level
        {
                player.setPosition(Vector2{map.getMapWidth()-player.getSize().x,player.getPosition().y});
        }
        if(player.getPosition().x>3000) // If player is past a certain point, switch to next level
        {
                state= LevelState::LEVEL_STATE_COMPLETED;
                player.startVictoryDance();
                return;
        } 


        player.updateStateAndPhysic();

}
void Level::DrawLevel()
{
        ClearBackground(backgroundColor);
        camera.target.y = GetScreenHeight()/2;
        if(player.getPosition().x>GetScreenWidth()/2&&player.getPosition().x<map.getMapWidth()-GetScreenWidth()/2)
        {
                camera.target.x = player.getPosition().x ;
        }
        else if(player.getPosition().x<GetScreenWidth()/2)
        {
                camera.target.x = GetScreenWidth()/2;
        }
        else camera.target.x=map.getMapWidth()-GetScreenWidth()/2;

        if(camera.target.x-GetScreenWidth()/2>=currBackgroundStarX)
        {
            currBackgroundStarX = currBackgroundStarX+background.width*1.3f;
        }
        if(camera.target.x+GetScreenWidth()/2<=currBackgroundStarX+background.width*1.3f)
        {
            currBackgroundStarX = currBackgroundStarX-background.width*1.3f;
        }

    

        
        BeginMode2D(camera);
        
        DrawTextureEx(background, Vector2{currBackgroundStarX-background.width*1.3f,-200}, 0.0f, 1.3f, WHITE);
        DrawTextureEx(background,Vector2{currBackgroundStarX,-200},0.0f,1.3f,WHITE);
        DrawTextureEx(background,Vector2{currBackgroundStarX+background.width*1.3f,-200},0.0f,1.3f,WHITE);
        map.Draw();
        player.Draw();
        EndMode2D();
}

void Level::loadCoins() {
        items.clear();
        for (Tile* tile : map.getInteractiveTiles()) {
            // Place a coin above each block (adjust offset as needed)
            Vector2 coinPos = tile->getPosition();
            coinPos.y -= 32; // Place coin one tile above the block
            items.emplace_back(new Coin(coinPos, Vector2{ 32, 32 }, WHITE, 0.1f, 4));
        }
    }