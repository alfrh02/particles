#pragma once

#include <vector>
#include "entity.h"
#include "particle.h"
#include "particleConfig.hpp"

class Emitter : public Entity {
    public:
        Emitter(vec2 pos, float spawnInterval, unsigned short maxParticles, ParticleType ptype);
        Emitter(vec2 pos, float spawnInterval, float rangeSpawnInterval, unsigned short maxParticles, ParticleType ptype);

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
        float _range0;
        float _range1;
        bool _isUsingRange = false;

        ParticleType _ptype;
};