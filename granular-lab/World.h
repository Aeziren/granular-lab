#pragma once

#include <vector>
#include "Particle.h"


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
	
	bool applyVerticalForce(Particle* particle);
	void swapParticles(Particle* particle1, Particle* particle2);
	bool spread(Particle* particle);
	bool canMove(Particle* particle, MovingDirections direction);
	void searchActiveParticles(std::vector<Particle*>& bufferActiveParticles);
public:
	World();
	~World();
	bool addParticle(Particle* particle);
	void update();
	void draw(SDL_Renderer* renderer);
};