#include "Button.h" 

/*
* class Particle
* @brief Manages UI IO
*/
class UIManager {
private:
	SDL_Renderer* _renderer{}; /**< Current SDL renderer. */
	GameState& _gameState; /**< GameState variables. */
	std::vector<Button> _buttons{}; /**< Current SDL renderer. */

	/*
	* @brief Get a vector of buttons based on a json file.
	* @param jsonLocation: Location of the file in string format.
	* @return A vector of Button objects.
	*/
	std::vector<Button> getJsonButtons(std::string jsonLocation);
public:
	/*
	* @brief Creates a UIManager.
	* @param renderer: The game SDL renderer.
	* @param gameState: Reference to the GameState type variable.
	*/
	UIManager(SDL_Renderer* renderer, GameState& gameState);

	/*
	* @brief Highlight the buttons accordingly to mouse events. 
	*/
	// TO DO: Change the GameState object so it update the current selected element.
	void ManageButtons();
};
