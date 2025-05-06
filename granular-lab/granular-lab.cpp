#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <SDL3/SDL.h>
#include "helpers.h"

const int SCREEN_WIDTH{ 640 };
const int SCREEN_HEIGHT{ 360 };
const int SCALING{ 2 };

bool MATRIX[640][360] = {};

// To do: add other types of particles. Add physical aspects
class Particle {
private:
	SDL_Rect position{};
	const int maxSideMoves{ 8 };
	int sideMoves{};

	bool canMoveHorizontally(int direction) {
		/* Check if its possible to move one pixel in a given direction.
		*  1 means going right. -1 means going left.
		*/
		if (direction == 1)
			return MATRIX[position.x + direction][position.y] == false && position.x < SCREEN_WIDTH;
		else if (direction == -1)
			return MATRIX[position.x + direction][position.y] == false && position.x > 0;

		return false;
	}
public:
	Particle(int x, int y) {
		position.x = x;
		position.y = y;
		position.w = 1;
		position.h = 1;
	}

	void update() {
		if (MATRIX[position.x][position.y + 1] == false && position.y < SCREEN_HEIGHT - 1) {
			MATRIX[position.x][position.y] = false;
			++position.y;
			MATRIX[position.x][position.y] = true;
			sideMoves = 0;
		}
		else {
			const int movingDirection{ std::rand() % 2 == 0 ? -1 : 1 };
			sideMoves++;

			if (canMoveHorizontally(movingDirection) && sideMoves < maxSideMoves) {
				MATRIX[position.x][position.y] = false;
				position.x += movingDirection;
				MATRIX[position.x][position.y] = true;
			}
		}
	}

	void draw(SDL_Renderer* renderer) {
		SDL_SetRenderDrawColor(renderer, 0xcb, 0xb1, 0x70, 255);
		SDL_RenderPoint(renderer, position.x, position.y);
	}
};

int main(int argc, char* argv[]) {
	// Global random seed
	std::srand(std::time(nullptr));

	// Prepare
	SDL_Window* window{};
	SDL_Renderer* renderer{};
	init(&window, &renderer, SCREEN_WIDTH, SCREEN_HEIGHT, SCALING);

	// Main loop
	std::vector<Particle> particles{};
	SDL_Event event{};
	bool quit{ false };
	float mouseX{};
	float mouseY{};
	bool mouseButtonDown{ false };

	while (quit == false) {
		if (mouseButtonDown) {
			SDL_GetMouseState(&mouseX, &mouseY);
			particles.push_back(Particle(mouseX / SCALING, mouseY / SCALING));
		}

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_EVENT_QUIT:
				quit = true;
				break;
			case SDL_EVENT_MOUSE_BUTTON_DOWN:
				mouseButtonDown = true;
				break;
			case SDL_EVENT_MOUSE_BUTTON_UP:
				mouseButtonDown = false;
				break;
			}
		}

		// Clear screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		for (Particle& particle : particles) {
			particle.update();
			particle.draw(renderer);
		}

		SDL_RenderPresent(renderer);

		// Delay
		SDL_Delay(16);
	}

	// Close
	close(&window, &renderer);
	return 0;
}