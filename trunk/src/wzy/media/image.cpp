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

}


// ----------------------------------------------
struct Image::Private {
    FIBITMAP* bitmap = nullptr;
};


// ---------------------------------------
Image::Image(const std::string& fileName) :
    mPrivate(new Private) {

    mPrivate->bitmap = FreeImage_Load(formatToFI(extensionToFormat(getFileExtension(fileName))), fileName.c_str());

    if (!mPrivate->bitmap)
        throw Exception("Unable to create image from file " + fileName + ".");

    int curbpp = bpp();
    if (curbpp != 8 && curbpp != 24 && curbpp != 32) {
        FreeImage_Unload(mPrivate->bitmap);
        throw Exception("Images have to be 8-, 24- or 32-bit.");
    }
}

Image::Image(const Image& other) :
    mPrivate(new Private) {

    mPrivate->bitmap = FreeImage_Clone(other.mPrivate->bitmap);

    if (!mPrivate->bitmap)
        throw Exception("Unable to clone image.");
}

Image::~Image() {
    FreeImage_Unload(mPrivate->bitmap);
}


// -------------------------------------------------------
Image& Image::operator=(const Image& rhs) {
    FIBITMAP* temp = FreeImage_Clone(rhs.mPrivate->bitmap);

    if (!temp)
        throw Exception("Unable to clone image.");

    FreeImage_Unload(mPrivate->bitmap);
    mPrivate->bitmap = temp;

    return *this;
}


// ----------------------------------------------------
int Image::width() const {
    return FreeImage_GetWidth(mPrivate->bitmap);
}

int Image::height() const {
    return FreeImage_GetHeight(mPrivate->bitmap);
}

int Image::bpp() const {
    return FreeImage_GetBPP(mPrivate->bitmap);
}

const unsigned char* Image::data() const {
    return FreeImage_GetBits(mPrivate->bitmap);
}

}
