#include "Button.h" 

class UIManager {
private:
	SDL_Renderer* _renderer{};
	GameState& _gameState;
	std::vector<Button> _buttons{};

	std::vector<Button> getJsonButtons(std::string jsonLocation);
public:
	UIManager(SDL_Renderer* renderer, GameState& gameState);

	void ManageButtons();
};
