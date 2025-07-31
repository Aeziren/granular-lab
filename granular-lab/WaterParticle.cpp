#include "WaterParticle.h"


WaterParticle::WaterParticle(int x, int y)
	: Particle(x, y)
{
	color.r = 0x10;
	color.g = 0x90;
	color.b = 0xF0;
	color.a = 0xFF;
	// To do: Solve this. A idea might be a particle of water move to the side when there is another particle of water above it. But that would need to improve the world. Another idea could be a particle of water also move horizontally if possible.
	maxSideMoves = 99999;
	density = 1000;
}