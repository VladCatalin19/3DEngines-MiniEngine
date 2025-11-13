#ifndef M3GTR_SRC_MATH_TNUMERICALCONCEPT_HXX_INCLUDED
#define M3GTR_SRC_MATH_TNUMERICALCONCEPT_HXX_INCLUDED

#include <type_traits>

namespace MG3TR
{
    template<typename T>
    concept TNumericalConcept = std::is_floating_point_v<T> || std::is_integral_v<T>;
}

#endif // M3GTR_SRC_MATH_TNUMERICALCONCEPT_HXX_INCLUDED
