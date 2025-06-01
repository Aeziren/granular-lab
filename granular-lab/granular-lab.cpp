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
	int sideMoves{};
	float density{}; // kg/m3 - for reference, air density = 1,2 | water = 1000 | sand = 1600 | steam = 0,6
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
			density = 1600;
			break;
		case WATER:
			color.r = 0x10;
			color.g = 0x90;
			color.b = 0xF0;
			color.a = 0xFF;
			// To do: Solve this. A idea might be a particle of water move to the side when there is another particle of water above it. But that would need to improve the world. Another idea could be a particle of water also move horizontally if possible.
			maxSideMoves = 99999;
			density = 1000;
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

	void resetSideMoves() {
		sideMoves = 0;
	}

	Element getElement() {
		return type;
	}

	float getDensity() {
		return density;
	}

	void increaseSideMoves() {
		++sideMoves;
	}

	bool outOfMoves() {
		return sideMoves >= maxSideMoves;
	}
};


class World {
private:
	using MatrixLine = std::vector<Particle*>;
	std::vector<MatrixLine> matrix{};
	enum MovingDirections {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	bool applyVerticalForce(Particle* particle) {
		auto currentPosition{ (*particle).getPosition() };
		const int x{ currentPosition.first };
		const int y{ currentPosition.second };
		constexpr double airDensity{ 1.2 };
		const double particleDensity{ (*particle).getDensity() };

		if (particleDensity > airDensity) {
			// Fall on air
			if (canMove(particle, DOWN)) {
				matrix[x][y + 1] = particle;
				matrix[x][y] = nullptr;
				(*particle).setPosition(x, y + 1);
				(*particle).resetSideMoves();
				return true;
			}
			else if ((*matrix[x][y + 1]).getDensity() < (*particle).getDensity()) { // Todo: Could each particle in world be a reference (&) instead of a pointer?
				// Below particle less dense gets swaped
				swapParticles(matrix[x][y + 1], particle)
			}
		}

		return false;
	}

	bool spread(Particle* particle) {
		//Choose a random direction to go
		const MovingDirections movingDirection{ std::rand() % 2 == 0 ? LEFT : RIGHT };
		(*particle).increaseSideMoves();

		if (canMove(particle, movingDirection) && !(*particle).outOfMoves()) {
			auto currentPosition{ (*particle).getPosition() };
			const int x{ currentPosition.first };
			const int y{ currentPosition.second };
			const int intDirection{ movingDirection == LEFT ? -1 : 1 };
			matrix[x + intDirection][y] = particle;
			matrix[x][y] = nullptr;
			(*particle).setPosition(x + intDirection, y);

			return true;
		}

		return false;
	}
	
	bool canMove(Particle* particle, MovingDirections direction) {
		/*Get a particle and a direction and check if there is no neighbor in that direction and its inbounds.*/
		auto currentPosition{ (*particle).getPosition() };
		const int x{ currentPosition.first };
		const int y{ currentPosition.second };

		switch (direction) {
		case DOWN:
			return y + 1 < SCREEN_HEIGHT && matrix[x][y + 1] == nullptr;
		case UP:
			return y - 1 >= 0 && matrix[x][y - 1] == nullptr;
		case RIGHT:
			return x + 1 < SCREEN_WIDTH && matrix[x + 1][y] == nullptr;
		case LEFT:
			return x - 1 >= 0 && matrix[x - 1][y] == nullptr;
		}
	}

	void searchActiveParticles(std::vector<Particle*>& bufferActiveParticles) {
		for (int y{}; y < SCREEN_HEIGHT; ++y) {
			for (int x{}; x < SCREEN_WIDTH; ++x) {
				Particle* currentParticle{ matrix[x][y] };

				if (currentParticle != nullptr) {
					bufferActiveParticles.push_back(currentParticle);
				}

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
		std::vector<Particle*> activeParticles{};
		searchActiveParticles(activeParticles);

		for (Particle* particle : activeParticles) {
			if (!applyVerticalForce(particle)) {
				spread(particle);
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
			Particle* newParticle = new Particle(static_cast<int>(mouseX / SCALING), static_cast<int>(mouseY / SCALING), leftMouseButtonDown ? Particle::SAND : Particle::WATER);
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
		SDL_Delay(16);
	}

	// Close
	close(&window, &renderer);
	return 0;
}