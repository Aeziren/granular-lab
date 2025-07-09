#include "Particle.h"


Particle::Particle(int x, int y, Element type)
	: body{ x, y, 1, 1 }
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

void Particle::draw(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderPoint(renderer, body.x, body.y);
}

std::pair<int, int> Particle::getPosition() {
	return { body.x, body.y };
}

void Particle::setPosition(int x, int y) {
	body.x = x;
	body.y = y;
}

void Particle::resetSideMoves() {
	sideMoves = 0;
}

Particle::Element Particle::getElement() {
	return type;
}

float Particle::getDensity() {
	return density;
}

void Particle::increaseSideMoves() {
	++sideMoves;
}

bool Particle::outOfMoves() {
	return sideMoves >= maxSideMoves;
}
