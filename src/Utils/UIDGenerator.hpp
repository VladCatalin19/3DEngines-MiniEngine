#ifndef MG3TR_SRC_UTILS_UIDGENERATOR_HPP_INCLUDED
#define MG3TR_SRC_UTILS_UIDGENERATOR_HPP_INCLUDED

#include <cstdint>              // std::uint64_t

namespace MG3TR
{
    using TUID = std::uint64_t;

    class UIDGenerator
    {
    private:
        TUID m_current_id;

    public:
        UIDGenerator() noexcept : m_current_id(0) {}
        virtual ~UIDGenerator() noexcept = default;

        UIDGenerator(const UIDGenerator &) noexcept = default;
        UIDGenerator(UIDGenerator &&) noexcept = default;

        UIDGenerator& operator=(const UIDGenerator &) noexcept = default;
        UIDGenerator& operator=(UIDGenerator &&) noexcept = default;

        TUID GetNextUID() noexcept
        {
            TUID aux = m_current_id;
            ++m_current_id;
            return aux;
        }
    };
}

#endif // MG3TR_SRC_UTILS_UIDGENERATOR_HPP_INCLUDED
