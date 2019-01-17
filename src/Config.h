#if defined(__unix__)
#define TK_PLATFORM_UNIX

#elif defined(_WIN32)
#define TK_PLATFORM_WINDOWS
#pragma message ("Support for this platform is incomplete and may cause crashes")

#else
#error This platform is not supported

#endif

#if defined(DEBUG)
#define TK_DEBUG
#endif