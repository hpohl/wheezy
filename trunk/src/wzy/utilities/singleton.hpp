#ifndef WZY_UTILITIES_SINGLETON_HPP
#define WZY_UTILITIES_SINGLETON_HPP

namespace wzy {

template <class T>
class Singleton {
public:
    static T* singletonPtr() {
        if (!mPtr)
            mPtr = new T;
        return mPtr;
    }

    static T& singleton()
    { return *singletonPtr(); }

    virtual ~Singleton() = 0;

private:
    static T* mPtr;
};

template <class T>
T* Singleton<T>::mPtr = nullptr;

template <class T>
Singleton<T>::~Singleton() { }

}

#endif
