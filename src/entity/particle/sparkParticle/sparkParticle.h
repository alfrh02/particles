#pragma once

#include "particle.h"

class SparkParticle : public Particle {
    public:
        SparkParticle(vec2 pos = vec2(0, 0), vec2 dir = vec2(0, 0), float size = 1, float speed = 50, unsigned short lifespan = 10, ofColor col = COLORS.SPARK);

        void update(double deltaTime) override;

        void onCollision(ofRectangle boundingBox) override;
};