#include "emitter.h"

Emitter::Emitter(vec2 pos, float spawnInterval, unsigned short maxParticles)
: GrabbableEntity(pos, 8){
    _spawnInterval = spawnInterval;
    _maxParticles = maxParticles;

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
    ofSetColor(COLORS.EMITTER);
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