#pragma once

#include "figure_d2d1.h"

struct Collision_area {
    int width;
    int height;
    int x;
    int y;
};

//Setting up rectangle collision between 2 sprites
int Collision(Collision_area sprite1, Collision_area sprite2)
{
    RECT rect1;
    rect1.left = sprite1.x + 1;
    rect1.top = sprite1.y + 1;
    rect1.right = sprite1.x + sprite1.width - 1;
    rect1.bottom = sprite1.y + sprite1.height - 1;

    RECT rect2;
    rect2.left = sprite2.x + 1;
    rect2.top = sprite2.y + 1;
    rect2.right = sprite2.x + sprite2.width - 1;
    rect2.bottom = sprite2.y + sprite2.height - 1;

    RECT dest;
    return IntersectRect(&dest, &rect1, &rect2);
}