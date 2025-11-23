#ifndef MG3TR_SRC_SERIALISATION_JSONSERIALISER_HPP_INCLUDED
#define MG3TR_SRC_SERIALISATION_JSONSERIALISER_HPP_INCLUDED

#include "ISerialiser.hpp"

#include <nlohmann/json.hxx>

#include <stack>

namespace MG3TR
{
    class JSONSerialiser : public ISerialiser
    {
    private:
        struct TNodeInformation
        {
            static constexpr int k_invalid_index = -1;

            nlohmann::json *m_json_node;

            const std::string *m_array_key;
            int m_array_current_index;

            TNodeInformation(nlohmann::json *const json_node,
                             const std::string *const array_key = nullptr,
                             const int array_current_index = k_invalid_index);
        };

        nlohmann::json m_json;
        nlohmann::json *m_current_node_json;
        std::stack<TNodeInformation> m_previous_nodes_json;

    public:
        JSONSerialiser();
        virtual ~JSONSerialiser() = default;

        virtual void SerialiseBool(const std::string &field, const bool value) override;
        virtual void SerialiseSigned(const std::string &field, const long long signed value) override;
        virtual void SerialiseUnsigned(const std::string &field, const long long unsigned value) override;
        virtual void SerialiseFloat(const std::string &field, const float value) override;
        virtual void SerialiseVector2(const std::string &field, const Vector2 &value) override;
        virtual void SerialiseVector3(const std::string &field, const Vector3 &value) override;
        virtual void SerialiseVector4(const std::string &field, const Vector4 &value) override;
        virtual void SerialiseQuaternion(const std::string &field, const Quaternion &value) override;
        virtual void SerialiseString(const std::string &field, const std::string &value) override;

        virtual void BeginSerialisingChild(const std::string &child_name) override;
        virtual void EndSerialisingLastChild() override;
        virtual void BeginSerialisingArray(const std::string &field_name, const std::size_t array_size) override;
        virtual void EndSerialisingCurrentArrayElement() override;
        virtual void EndSerialisingLastArray() override;

        const nlohmann::json& GetJSON() const;
    };
}

#endif // MG3TR_SRC_SERIALISATION_JSONSERIALISER_HPP_INCLUDED
