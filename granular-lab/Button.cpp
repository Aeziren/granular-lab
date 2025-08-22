#include <SDL3/SDL.h>
#include <stdexcept>
#include "Button.h"


Button::Button(const std::string name, const std::string imageLocation, const SDL_FRect position)
	: _name(name),
	_imageLocation(imageLocation),
	_position(position)
{
}

const SDL_Color Button::getColor(std::string_view chosenMode) {
	if (chosenMode == "base")
		return _baseColor;
	else if (chosenMode == "highlight")
		return _highlightColor;
	else if (chosenMode == "selected")
		return _selectedColor;
	else
		throw std::invalid_argument("Invalid button color mode: " + std::string(chosenMode));
}

const SDL_FRect& Button::getPosition() {
	return _position;
}
