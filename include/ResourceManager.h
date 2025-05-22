#pragma once
#include "raylib.h"
#include <unordered_map>
#include <string>
Texture2D FlipTextureHorizontal(const Texture2D &texture);
class ResourceManager{
    private:
        static std::unordered_map < std::string, Texture2D>textures;
        static std::unordered_map<std::string, Sound> sounds;
        static std::unordered_map<std::string, Music> musics;

        static void loadTextures();
        static void loadSounds();
        static void loadMusics();

        static void unloadTexture();
        static void unloadSounds();
        static void unloadMusics();

    public:
    //Load and unload
        static void loadResource();
        static void unloadResource();
    //Texture
    //Access an element by typing getTexture[nameofanimation+index]
        static Texture2D& getTexture( std::string) ;
        static Sound &getSounds( std::string name);
        static Music &getMusics( std::string name);
};