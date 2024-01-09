#include "particle.h"

Particle::Particle(vec3 pos, float lifespan) {
    _position = pos;
    _lifespan = lifespan;

    box.set(8);
}

void Particle::update(double deltaTime) {
    box.setPosition(_position);
    _lifetime += ofGetLastFrameTime();
    cout << "udpate" << endl;
}

void Particle::draw() {
    box.draw();
    // cout << "draw" << endl;
}

bool Particle::isDead(double deltaTime) {
    cout << _lifetime << "/" << _lifespan << endl;
    return _lifetime > _lifespan;
}