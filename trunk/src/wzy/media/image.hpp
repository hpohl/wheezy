#ifndef WZY_MEDIA_IMAGE_HPP
#define WZY_MEDIA_IMAGE_HPP

#include <memory>
#include <type_traits>
#include <vector>

#include <wzy/utilities/general.hpp>
#include <wzy/utilities/vec.hpp>


namespace wzy {


template <int n, class T>
using ImagePixelType = Vector<n, T>;

template <class T>
using IsImagePixelType = IsVec<T>;


template <class PixelType>
class Image {
public:
    static_assert(IsImagePixelType<PixelType>::value, "Invalid pixel type.");

    typedef std::vector<PixelType> Data;
    typedef std::shared_ptr<Data> DataPtr;
    typedef std::shared_ptr<const Data> ConstDataPtr;

    Image() :
        mSize(Vector2ui(0, 0)),
        mData(new Data) {
    }

    Image(const Vector2ui& size, const ConstDataPtr& data) :
        mSize(size),
        mData(new Data(*validate(data))) { }

    Image(std::istream& is) :
        mSize(),
        mData() {
        load(is);
    }

    Image(const Image& other) :
        mSize(other.mSize),
        mData(new Data(*other.mData)) { }

    ~Image() { }


    const Vector2ui size() const
    { return mSize; }

    const DataPtr data()
    { return mData; }

    const ConstDataPtr data() const
    { return mData; }

    const PixelType pixel(const Vector2ui& pos) const
    { return mData->at(pos.y() * mSize.x() + pos.x()); }

    void load(std::istream& is);
    void save(std::ostream& os) const;

private:
    Vector2ui mSize;
    DataPtr mData;
};


// ----------------------------------------------------
template <class PixelType>
void Image<PixelType>::load(std::istream& is) {
    Vector2<std::int32_t> size;
    is.read(reinterpret_cast<char*>(&size), sizeof(size));
    mSize = size;

    std::size_t toRead = mSize.x() * mSize.y() * sizeof(PixelType);
    mData->resize(toRead);
    is.read(reinterpret_cast<char*>(&(*mData)[0]), toRead);
}

template <class PixelType>
void Image<PixelType>::save(std::ostream& os) const {
    Vector2<std::int32_t> size = mSize;
    os.write(reinterpret_cast<const char*>(&size), sizeof(size));
    os.write(reinterpret_cast<const char*>(&(*mData)[0]), mSize.x() * mSize.y() * sizeof(PixelType));
}


// -----------------------------------------------------
typedef Vector4uc RGBAImagePixel;
typedef Vector3uc RGBImagePixel;

typedef Image<RGBAImagePixel> RGBAImage;
typedef Image<RGBAImagePixel> RGBImage;

}

#endif
