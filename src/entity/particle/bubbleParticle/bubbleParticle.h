#pragma once

#include "particle.h"

class BubbleParticle : public Particle {
    public:
        BubbleParticle(vec2 pos = vec2(0, 0), vec2 dir = vec2(0, 0), float size = ofRandom(4) + 1, float speed = (ofRandom(4) + 1) * 2, unsigned short lifespan = 6, ofColor col = COLORS.BUBBLE);

        void draw();
        void update(double deltaTime);

        void onCollision();
};