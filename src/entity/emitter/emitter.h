#pragma once

#include <vector>
#include "entity.h"
#include "particle.h"

class Emitter : public Entity {
    public:
        Emitter(vec2 pos, float spawnInterval, unsigned short maxParticles);
        ~Emitter();

        void update(double deltaTime) override;
        void draw() override;
        void drawEditMode() override;

        void setCaptured(bool captured);

        bool getCaptured();
        unsigned int getParticleAmount();

    private:
        float _spawnInterval;
        unsigned short _maxParticles;

        bool _captured;
        float _timeSinceLastSpawn;

        vector<Particle*> particles;
};