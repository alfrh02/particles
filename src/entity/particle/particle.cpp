#include "particle.h"

Particle::Particle(vec2 pos, vec2 dir, float size, float speed, unsigned short lifespan, ofColor col)
: Entity(pos, size, col) {
    _speed = speed;
    _direction = dir;

    _lifetime = 0;
    _lifespan = lifespan;
}

void Particle::update(double deltaTime) {
    _position += _speed * _direction;
    _lifetime += ofGetLastFrameTime();
}

void Particle::draw() {
    ofSetColor(_color);
    ofDrawCircle(_position, _size);
}

void Particle::onCollision(ofRectangle boundingBox) {
    // find direction to the centre of the bounding box
    vec2 dir = normalize(_position - (boundingBox.getPosition() + vec2(boundingBox.getWidth(), boundingBox.getHeight()) / 2));
    cout << dir.x << " , " << dir.y << endl;
    _direction = dir;
}

bool Particle::getIsDead() {
    if ((_position.x > ofGetWidth() || _position.x < 0) || (_position.y > ofGetHeight() || _position.y < 0)) {
        return true;
    }
    return _lifetime > _lifespan;
}