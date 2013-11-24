#ifndef _H_PUNK_MATH_ERROR
#define _H_PUNK_MATH_ERROR

#include <exception>
#include "error/module.h"

namespace Punk {
    namespace Engine {
        namespace Math {
            namespace Error {

                class PUNK_ENGINE_API MathError : public Core::Error::Exception {
                    using Core::Error::Exception::Exception;
                };

                class MathTestFailed : public MathError {
                    using MathError::MathError;
                };

                class MathIndexOutOfRange : public MathError {
                    using MathError::MathError;
                };

                class MathDevisionByZero : public MathError {
                    using MathError::MathError;
                };

                class MatrixToQuaternionConversionFailed : public MathError {
                    using MathError::MathError;
                };

                class IndexOutOfRange : public MathError {
                    using MathError::MathError;
                };

                class MatrixInverseFailed : public MathError {
                    using MathError::MathError;
                };

                class DevisionByZero : public MathError {
                    using MathError::MathError;
                };

                class NotEnoughData : public MathError {
                    using MathError::MathError;
                };

                class EigenValuesNotFound : public MathError {
                    using MathError::MathError;
                };

                class MathNotImplemented : public MathError {
                    using MathError::MathError;
                };

                class UnexpectedResult : public MathError {
                    using MathError::MathError;
                };
            }
        }
    }
}

#endif
