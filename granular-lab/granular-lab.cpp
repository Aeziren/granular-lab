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

class Particle {
private:
	SDL_Rect position{};
	SDL_Color color{};
	int maxSideMoves{};
	int sideMoves{};
	int density{}; // To do: Particle of different density swap vertical positions accordingly.

	bool canMoveHorizontally(int direction) {
		/* Check if its possible to move one pixel in a given direction.
		   1 means going right. -1 means going left.*/
		if (direction == 1)
			return MATRIX[position.x + direction][position.y] == false && position.x < SCREEN_WIDTH;
		else if (direction == -1)
			return MATRIX[position.x + direction][position.y] == false && position.x > 0;

		return false;
	}

	bool applyVerticalForce() {
		/*Apply gravity. Returns true if moved.*/
		if (MATRIX[position.x][position.y + 1] == false && position.y < SCREEN_HEIGHT - 1) {
			MATRIX[position.x][position.y] = false;
			++position.y;
			MATRIX[position.x][position.y] = true;
			sideMoves = 0;
			return true;
		}

		return false;
	}

	bool spread() {
		/*Choose a random side and move in that direction. Returns true if moved.*/
		const int movingDirection{ std::rand() % 2 == 0 ? -1 : 1 };
		sideMoves++;

		if (canMoveHorizontally(movingDirection) && sideMoves < maxSideMoves) {
			MATRIX[position.x][position.y] = false;
			position.x += movingDirection;
			MATRIX[position.x][position.y] = true;

			return true;
		}

		return false;
	}
public:
	enum Type {
		SAND,
		WATER,
	};

	Particle(int x, int y, Type type) {
		position.x = x;
		position.y = y;
		position.w = 1;
		position.h = 1;

		switch (type) {
		case SAND:
			color.r = 0xcb;
			color.g = 0xb1;
			color.b = 0x70;
			color.a = 0xFF;
			maxSideMoves = 8;
			density = 3;
			break;
		case WATER:
			color.r = 0x10;
			color.g = 0x90;
			color.b = 0xF0;
			color.a = 0xFF;
			// To do: Solve this. A idea might be a particle of water move to the side when there is another particle of water above it. But that would need to improve the world.
			maxSideMoves = 99999; 
			density = 1;
			break;
		}
	}

	void update() {
		if (!applyVerticalForce()) {
			spread();
		}
	}

	void draw(SDL_Renderer* renderer) {
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
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
	bool leftMouseButtonDown{ false };
	bool rightMouseButtonDown{ false };

	while (quit == false) {
		if (leftMouseButtonDown || rightMouseButtonDown) {
			SDL_GetMouseState(&mouseX, &mouseY);
			particles.push_back(Particle(static_cast<int>(mouseX / SCALING), static_cast<int>(mouseY / SCALING), leftMouseButtonDown ? Particle::SAND : Particle::WATER));
		}

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_EVENT_QUIT:
				quit = true;
				break;
			case SDL_EVENT_MOUSE_BUTTON_DOWN:
				switch (event.button.button) {
				case SDL_BUTTON_LEFT:
					leftMouseButtonDown = true;
					break;
				case SDL_BUTTON_RIGHT:
					rightMouseButtonDown = true;
					break;
				}
				break;
			case SDL_EVENT_MOUSE_BUTTON_UP:
				switch (event.button.button) {
				case SDL_BUTTON_LEFT:
					leftMouseButtonDown = false;
					break;
				case SDL_BUTTON_RIGHT:
					rightMouseButtonDown = false;
					break;
				}
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