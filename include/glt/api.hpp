#ifndef __API_HPP__
#define __API_HPP__

#if !defined(_WIN32) && (defined(__WIN32__) || defined(WIN32) || defined(__MINGW32__))
  #define _WIN32
#endif /* _WIN32 */

#ifdef _WIN32
  #ifdef GLT_EXPORTS
    #define GLT_API _declspec(dllexport)
  #else
    #define GLT_API _declspec(dllimport)
  #endif /* GLT_EXPORTS */
#else
  #define GLT_API
#endif /* GLT_API */

#endif // __API_HPP__
