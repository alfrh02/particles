#include "entity.h"

Entity::Entity(vec2 pos, float size, ofColor col) {
    _position = pos;
    _size = size;

    _direction = vec2(0, 0);

    _color = col;

    _captured = false;
}

void Entity::update(double deltaTime) {
    _position += _direction * _speed;
}

void Entity::draw() {

}

void Entity::drawEditMode() {

}

void Entity::setPosition(vec2 position) {
    _position = position;
}

void Entity::setCaptured(bool captured, int x, int y) {
    _captured = captured;
}

vec2 Entity::getPosition() {
    return _position;
}

vec2 Entity::getDirection() {
    return _direction;
}

float Entity::getSize() {
    return _size;
}

float Entity::getSpeed() {
    return _speed;
}

bool Entity::getCaptured() {
    return _captured;
}