#ifndef WZY_MEDIA_IMAGE_HPP
#define WZY_MEDIA_IMAGE_HPP

#include <memory>
#include <type_traits>
#include <vector>

#include <wzy/resource/item.hpp>
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


    Image(const Vector2ui& size, const ConstDataPtr& data) :
        mSize(size),
        mData(new Data(*data)) { }

    explicit Image(const std::string& data) :
        mSize(),
        mData(new Data())
    { loadFromString(data); }

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

    const std::string saveToString() const;
    void loadFromString(const std::string& data);


private:
    Vector2ui mSize;
    DataPtr mData;
};


// ----------------------------------------------------
template <class PixelType>
const std::string Image<PixelType>::saveToString() const {
    std::string ret;
    ret.insert(0, reinterpret_cast<const char*>(mData->data()), mData->size() * sizeof(PixelType));
    ret.insert(0, reinterpret_cast<const char*>(&mSize), sizeof(mSize));
    return ret;
}

template <class PixelType>
void Image<PixelType>::loadFromString(const std::string& data) {
    mSize = reinterpret_cast<const Vector2ui&>(*data.data());
    mData->clear();
    mData->reserve((data.size() - sizeof(mSize)) / sizeof(PixelType));
    mData->assign(reinterpret_cast<const PixelType*>(data.data() + sizeof(mSize)),
                  reinterpret_cast<const PixelType*>(data.data() + data.size()));
}


// -----------------------------------------------------
typedef Vector4uc RGBAImagePixelType;

typedef Image<RGBAImagePixelType> RGBAImage;


// -------------------------------------------------
class RGBAImageItem : public Item {
public:
    constexpr static int constId = -2;

    template <class... Args>
    RGBAImageItem(const std::string& name, const std::string& content, Args&&... args) :
        Item(constId, name, std::forward<Args>(args)...),
        mImage(new RGBAImage(content)) {
    }

    template <class... Args>
    RGBAImageItem(const std::string& name, const std::shared_ptr<RGBAImage>& img, Args&&... args) :
        Item(constId, name, std::forward<Args>(args)...),
        mImage(img) {
    }

    const std::string content() const override
    { return mImage->saveToString(); }

    const std::shared_ptr<RGBAImage> image()
    { return mImage; }

private:
    static bool mReg;

    static const std::shared_ptr<Item> create(const std::string& name,
                                              const std::string& content)
    { return std::make_shared<RGBAImageItem>(name, content); }

    std::shared_ptr<RGBAImage> mImage;
};

}

#endif
