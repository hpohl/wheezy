#ifndef WZY_CORE_INFO_H
#define WZY_CORE_INFO_H

// -----------------------------------
// Operating system specific
#define WZY_OS "unknown"

// Windows
#ifdef _WIN32
    #define WZY_WINDOWS
    #undef WZY_OS
    #define WZY_OS "Windows"
#endif


// Unix-like
#ifdef __unix__
    #define WZY_UNIX
    #undef WZY_OS
    #define WZY_OS "Unix"
#endif

#ifdef __linux__
    #define WZY_LINUX
    #undef WZY_OS
    #define WZY_OS "Linux"
#endif

#ifdef __APPLE__
    #define WZY_APPLE
    #undef WZY_OS
    #define WZY_OS "Mac OS X"
#endif

// ----------------------------------------
// Compiler specific

// GCC
#ifdef __GNUC__
    #define WZY_GCC
#endif

// -------------------------------------
// Standard specific

// Override "final" and "override" for C++ < 11
#if (__cplusplus < 201112L)
    #define final
    #define override
#endif

#endif // WZY_CORE_INFO_H
