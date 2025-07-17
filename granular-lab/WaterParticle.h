#pragma once

#include "Particle.h"

class WaterParticle : public Particle {
public:
	WaterParticle(int x, int y);
	void behave(World& world) override;
};
