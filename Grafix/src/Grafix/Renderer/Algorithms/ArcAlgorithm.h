#pragma once

#include "GraphicsAlgorithm.h"

namespace Grafix
{
    class ArcAlgorithm final : public GraphicsAlgorithm
    {
    public:
        static void Midpoint(glm::vec2 center, float radius, float angle1, float angle2, bool major, const glm::vec3& color);
    private:
        static void SetArcPixels(int centerX, int centerY, int x, int y, float beginAngle, float endAngle, uint32_t colorValue);
        static bool IsInRange(int x, int y, float beginAngle, float endAngle);
    };
}