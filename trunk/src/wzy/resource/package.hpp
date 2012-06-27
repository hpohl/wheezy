#ifndef WZY_RESOURCE_PACKAGE_HPP
#define WZY_RESOURCE_PACKAGE_HPP

#include <memory>
#include <string>
#include <vector>


namespace wzy {

class Package {
public:
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

    class Item {
    public:
        Item(const std::string& name,
             const std::string& content = std::string()) :
            mName(name),
            mContent(content) {
        }

        virtual ~Item() = 0;

        const std::string name() const
        { return mName; }

        const std::string content() const
        { return mContent; }

        void setContent(const std::string& content)
        { mContent = content; }

    private:
        std::string mName;
        std::string mContent;
    };

    class UniversalItem : public Item {
    public:
        template <class... Args>
        UniversalItem(Args&&... args) :
            Item(std::forward<Args>(args)...) { }
    };


    static const std::shared_ptr<Package> load(const std::string& name);
    static void write(const std::shared_ptr<const Package>& pkg);

    Package(const std::string& name, const Version& version);
    ~Package();

    const std::string name() const
    { return mName; }

    const Version version() const
    { return mVersion; }

    template <class ItemT, class... Args>
    void addItem(Args&&... args)
    { mItems.push_back(std::make_shared<ItemT>(std::forward<Args>(args)...)); }

private:
    std::string mName;
    Version mVersion;
    std::vector<std::shared_ptr<Item> > mItems;
};

}

#endif
