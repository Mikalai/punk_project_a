#ifndef _H_PUNK_ENGINE_PUBLIC_CONFIG
#define _H_PUNK_ENGINE_PUBLIC_CONFIG

// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
#   define PUNK_ENGINE_HELPER_DLL_IMPORT __declspec(dllimport)
#   define PUNK_ENGINE_HELPER_DLL_EXPORT __declspec(dllexport)
#   define PUNK_ENGINE_HELPER_DLL_LOCAL
#else
#if __GNUC__ >= 4
#   define PUNK_ENGINE_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
#   define PUNK_ENGINE_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
#   define PUNK_ENGINE_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#else
#   define PUNK_ENGINE_HELPER_DLL_IMPORT
#   define PUNK_ENGINE_HELPER_DLL_EXPORT
#   define PUNK_ENGINE_HELPER_DLL_LOCAL
#endif
#endif

// Now we use the generic helper definitions above to define PUNK_ENGINE_API and PUNK_ENGINE_LOCAL.
// PUNK_ENGINE_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// PUNK_ENGINE_LOCAL is used for non-api symbols.

#ifdef PUNK_ENGINE_EXPORTS // defined if we are building the FOX DLL (instead of using it)
#   define PUNK_ENGINE_API PUNK_ENGINE_HELPER_DLL_EXPORT
#else
#define PUNK_ENGINE_API PUNK_ENGINE_HELPER_DLL_IMPORT
#endif // PUNK_ENGINE_EXPORTS_EXPORTS

#define PUNK_ENGINE_LOCAL PUNK_ENGINE_HELPER_DLL_LOCAL


#ifdef _WIN32
#define PUNK_STDCALL __stdcall
#define PUNK_CDECL __cdecl
#define PUNK_INFINITE INFINITE

#elif defined __linux__
#define PUNK_STDCALL
#define PUNK_CDECL __attribute__((__cdecl__))
#define PUNK_INFINITE ~0u
#endif


#define PUNK_ENGINE_BEGIN namespace Punk { namespace Engine {
#define PUNK_ENGINE_END } }

#endif	//	_H_PUNK_IMAGE_CONFIG
