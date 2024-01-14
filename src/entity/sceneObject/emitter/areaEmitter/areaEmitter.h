#pragma once

#include "emitter.h"

class AreaEmitter : public Emitter {
    public:
        AreaEmitter(vec2 pos, float spawnInterval, unsigned short maxParticles, ParticleType ptype);
        AreaEmitter(vec2 pos, float spawnInterval, float rangeSpawnInterval, unsigned short maxParticles, ParticleType ptype);

        void update(double deltaTime) override;
        void drawEditMode() override;

        vec2 getSpawnPosition();

    private:
        bool _editing;
};