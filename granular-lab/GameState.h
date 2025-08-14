#pragma once


struct GameState {
	bool quit{ false };
	bool leftMouseButtonDown{ false };
	bool rightMouseButtonDown{ false };
	float mouseX{};
	float mouseY{};
};
