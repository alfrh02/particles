#pragma once

#include "particle.h"

class FireParticle : public Particle {
    public:
        FireParticle(vec2 pos, vec2 dir, float size, float speed, unsigned short lifespan, ofColor col);

        void update(double deltaTime);

        void onCollision(ofRectangle boundingBox) override;
};