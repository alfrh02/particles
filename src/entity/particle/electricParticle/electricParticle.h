#pragma once

#include "particle.h"

class ElectricParticle : public Particle {
    public:
        ElectricParticle(vec2 pos, vec2 dir, float size, float speed, unsigned short lifespan, ofColor col);

        void update(double deltaTime) override;

        void onCollision(ofRectangle boundingBox) override;
};