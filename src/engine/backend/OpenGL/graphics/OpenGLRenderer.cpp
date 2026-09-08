#include "engine/backend/OpenGL/graphics/OpenGLRenderer.hpp"

#include <string>

#include <SDL3_image/SDL_image.h>

#include <engine/backend/OpenGL/graphics/OpenGLTexture.hpp>
#include <engine/core/graphics/MeshData.hpp>
#include <engine/core/log/Log.hpp>
#include <engine/core/math/Matrix4.hpp>
#include <engine/core/math/Vector3D.hpp>
#include <engine/core/math/Vector4D.hpp>
#include <engine/core/math/conversions/GLMConverter.hpp>

OpenGLRenderer::OpenGLRenderer(SDL_Window *windowHandle) : window(windowHandle) {}

OpenGLRenderer::~OpenGLRenderer()
{
    if (context)
        SDL_GL_DestroyContext(context);

    LOG_DEBUG("OpenGL Renderer destroyed.");
}

bool OpenGLRenderer::onInit()
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    context = SDL_GL_CreateContext(window);

    if (!context)
    {
        LOG_ERROR("Failed to create OpenGL Context: {}", SDL_GetError());
        return false;
    }

    if (!initGlad())
        return false;

    if (!initViewport())
        return false;

    if (!initTexturePipeline())
        return false;

    if (!initTrianglePipeline())
        return false;

    if (!initRectPipeline())
        return false;

    if (!initOpenGLState())
        return false;

    return true;
}

bool OpenGLRenderer::initGlad()
{
    int version = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);

    if (version == 0)
    {
        LOG_ERROR("Failed to initialize GLAD.");
        SDL_GL_DestroyContext(context);
        context = nullptr;
        return false;
    }

    LOG_DEBUG("Vendor: {}", reinterpret_cast<const char *>(glGetString(GL_VENDOR)));
    LOG_DEBUG("OpenGL: {}.", reinterpret_cast<const char *>(glGetString(GL_VERSION)));
    LOG_DEBUG("GPU: {}.", reinterpret_cast<const char *>(glGetString(GL_RENDERER)));
    return true;
}

bool OpenGLRenderer::initViewport()
{
    int width;
    int height;

    if (!SDL_GetWindowSize(window, &width, &height))
    {
        LOG_ERROR("Unable to get Window Size: {}", SDL_GetError());
        return false;
    }

    glViewport(0, 0, width, height);
    return true;
}

bool OpenGLRenderer::initTexturePipeline()
{
    // clang-format off
    constexpr float vertices[] = {
        // positions        // UV
        0.0f, 0.0f, 0.0f,   1.0f, 0.0f,   // top left
        1.0f, 0.0f, 0.0f,   0.0f, 0.0f,   // top right
        1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // bottom right
        0.0f, 1.0f, 0.0f,   1.0f, 1.0f    // bottom left 
    };
    // clang-format on

    // clang-format off
    constexpr GLuint indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    // clang-format on

    VertexAttribute position = {.type = VertexType::Float, .location = 0, .count = 3, .offset = 0};
    VertexAttribute uv = {
        .type = VertexType::Float, .location = 1, .count = 2, .offset = 3 * sizeof(float)
    };

    VertexLayout layout{
        .attributes{position, uv},
        .stride = 5 * sizeof(float)
    };

    MeshData data = makeMeshData<float>(vertices, indices, layout, PrimitiveType::Triangles);

    if (!textureMesh.init(data))
        return false;

    const std::string vertexShaderSource = R"(
    #version 460 core
    layout (location = 0) in vec3 aPosition;
    layout (location = 1) in vec2 aTexCoord;

    out vec2 texCoord;

    uniform mat4 projection;
    uniform mat4 transform;

    void main()
    {
        gl_Position = projection * transform * vec4(aPosition, 1.0);
        texCoord = aTexCoord;
    }
    )";

    const std::string fragmentShaderSource = R"(
    #version 460 core
    out vec4 fragColor;
  
    in vec2 texCoord;

    uniform vec4 texColor;
    uniform sampler2D ourTexture;

    void main()
    {
        fragColor = texture(ourTexture, texCoord) * texColor;
    }
    )";

    if (!textureShader.init(vertexShaderSource, fragmentShaderSource))
        return false;

    LOG_DEBUG("OpenGL Pipeline: Texture Pipeline Initialized.");
    return true;
}

bool OpenGLRenderer::initTrianglePipeline()
{
    // clang-format off
    constexpr float vertices[] = {
        // positions   // colors
         0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   // bottom left
         0.0f,  0.5f,  0.0f, 0.0f, 1.0f    // top 
    };
    // clang-format on

    // clang-format off
    constexpr uint32_t indices[] = {
        0, 1, 2
    };
    // clang-format on

    VertexAttribute position = {.type = VertexType::Float, .location = 0, .count = 2, .offset = 0};
    VertexAttribute color = {
        .type = VertexType::Float, .location = 1, .count = 3, .offset = 2 * sizeof(float)
    };

    VertexLayout layout{
        .attributes{position, color},
        .stride = 5 * sizeof(float)
    };

    MeshData data = makeMeshData<float>(vertices, indices, layout, PrimitiveType::Triangles);

    if (!triangleMesh.init(data))
        return false;

    const std::string vertexShaderSource = R"(
    #version 460 core
    layout (location = 0) in vec2 aPosition;
    layout (location = 1) in vec3 aColor;

    out vec3 triangleColor;

    void main()
    {
        gl_Position = vec4(aPosition, 0.0, 1.0);
        triangleColor = aColor;
    }
    )";

    const std::string fragmentShaderSource = R"(
    #version 460 core
    out vec4 fragColor;
    in vec3 triangleColor;

    void main()
    {
        fragColor = vec4(triangleColor, 1.0);
    }
    )";

    if (!triangleShader.init(vertexShaderSource, fragmentShaderSource))
        return false;

    LOG_DEBUG("OpenGL Pipeline: Triangle Pipeline Initialized.");
    return true;
}

bool OpenGLRenderer::initRectPipeline()
{
    // clang-format off
    constexpr float vertices[] = {
         1.0f,  1.0f, // bottom right
         1.0f,  0.0f, // top right
         0.0f,  0.0f, // top left
         0.0f,  1.0f  // bottom left
    };
    // clang-format on

    // clang-format off
    constexpr uint32_t indices[] = {
        0, 1, 3,
        1, 2, 3
    };
    // clang-format on

    VertexAttribute position = {.type = VertexType::Float, .location = 0, .count = 2, .offset = 0};

    VertexLayout layout{.attributes{position}, .stride = 2 * sizeof(float)};

    MeshData data = makeMeshData<float>(vertices, indices, layout, PrimitiveType::Triangles);

    if (!rectMesh.init(data))
        return false;

    const std::string vertexShaderSource = R"(
    #version 460 core
    layout (location = 0) in vec2 aPosition;

    uniform mat4 projection;
    uniform mat4 transform;

    void main()
    {
        gl_Position = projection * transform * vec4(aPosition, 0.0, 1.0);
    }
    )";

    const std::string fragmentShaderSource = R"(
    #version 460 core
    out vec4 fragColor;

    uniform vec4 rectColor;

    void main()
    {
        fragColor = rectColor;
    }
    )";

    if (!rectShader.init(vertexShaderSource, fragmentShaderSource))
        return false;

    LOG_DEBUG("OpenGL Pipeline: Rectangle Pipeline Initialized.");
    return true;
}

bool OpenGLRenderer::initOpenGLState()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true;
}

std::unique_ptr<Texture> OpenGLRenderer::loadTexture(const std::string &path)
{
    SDL_Surface *surface = IMG_Load(path.c_str());

    if (!surface)
    {
        LOG_ERROR("Unable to create surface: {}", SDL_GetError());
        return nullptr;
    }

    SDL_Surface *rgbaSurface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
    SDL_DestroySurface(surface);

    if (!rgbaSurface)
    {
        LOG_ERROR("Unable to create surface: {}", SDL_GetError());
        return nullptr;
    }

    int width = rgbaSurface->w;
    int height = rgbaSurface->h;

    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgbaSurface->pixels
    );
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    SDL_DestroySurface(rgbaSurface);

    if (textureId == 0)
    {
        LOG_ERROR("Unable to create texture from image in path: '{}'", path);
        return nullptr;
    }

    LOG_DEBUG("OpenGL Texture Created.");

    return std::make_unique<OpenGLTexture>(textureId, width, height);
}

void OpenGLRenderer::drawTexture(Texture *texture, float x, float y)
{
    drawTexture(
        texture,
        x,
        y,
        static_cast<float>(texture->getWidth()),
        static_cast<float>(texture->getHeight())
    );
}

void OpenGLRenderer::drawTexture(Texture *texture, float x, float y, float w, float h)
{
    auto *glTexture = static_cast<OpenGLTexture *>(texture);

    if (!glTexture || !glTexture->isValid())
        return;

    GLuint handle = glTexture->getNativeHandle();

    Vector4D texColor(1.0f, 1.0f, 1.0f, 1.0f);

    Matrix4 transform =
        Matrix4::translation(Vector3D(x, y, 0.0f)) * Matrix4::scale(Vector3D(w, h, 1.0f));

    Matrix4 projection = Matrix4::orthographic(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

    textureShader.use();
    textureShader.setMat4("transform", GLMConverter::toGLM(transform));
    textureShader.setMat4("projection", GLMConverter::toGLM(projection));
    textureShader.setVec4("texColor", GLMConverter::toGLM(texColor));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, handle);
    textureShader.setInt("ourTexture", 0);
    textureMesh.draw();
}

void OpenGLRenderer::drawTexture(Texture *texture, Rect2D rect)
{
    drawTexture(texture, rect.x, rect.y, rect.w, rect.h);
}

void OpenGLRenderer::drawRect(
    float x, float y, float w, float h, uint8_t r, uint8_t g, uint8_t b, uint8_t a
)
{
    Matrix4 transform =
        Matrix4::translation(Vector3D(x, y, 0.0f)) * Matrix4::scale(Vector3D(w, h, 1.0f));

    Matrix4 projection = Matrix4::orthographic(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

    Vector4D rectColor(
        static_cast<float>(r) / 255.0f,
        static_cast<float>(g) / 255.0f,
        static_cast<float>(b) / 255.0f,
        static_cast<float>(a) / 255.0f
    );

    rectShader.use();
    rectShader.setMat4("transform", GLMConverter::toGLM(transform));
    rectShader.setMat4("projection", GLMConverter::toGLM(projection));
    rectShader.setVec4("rectColor", GLMConverter::toGLM(rectColor));
    rectMesh.draw();
}

void OpenGLRenderer::drawRect(Rect2D rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    drawRect(rect.x, rect.y, rect.w, rect.h, r, g, b, a);
}

void OpenGLRenderer::clear()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRenderer::present()
{
    SDL_GL_SwapWindow(window);
}
