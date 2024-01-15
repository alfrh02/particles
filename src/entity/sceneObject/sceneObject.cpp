#include "sceneObject.h"

SceneObject::SceneObject(vec2 pos, float size, ofColor col)
: Entity(pos, size, col) {
    _boundingBox = ofRectangle(pos, size, size);
}

ofRectangle SceneObject::getBoundingBox() {
    return _boundingBox;
}