#pragma once
#include <string>

class Button {
private:
	std::string _name{};
	std::string _imageLocation{};
	SDL_FRect _position{};
	SDL_Color _baseColor{ 240, 240, 240, 255 };
	SDL_Color _highlightColor{ 240, 200, 200, 255 };
	SDL_Color _selectedColor{ 240, 100, 100, 255 };

public:
	bool selected{ false };
	Button(const std::string name, const std::string imageLocation, const SDL_FRect position);

	const SDL_Color getColor(std::string_view chosenMode);

	const SDL_FRect& getPosition();	
};