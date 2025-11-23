#include "JSONDeserialiser.hpp"

#include <Utils/TryCathRethrowStacktrace.hpp>

namespace MG3TR
{
    JSONDeserialiser::TNodeInformation::TNodeInformation(const nlohmann::json *const json_node,
                                                         const std::string *const array_key,
                                                         const int array_current_index)
        : m_json_node(json_node),
          m_array_key(array_key),
          m_array_current_index(array_current_index)
    {

    }
    
    JSONDeserialiser::JSONDeserialiser()
        : m_json(),
          m_current_node_json(&m_json),
          m_previous_nodes_json()
    {

    }

    bool JSONDeserialiser::ContainsField(const std::string &field)
    {
        const auto &json = *m_current_node_json;
        const bool contains = json.contains(field);

        return contains;
    }

    bool JSONDeserialiser::DeserialiseBool(const std::string &field)
    {
        const auto &json = *m_current_node_json;
        bool value;

        TRY_CATCH_RETHROW_STACKTRACE(value = json.at(field));

        return value;
    }

    long long signed JSONDeserialiser::DeserialiseSigned(const std::string &field)
    {
        const auto &json = *m_current_node_json;
        long long signed value;

        TRY_CATCH_RETHROW_STACKTRACE(value = json.at(field));

        return value;
    }

    long long unsigned JSONDeserialiser::DeserialiseUnsigned(const std::string &field)
    {
        const auto &json = *m_current_node_json;
        long long unsigned value;

        TRY_CATCH_RETHROW_STACKTRACE(value = json.at(field));

        return value;
    }

    float JSONDeserialiser::DeserialiseFloat(const std::string &field)
    {
        const auto &json = *m_current_node_json;
        float value;

        TRY_CATCH_RETHROW_STACKTRACE(value = json.at(field));

        return value;
    }

    Vector2 JSONDeserialiser::DeserialiseVector2(const std::string &field)
    {
        const auto &json = *m_current_node_json;
        Vector2 value;
        nlohmann::json vector_json;

        TRY_CATCH_RETHROW_STACKTRACE(vector_json = json.at(field));
        TRY_CATCH_RETHROW_STACKTRACE(value.x() = vector_json.at(0));
        TRY_CATCH_RETHROW_STACKTRACE(value.y() = vector_json.at(1));

        return value;
    }

    Vector3 JSONDeserialiser::DeserialiseVector3(const std::string &field)
    {
        const auto &json = *m_current_node_json;
        Vector3 value;
        nlohmann::json vector_json;

        TRY_CATCH_RETHROW_STACKTRACE(vector_json = json.at(field));
        TRY_CATCH_RETHROW_STACKTRACE(value.x() = vector_json.at(0));
        TRY_CATCH_RETHROW_STACKTRACE(value.y() = vector_json.at(1));
        TRY_CATCH_RETHROW_STACKTRACE(value.z() = vector_json.at(2));

        return value;
    }

    Vector4 JSONDeserialiser::DeserialiseVector4(const std::string &field)
    {
        const auto &json = *m_current_node_json;
        Vector4 value;
        nlohmann::json vector_json;

        TRY_CATCH_RETHROW_STACKTRACE(vector_json = json.at(field));
        TRY_CATCH_RETHROW_STACKTRACE(value.x() = vector_json.at(0));
        TRY_CATCH_RETHROW_STACKTRACE(value.y() = vector_json.at(1));
        TRY_CATCH_RETHROW_STACKTRACE(value.z() = vector_json.at(2));
        TRY_CATCH_RETHROW_STACKTRACE(value.w() = vector_json.at(3));

        return value;
    }

    Quaternion JSONDeserialiser::DeserialiseQuaternion(const std::string &field)
    {
        const auto &json = *m_current_node_json;
        Quaternion value;
        nlohmann::json quat_json;

        TRY_CATCH_RETHROW_STACKTRACE(quat_json = json.at(field));
        TRY_CATCH_RETHROW_STACKTRACE(value.w() = quat_json.at(0));
        TRY_CATCH_RETHROW_STACKTRACE(value.x() = quat_json.at(1));
        TRY_CATCH_RETHROW_STACKTRACE(value.y() = quat_json.at(2));
        TRY_CATCH_RETHROW_STACKTRACE(value.z() = quat_json.at(3));

        return value;
    }

    std::string JSONDeserialiser::DeserialiseString(const std::string &field)
    {
        const auto &json = *m_current_node_json;
        std::string value;

        TRY_CATCH_RETHROW_STACKTRACE(value = static_cast<std::string>(json.at(field)));

        return value;
    }

    void JSONDeserialiser::BeginDeserialisingChild(const std::string &child_name)
    {
        const auto &current_json = *m_current_node_json;
        const nlohmann::json *new_json = nullptr;

        TRY_CATCH_RETHROW_STACKTRACE(new_json = &(current_json.at(child_name)));

        TRY_CATCH_RETHROW_STACKTRACE(m_previous_nodes_json.emplace(m_current_node_json));
        m_current_node_json = new_json;
    }

    void JSONDeserialiser::EndDeserialisingLastChild()
    {
        const bool stack_empty = m_previous_nodes_json.empty();

        if (stack_empty)
        {
            throw ExceptionWithStacktrace("No child to end serialising!");
        }

        const auto node_info = m_previous_nodes_json.top();

        if (node_info.m_array_current_index != TNodeInformation::k_invalid_index)
        {
            throw ExceptionWithStacktrace("Cannot end serialising child before ending serialising array!");
        }

        m_current_node_json = node_info.m_json_node;
        m_previous_nodes_json.pop();
    }

    std::size_t JSONDeserialiser::BeginDeserialisingArray(const std::string &field_name)
    {
        const auto &current_json = *m_current_node_json;
        const nlohmann::json *array_json = nullptr;
        const nlohmann::json *next_json = nullptr;

        TRY_CATCH_RETHROW_STACKTRACE(array_json = &(current_json.at(field_name)));
        TRY_CATCH_RETHROW_STACKTRACE(next_json = &(array_json->at(0)));

        const std::string *const array_key = &(current_json.find(field_name).key());
        const std::size_t array_size = array_json->size();

        m_previous_nodes_json.emplace(m_current_node_json, array_key, 0);
        m_current_node_json = next_json;

        return array_size;
    }

    void JSONDeserialiser::EndDeserialisingCurrentArrayElement()
    {
        const bool stack_empty = m_previous_nodes_json.empty();

        if (stack_empty)
        {
            throw ExceptionWithStacktrace("No child to end serialising!");
        }

        TNodeInformation &parent_node_info = m_previous_nodes_json.top();
        const std::string &array_key = *(parent_node_info.m_array_key);
        const nlohmann::json &parent_json = (*parent_node_info.m_json_node)[array_key];
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
            m_current_node_json = &(parent_json.at(parent_node_info.m_array_current_index));
        }
    }

    void JSONDeserialiser::EndDeserialisingLastArray()
    {
        const bool stack_empty = m_previous_nodes_json.empty();

        if (stack_empty)
        {
            throw ExceptionWithStacktrace("No array to end serialising!");
        }

        const auto node_info = m_previous_nodes_json.top();
        m_current_node_json = node_info.m_json_node;
        m_previous_nodes_json.pop();
    }

    void JSONDeserialiser::SetJSON(const nlohmann::json &json)
    {
        m_json = json;
    }
}
