#include <wzy/utilities/general.hpp>

#include <wzy/utilities/exception.hpp>


namespace wzy {

const std::string getFileExtension(const std::string& fileName) {
    size_t pos = fileName.find_last_of('.');

    if (pos == std::string::npos || pos + 1 >= fileName.size())
        throw Exception("File name does not contain file extension.");

    return std::string(fileName, pos + 1);
}

}
