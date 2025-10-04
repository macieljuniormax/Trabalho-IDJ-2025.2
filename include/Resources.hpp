//
//  Resources.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 04/10/25.
//

#ifndef Resources_hpp
#define Resources_hpp

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER

#include "SDL_include.h"

#include <string>
#include <unordered_map>

class Resources {
  public:
    static SDL_Texture *GetImage(const std::string &file);
    static Mix_Music *GetMusic(const std::string &file);
    static Mix_Chunk *GetSound(const std::string &file);

    static void ClearImages();
    static void ClearMusics();
    static void ClearSounds();

  private:
    static std::unordered_map<std::string, SDL_Texture *> imageTable;
    static std::unordered_map<std::string, Mix_Music *> musicTable;
    static std::unordered_map<std::string, Mix_Chunk *> soundTable;
};

#endif /* Resources_hpp */
