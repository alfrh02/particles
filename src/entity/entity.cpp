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

void Entity::drawEditMode() {
    ofSetColor(COLORS.RED);
    ofDrawRectangle(_boundingBox);

    ofSetColor(COLORS.GREEN);
    ofDrawLine(_position, _position + (_direction * _size));
}

vec2 Entity::getPosition() {
    return _position;
}

float Entity::getSize() {
    return _size;
}

ofRectangle Entity::getBoundingBox() {
    return _boundingBox;
}