#ifndef WZY_RESOURCE_VERSION_HPP
#define WZY_RESOURCE_VERSION_HPP


namespace wzy {

class Version {
public:
    Version(int major, int minor, int patchLevel) :
        mMajor(major), mMinor(minor), mPatchLevel(patchLevel) {
    }

    int major() const
    { return mMajor; }

    int minor() const
    { return mMinor; }

    int patchLevel() const
    { return mPatchLevel; }

private:
    int mMajor;
    int mMinor;
    int mPatchLevel;
};

}

#endif
