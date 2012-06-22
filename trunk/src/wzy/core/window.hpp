#ifndef WZY_CORE_WINDOW_HPP
#define WZY_CORE_WINDOW_HPP

#include <map>
#include <set>

#include <wzy/utilities/vec.hpp>


namespace wzy {

class Window {
public:
    enum class Key {
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z
    };

    enum class MouseButton {
        Left, Middle, Right
    };

    static Vector2i defaultSize;

    static void execute();
    static void update();
    static Key asciiToKey(unsigned char key);
    static unsigned char keyToAscii(Key k);
    static Window& currentWindow();

    Window();
    virtual ~Window() = 0;

    int width() const;
    int height() const;
    const Vector2i size() const;
    void setWidth(int width);
    void setHeight(int height);
    void resize(const Vector2i& size);

    bool isClosed() const;

    bool isPressed(Key k) const;
    bool isReleased(Key k) const;
    bool isPressed(MouseButton but) const;
    bool isReleased(MouseButton but) const;

    const Vector2i mousePos() const
    { return mMousePos; }

    const Vector2i mouseForce() const
    { return mMouseForce; }

private:
    static bool mInitialised;
    static std::map<int, Window*> mWindows;

    static void displayFunc();
    static void reshapeFunc(int width, int height);
    static void keyboardFunc(unsigned char key, int, int);
    static void keyboardUpFunc(unsigned char key, int, int);
    static void mouseFunc(int button, int state, int, int);
    static void motionFunc(int x, int y);
    static void passiveMotionFunc(int x, int y);
    static void closeFunc();

    int mId;
    std::set<Key> mKeys;
    std::set<MouseButton> mMouseButtons;
    Vector2i mMousePos;
    Vector2i mLastMousePos;
    Vector2i mMouseForce;
    bool mMouseForceUpdated;
    int mTimeSinceLastUpdate;
    bool mClosed;

    virtual void frame() { }
    virtual void resized(const Vector2i& size) { }
    virtual void keyPressed(Key k) { }
    virtual void keyReleased(Key k) { }
    virtual void mousePressed(MouseButton but) { }
    virtual void mouseReleased(MouseButton but) { }
    virtual void mouseMoved(const Vector2i& pos) { }

    void set() const;
};

}

#endif
