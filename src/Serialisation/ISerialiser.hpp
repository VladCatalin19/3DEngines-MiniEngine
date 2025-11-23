#ifndef MG3TR_SRC_SERIALISATION_ISERIALISER_HPP_INCLUDED
#define MG3TR_SRC_SERIALISATION_ISERIALISER_HPP_INCLUDED

#include <Math/Vector2.hpp>
#include <Math/Vector3.hpp>
#include <Math/Vector4.hpp>
#include <Math/Quaternion.hpp>

#include <string>

namespace MG3TR
{
    class ISerialiser
    {
    public:
        virtual ~ISerialiser() = default;

        virtual void SerialiseBool(const std::string &field, const bool value) = 0;
        virtual void SerialiseSigned(const std::string &field, const long long signed value) = 0;
        virtual void SerialiseUnsigned(const std::string &field, const long long unsigned value) = 0;
        virtual void SerialiseFloat(const std::string &field, const float value) = 0;
        virtual void SerialiseVector2(const std::string &field, const Vector2 &value) = 0;
        virtual void SerialiseVector3(const std::string &field, const Vector3 &value) = 0;
        virtual void SerialiseVector4(const std::string &field, const Vector4 &value) = 0;
        virtual void SerialiseQuaternion(const std::string &field, const Quaternion &value) = 0;
        virtual void SerialiseString(const std::string &field, const std::string &value) = 0;

        virtual void BeginSerialisingChild(const std::string &child_name) = 0;
        virtual void EndSerialisingLastChild() = 0;
        virtual void BeginSerialisingArray(const std::string &field_name, const std::size_t array_size) = 0;
        virtual void EndSerialisingCurrentArrayElement() = 0;
        virtual void EndSerialisingLastArray() = 0;
    };
}

#endif // MG3TR_SRC_SERIALISATION_ISERIALISER_HPP_INCLUDED
