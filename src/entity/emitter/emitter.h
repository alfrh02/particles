#pragma once

#include <vector>
#include "entity.h"
#include "particle.h"

class Emitter : public Entity {
    public:
        Emitter(vec2 pos, ofColor col, float spawnInterval, unsigned short maxParticles, ParticleType ptype);

        void update(double deltaTime) override;
        void drawEditMode() override;

        void addParticle(unsigned short num);
        bool canSpawn();

        ParticleType getParticleType();

    private:
        unsigned short _particleNum;
        unsigned short _maxParticles;

        float _spawnInterval;
        float _timeSinceLastSpawn;

        ParticleType _ptype;
};