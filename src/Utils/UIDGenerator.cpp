#include "UIDGenerator.hpp"

namespace MG3TR
{
    UIDGenerator::UIDGenerator()
        : m_current_id(0)
    {}

    TUID UIDGenerator::GetNextUID()
    {
        TUID aux = m_current_id;
        ++m_current_id;
        return aux;
    }
}
