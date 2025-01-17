#pragma once

#include "Grafix/Events/Event.h"

#include <string>

namespace Grafix
{
    // --------------------------------------------------------
    // Inherit this class to create layers for the application.
    // --------------------------------------------------------
    class Layer
    {
    public:
        Layer(const std::string& name = "Layer") : m_Name(name) {}
        virtual ~Layer() = default;

        inline const std::string& GetName() const { return m_Name; }

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(float ts) {}
        virtual void OnUIRender() {}
        virtual void OnEvent(Event& e) {}
    protected:
        std::string m_Name;
    };
}
