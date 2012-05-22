#ifndef WZY_UTILITIES_GENERAL_HPP
#define WZY_UTILITIES_GENERAL_HPP

#include <string>


namespace wzy {

constexpr double pi = 3.14159265358979323846264338327950288419716939937;

template <class T>
T degreesToRadians(T degrees)
{ return degrees * static_cast<T>(pi / 180); }

template <class T>
T radiansToDegrees(T radians)
{ return radians * static_cast<T>(180 / pi); }

const std::string getFileExtension(const std::string& fileName);
const std::string fileToString(const std::string& fileName);

}

#endif
