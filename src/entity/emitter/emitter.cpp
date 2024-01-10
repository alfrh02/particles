#include "emitter.h"

Emitter::Emitter(vec2 pos, float spawnInterval, unsigned short maxParticles)
: Entity(pos, 8){
    _spawnInterval = spawnInterval;
    _maxParticles = maxParticles;

    _captured = false;
    _timeSinceLastSpawn = 0;
}

Emitter::~Emitter() {
    for (Particle* p : particles) {
        delete p;
    }
}

void Emitter::update(double deltaTime) {
    _timeSinceLastSpawn += ofGetLastFrameTime();

    if (_timeSinceLastSpawn >= _spawnInterval && particles.size() + 1 <= _maxParticles) {
        _timeSinceLastSpawn = 0;

        Particle* p = new Particle(_position, vec2(sin(deltaTime), cos(deltaTime)) / 10, 1, 4, 20);
        particles.push_back(p);
    }

    for (int i = 0; i < particles.size(); i++) {
        particles[i]->update(deltaTime);

        if (particles[i]->getIsDead()) {
            delete particles[i];
            particles.erase(particles.begin() + i);
            i--;
        }
    }

    if (_captured) {
        _position = vec2(ofGetMouseX(), ofGetMouseY());
    }
}

void Emitter::draw() {
    for (Particle* p : particles) {
        p->draw();
    }
}

void Emitter::drawEditMode() {
    ofSetColor(COLORS.EMITTER);
    if (_captured) {
        ofSetColor(COLORS.RED);
    }

    ofDrawCircle(_position, _size);

    for (Particle* p : particles) {
        p->drawEditMode();
    }
}

void Emitter::setCaptured(bool captured) {
    _captured = captured;
}

bool Emitter::getCaptured() {
    return _captured;
}