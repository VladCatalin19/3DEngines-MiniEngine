#ifndef MG3TR_SRC_SERIALISATION_ISERIALISABLE_HPP_INCLUDED
#define MG3TR_SRC_SERIALISATION_ISERIALISABLE_HPP_INCLUDED

namespace MG3TR
{
    class ISerialiser;
    class IDeserialiser;

    class ISerialisable
    {
    public:
        virtual ~ISerialisable() = default;

        virtual void Serialise(ISerialiser &serialiser) = 0;
        virtual void Deserialise(IDeserialiser &deserialiser) = 0;
    };
}

#endif // MG3TR_SRC_SERIALISATION_ISERIALISABLE_HPP_INCLUDED
