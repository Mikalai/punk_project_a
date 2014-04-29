#ifndef _H_PUNK_MATH_ERROR
#define _H_PUNK_MATH_ERROR

#include <exception>
#include "error/module.h"

namespace Punk {
    namespace Engine {
        namespace Math {
            namespace Error {

                class PUNK_ENGINE_API PUNK_ENGINE_API MathError : public Core::Error::Exception {
                    using Core::Error::Exception::Exception;
                };

				class PUNK_ENGINE_API MathTestFailed : public MathError {
                    using MathError::MathError;
                };

				class PUNK_ENGINE_API MathIndexOutOfRange : public MathError {
                    using MathError::MathError;
                };

				class PUNK_ENGINE_API MathDevisionByZero : public MathError {
                    using MathError::MathError;
                };

				class PUNK_ENGINE_API MatrixToQuaternionConversionFailed : public MathError {
                    using MathError::MathError;
                };

				class PUNK_ENGINE_API IndexOutOfRange : public MathError {
                    using MathError::MathError;
                };

				class PUNK_ENGINE_API MatrixInverseFailed : public MathError {
                    using MathError::MathError;
                };

				class PUNK_ENGINE_API DevisionByZero : public MathError {
                    using MathError::MathError;
                };

				class PUNK_ENGINE_API NotEnoughData : public MathError {
                    using MathError::MathError;
                };

				class PUNK_ENGINE_API EigenValuesNotFound : public MathError {
                    using MathError::MathError;
                };

				class PUNK_ENGINE_API MathNotImplemented : public MathError {
                    using MathError::MathError;
                };

				class PUNK_ENGINE_API UnexpectedResult : public MathError {
                    using MathError::MathError;
                };

				class PUNK_ENGINE_API SingularMatrix : public MathError {
					using MathError::MathError;
				};
            }
        }
    }
}

#endif
