#ifndef MG3TR_SRC_UTILS_UIDGENERATOR_HPP_INCLUDED
#define MG3TR_SRC_UTILS_UIDGENERATOR_HPP_INCLUDED

#include "TUID.hpp"

namespace MG3TR
{
    class UIDGenerator
    {
    private:
        TUID m_current_id;

    public:
        UIDGenerator();
        virtual ~UIDGenerator() = default;

        UIDGenerator(const UIDGenerator &) = default;
        UIDGenerator(UIDGenerator &&) = default;

        UIDGenerator& operator=(const UIDGenerator &) = default;
        UIDGenerator& operator=(UIDGenerator &&) = default;

        TUID GetNextUID();
    };
}

#endif // MG3TR_SRC_UTILS_UIDGENERATOR_HPP_INCLUDED
