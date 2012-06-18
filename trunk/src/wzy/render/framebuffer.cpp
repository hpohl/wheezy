#include <wzy/render/framebuffer.hpp>

#include <wzy/core/window.hpp>
#include <wzy/render/glew.hpp>
#include <wzy/utilities/exception.hpp>


namespace wzy {
namespace render {

void FrameBuffer::useDefault() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

const Vector2i FrameBuffer::currentSize() {
    GLint name = 0;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &name);

    Vector2i ret;

    if (name == 0)
        ret = Window::currentWindow().size();
    else {
        glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,
                                              GL_COLOR_ATTACHMENT0,
                                              GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME,
                                              &name);

        if (!name)
            throw Exception("Can't determine framebuffer size: No colour attachment.");

        GLint width = 0, height = 0;
        glBindTexture(GL_TEXTURE_2D, name);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);

        ret = Vector2i(width, height);
    }

    return ret;
}


// -----------------------------------------------
FrameBuffer::Pusher::Pusher(const std::shared_ptr<FrameBuffer>& fb) :
    mPrevious(0),
    mPopped(false) {

    GLint name = 0;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &name);
    mPrevious = name;

    fb->bind();
}

FrameBuffer::Pusher::~Pusher() {
    pop();
}


// --------------------------------------------------
void FrameBuffer::Pusher::pop() {
    if (!mPopped)
        glBindFramebuffer(GL_FRAMEBUFFER, mPrevious);
    mPopped = true;
}


// ------------------------------------------------
FrameBuffer::FrameBuffer(const Vector2i& size) :
    mName(),
    mColourAttachments(),
    mRenderBuffer(0),
    mSize(size) {

    GLuint fbname = 0;
    glGenFramebuffers(1, &fbname);
    if (!fbname)
        throw Exception("Unable to create frame buffer.");
    mName.reset(new GLuint(fbname), [](GLuint* id) -> void { glDeleteFramebuffers(1, id); delete id; });

    mColourAttachments.push_back(std::make_shared<Texture2D>());
    mColourAttachments.back()->reserve(Texture2D::SizedInternalFormat::RGBA8, size);

    GLuint rbname = 0;
    glGenRenderbuffers(1, &rbname);
    if (!rbname)
        throw Exception("Unable to create render buffer.");
    mRenderBuffer.reset(new GLuint(rbname), [](GLuint* id) -> void { glDeleteRenderbuffers(1, id); delete id; });


    glBindRenderbuffer(GL_RENDERBUFFER, *mRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT,
                          size.x(), size.y());

    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                           GL_TEXTURE_2D, mColourAttachments.back()->name(), 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                              GL_RENDERBUFFER, *mRenderBuffer);

    validate();
}

FrameBuffer::~FrameBuffer() {
}


// ---------------------------------------
void FrameBuffer::bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, *mName);
    if (!bound())
        throw Exception("Failed to bind render buffer.");
}

bool FrameBuffer::bound() const {
    GLint name = 0;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &name);
    return static_cast<unsigned int>(name) == *mName;
}

bool FrameBuffer::valid() const {
    bind();
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    return status == GL_FRAMEBUFFER_COMPLETE;
}

void FrameBuffer::validate() const {
    if (!valid())
        throw Exception("Invalid frame buffer detected.");
}

}
}
