#include "World.h"
#include "ResourceManager.h"
#include "Map.h"

World::World():player(), interactiveTiles(map.getInteractiveTiles()){

        map.LoadMap(0);
        camera.offset = Vector2{(float)GetScreenWidth()/2,(float) GetScreenHeight()/2};
        camera.target = player.getPosition();
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;

}
World::~World()
{

}
void World::UpdateWorld()
{

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
void World::DrawWorld()
{

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
const float World::GetGravity()
{
        return GRAVITY;
}
void World::InitWorld()
{

        ResourceManager::getInstance().loadResource();
}
