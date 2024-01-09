#include "entity.h"

Entity::Entity(vec2 pos, float size) {
    _position = pos;
    _size = size;

    _rotation = 0;
    _direction = vec2(0, 0);

    _boundingBox = ofRectangle(_position - _size/2, _size, _size);
}

void Entity::update(double deltaTime) {
    _boundingBox.setPosition(_position.x - _size/2, _position.y - _size/2);
    _position += _direction * _speed;
}

void Entity::draw() {
    
}

void Entity::drawDebug() {
    ofSetColor(255, 32, 32);
    ofDrawRectangle(_boundingBox);

    ofSetColor(0, 255, 0);
    ofDrawLine(_position, _position + (_direction * _size));
}