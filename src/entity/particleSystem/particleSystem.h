#pragma once

#include <vector>
#include "entity.h"
#include "particle.h"

class ParticleSystem : public Entity {
    public:
        ParticleSystem(vec2 pos, float size, unsigned short maxParticles);

        void update(double deltaTime) override;
        void draw() override;

    private:
        unsigned short _maxParticles;

        vector<Particle*> particles;
};