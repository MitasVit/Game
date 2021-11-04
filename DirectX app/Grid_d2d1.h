#pragma once
#include "figure_d2d1.h"

void DrawGrid(ID2D1HwndRenderTarget* target, ID2D1SolidColorBrush* brush, int width, int height) {
    D2D1_SIZE_F rtSize = target->GetSize();
    for (int x = 0; x < width; x += 10)
    {
        target->DrawLine(
            D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
            D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
            brush,
            0.5f
        );
    }

    for (int y = 0; y < height; y += 10)
    {
        target->DrawLine(
            D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
            D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
            brush,
            0.5f
        );
    }
}


void Zoom(ID2D1RenderTarget* target, float DPIsizeX, float DPIsizeY) {
    target->SetDpi(DPIsizeX, DPIsizeY);
}