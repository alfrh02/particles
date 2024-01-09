#include "particleSystem.h"

ParticleSystem::ParticleSystem(vec2 pos, float size, unsigned short maxParticles)
: Entity(pos, size) {
    _maxParticles = maxParticles;

    for (int i = 0; i < _maxParticles; i++) {
        Particle* p = new Particle(pos, size/8, 16);
        particles.push_back(p);
    }
}

void ParticleSystem::update(double deltaTime) {
    for (int i = 0; i < particles.size(); i++) {
        particles[i]->update(deltaTime);

        if (particles[i]->isDead(deltaTime)) {
            delete particles[i];
            particles.erase(particles.begin() + i);
            i--;
        }
    }
}

void ParticleSystem::draw() {
    for (Particle* p : particles) {
        p->draw();
    }
}