#include "Particle.h"


Particle::Particle(int x, int y)
	: body{ x, y, 1, 1 } { }

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

std::string_view Particle::getElement() {
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
