#include "emitter.h"

Emitter::Emitter(vec2 pos, float spawnInterval, unsigned short maxParticles, ParticleType ptype)
: Entity(pos, 8){
    _spawnInterval = spawnInterval;
    _particleNum = 0;
    _maxParticles = maxParticles;
    _ptype = ptype;

    _captured = false;
    _timeSinceLastSpawn = 0;
}

Emitter::Emitter(vec2 pos, float spawnInterval, float rangeSpawnInterval, unsigned short maxParticles, ParticleType ptype)
: Emitter(pos, spawnInterval, maxParticles, ptype){
    _isUsingRange = true;
    _range0 = spawnInterval;
    _range1 = rangeSpawnInterval;
}

void Emitter::update(double deltaTime) {
    cout << _isUsingRange << endl;
    _timeSinceLastSpawn += ofGetLastFrameTime();

    if (_captured) {
        _position = vec2(ofGetMouseX(), ofGetMouseY());
    }
}

void Emitter::drawEditMode() {
    ofSetColor(COLORS.FOREGROUND);
    if (_captured) {
        ofSetColor(COLORS.HIGHLIGHT);
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
        if (_isUsingRange) {
            _spawnInterval = ofRandom(_range1 - _range0) + _range0;
        }
        return true;
    }
    return false;
}

ParticleType Emitter::getParticleType() {
    return _ptype;
}