#ifndef MG3TR_SRC_SERIALISATION_IDESERIALISER_HPP_INCLUDED
#define MG3TR_SRC_SERIALISATION_IDESERIALISER_HPP_INCLUDED

#include <Math/Vector2.hpp>
#include <Math/Vector3.hpp>
#include <Math/Vector4.hpp>
#include <Math/Quaternion.hpp>

#include <string>

namespace MG3TR
{
    class IDeserialiser
    {
    public:
        virtual ~IDeserialiser() = default;

        virtual bool ContainsField(const std::string &field) = 0;
        virtual bool DeserialiseBool(const std::string &field) = 0;
        virtual long long signed DeserialiseSigned(const std::string &field) = 0;
        virtual long long unsigned DeserialiseUnsigned(const std::string &field) = 0;
        virtual float DeserialiseFloat(const std::string &field) = 0;
        virtual Vector2 DeserialiseVector2(const std::string &field) = 0;
        virtual Vector3 DeserialiseVector3(const std::string &field) = 0;
        virtual Vector4 DeserialiseVector4(const std::string &field) = 0;
        virtual Quaternion DeserialiseQuaternion(const std::string &field) = 0;
        virtual std::string DeserialiseString(const std::string &field) = 0;

        virtual void BeginDeserialisingChild(const std::string &child_name) = 0;
        virtual void EndDeserialisingLastChild() = 0;
        virtual std::size_t BeginDeserialisingArray(const std::string &field_name) = 0;
        virtual void EndDeserialisingCurrentArrayElement() = 0;
        virtual void EndDeserialisingLastArray() = 0;
    };
}

#endif // MG3TR_SRC_SERIALISATION_IDESERIALISER_HPP_INCLUDED
