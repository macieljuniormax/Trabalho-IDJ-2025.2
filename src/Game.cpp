//
//  Game.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 03/09/25.
//

#include "Game.hpp"
#include "Resources.hpp"
#include "InputManager.hpp"

#include <iostream>
#include <stdexcept>

Game *Game::instance = nullptr;

Game &Game::GetInstance() {
    if (instance == nullptr) {
        instance =
            new Game("Maciel Ferreira Custódio Júnior - 190100087", 1200, 900);
    }

    return *instance;
}

Game::Game(std::string title, int width, int height) {
    if (instance != nullptr) {
        std::cerr << "Erro: já existe uma instância de Game rodando!"
                  << std::endl;
        exit(1);
    }

    instance = this;

    try {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
            throw std::runtime_error(std::string("Erro ao inicializar SDL: ") +
                                     SDL_GetError());
        }

        int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
        if ((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
            throw std::runtime_error(
                std::string("Erro ao inicializar SDL_image: ") +
                IMG_GetError());
        }

        int mixFlags =
            MIX_INIT_FLAC | MIX_INIT_OGG | MIX_INIT_MP3 | MIX_INIT_MOD;
        if ((Mix_Init(mixFlags) & mixFlags) != mixFlags) {
            throw std::runtime_error(
                std::string("Erro ao inicializar SDL_mixer"));
        }

        if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
                          MIX_DEFAULT_CHANNELS, 1024) != 0) {
            throw std::runtime_error(std::string("Erro ao abrir áudio: ") +
                                     Mix_GetError());
        }

        Mix_AllocateChannels(32);
    } catch (const std::exception &exception) {
        std::cerr << exception.what() << std::endl;
        exit(1);
    }

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (window == nullptr) {
        throw std::runtime_error(std::string("Erro ao criar janela: ") +
                                 SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        throw std::runtime_error(std::string("Erro ao renderizar: ") +
                                 SDL_GetError());
    }

    state = new State();
}

Game::~Game() {
    delete state;

    Mix_CloseAudio();
    Mix_Quit();

    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

State &Game::GetState() { return *state; }

SDL_Renderer *Game::GetRenderer() { return renderer; }

void Game::Run() {
    while (!state->QuitRequested()) {
        InputManager::GetInstance().Update();
        state->Update(0);
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }

    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
}
