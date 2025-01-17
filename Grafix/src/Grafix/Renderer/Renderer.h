#pragma once

#include "Image.h"

#include "Grafix/Scene/Scene.h"
#include "Grafix/Scene/Entity.h"

#include "Camera.h"
#include "Camera3D.h"
#include "Algorithms/LineAlgorithm.h"

#include <memory>

#include "Ray.h"

namespace Grafix
{
    class Renderer final
    {
    public:
        static void Init(uint32_t width, uint32_t height);
        static void Shutdown();

        static std::shared_ptr<Image> GetImage() { return m_Image; }
        static void SetSize(uint32_t newWidth, uint32_t newHeight);

        static void BeginFrame(const Camera& camera);
        static void EndFrame();

        static void SetClearColor(const glm::vec3& color) { m_ClearColor = color; }
        static int ReadPixel(glm::vec2 pos);

        static void Fill(glm::vec2 point, const glm::vec3& color);
        static void DrawSphere(const Camera3D& camera, const Scene& scene);

        // *******************************************************************************************************************************************************************
        // Line
        // *******************************************************************************************************************************************************************
        static inline void DrawLine(glm::vec2 p0, glm::vec2 p1, const glm::vec3& color, float lineWidth = 1.0f, LineStyleType lineStyle = LineStyleType::Solid, LineAlgorithmType algorithm = LineAlgorithmType::Bresenham, int id = -1)
        {
            DrawLine(TransformComponent(), p0, p1, color, lineWidth, lineStyle, algorithm, id);
        }

        static inline void DrawLine(const TransformComponent& transform, const LineComponent& line, int id = -1)
        {
            DrawLine(transform, line.P0, line.P1, line.Color, line.LineWidth, line.LineStyle, line.Algorithm, id);
        }

        static void DrawLine(const TransformComponent& transform, glm::vec2 p0, glm::vec2 p1, const glm::vec3& color, float lineWidth = 1.0f, LineStyleType lineStyle = LineStyleType::Solid, LineAlgorithmType algorithm = LineAlgorithmType::Bresenham, int id = -1);

        // *******************************************************************************************************************************************************************
        // Circle
        // *******************************************************************************************************************************************************************
        static inline void DrawCircle(glm::vec2 center, float radius, const glm::vec3& color, float lineWidth = 1.0f, LineStyleType style = LineStyleType::Solid, int id = -1)
        {
            DrawCircle(TransformComponent(), center, radius, color, lineWidth, style, id);
        }

        static inline void DrawCircle(const TransformComponent& transform, const CircleComponent& circle, int id = -1)
        {
            DrawCircle(transform, circle.Center, circle.Radius, circle.Color, circle.LineWidth, circle.LineStyle, id);
        }

        static void DrawCircle(const TransformComponent& transform, glm::vec2 center, float radius, const glm::vec3& color, float lineWidth = 1.0f, LineStyleType style = LineStyleType::Solid, int id = -1);

        // *******************************************************************************************************************************************************************
        // Arc
        // *******************************************************************************************************************************************************************
        static inline void DrawArc(glm::vec2 center, float radius, float angle1, float angle2, bool major, const glm::vec3& color, float lineWidth = 1.0f, LineStyleType style = LineStyleType::Solid, int id = -1)
        {
            DrawArc(TransformComponent(), center, radius, angle1, angle2, major, color, lineWidth, style, id);
        }

        static inline void DrawArc(const TransformComponent& transform, const ArcComponent& arc, int id = -1)
        {
            DrawArc(transform, arc.Center, arc.Radius, arc.Angle1, arc.Angle2, arc.Major, arc.Color, arc.LineWidth, arc.LineStyle, id);
        }

        static void DrawArc(const TransformComponent& transform, glm::vec2 center, float radius, float angle1, float angle2, bool major, const glm::vec3& color, float lineWidth = 1.0f, LineStyleType style = LineStyleType::Solid, int id = -1);

        // *******************************************************************************************************************************************************************
        // Polygon
        // *******************************************************************************************************************************************************************
        static inline void DrawPolygon(const std::vector<glm::vec2>& vertices, const glm::vec3& color, int id = -1)
        {
            DrawPolygon(TransformComponent(), vertices, color, id);
        }

        static inline void DrawPolygon(const TransformComponent& transform, const PolygonComponent& polygon, int id = -1)
        {
            DrawPolygon(transform, polygon.Vertices, polygon.Color, id);
        }

        static void DrawPolygon(const TransformComponent& transform, const std::vector<glm::vec2>& vertices, const glm::vec3& color, int id = -1);

        // *******************************************************************************************************************************************************************
        // Curve
        // *******************************************************************************************************************************************************************
        static inline void DrawCurve(const std::vector<glm::vec2>& controlPoints, const glm::vec3& color, int order, float step, std::vector<float>& knots, std::vector<float>& weights,
            float lineWidth = 1.0f, LineStyleType lineStyle = LineStyleType::Solid, CurveAlgorithmType algorithm = CurveAlgorithmType::Bezier, int id = -1)
        {
            DrawCurve(TransformComponent(), controlPoints, color, order, step, knots, weights, lineWidth, lineStyle, algorithm, id);
        }

        static inline void DrawCurve(const TransformComponent& transform, CurveComponent& curve, int id = -1)
        {
            DrawCurve(transform, curve.ControlPoints, curve.Color, curve.Order, curve.Step, curve.Knots, curve.Weights, curve.LineWidth, curve.LineStyle, curve.Algorithm, id);
        }

        static void DrawCurve(const TransformComponent& transform, const std::vector<glm::vec2>& controlPoints, const glm::vec3& color, int order, float step, std::vector<float>& knots, std::vector<float>& weights,
            float lineWidth = 1.0f, LineStyleType lineStyle = LineStyleType::Solid, CurveAlgorithmType algorithm = CurveAlgorithmType::Bezier, int id = -1);

        // *******************************************************************************************************************************************************************
        // Others
        // *******************************************************************************************************************************************************************
        static void DrawSquare(glm::vec2 center, float length, const glm::vec3& color, int id = -1);

        static inline void DrawCross(glm::vec2 center, float radius, const glm::vec3& color, int id = -1)
        {
            DrawCross(TransformComponent(), center, radius, color, id);
        }

        static void DrawCross(const TransformComponent& transform, glm::vec2 center, float radius, const glm::vec3& color, int id = -1);

        static inline void DrawRect(glm::vec2 leftBottom, glm::vec2 rightTop, const glm::vec3& color, int id = -1)
        {
            DrawRect(TransformComponent(), leftBottom, rightTop, color, id);
        }

        static void DrawRect(const TransformComponent& transform, glm::vec2 leftBottom, glm::vec2 rightTop, const glm::vec3& color, int id = -1);
    private:
        static glm::vec3 CalculateSpherePixel(uint32_t x, uint32_t y);
        static glm::vec3 TraceRay(const Ray& ray);
    private:
        static std::shared_ptr<Image> m_Image;
        static uint32_t* m_Pixels;
        static int* m_IdMap;

        static const Camera3D* m_ActiveCamera;
        static const Scene* m_ActiveScene;

        static glm::vec3 m_ClearColor;
    };
}
