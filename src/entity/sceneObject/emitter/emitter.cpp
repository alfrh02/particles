#include "emitter.h"

Emitter::Emitter(vec2 pos, float spawnIntervalRangeBegin, float spawnIntervalRangeEnd, unsigned short maxParticles, ParticleType ptype)
: SceneObject(pos, 8){
    _spawnInterval = spawnIntervalRangeBegin;
    _particleNum = 0;
    _maxParticles = maxParticles;
    _ptype = ptype;

    _captured = false;
    _timeSinceLastSpawn = 0;

    _isUsingRange = false;
    _rangeBegin = spawnIntervalRangeBegin;
    _rangeEnd = 0;

    if (spawnIntervalRangeBegin != spawnIntervalRangeEnd) {
        _isUsingRange = true;
        _rangeBegin = spawnIntervalRangeBegin;
        _rangeEnd = spawnIntervalRangeEnd;
    }

    _boundingBox = ofRectangle(pos, _size * 2, _size * 2);
    _boundingBox.setPosition(_position.x - _size, _position.y - _size);
}

// take only one spawnInterval argument, and pass it onto the constructor as if there were two
// basically circumvent the "range" mechanic
Emitter::Emitter(vec2 pos, float spawnInterval, unsigned short maxParticles, ParticleType ptype)
:Emitter(pos, spawnInterval, spawnInterval, maxParticles, ptype) {

}

void Emitter::update(double deltaTime) {
    _timeSinceLastSpawn += ofGetLastFrameTime();

    if (_captured) {
        _position = vec2(ofGetMouseX(), ofGetMouseY());
        _boundingBox.setPosition(_position.x - _size, _position.y - _size);
    }
}

void Emitter::drawEditMode() {
    ofSetColor(COLORS.FOREGROUND);

    if (_captured) {
        ofSetColor(COLORS.HIGHLIGHT);
    }

    ofNoFill();
    ofDrawCircle(_position, _size);
    ofFill();
}

void Emitter::addParticle(unsigned short num) {
    _particleNum += num;
}

bool Emitter::canSpawn() {
    if (_timeSinceLastSpawn >= _spawnInterval && _particleNum + 1 <= _maxParticles) {
        _timeSinceLastSpawn = 0;
        if (_isUsingRange) {
            _spawnInterval = ofRandom(_rangeEnd - _rangeBegin) + _rangeBegin;
        }
        return true;
    }
    return false;
}

vec2 Emitter::getSpawnPosition() {
    return _position;
}

ParticleType Emitter::getParticleType() {
    return _ptype;
}

void Emitter::setSpawnInterval(float spawnInterval) {
    _spawnInterval = spawnInterval;
    _rangeBegin = spawnInterval;
}

void Emitter::setSpawnRangeEnd(float spawnRangeEnd) {
    _rangeEnd = spawnRangeEnd;
}

void Emitter::setUsingRange(bool range) {
    cout << range << endl;
    _isUsingRange = range;
}

void Emitter::setMaxParticles(int maxParticles) {
    _maxParticles = maxParticles;
}

float Emitter::getSpawnRangeBegin() {
    return _rangeBegin;
}

float Emitter::getSpawnRangeEnd() {
    return _rangeEnd;
}

float Emitter::getIsUsingRange() {
    return _isUsingRange;
}

unsigned int Emitter::getMaxParticles() {
    return _maxParticles;
}