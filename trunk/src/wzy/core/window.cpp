#include <wzy/core/window.hpp>

#include <wzy/utilities/exception.hpp>
#include <wzy/utilities/info.hpp>

#ifdef WZY_APPLE
    #include <GLUT/freeglut.h>
#else
    #include <GL/freeglut.h>
#endif


namespace wzy {


Window::MouseButton glut2MouseButton(int button) {
    switch (button) {
    case GLUT_LEFT_BUTTON: return Window::MouseButton::Left;
    case GLUT_MIDDLE_BUTTON: return Window::MouseButton::Middle;
    case GLUT_RIGHT_BUTTON: return Window::MouseButton::Right;

    default:
        throw Exception("Invalid GLUT button value.");
    }
}


// -----------------------------------------------
bool Window::mInitialised = false;
std::map<int, Window*> Window::mWindows;


// ----------------------------------------
void Window::execute() {
    glutMainLoop();
}

void Window::update() {
    glutMainLoopEvent();
}

Window::Key Window::asciiToKey(unsigned char key) {
    switch (key) {
    case 'a': return Key::a;
    case 'b': return Key::b;
    case 'c': return Key::c;
    case 'd': return Key::d;
    case 'e': return Key::e;
    case 'f': return Key::f;
    case 'g': return Key::g;
    case 'h': return Key::h;
    case 'i': return Key::i;
    case 'j': return Key::j;
    case 'k': return Key::k;
    case 'l': return Key::l;
    case 'm': return Key::m;
    case 'n': return Key::n;
    case 'o': return Key::o;
    case 'p': return Key::p;
    case 'q': return Key::q;
    case 'r': return Key::r;
    case 's': return Key::s;
    case 't': return Key::t;
    case 'u': return Key::u;
    case 'v': return Key::v;
    case 'w': return Key::w;
    case 'x': return Key::x;
    case 'y': return Key::y;
    case 'z': return Key::z;

    default: throw Exception("ASCII code not valid key.");
    }
}

unsigned char Window::keyToAscii(Key k) {
    switch (k) {
    case Key::a: return 'a';
    case Key::b: return 'b';
    case Key::c: return 'c';
    case Key::d: return 'd';
    case Key::e: return 'e';
    case Key::f: return 'f';
    case Key::g: return 'g';
    case Key::h: return 'h';
    case Key::i: return 'i';
    case Key::j: return 'j';
    case Key::k: return 'k';
    case Key::l: return 'l';
    case Key::m: return 'm';
    case Key::n: return 'n';
    case Key::o: return 'o';
    case Key::p: return 'p';
    case Key::q: return 'q';
    case Key::r: return 'r';
    case Key::s: return 's';
    case Key::t: return 't';
    case Key::u: return 'u';
    case Key::v: return 'v';
    case Key::w: return 'w';
    case Key::x: return 'x';
    case Key::y: return 'y';
    case Key::z: return 'z';

    default: throw Exception("Key not an ASCII code.");
    }
}

// ------------------------------------------------
Window& Window::currentWindow() {
    auto it = mWindows.find(glutGetWindow());

    if (it == mWindows.end())
        throw Exception("Current window not found in keys.");

    return *it->second;
}

void Window::displayFunc() {
    currentWindow().frame();
    glutSwapBuffers();
    glutPostRedisplay();
}

void Window::reshapeFunc(int width, int height) {
    currentWindow().resized({width, height});
}

void Window::keyboardFunc(unsigned char key, int, int) {
    Window& win = currentWindow();
    Key k = asciiToKey(key);

    win.mKeys.insert(k);
    win.keyPressed(k);
}

void Window::keyboardUpFunc(unsigned char key, int, int) {
    Window& win = currentWindow();
    Key k = asciiToKey(key);

    win.mKeys.erase(k);
    win.keyReleased(k);
}

void Window::mouseFunc(int button, int state, int, int) {
    Window& win = currentWindow();
    MouseButton but = glut2MouseButton(button);

    if (state == GLUT_DOWN) {
        win.mMouseButtons.insert(but);
        win.mousePressed(but);
    } else if (state == GLUT_UP) {
        win.mMouseButtons.erase(but);
        win.mouseReleased(but);
    }
}

void Window::passiveMotionFunc(int x, int y) {
    Window& win = currentWindow();
    win.mMouseX = x;
    win.mMouseY = y;
    win.mouseMoved({x, y});
}

void Window::closeFunc() {
    currentWindow().mClosed = true;
}


// -----------------------------------------------
Window::Window() :
    mId(0),
    mKeys(),
    mMouseButtons(),
    mClosed(false) {

    if (!mInitialised) {
        mInitialised = true;
        int argc = 0;
        glutInit(&argc, nullptr);
        glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
    }

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    mId = glutCreateWindow("wzy::Window");

    if (!mId)
        throw Exception("Unable to create wzy::Window.");

    glutDisplayFunc(displayFunc);
    glutReshapeFunc(reshapeFunc);
    glutKeyboardFunc(keyboardFunc);
    glutKeyboardUpFunc(keyboardUpFunc);
    glutMouseFunc(mouseFunc);
    glutPassiveMotionFunc(passiveMotionFunc);
    glutCloseFunc(closeFunc);

    mWindows.insert(std::make_pair(mId, this));
}

Window::~Window() {
    glutDestroyWindow(mId);
    mWindows.erase(mId);
}


// ---------------------------------------------
int Window::width() const {
    set();
    return glutGet(GLUT_WINDOW_WIDTH);
}

int Window::height() const {
    set();
    return glutGet(GLUT_WINDOW_HEIGHT);
}

const Vector2i Window::size() const {
    return {width(), height()};
}

void Window::setWidth(int width) {
    set();
    glutReshapeWindow(width, height());
}

void Window::setHeight(int height) {
    set();
    glutReshapeWindow(width(), height);
}

void Window::resize(const Vector2i& size) {
    set();
    glutReshapeWindow(size.width(), size.height());
}

bool Window::isClosed() const
{ return mClosed; }

bool Window::isPressed(Key k) const
{ return mKeys.find(k) != mKeys.end(); }

bool Window::isReleased(Key k) const
{ return !isPressed(k); }

bool Window::isPressed(MouseButton but) const
{ return mMouseButtons.find(but) != mMouseButtons.end(); }

bool Window::isReleased(MouseButton but) const
{ return !isPressed(but); }


// -----------------------------------------
void Window::set() const
{ glutSetWindow(mId); }

}
