#include "engine/renderer/OpenGL/OpenGLDevice.hpp"

#include <SDL3_image/SDL_image.h>

#include <engine/core/log/Log.hpp>
#include <engine/core/math/Matrix4.hpp>
#include <engine/core/math/Vector3D.hpp>
#include <engine/core/math/Vector4D.hpp>
#include <engine/core/math/conversions/GLMConverter.hpp>
#include <engine/renderer/OpenGL/resources/OpenGLTexture.hpp>
#include <engine/renderer/descriptions/Mesh.hpp>
#include <engine/renderer/descriptions/Shader.hpp>

OpenGLDevice::OpenGLDevice(SDL_Window *windowHandle) : window(windowHandle) {}

OpenGLDevice::~OpenGLDevice()
{
    if (context)
        SDL_GL_DestroyContext(context);
}

bool OpenGLDevice::init()
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

void OpenGLDevice::clear(Color color)
{
    glClearColor(color.r, color.b, color.g, color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLDevice::present()
{
    SDL_GL_SwapWindow(window);
}

void OpenGLDevice::setViewport(Rect2D rect)
{
    glViewport(rect.x, rect.y, rect.w, rect.h);
}

std::unique_ptr<Texture> OpenGLDevice::createTexture(const std::string &path)
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

void OpenGLDevice::drawTexture(Texture *texture, Rect2D rect)
{
    auto *glTexture = static_cast<OpenGLTexture *>(texture);

    if (!glTexture || !glTexture->isValid())
        return;

    GLuint handle = glTexture->getNativeHandle();

    Vector4D texColor(1.0f, 1.0f, 1.0f, 1.0f);

    Matrix4 model = Matrix4::translation(Vector3D(rect.x, rect.y, 0.0f)) *
                    Matrix4::scale(Vector3D(rect.w, rect.h, 1.0f));

    Matrix4 projection = Matrix4::orthographic(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
    Matrix4 view = Matrix4::identity();

    textureShader.use();
    textureShader.set("model", GLMConverter::toGLM(model));
    textureShader.set("view", GLMConverter::toGLM(view));
    textureShader.set("projection", GLMConverter::toGLM(projection));
    textureShader.set("texColor", GLMConverter::toGLM(texColor));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, handle);
    textureShader.set("ourTexture", 0);
    textureMesh.draw();
}

void OpenGLDevice::drawRect(Rect2D rect, Color color)
{
    Matrix4 model = Matrix4::translation(Vector3D(rect.x, rect.y, 0.0f)) *
                    Matrix4::scale(Vector3D(rect.w, rect.h, 1.0f));

    Matrix4 projection = Matrix4::orthographic(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
    Matrix4 view = Matrix4::identity();

    Vector4D rectColor(color.r, color.g, color.b, color.a);

    rectShader.use();
    rectShader.set("model", GLMConverter::toGLM(model));
    rectShader.set("view", GLMConverter::toGLM(view));
    rectShader.set("projection", GLMConverter::toGLM(projection));
    rectShader.set("rectColor", GLMConverter::toGLM(rectColor));
    rectMesh.draw();
}

bool OpenGLDevice::initGlad()
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

bool OpenGLDevice::initOpenGLState()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    return true;
}

bool OpenGLDevice::initTexturePipeline()
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

    VertexAttribute position = {.type = VertexType::Float, .count = 3, .offset = 0};
    VertexAttribute uv = {.type = VertexType::Float, .count = 2, .offset = 3 * sizeof(float)};

    VertexLayout layout{
        .attributes{position, uv}
    };

    MeshDescription desc =
        makeMeshDescription<float>(vertices, indices, layout, PrimitiveType::Triangles);

    if (!textureMesh.init(desc))
        return false;

    const std::string vertexShaderSource = R"(
    #version 460 core
    layout (location = 0) in vec3 aPosition;
    layout (location = 1) in vec2 aTexCoord;

    out vec2 texCoord;

    uniform mat4 projection;
    uniform mat4 view;
    uniform mat4 model;

    void main()
    {
        gl_Position = projection * view * model * vec4(aPosition, 1.0);
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

    ShaderSource sources[] = {
        {ShaderStage::Vertex,   vertexShaderSource  },
        {ShaderStage::Fragment, fragmentShaderSource}
    };

    ShaderDescription shaderDesc = makeShaderDescription(sources);

    if (!textureShader.init(shaderDesc))
        return false;

    LOG_DEBUG("OpenGL Pipeline: Texture Pipeline Initialized.");
    return true;
}

bool OpenGLDevice::initTrianglePipeline()
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

    VertexAttribute position = {.type = VertexType::Float, .count = 2, .offset = 0};
    VertexAttribute color = {.type = VertexType::Float, .count = 3, .offset = 2 * sizeof(float)};

    VertexLayout layout{
        .attributes{position, color}
    };

    MeshDescription desc =
        makeMeshDescription<float>(vertices, indices, layout, PrimitiveType::Triangles);

    if (!triangleMesh.init(desc))
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

    ShaderSource sources[] = {
        {ShaderStage::Vertex,   vertexShaderSource  },
        {ShaderStage::Fragment, fragmentShaderSource}
    };

    ShaderDescription shaderDesc = makeShaderDescription(sources);

    if (!triangleShader.init(shaderDesc))
        return false;

    LOG_DEBUG("OpenGL Pipeline: Triangle Pipeline Initialized.");
    return true;
}

bool OpenGLDevice::initRectPipeline()
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

    VertexAttribute position = {.type = VertexType::Float, .count = 2, .offset = 0};

    VertexLayout layout{.attributes{position}};

    MeshDescription desc =
        makeMeshDescription<float>(vertices, indices, layout, PrimitiveType::Triangles);

    if (!rectMesh.init(desc))
        return false;

    const std::string vertexShaderSource = R"(
    #version 460 core
    layout (location = 0) in vec2 aPosition;

    uniform mat4 projection;
    uniform mat4 view;
    uniform mat4 model;

    void main()
    {
        gl_Position = projection * view * model * vec4(aPosition, 0.0, 1.0);
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

    ShaderSource sources[] = {
        {ShaderStage::Vertex,   vertexShaderSource  },
        {ShaderStage::Fragment, fragmentShaderSource}
    };

    ShaderDescription shaderDesc = makeShaderDescription(sources);

    if (!rectShader.init(shaderDesc))
        return false;

    LOG_DEBUG("OpenGL Pipeline: Rectangle Pipeline Initialized.");
    return true;
}
