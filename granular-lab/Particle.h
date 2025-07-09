#pragma once
#include <SDL3/SDL.h>
#include <utility>

class Particle {
public:
	enum Element {
		SAND,
		WATER
	};
	Particle(int x, int y, Element type);
	void draw(SDL_Renderer* renderer);
	std::pair<int, int> getPosition();
	void setPosition(int x, int y);
	void resetSideMoves();
	Element getElement();
	float getDensity();
	void increaseSideMoves();
	bool outOfMoves();

private:
	SDL_Rect body{};
	SDL_Color color{};
	Element type{};
	int maxSideMoves{};
	int sideMoves{};
	float density{}; // kg/m3 - for reference, air density = 1,2 | water = 1000 | sand = 1600 | steam = 0,6
};
