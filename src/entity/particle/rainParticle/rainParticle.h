#pragma once

#include "particle.h"

class RainParticle : public Particle {
    public:
        RainParticle(vec2 pos = vec2(0, 0), vec2 dir = vec2(0, 0), float size = 1, float speed = ((int)ofRandom(3) + 1) * 20 + 160, unsigned short lifespan = -1, ofColor col = COLORS.RAIN);

        void draw() override;

        void onCollision(ofRectangle boundingBox) override;
};