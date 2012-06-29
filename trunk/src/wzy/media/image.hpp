#ifndef WZY_MEDIA_IMAGE_HPP
#define WZY_MEDIA_IMAGE_HPP

#include <iostream>
#include <memory>
#include <string>

#include <wzy/utilities/vec.hpp>


namespace wzy {

class Image {
public:
    enum class Format {
        BMP,
        JPG,
        PNG
    };

    Image(std::istream& is, const Format& format, std::size_t size);
    Image(const Image& other);
    ~Image();
    Image& operator=(const Image& rhs);

    void load(std::istream& is, const Format& format, std::size_t size);
    void save(std::ostream& os, const Format& format);

    int width() const;
    int height() const;
    Vector2i size() const
    { return {width(), height()}; }

    int bpp() const;

    const unsigned char* data() const;

private:
    struct Private;
    std::unique_ptr<Private> mPrivate;
};

}

#endif
