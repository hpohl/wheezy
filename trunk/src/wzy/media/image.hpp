#ifndef WZY_MEDIA_IMAGE_HPP
#define WZY_MEDIA_IMAGE_HPP

#include <memory>
#include <string>


namespace wzy {

class Image {
public:
    enum class Format {
        BMP,
        PNG
    };

    Image(const std::string& fileName);
    Image(const Image& other);
    ~Image();
    Image& operator=(const Image& rhs);

private:
    struct Private;
    typedef std::unique_ptr<Private> PrivatePtr;

    PrivatePtr mPrivate;
};

}

#endif
