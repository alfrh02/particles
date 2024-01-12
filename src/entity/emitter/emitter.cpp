#include "emitter.h"

Emitter::Emitter(vec2 pos, ofColor col, float spawnInterval, unsigned short maxParticles, ParticleType ptype)
: Entity(pos, 8, col){
    _spawnInterval = spawnInterval;
    _particleNum = 0;
    _maxParticles = maxParticles;
    _ptype = ptype;

    _captured = false;
    _timeSinceLastSpawn = 0;
}

void Emitter::update(double deltaTime) {
    _timeSinceLastSpawn += ofGetLastFrameTime();

    if (_captured) {
        _position = vec2(ofGetMouseX(), ofGetMouseY());
    }
}

void Emitter::drawEditMode() {
    ofSetColor(_color);
    if (_captured) {
        ofSetColor(COLORS.RED);
    }

    ofDrawCircle(_position, _size);

    ofSetColor(COLORS.BACKGROUND);
    ofDrawCircle(_position, _size-1);
}

void Emitter::addParticle(unsigned short num) {
    _particleNum += num;
}

bool Emitter::canSpawn() {
    if (_timeSinceLastSpawn >= _spawnInterval && _particleNum + 1 <= _maxParticles) {
        _timeSinceLastSpawn = 0;
        return true;
    }
    return false;
}

ParticleType Emitter::getParticleType() {
    return _ptype;
}