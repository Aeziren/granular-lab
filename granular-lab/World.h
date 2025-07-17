#pragma once

#include <vector>
#include "Particle.h"

// Todo: Refactor so this class doesn't break the SRP.

/*
* @class World
* @brief Represents the world where the particles lives and interacts with each other.
* 
* This class manages the matrix of particles, physics updates and rendering.
*/
class World {
private:
	// To do: Have an vector with all active particles
	using MatrixLine = std::vector<Particle*>;
	enum MovingDirections {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	std::vector<MatrixLine> matrix{}; /*< Vector that holds all particles. */
	
	/*
	* @brief Apply vertical force to a particle falling or floating on air.
	* @param particle: Pointer to a particle.
	* @return true if particle moved, else false.
	*/
	bool applyVerticalForce(Particle* particle);

	/*
	* @brief Swap the position of 2 particles in the world.
	* @param particle1, particle2: Pointer to the particle that will get swapped.
	*/
	void swapParticles(Particle* particle1, Particle* particle2);

	/*
	* @brief Chooses randomly a horizontal direction to go.
	* @param particle: Pointer to the particle that will move horizontally.
	*/
	bool spread(Particle* particle);

	/*
	* @brief Get a particle and a direction and check if there is no 
	* neighbor in that direction and its inbounds.
	* @param particle: Pointer to the particle to check.
	* @param direction: The direction to check if that particle can move.
	* @return true if particle can move in given direction, else false.
	*/
	bool canMove(Particle* particle, MovingDirections direction);

	/*
	* @brief Get a buffer. Search on the grid for all active particles and saves them to buffer.
	* @param bufferActiveParticles: Address of buffer that will store the active particles.
	*/
	void searchActiveParticles(std::vector<Particle*>& bufferActiveParticles);
public:
	/*
	* @brief Setup the world matrix based on the SCREEN_WIDTH and SCREEN_HEIGHT constants.
	*/
	World();
	
	/*
	* @brief Deletes all particle in the current object.
	*/
	~World();

	/*
	* @brief Try to add a particle. 
	* @param particle: Pointer to the particle to add.
	* @return true if position was unoccupied, else false.
	*/
	bool addParticle(Particle* particle);

	/*
	* @brief Returns the type of a particle at X and Y coordinates.
	* @param x, y: Coordinate
	* @return string_view containing the particle type.
	*/
	std::string_view getParticleTypeAt(int x, int y);

	void update();

	/*
	* @brief Get a renderer and uses it to draw all particles.
	* @param renderer: Pointer to the renderer.
	*/
	void draw(SDL_Renderer* renderer);
};