# Particle Simulator

This is a real-time particle simulation written in C++ using SDL3. It simulates basic physics for particles like **sand** and **water**, based on their **density** and behavior under gravity.

## Demonstration
https://github.com/user-attachments/assets/f8860473-ed42-4262-8bdb-a21cfc54a50b


## Features

- Simulates falling and spreading of particles (sand and water)
- Density-based interaction (e.g., sand falls through water)
- Real-time mouse interaction (left-click = sand, right-click = water)
- Basic side movement logic
- Lightweight rendering with `SDL_RenderPoint`

## Controls

- **Left Click**: Spawn sand  
- **Right Click**: Spawn water   

## Getting Started

### Prerequisites

- C++ compiler supporting C++17 or later  
- [SDL3](https://github.com/libsdl-org/SDL) installed  

## Code Structure

- `main.cpp`: Main loop, SDL setup, and particle logic  
- `helpers.h`: Contains SDL init/close helper functions  
- `Particle` class: Represents each particle, with its type, density, color, and movement behavior  
- `World` class: Holds and updates the grid of particles

## Known Limitations that will be fixed soon  
- Water behavior can still be improved  
- No optimization or performance throttling  
- Only sand and water types are implemented

## Ideas for Future Improvements

- Add more elements (steam, fire, oil, etc.)  
- Use a particle pool instead of raw pointers to manage memory  
- Improve the water physics for better horizontal flow  
- Add UI to switch particle types and pause/resume

## License

This project is open-source and free to use under the MIT License.
