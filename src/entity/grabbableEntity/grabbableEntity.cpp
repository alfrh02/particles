#include "grabbableEntity.h"

GrabbableEntity::GrabbableEntity(vec2 pos, float size)
: Entity(pos, size) {
    _captured = false;
}

void GrabbableEntity::setCaptured(bool captured) {
    _captured = captured;
}

bool GrabbableEntity::getCaptured() {
    return _captured;
}