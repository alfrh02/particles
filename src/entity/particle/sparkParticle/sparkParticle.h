#pragma once

#include "particle.h"

class SparkParticle : public Particle {
    public:
        SparkParticle(vec2 pos, vec2 dir, float size, float speed, unsigned short lifespan, ofColor col);

        void update(double deltaTime) override;

        void onCollision(ofRectangle boundingBox) override;
};