#include <utility>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <SDL3/SDL.h>
#include "helpers.h"

const int SCREEN_WIDTH{ 640 };
const int SCREEN_HEIGHT{ 360 };
const int SCALING{ 2 };


class Particle {
private:
	enum Element;
	SDL_Rect body{};
	SDL_Color color{};
	Element type{};
	int maxSideMoves{};
public:
	Particle(int x, int y, Element type)
		: body{x, y, 1, 1}
		, type{ type }
	{

		switch (type) {
		case SAND:
			color.r = 0xcb;
			color.g = 0xb1;
			color.b = 0x70;
			color.a = 0xFF;
			maxSideMoves = 8;
			break;
		case WATER:
			color.r = 0x10;
			color.g = 0x90;
			color.b = 0xF0;
			color.a = 0xFF;
			// To do: Solve this. A idea might be a particle of water move to the side when there is another particle of water above it. But that would need to improve the world. Another idea could be a particle of water also move horizontally if possible.
			maxSideMoves = 99999;
			break;
		}
	}

	enum Element {
		SAND,
		WATER
	};

	void draw(SDL_Renderer* renderer) {
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderPoint(renderer, body.x, body.y);
	}

	std::pair<int, int> getPosition() {
		return { body.x, body.y };
	}

	void setPosition(int x, int y) {
		body.x = x;
		body.y = y;
	}

	Element getElement() {
		return type;
	}
};


class World {
private:
	using MatrixLine = std::vector<Particle*>;
	std::vector<MatrixLine> matrix{};

	bool applyVerticalForce(Particle* particle) {
		switch ((*particle).getElement()) {
		case Particle::SAND:
			auto currentPosition{ (*particle).getPosition() };

			if (matrix[currentPosition.first][currentPosition.second + 1] == nullptr) {
				matrix[currentPosition.first][currentPosition.second + 1] = particle;
				(*particle).setPosition(currentPosition.first, currentPosition.second + 1);
				return true;
			}
		}

	}
public:
	World() : matrix(SCREEN_WIDTH, MatrixLine(SCREEN_HEIGHT, nullptr)) {
	};

	bool addParticle(Particle* particle) {
		/*Try to add a particle. Returns true if position was unoccupied.*/
		auto position{ (*particle).getPosition() };

		if (matrix[position.first][position.second] == nullptr) {
			matrix[position.first][position.second] = particle;

			return true;
		}

		return false;
	}

	void update() {
		for (int y{}; y < SCREEN_HEIGHT; ++y) {
			for (int x{}; x < SCREEN_WIDTH; ++x) {
				Particle* currentParticle{ matrix[x][y] };

				if (currentParticle != nullptr) {
					if (!applyVerticalForce(currentParticle)) {

					}
				}

			}
		}
	};

	void draw(SDL_Renderer* renderer) {
		for (int y{}; y < SCREEN_HEIGHT; ++y) {
			for (int x{}; x < SCREEN_WIDTH; ++x) {
				Particle* currentParticle{ matrix[x][y] };

				if (currentParticle != nullptr) {
					(*currentParticle).draw(renderer);
				}	
			}
		}
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
	World world{};
	SDL_Event event{};
	bool quit{ false };
	float mouseX{};
	float mouseY{};
	bool leftMouseButtonDown{ false };
	bool rightMouseButtonDown{ false };

	while (quit == false) {
		if (leftMouseButtonDown || rightMouseButtonDown) {
			SDL_GetMouseState(&mouseX, &mouseY);
			Particle* newParticle = new Particle(static_cast<int>(mouseX / SCALING), static_cast<int>(mouseY / SCALING), Particle::SAND);
			world.addParticle(newParticle);
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

		// Render & update particles
		world.update();
		world.draw(renderer);

		SDL_RenderPresent(renderer);

		// Delay
		SDL_Delay(64);
	}

	// Close
	close(&window, &renderer);
	return 0;
}