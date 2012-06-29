#include <wzy/media/image.hpp>

#include <FreeImage.h>

#include <wzy/utilities/exception.hpp>
#include <wzy/utilities/general.hpp>


namespace wzy {

namespace {

FREE_IMAGE_FORMAT formatToFI(Image::Format f) {
    switch (f) {
    case Image::Format::BMP: return FIF_BMP;
    case Image::Format::JPG: return FIF_JPEG;
    case Image::Format::PNG: return FIF_PNG;
    default: throw Exception("Unknown image format.");
    }
}

Image::Format extensionToFormat(const std::string& ext) {
    if (ext == "bmp") return Image::Format::BMP;
    else if (ext == "jpg") return Image::Format::JPG;
    else if (ext == "png") return Image::Format::PNG;

    throw Exception("Unknown image file extension.");
}

FIBITMAP* load(std::istream& is, const Image::Format& format, std::size_t size) {
    std::string content(size, 0);
    is.read(&content[0], size);
    if (!is.good())
        throw Exception("Error while loading image data from stream.");

    std::unique_ptr<FIMEMORY, void(*)(FIMEMORY*)>
            mem(FreeImage_OpenMemory(reinterpret_cast<BYTE*>(&content[0]), size), FreeImage_CloseMemory);

    auto ptr = FreeImage_LoadFromMemory(formatToFI(format), mem.get());

    if (!ptr)
        throw Exception("Unable to load image.");

    return ptr;
}

void save(FIBITMAP* bitmap, std::ostream& os, const Image::Format& format) {
    std::unique_ptr<FIMEMORY, void(*)(FIMEMORY*)> mem(FreeImage_OpenMemory(), FreeImage_CloseMemory);
    if (!FreeImage_SaveToMemory(formatToFI(format), bitmap, mem.get()))
        throw Exception("Unable to save image.");
    char* data = nullptr;
    DWORD count = 0;
    FreeImage_AcquireMemory(mem.get(), reinterpret_cast<BYTE**>(&data), &count);
    os.write(data, count);
    if (!os.good())
        throw Exception("Unable to save image.");
}

FIBITMAP* clone(const FIBITMAP* bitmap) {
    auto ptr = FreeImage_Clone(const_cast<FIBITMAP*>(bitmap));

    if (!ptr)
        throw Exception("Unable to clone bitmap.");
    return ptr;
}

}


// ----------------------------------------------
class Image::Private {
public:
    Private(FIBITMAP* bitmap) :
        mBitmap(bitmap, FreeImage_Unload) { }

    FIBITMAP* bitmap()
    { return mBitmap.get(); }

    void setBitmap(FIBITMAP* bitmap)
    { mBitmap.reset(bitmap, FreeImage_Unload); }

private:
    std::shared_ptr<FIBITMAP> mBitmap;
};


// ---------------------------------------
Image::Image(std::istream& is, const Format& format, std::size_t size) :
    mPrivate(new Private(wzy::load(is, format, size))) {
}

Image::Image(const Image& other) :
    mPrivate(new Private(wzy::clone(other.mPrivate->bitmap()))) {
}

Image::~Image() {
}


// -------------------------------------------------------
Image& Image::operator=(const Image& rhs) {
    mPrivate->setBitmap(wzy::clone(rhs.mPrivate->bitmap()));
    return *this;
}


// ----------------------------------------------------
void Image::load(std::istream& is, const Format& format, std::size_t size)
{ mPrivate->setBitmap(wzy::load(is, format, size)); }

void Image::save(std::ostream& os, const Format& format)
{ wzy::save(mPrivate->bitmap(), os, format); }

int Image::width() const {
    return FreeImage_GetWidth(mPrivate->bitmap());
}

int Image::height() const {
    return FreeImage_GetHeight(mPrivate->bitmap());
}

int Image::bpp() const {
    return FreeImage_GetBPP(mPrivate->bitmap());
}

const unsigned char* Image::data() const {
    return FreeImage_GetBits(mPrivate->bitmap());
}

}
