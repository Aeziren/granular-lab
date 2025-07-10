#include "SandParticle.h"

SandParticle::SandParticle(int x, int y)
    : Particle(x, y) // Call base class constructor with default position
{
	color.r = 0xcb;
	color.g = 0xb1;
	color.b = 0x70;
	color.a = 0xFF;
	maxSideMoves = 8;
	density = 1600;
}