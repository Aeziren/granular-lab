#pragma once
#include <SDL3/SDL.h>
#include <utility>
#include <string>

/*
* class Particle
* @brief Represents a particle type.
*/
class Particle {
public:
	/*
	* @brief Creates a particle.
	* @param x, y: Particle position.
	*/
	Particle(int x, int y);

	/*
	* @brief Draw the current particle.
	* @param renderer: Pointer to the renderer.
	*/
	void draw(SDL_Renderer* renderer);

	/*
	* @brief Get the position of the current particle.
	* @return (x, y) pair of the particle.
	*/
	std::pair<int, int> getPosition();

	/*
	* @brief Set the particle position.
	* @param x, y: Position to be set.
	*/
	void setPosition(int x, int y);

	/*
	* @brief Reset the counter of side moves made by this particle.
	*/
	void resetSideMoves();

	/*
	* @brief Get the particle type.
	* @return Element type in text format.
	*/
	std::string_view getElement();

	/*
	* @brief Get the particle density.
	* @return Float with density of the current particle.
	*/
	float getDensity();

	/*
	* @brief Increases the counter of side moves made by this particle.
	*/
	void increaseSideMoves();

	/*
	* @brief Checks if the particle has exhausted its allowed side moves.
	* @return True if the particle is out of moves, else false.
	*/
	bool outOfMoves();

protected:
	SDL_Rect body{};			/**< Rectangle representing the particle's position and size. */
	SDL_Color color{};			/**< Color of the particle. */
	std::string_view type{};    /**< Element type of the particle. */
	int maxSideMoves{};			/**< Maximum allowed side moves for the particle. */
	int sideMoves{};			/**< Current number of side moves made. */
	float density{};			/**< Density of the particle in kg/m3. for reference, air density = 1,2 | water = 1000 | sand = 1600 | steam = 0,6 */
};
