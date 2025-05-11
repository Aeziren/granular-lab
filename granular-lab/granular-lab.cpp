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

class World {
private:
	Particle* matrix[640][360] = {};

public:
	World() {};

	bool addParticle(int x, int y, Particle* particle) {
		/*Try to put a particle on the grid. Returns true if successful else false*/
		if (matrix[x][y] == nullptr) {
			matrix[x][y] = particle;
			return true;
		}
		
		return false;
	}

	bool canMoveHorizontally(int x, int y, int direction) {
		/* Check if its possible to move one pixel in a given direction.
		   1 means going right. -1 means going left.*/
		if (direction == 1)
			return matrix[x + direction][y] == nullptr && x < SCREEN_WIDTH;
		else if (direction == -1)
			return matrix[x + direction][y] == nullptr && x > 0;

		return false;
	}

	bool applyVerticalForce(int x, int y) {
		/*Apply gravity. Returns true if moved.*/
		if (matrix[x][y + 1] == nullptr && y < SCREEN_HEIGHT - 1) {
			matrix[x][y + 1] = matrix[x][y];
			matrix[x][y] = nullptr;
			(*matrix[x][y]).setSideMoves(0);
			return true;
		}

		return false;
	}

	bool spread(int x, int y) {
		/*Make a particle spread to one side or another. Returns true if moved.*/
		const int movingDirection{ std::rand() % 2 == 0 ? -1 : 1 };
		(*matrix[x][y]).setSideMoves(0);

		if (canMoveHorizontally(x, y, movingDirection) && (*matrix[x][y]).getSideMoves() < (*matrix[x][y]).getMaxSideMoves()) {
			matrix[x + movingDirection][y] = matrix[x][y];
			matrix[x][y] = nullptr;

			return true;
		}

		return false;
	}
};

class Particle {
private:
	SDL_Color color{};
	int maxSideMoves{};
	int sideMoves{};
	int density{}; // To do: Particle of different density swap vertical positions accordingly.

public:
	enum Type {
		SAND,
		WATER,
	};

	Particle(Type type) {

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

	void setSideMoves(int n) {
		sideMoves = n;
	}

	int getSideMoves() {
		return sideMoves;
	}

	int getMaxSideMoves() {
		return maxSideMoves;
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