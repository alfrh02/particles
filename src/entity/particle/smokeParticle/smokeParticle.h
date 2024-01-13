#pragma once

#include "particle.h"

class SmokeParticle : public Particle {
    public:
        SmokeParticle(vec2 pos = vec2(0, 0), vec2 dir = vec2(0, 0), float size = ofRandom(4) + 1, float speed = (ofRandom(4) + 1) * 2, unsigned short lifespan = 60, ofColor col = COLORS.SMOKE[(int)ofRandom(5)]);

        void update(double deltaTime);
};