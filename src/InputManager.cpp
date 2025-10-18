//
//  InputManager.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 16/10/25.
//

#include "InputManager.hpp"

static int ToMouseIndex(Uint8 sdlbutton) {
    switch (sdlbutton) {
        case SDL_BUTTON_LEFT: return 0; break;
        case SDL_BUTTON_MIDDLE: return 1; break;
        case SDL_BUTTON_RIGHT: return 2; break;
        case SDL_BUTTON_X1: return 3; break;
        case SDL_BUTTON_X2: return 4; break;
        default: return -1; break;
    }
}

InputManager &InputManager::GetInstance() {
    static InputManager instance;
    return instance;
}

InputManager::InputManager()
    : mouseX(0), mouseY(0), quitRequested(false), updateCounter(0) {

    for (int i = 0; i < 6; ++i) {
        mouseState[i] = false;
        mouseUpdate[i] = 0;
    }
}

InputManager::~InputManager() {}

void InputManager::Update() {
    ++updateCounter;
    
    SDL_GetMouseState(&mouseX, &mouseY);
    
    quitRequested = false;
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                quitRequested = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:{
                const int index = ToMouseIndex(event.button.button);
                if (index >= 0 && index < MOUSE_BUTTONS) {
                    mouseState[index] = (event.type == SDL_MOUSEBUTTONDOWN);
                    mouseUpdate[index] = updateCounter;
                }
                break;
            }
            case SDL_KEYDOWN:
                if (event.key.repeat) break;
                keyState[event.key.keysym.sym] = true;
                keyUpdate[event.key.keysym.sym] = updateCounter;
                break;
            case SDL_KEYUP:
                keyState[event.key.keysym.sym] = false;
                keyUpdate[event.key.keysym.sym] = updateCounter;
                break;
            default:
                break;
        }
    }
}

bool InputManager::KeyPress(int key) {
    return keyState[key] && keyUpdate[key] == updateCounter;
}

bool InputManager::KeyRelease(int key) {
    return !keyState[key] && keyUpdate[key] == updateCounter;
}

bool InputManager::IsKeyDown(int key) {
    auto it = keyState.find(key);
    return (it != keyState.end()) ? it->second : false;
}

// ---------- Mouse ----------
bool InputManager::MousePress(int button) {
    const int idx = ToMouseIndex(static_cast<Uint8>(button));
    return (idx >= 0 && idx < MOUSE_BUTTONS) &&
           mouseState[idx] && mouseUpdate[idx] == updateCounter;
}

bool InputManager::MouseRelease(int button) {
    const int idx = ToMouseIndex(static_cast<Uint8>(button));
    return (idx >= 0 && idx < MOUSE_BUTTONS) &&
           !mouseState[idx] && mouseUpdate[idx] == updateCounter;
}

bool InputManager::IsMouseDown(int button) {
    const int idx = ToMouseIndex(static_cast<Uint8>(button));
    return (idx >= 0 && idx < MOUSE_BUTTONS) && mouseState[idx];
}

bool InputManager::QuitRequested() {
    return quitRequested;
}
