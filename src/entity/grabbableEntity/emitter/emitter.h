#pragma once

#include <vector>
#include "grabbableEntity.h"
#include "particle.h"

class Emitter : public GrabbableEntity {
    public:
        Emitter(vec2 pos, float spawnInterval, unsigned short maxParticles);
        ~Emitter();

        void update(double deltaTime) override;
        void draw() override;
        void drawEditMode() override;

        unsigned int getParticleAmount();

    private:
        float _spawnInterval;
        unsigned short _maxParticles;

        float _timeSinceLastSpawn;

        vector<Particle*> particles;
};