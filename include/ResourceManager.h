#pragma once
#include "raylib.h"
#include <unordered_map>
#include <string>

class ResourceManager{
    private:
        static std::unordered_map < std::string, Texture2D>textures;
        static std::unordered_map<std::string, Sound> sounds;
        static std::unordered_map<std::string, Music> musics;

        static void loadTexture();
        static void loadSounds();
        static void loadMusics();

    public:
    //Load and unload
        static void loadResource();
        static void unloadResource();
    //Texture
    //Access an element by typing getTexture[nameofanimation+index]
        static Texture2D& getTexture(const std::string& name) ;
        static Sound &getSounds(const std::string& name);
        static Music &getMusics(const std::string& name);
};