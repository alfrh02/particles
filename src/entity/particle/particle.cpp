#include "particle.h"

Particle::Particle(vec2 pos, vec2 dir, float size, float speed, float lifespan, ofColor col)
: Entity(pos, size) {
    _speed = speed;
    _direction = dir;

    _lifetime = 0;
    _lifespan = lifespan;

    _color = col;

    cout << "created new particle" << endl;
}

void Particle::update(double deltaTime) {
    _position += _speed * _direction;
    _boundingBox.setPosition(_position.x - _size/2, _position.y - _size/2);
    _lifetime += ofGetLastFrameTime();

    _color.a = 255 - (_lifetime / _lifespan * 255);
}

void Particle::draw() {
    ofSetColor(_color);
    ofDrawCircle(_position, _size);
}

bool Particle::getIsDead() {
    if ((_position.x > ofGetWidth() || _position.x < 0) || (_position.y > ofGetHeight() || _position.y < 0)) {
        return true;
    }
    return _lifetime > _lifespan;
}