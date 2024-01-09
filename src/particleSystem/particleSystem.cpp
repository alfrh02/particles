#include "particleSystem.h"

ParticleSystem::ParticleSystem(vec3 pos, unsigned short particleAmount) {
    _position = pos;
    _particleAmount = particleAmount;

    for (int i = 0; i < particleAmount; i++) {
        Particle* p = new Particle(_position, 16);
        particles.push_back(p);
    }
}

void ParticleSystem::update(double deltaTime) {
    for (int i = 0; i < particles.size(); i++) {
        particles[i]->update(deltaTime);

        cout << "test" << endl;
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