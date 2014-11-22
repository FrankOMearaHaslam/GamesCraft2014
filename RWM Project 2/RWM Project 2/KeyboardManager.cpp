#include "KeyboardManager.h"

KeyboardManager* KeyboardManager::m_instance = 0;
KeyboardManager::KeyboardManager() {}

KeyboardManager* KeyboardManager::instance() {
	if (m_instance == 0)
		m_instance = new KeyboardManager();
	return m_instance;
}

bool KeyboardManager::IsKeyDown(key k) {
  SDL_Event event;
    if( SDL_PollEvent(&event)) {
        switch(event.type) {
                case SDL_KEYDOWN:
                        keyboardState[event.key.keysym.sym] = true;
                        break;
                case SDL_KEYUP:
                        keyboardState[event.key.keysym.sym] = false;
                        break;
                case SDL_MOUSEBUTTONDOWN:
                        keyboardState[0] = true;
                        break;
                case SDL_MOUSEBUTTONUP:
                        keyboardState[0] = false;
        }
    }
	if (k==KeyboardManager::ESC && keyboardState[SDLK_ESCAPE] == true)
		return true;
	if (k==KeyboardManager::RIGHT && keyboardState[SDLK_RIGHT] == true)
		return true;
	if (k==KeyboardManager::LEFT && keyboardState[SDLK_LEFT] == true)
		return true;
	if (k==KeyboardManager::UP && keyboardState[SDLK_UP] == true)
		return true;
	if (k==KeyboardManager::DOWN && keyboardState[SDLK_DOWN] == true)
		return true;
	if (k==KeyboardManager::R && keyboardState[SDLK_r] == true)
		return true;
	if (k==KeyboardManager::SPACE && keyboardState[SDLK_SPACE] == true)
		return true;
	if (k==KeyboardManager::MOUSE && keyboardState[0] == true)
                return true;

	else return false;
}