#ifndef STREAMING_RESULT_H
#define STREAMING_RESULT_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace System {
    enum class StreamingStepResult { STREAM_ERROR, STREAM_TRY_AGAIN, STREAM_OK };
}
PUNK_ENGINE_END

#endif // STREAMING_RESULT_H
