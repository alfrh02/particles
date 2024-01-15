#pragma once

#include "entity.h"

class SceneObject : public Entity {
    public:
        SceneObject(vec2 pos = vec2(0, 0), float size = 0, ofColor col = COLORS.FOREGROUND);

        void drawEditMode() override;
    protected:
        float _width;
        float _height;

        ofRectangle _boundingBox;
        ofRectangle _rect;
};