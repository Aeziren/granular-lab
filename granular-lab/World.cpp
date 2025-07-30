#include "World.h"
#include "Constants.h"


World::World() : matrix(SCREEN_WIDTH, MatrixLine(SCREEN_HEIGHT, nullptr)) {}
World::~World() {
	for (const MatrixLine& matrixLine : matrix) {
		for (Particle* particle : matrixLine) {
			delete particle;
		}
	}
}

bool World::applyVerticalForce(Particle& particle) {
	auto currentPosition{ particle.getPosition() };
	const int x{ currentPosition.first };
	const int y{ currentPosition.second };
	constexpr double airDensity{ 1.2 };
	const double particleDensity{ particle.getDensity() };

	if (particleDensity > airDensity) {
		// Fall on air
		if (y + 1 >= SCREEN_HEIGHT)
			return false;
		// Todo: Intrissically checking twice if matrix[x][y + 1] is nullptr
		if (canMove(particle, DOWN)) {
			matrix[x][y + 1] = &particle;
			matrix[x][y] = nullptr;
			particle.setPosition(x, y + 1);
			particle.resetSideMoves();
			return true;
		}
		else if ((*matrix[x][y + 1]).getDensity() < particle.getDensity()) { // Todo: Could each particle in world be a reference (&) instead of a pointer?
			// Below particle that are less dense gets swaped			
			swapParticles(matrix[x][y + 1], &particle);
		}
	}

	return false;
}

void World::swapParticles(Particle* particle1, Particle* particle2) {
	auto positionParticle1{ (*particle1).getPosition() };
	auto positionParticle2{ (*particle2).getPosition() };

	matrix[positionParticle2.first][positionParticle2.second] = particle1;
	(*particle1).setPosition(positionParticle2.first, positionParticle2.second);

	matrix[positionParticle1.first][positionParticle1.second] = particle2;
	(*particle2).setPosition(positionParticle1.first, positionParticle1.second);

	(*particle1).resetSideMoves();
	(*particle2).resetSideMoves();
}

bool World::spread(Particle& particle) {
	const MovingDirections movingDirection{ std::rand() % 2 == 0 ? LEFT : RIGHT };
	particle.increaseSideMoves();

	if (!canMove(particle, movingDirection) || particle.outOfMoves())
		return false;
	
	auto currentPosition{ particle.getPosition() };
	const int x{ currentPosition.first };
	const int y{ currentPosition.second };
	const int intDirection{ movingDirection == LEFT ? -1 : 1 };
	matrix[x + intDirection][y] = &particle;
	matrix[x][y] = nullptr;
	particle.setPosition(x + intDirection, y);

	return true;
}

bool World::canMove(Particle& particle, MovingDirections direction) {
	auto currentPosition{ particle.getPosition() };
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

	return false;
}

void World::searchActiveParticles(std::vector<Particle*>& bufferActiveParticles) {
	for (int y{}; y < SCREEN_HEIGHT; ++y) {
		for (int x{}; x < SCREEN_WIDTH; ++x) {
			Particle* currentParticle{ matrix[x][y] };

			if (currentParticle != nullptr) {
				bufferActiveParticles.push_back(currentParticle);
			}
		}
	}
}

bool World::addParticle(Particle& particle) {
	auto position{ particle.getPosition() };

	if (matrix[position.first][position.second] == nullptr) {
		matrix[position.first][position.second] = &particle;

		return true;
	}

	return false;
}

void World::update() {	
	std::vector<Particle*> activeParticles{};
	searchActiveParticles(activeParticles);

	for (Particle* particle : activeParticles) {
		if (!applyVerticalForce(*particle)) {
			spread(*particle);
		}
	}
};

void World::draw(SDL_Renderer* renderer) {
	for (int y{}; y < SCREEN_HEIGHT; ++y) {
		for (int x{}; x < SCREEN_WIDTH; ++x) {
			Particle* currentParticle{ matrix[x][y] };

			if (currentParticle != nullptr) {
				(*currentParticle).draw(renderer);
			}
		}
	}
}