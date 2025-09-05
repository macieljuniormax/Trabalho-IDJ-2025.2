//
//  Game.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 03/09/25.
//

#include "Game.hpp"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>

Game* Game::instance = nullptr;

Game& Game::GetInstance() {
    if (instance == nullptr) {
        instance = new Game("Maciel Ferreira Custódio Júnior - 190100087", 1024, 600);
    }

    return *instance;
}

Game::Game(std::string title, int width, int hieght) {
    if (instance != nullptr) {
        std::cerr << "Erro: já existe uma instância de Game rodando!" << std::endl;
        exit(1);
    }

    instance = this;

    try {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
            throw std::runtime_error(std::string("Erro ao inicializar SDL: ")+ SDL_GetError());
        }

        int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
        if ((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
            throw std::runtime_error(std::string("Erro ao inicializar SDL_image: ")+ IMG_GetError());
        }

        int mixFlags = MIX_INIT_FLAC | MIX_INIT_OGG | MIX_INIT_MP3 | MIX_INIT_MOD;
        if ((Mix_Init(mixFlags) & mixFlags) != mixFlags) {
            throw std::runtime_error(std::string("Erro ao inicializar SDL_mixer"));
        }

        if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) {
            throw std::runtime_error(std::string("Erro ao abrir áudio: ")+ Mix_GetError());
        }

        Mix_AllocateChannels(32);
    } catch (const std::exception& exception) {
        std::cerr << exception.what() << std::endl;
        exit(1);
    }

    window = SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, width, hieght, 0);
    if (window == nullptr) {
        throw std::runtime_error(std::string("Erro ao criar janela: ")+ SDL_GetError());
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        throw std::runtime_error(std::string("Erro ao renderizar: ")+ SDL_GetError());
    }
    
    //    A última coisa que o construtor deve fazer é
    //    instanciar um State para o nosso jogo, inicializando o membro state
    //    Lembrar de adicionar State aqui
    //    state = new State();
}

Game::~Game() {
    //    Lembrar de remover State aqui
    //    delete state;
    
    Mix_CloseAudio();
    Mix_Quit();
    
    IMG_Quit();
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    SDL_Quit();
}

//State& Game::GetState() {
//    return *state;
//} Rever após implementar classe State

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

// implementar run quando tiver State

void Game::Run() {
    
}




