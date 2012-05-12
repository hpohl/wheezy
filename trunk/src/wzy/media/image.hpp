#ifndef WZY_MEDIA_IMAGE_HPP
#define WZY_MEDIA_IMAGE_HPP

#include <memory>
#include <string>

#include <wzy/utilities/vec.hpp>


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

    int width() const;
    int height() const;
    Vector2i size() const
    { return {width(), height()}; }

    int bpp() const;

    const unsigned char* data() const;

private:
    struct Private;
    typedef std::unique_ptr<Private> PrivatePtr;

    PrivatePtr mPrivate;
};

}

#endif
