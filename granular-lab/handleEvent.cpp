#include "handleEvent.h"
#include "GameState.h"


void handleEvent(SDL_Event event, GameState& gameState) {
	switch (event.type) {
	case SDL_EVENT_QUIT:
		gameState.quit = true;
		break;
	case SDL_EVENT_MOUSE_BUTTON_DOWN:
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			gameState.leftMouseButtonDown = true;
			break;
		case SDL_BUTTON_RIGHT:
			gameState.rightMouseButtonDown = true;
			break;
		}
		break;
	case SDL_EVENT_MOUSE_BUTTON_UP:
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			gameState.leftMouseButtonDown = false;
			break;
		case SDL_BUTTON_RIGHT:
			gameState.rightMouseButtonDown = false;
			break;
		}
		break;
	}
}