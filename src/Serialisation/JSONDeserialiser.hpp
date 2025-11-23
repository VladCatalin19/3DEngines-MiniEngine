#ifndef MG3TR_SRC_SERIALISATION_JSONDESERIALISER_HPP_INCLUDED
#define MG3TR_SRC_SERIALISATION_JSONDESERIALISER_HPP_INCLUDED

#include "IDeserialiser.hpp"

#include <nlohmann/json.hxx>

#include <stack>

namespace MG3TR
{
    class JSONDeserialiser : public IDeserialiser
    {
    private:
        struct TNodeInformation
        {
            static constexpr int k_invalid_index = -1;

            const nlohmann::json *m_json_node;

            const std::string *m_array_key;
            int m_array_current_index;

            TNodeInformation(const nlohmann::json *const json_node,
                             const std::string *const array_key = nullptr,
                             const int array_current_index = k_invalid_index);
        };

        nlohmann::json m_json;
        const nlohmann::json *m_current_node_json;
        std::stack<TNodeInformation> m_previous_nodes_json;

    public:
        JSONDeserialiser();
        virtual ~JSONDeserialiser() = default;

        virtual bool ContainsField(const std::string &field) override;
        virtual bool DeserialiseBool(const std::string &field) override;
        virtual long long signed DeserialiseSigned(const std::string &field) override;
        virtual long long unsigned DeserialiseUnsigned(const std::string &field) override;
        virtual float DeserialiseFloat(const std::string &field) override;
        virtual Vector2 DeserialiseVector2(const std::string &field) override;
        virtual Vector3 DeserialiseVector3(const std::string &field) override;
        virtual Vector4 DeserialiseVector4(const std::string &field) override;
        virtual Quaternion DeserialiseQuaternion(const std::string &field) override;
        virtual std::string DeserialiseString(const std::string &field) override;

        virtual void BeginDeserialisingChild(const std::string &child_name) override;
        virtual void EndDeserialisingLastChild() override;
        virtual std::size_t BeginDeserialisingArray(const std::string &field_name) override;
        virtual void EndDeserialisingCurrentArrayElement() override;
        virtual void EndDeserialisingLastArray() override;

        void SetJSON(const nlohmann::json &json);
    };
}

#endif // MG3TR_SRC_SERIALISATION_JSONDESERIALISER_HPP_INCLUDED
