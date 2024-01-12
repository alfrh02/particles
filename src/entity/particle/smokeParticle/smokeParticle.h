#pragma once

#include "particle.h"

class SmokeParticle : public Particle {
    public:
        SmokeParticle(vec2 pos, vec2 dir, float size, float speed, unsigned short lifespan, ofColor col);
};