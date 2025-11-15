#include "GraphicsAPISingleton.hpp"

namespace MG3TR
{
    GraphicsAPISingleton GraphicsAPISingleton::m_instance;

    GraphicsAPISingleton& GraphicsAPISingleton::GetInstance()
    {
        return m_instance;
    }

    void GraphicsAPISingleton::SetGraphicsAPI(std::unique_ptr<IGraphicsAPI> graphics_api)
    {
        m_graphics_api = std::move(graphics_api);
    }

    IGraphicsAPI& GraphicsAPISingleton::GetGraphicsAPI() const
    {
        IGraphicsAPI& reference = *m_graphics_api;
        return reference;
    }
}
