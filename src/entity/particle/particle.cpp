#include "particle.h"

Particle::Particle(vec2 pos, float size, float lifespan)
: Entity(pos, size) {
    _lifespan = lifespan;

    cout << "particle spawned" << endl;
}

void Particle::update(double deltaTime) {
    _boundingBox.setPosition(_position.x - _size/2, _position.y - _size/2);
    _position += _direction * _speed;

    _lifetime += ofGetLastFrameTime();
}

void Particle::draw() {
    ofSetColor(255, 0, 0);
    ofDrawCircle(_position, _size);
}

bool Particle::isDead(double deltaTime) {
    return _lifetime > _lifespan;
}