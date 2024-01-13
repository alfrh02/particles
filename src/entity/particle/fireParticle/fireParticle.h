#pragma once

#include "particle.h"

class FireParticle : public Particle {
    public:
        FireParticle(vec2 pos = vec2(0, 0), vec2 dir = vec2(0, 0), float size = ofRandom(4) + 1, float speed = (ofRandom(4) + 1) * 2, unsigned short lifespan = 6, ofColor col = COLORS.FIRE[(int)ofRandom(5)]);

        void update(double deltaTime);

        void onCollision(ofRectangle boundingBox) override;
};