#pragma once

#include <vector>
#include "ofMain.h"
#include "particle.h"

using namespace glm;

class ParticleSystem {
    public:
        ParticleSystem(vec3 pos, unsigned short particleAmount);

        void update(double deltaTime);
        void draw();

    private:
        vec3 _position;
        unsigned short _particleAmount;

        vector<Particle*> particles;
};