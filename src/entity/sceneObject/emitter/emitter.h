#pragma once

#include <vector>
#include "sceneObject.h"
#include "particle.h"
#include "particleConfig.hpp"

class Emitter : public SceneObject {
    public:
        Emitter(vec2 pos, float spawnInterval, unsigned short maxParticles, ParticleType ptype);
        Emitter(vec2 pos, float spawnInterval, float rangeSpawnInterval, unsigned short maxParticles, ParticleType ptype);

        void update(double deltaTime) override;
        void drawEditMode() override;

        void addParticle(unsigned short num);
        bool canSpawn();
        virtual vec2 getSpawnPosition();

        ParticleType getParticleType();

    protected:
        unsigned short _particleNum;
        unsigned short _maxParticles;

        float _spawnInterval;
        float _timeSinceLastSpawn;
        float _rangeBegin;
        float _rangeEnd;
        bool _isUsingRange = false;

        ParticleType _ptype;
};