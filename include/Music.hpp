//
//  Music.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 06/09/25.
//

#ifndef Music_hpp
#define Music_hpp

#define INCLUDE_SDL_MIXER

#include <string>

#include "SDL_include.h"

class Music {
public:
    Music();
    Music(const std::string& file);
    ~Music();
    
    void Play(int times = -1);
    void Stop(int msToStop = 1500);
    void Open(const std::string& file);
    bool IsOpen();
    
private:
    Mix_Music* music;
};

#endif /* Music_hpp */
