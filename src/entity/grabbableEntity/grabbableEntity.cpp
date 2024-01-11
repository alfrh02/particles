#include "grabbableEntity.h"

GrabbableEntity::GrabbableEntity(vec2 pos, float size, ofColor col)
: Entity(pos, size, col) {
    _captured = false;
}

void GrabbableEntity::setCaptured(bool captured, int x, int y) {
    _captured = captured;
    _mouseCoordinates = _position - vec2(x, y);
}

bool GrabbableEntity::getCaptured() {
    return _captured;
}