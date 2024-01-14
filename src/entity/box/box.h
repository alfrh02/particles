#pragma once

#include "entity.h"

class Box : public Entity {
    public:
        Box(vec2 pos);

        void update(double deltaTime);
        void draw() override;
        void drawEditMode() override;

        ofRectangle getBoundingBox();

    private:
        float _width;
        float _height;

        bool _editing;

        ofRectangle _boundingBox;
        ofRectangle _rect;
};