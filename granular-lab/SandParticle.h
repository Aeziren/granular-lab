#pragma once

#include "Particle.h"

class SandParticle : public Particle {
public:
	SandParticle(int x, int y);
	void behave(World& world) override;
};

