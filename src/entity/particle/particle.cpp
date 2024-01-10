#include "particle.h"

Particle::Particle(vec2 pos, vec2 dir, float size, float speed, float lifespan)
: Entity(pos, size) {
    _speed = speed;
    _direction = dir;

    _lifetime = 0;
    _lifespan = lifespan;

    cout << "created new particle" << endl;
}

void Particle::update(double deltaTime) {
    _position += _speed * _direction;
    _boundingBox.setPosition(_position.x - _size/2, _position.y - _size/2);
    _lifetime += ofGetLastFrameTime();
}

void Particle::draw() {
    ofSetColor(COLORS.RED);
    ofDrawCircle(_position, _size);
}

bool Particle::getIsDead() {
    return _lifetime > _lifespan;
}