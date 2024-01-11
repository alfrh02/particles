#pragma once

#include "grabbableEntity.h"

class SceneObject : public GrabbableEntity {
    public:
        SceneObject(vec2 pos, float w, float h, ofColor col);

        void update(double deltaTime) override;
        void drawEditMode() override;

        ofRectangle getBoundingBox();

    protected:
        float _width;
        float _height;

        bool _editing;

        ofRectangle _boundingBox;
};