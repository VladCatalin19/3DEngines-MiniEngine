#ifndef MG3TR_SRC_GRAPHICS_API_GRAPHICSAPISINGLETON_HPP_INCLUDED
#define MG3TR_SRC_GRAPHICS_API_GRAPHICSAPISINGLETON_HPP_INCLUDED

#include "IGraphicsAPI.hpp"

#include <memory>

namespace MG3TR
{
    class GraphicsAPISingleton
    {
    private:
        std::unique_ptr<IGraphicsAPI> m_graphics_api;

        static GraphicsAPISingleton m_instance;

        GraphicsAPISingleton() = default;
        ~GraphicsAPISingleton() = default;

    public:
        GraphicsAPISingleton(const GraphicsAPISingleton &) = delete;
        GraphicsAPISingleton(GraphicsAPISingleton &&) = delete;

        GraphicsAPISingleton& operator=(const GraphicsAPISingleton &) = delete;
        GraphicsAPISingleton& operator=(GraphicsAPISingleton &&) = delete;

        static GraphicsAPISingleton& GetInstance();

        void SetGraphicsAPI(std::unique_ptr<IGraphicsAPI> graphics_api);
        IGraphicsAPI& GetGraphicsAPI() const;
    };
}

#endif // MG3TR_SRC_GRAPHICS_API_GRAPHICSAPISINGLETON_HPP_INCLUDED
