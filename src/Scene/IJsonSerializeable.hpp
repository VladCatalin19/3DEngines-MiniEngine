#ifndef MG3TR_SRC_SCENE_IJSONSERIALIZEABLE_HPP_INCLUDED
#define MG3TR_SRC_SCENE_IJSONSERIALIZEABLE_HPP_INCLUDED

#include <nlohmann/json.hxx>

namespace MG3TR
{
    class Scene;

    class IJsonSerializeable
    {
    public:
        virtual ~IJsonSerializeable() = default;

        virtual nlohmann::json Serialize() const = 0;
        virtual void Deserialize(const nlohmann::json &json) = 0;
        virtual void LateBindAfterDeserialization(Scene &scene) = 0;
    };
}

#endif // MG3TR_SRC_SCENE_IJSONSERIALIZEABLE_HPP_INCLUDED
