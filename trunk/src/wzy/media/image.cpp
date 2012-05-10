#include <wzy/media/image.hpp>

#include <FreeImage.h>

#include <wzy/utilities/exception.hpp>
#include <wzy/utilities/general.hpp>


namespace wzy {

namespace {

FREE_IMAGE_FORMAT formatToFI(Image::Format f) {
    switch (f) {
    case Image::Format::BMP: return FIF_BMP;
    case Image::Format::PNG: return FIF_PNG;
    default: throw Exception("Unknown image format.");
    }
}

Image::Format extensionToFormat(const std::string& ext) {
    if (ext == "bmp") return Image::Format::BMP;
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

}
