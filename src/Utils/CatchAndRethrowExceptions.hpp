#ifndef MG3TR_SRC_UTILS_CATCHANDRETHROWEXCEPTIONS_HPP_INCLUDED
#define MG3TR_SRC_UTILS_CATCHANDRETHROWEXCEPTIONS_HPP_INCLUDED

#include <exception>            // std::throw_with_nested
#include <stdexcept>            // std::exception, std::runtime_error

#include "Traces.hpp"           // IN_FUNC_FILE_TRACE

#define CATCH_RETHROW_EXCEPTIONS catch (const std::exception &)\
    {\
        std::throw_with_nested(std::runtime_error(IN_FUNC_FILE_TRACE));\
    }

#define TRY_CATCH_RETHROW_EXCEPTIONS(expression) try\
    {\
        expression;\
    }\
    CATCH_RETHROW_EXCEPTIONS

#endif // MG3TR_SRC_UTILS_CATCHANDRETHROWEXCEPTIONS_HPP_INCLUDED
