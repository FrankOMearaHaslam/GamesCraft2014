#ifndef KEYBOARDMANAGER_H
#define KEYBOARDMANAGER_H

#include <SDL_dev\SDL2-2.0.3\include\SDL.h>
#include <SDL_dev\SDL2-2.0.3\include\SDL_keyboard.h>
#include <SDL_dev\SDL2-2.0.3\include\SDL_keycode.h>
#include <map>

class KeyboardManager {
public:
	static KeyboardManager* m_instance;
	static KeyboardManager* instance();
	enum key {UP, DOWN, LEFT, RIGHT, SPACE, ESC, R, MOUSE};
	bool IsKeyDown(key);
private:
	KeyboardManager();
	SDL_Event event;
	Uint8* keyboard;
	std::map<Uint8, bool> keyboardState;
};
#endif