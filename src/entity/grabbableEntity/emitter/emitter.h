#pragma once

#include <vector>
#include "grabbableEntity.h"
#include "particle.h"

class Emitter : public GrabbableEntity {
    public:
        Emitter(vec2 pos, ofColor col, float spawnInterval, unsigned short maxParticles);

        void update(double deltaTime) override;
        void drawEditMode() override;

        void addParticle(unsigned short num);
        bool canSpawn();

    private:
        unsigned short _particleNum;
        unsigned short _maxParticles;

        float _spawnInterval;
        float _timeSinceLastSpawn;
};