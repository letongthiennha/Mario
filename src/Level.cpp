#include "Level.h"
#include "ResourceManager.h"
#include "Map.h"
#include "LevelState.h"
Level::Level(int mapNumber,GameState* gamestate,const PlayerData& playerData):gameState(gamestate),
player(startPositionforPlayer,playerData),
map(mapNumber), 
interactiveTiles(map.getInteractiveTiles()),
state(LevelState::LEVEL_STATE_PLAYING)
{
        switch(mapNumber) {
            case 0:
                background = ResourceManager::getInstance().getTexture("BACKGROUND_0");
                // backgroundColor = ResourceManager::getInstance().getColor("LEVEL_0_BACKGROUND_COLOR");
                backgroundColor = Color{0,96,184,255}; // Default color for level 0
                break;
            case 1:
                background = ResourceManager::getInstance().getTexture("LEVEL_1_BACKGROUND");
                backgroundColor = BLUE;
                break;
        //     case 2:
        //         background = ResourceManager::getInstance().getTexture("LEVEL_2_BACKGROUND");
        //         backgroundColor = ResourceManager::getInstance().getColor("LEVEL_2_BACKGROUND_COLOR");
        //         break;
        //     case 3:
        //         background = ResourceManager::getInstance().getTexture("LEVEL_3_BACKGROUND");
        //         backgroundColor = ResourceManager::getInstance().getColor("LEVEL_3_BACKGROUND_COLOR");
        //         break;
            default:
                // background = ResourceManager::getInstance().getTexture("DEFAULT_BACKGROUND");
                backgroundColor = WHITE;
        }
        player.addObserver(&gameState->getHUD());
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
        if(player.getState() == ENTITY_STATE_TO_BE_REMOVED) // If player is dead, reset the level
        {
                state = LevelState::LEVEL_STATE_NEED_RESET;
                return;
        }

        if(player.getPosition().x>3000) // If player is past a certain point, switch to next level
        {
                state= LevelState::LEVEL_STATE_COMPLETED;
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

