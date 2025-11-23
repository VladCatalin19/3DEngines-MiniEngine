#include "JSONSerialiser.hpp"

#include <Utils/TryCathRethrowStacktrace.hpp>

#include <array>
#include <vector>

namespace MG3TR
{
    JSONSerialiser::TNodeInformation::TNodeInformation(nlohmann::json *const json_node,
                                                       const std::string *const array_key,
                                                       const int array_current_index)
        : m_json_node(json_node),
          m_array_key(array_key),
          m_array_current_index(array_current_index)
    {

    }
    
    JSONSerialiser::JSONSerialiser()
        : m_json(),
          m_current_node_json(&m_json),
          m_previous_nodes_json()
    {

    }

    void JSONSerialiser::SerialiseBool(const std::string &field, const bool value)
    {
        auto &json = *m_current_node_json;

        TRY_CATCH_RETHROW_STACKTRACE(json[field] = value);
    }

    void JSONSerialiser::SerialiseSigned(const std::string &field, const long long signed value)
    {
        auto &json = *m_current_node_json;

        TRY_CATCH_RETHROW_STACKTRACE(json[field] = value);
    }

    void JSONSerialiser::SerialiseUnsigned(const std::string &field, const long long unsigned value)
    {
        auto &json = *m_current_node_json;

        TRY_CATCH_RETHROW_STACKTRACE(json[field] = value);
    }

    void JSONSerialiser::SerialiseFloat(const std::string &field, const float value)
    {
        auto &json = *m_current_node_json;

        TRY_CATCH_RETHROW_STACKTRACE(json[field] = value);
    }

    void JSONSerialiser::SerialiseVector2(const std::string &field, const Vector2 &vector)
    {
        auto &json = *m_current_node_json;
        std::array values = { vector.x(), vector.y() };

        TRY_CATCH_RETHROW_STACKTRACE(json[field] = values);
    }

    void JSONSerialiser::SerialiseVector3(const std::string &field, const Vector3 &vector)
    {
        auto &json = *m_current_node_json;
        std::array values = { vector.x(), vector.y(), vector.z() };

        TRY_CATCH_RETHROW_STACKTRACE(json[field] = values);
    }

    void JSONSerialiser::SerialiseVector4(const std::string &field, const Vector4 &vector)
    {
        auto &json = *m_current_node_json;
        std::array values = { vector.x(), vector.y(), vector.z(), vector.w() };

        TRY_CATCH_RETHROW_STACKTRACE(json[field] = values);
    }

    void JSONSerialiser::SerialiseQuaternion(const std::string &field, const Quaternion &quaternion)
    {
        auto &json = *m_current_node_json;
        std::array values = { quaternion.w(), quaternion.x(), quaternion.y(), quaternion.z() };

        TRY_CATCH_RETHROW_STACKTRACE(json[field] = values);
    }

    void JSONSerialiser::SerialiseString(const std::string &field, const std::string &value)
    {
        auto &json = *m_current_node_json;

        TRY_CATCH_RETHROW_STACKTRACE(json[field] = value);
    }

    void JSONSerialiser::BeginSerialisingChild(const std::string &child_name)
    {
        auto &current_json = *m_current_node_json;
        nlohmann::json new_json;

        TRY_CATCH_RETHROW_STACKTRACE(current_json[child_name] = new_json);

        TRY_CATCH_RETHROW_STACKTRACE(m_previous_nodes_json.emplace(m_current_node_json));
        m_current_node_json = &(current_json[child_name]);
    }

    void JSONSerialiser::EndSerialisingLastChild()
    {
        const bool stack_empty = m_previous_nodes_json.empty();

        if (stack_empty)
        {
            throw ExceptionWithStacktrace("No child to end serialising!");
        }

        auto node_info = m_previous_nodes_json.top();

        if (node_info.m_array_current_index != TNodeInformation::k_invalid_index)
        {
            throw ExceptionWithStacktrace("Cannot end serialising child before ending serialising array!");
        }

        m_current_node_json = node_info.m_json_node;
        m_previous_nodes_json.pop();
    }

    void JSONSerialiser::BeginSerialisingArray(const std::string &field_name, const std::size_t array_size)
    {
        auto &current_json = *m_current_node_json;
        std::vector<nlohmann::json> values(array_size, nlohmann::json());

        TRY_CATCH_RETHROW_STACKTRACE(current_json[field_name] = values);

        const std::string *const array_key = &(current_json.find(field_name).key());

        m_previous_nodes_json.emplace(m_current_node_json, array_key, 0);
        m_current_node_json = &(current_json[field_name][0]);
    }

    void JSONSerialiser::EndSerialisingCurrentArrayElement()
    {
        const bool stack_empty = m_previous_nodes_json.empty();

        if (stack_empty)
        {
            throw ExceptionWithStacktrace("No child to end serialising!");
        }

        TNodeInformation &parent_node_info = m_previous_nodes_json.top();
        const std::string &array_key = *(parent_node_info.m_array_key);
        nlohmann::json &parent_json = (*parent_node_info.m_json_node)[array_key];
        const bool is_parent_array = parent_json.is_array();

        if (!is_parent_array)
        {
            throw ExceptionWithStacktrace("Cannot end serialising current array element! Not an array!");
        }

        const int size = static_cast<int>(parent_json.size());

        if (parent_node_info.m_array_current_index >= size)
        {
            throw ExceptionWithStacktrace("Cannot end serialising current array element! Cannot increment array past last element!");
        }
        else if (parent_node_info.m_array_current_index == (size - 1))
        {
            ++parent_node_info.m_array_current_index;
            m_current_node_json = nullptr;

            // Important note:
            // If EndDeserialisingLastArray is not called immediately after this function ends,
            // this could lead to null pointer dereferencing! This is not the case with the current
            // implementation. For now, we leave it as is.
        }
        else
        {
            ++parent_node_info.m_array_current_index;
            m_current_node_json = &(parent_json[parent_node_info.m_array_current_index]);
        }
    }

    void JSONSerialiser::EndSerialisingLastArray()
    {
        const bool stack_empty = m_previous_nodes_json.empty();

        if (stack_empty)
        {
            throw ExceptionWithStacktrace("No array to end serialising!");
        }

        auto node_info = m_previous_nodes_json.top();
        m_current_node_json = node_info.m_json_node;
        m_previous_nodes_json.pop();
    }

    const nlohmann::json& JSONSerialiser::GetJSON() const
    {
        return m_json;
    }
}
