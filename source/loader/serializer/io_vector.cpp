//#include "io_vector.h"
//
//PUNK_ENGINE_BEGIN
//namespace IoModule {
//    PUNK_ENGINE_API void SaveVector2f(Core::Buffer* buffer, const Math::vec2& value) {
//        for (int i = 0; i < 2; ++i)
//            buffer->WriteReal32(value[i]);
//    }
//
//    PUNK_ENGINE_API void LoadVector2f(Core::Buffer* buffer, Math::vec2& value) {
//        for (int i = 0; i < 2; ++i)
//            value[i] = buffer->ReadReal32();
//    }
//
//    PUNK_ENGINE_API void SaveVector2i(Core::Buffer* buffer, const Math::ivec2& value) {
//        for (int i = 0; i < 2; ++i)
//            buffer->WriteSigned32(value[i]);
//    }
//
//    PUNK_ENGINE_API void LoadVector2i(Core::Buffer* buffer, Math::ivec2& value) {
//        for (int i = 0; i < 2; ++i)
//            value[i] = buffer->ReadSigned32();
//    }
//
//    PUNK_ENGINE_API void SaveVector3f(Core::Buffer* buffer, const Math::vec3& value) {
//        for (int i = 0; i < 3; ++i)
//            buffer->WriteReal32(value[i]);
//    }
//
//    PUNK_ENGINE_API void LoadVector3f(Core::Buffer* buffer, Math::vec3& value) {
//        for (int i = 0; i < 3; ++i)
//            value[i] = buffer->ReadReal32();
//    }
//
//    PUNK_ENGINE_API void SaveVector3i(Core::Buffer* buffer, const Math::ivec3& value) {
//        for (int i = 0; i < 3; ++i)
//            buffer->WriteSigned32(value[i]);
//    }
//
//    PUNK_ENGINE_API void LoadVector3i(Core::Buffer* buffer, Math::ivec3& value) {
//        for (int i = 0; i < 3; ++i)
//            value[i] = buffer->ReadSigned32();
//    }
//
//    PUNK_ENGINE_API void SaveVector4f(Core::Buffer* buffer, const Math::vec4& value) {
//        for (int i = 0; i < 4; ++i)
//            buffer->WriteReal32(value[i]);
//    }
//
//    PUNK_ENGINE_API void LoadVector4f(Core::Buffer* buffer, Math::vec4& value) {
//        for (int i = 0; i < 4; ++i)
//            value[i] = buffer->ReadReal32();
//    }
//}
//PUNK_ENGINE_END
