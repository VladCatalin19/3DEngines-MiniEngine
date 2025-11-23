#ifndef MG3TR_SRC_CONSTANTS_SHADERCONSTANTS_HPP_INCLUDED
#define MG3TR_SRC_CONSTANTS_SHADERCONSTANTS_HPP_INCLUDED

#include <Graphics/Shader.hpp>
#include <Graphics/ShaderType.hpp>
#include <Graphics/Shaders/FragmentNormalShader.hpp>
#include <Graphics/Shaders/TextureAndLightingShader.hpp>
#include <Graphics/Shaders/TextureShader.hpp>

#include <functional>
#include <typeindex>
#include <unordered_map>

namespace MG3TR::ShaderConstants
{
    const std::unordered_map<std::type_index, ShaderType> k_type_to_shader = {
        { std::type_index(typeid(Shader)),                   ShaderType::General },
        { std::type_index(typeid(FragmentNormalShader)),     ShaderType::FragmentNormal },
        { std::type_index(typeid(TextureAndLightingShader)), ShaderType::TextureAndLighting },
        { std::type_index(typeid(TextureShader)),            ShaderType::Texture }
    };

    using TShaderConstructor = std::function<std::shared_ptr<Shader>()>;

    template<typename ShaderType>
    std::shared_ptr<ShaderType> Construct()
    {
        auto shader = std::make_shared<ShaderType>();
        return shader;
    }

    const std::unordered_map<ShaderType, TShaderConstructor> k_shader_to_constructor = {
        { ShaderType::General,            TShaderConstructor(&Construct<Shader>) },
        { ShaderType::FragmentNormal,     TShaderConstructor(&Construct<FragmentNormalShader>) },
        { ShaderType::TextureAndLighting, TShaderConstructor(&Construct<TextureAndLightingShader>) },
        { ShaderType::Texture,            TShaderConstructor(&Construct<TextureShader>) }
    };
}

#endif // MG3TR_SRC_CONSTANTS_SHADERCONSTANTS_HPP_INCLUDED
