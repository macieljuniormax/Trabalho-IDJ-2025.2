//
//  Sound.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 03/10/25.
//

#ifndef Sound_hpp
#define Sound_hpp

#define INCLUDE_SDL_MIXER

#include "SDL_include.h"

#include <string>

class Sound {
  public:
    Sound();
    Sound(const std::string &file);
    ~Sound();

    void Play(int times = 1);
    void Stop();
    void Open(const std::string file);
    bool IsOpen() const;

  private:
    Mix_Chunk *chunk;
    int channel;
};

#endif /* Sound_hpp */
