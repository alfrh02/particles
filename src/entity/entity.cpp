#include "entity.h"

Entity::Entity(vec2 pos, float size, ofColor col) {
    _position = pos;
    _size = size;

    _rotation = 0;
    _direction = vec2(0, 0);

    _color = col;
}

void Entity::update(double deltaTime) {
    _position += _direction * _speed;
}

void Entity::draw() {

}

void Entity::drawEditMode() {

}

vec2 Entity::getPosition() {
    return _position;
}

float Entity::getSize() {
    return _size;
}