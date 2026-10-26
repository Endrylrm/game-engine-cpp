#include "engine/renderer/OpenGL/OpenGLDevice.hpp"

#include <SDL3_image/SDL_image.h>

#include "engine/core/log/Log.hpp"
#include "engine/core/math/Matrix4.hpp"
#include "engine/core/math/Vector3D.hpp"
#include "engine/core/math/Vector4D.hpp"
#include "engine/core/math/conversions/GLMConverter.hpp"
#include "engine/renderer/OpenGL/resources/OpenGLTexture.hpp"
#include "engine/renderer/descriptions/Mesh.hpp"
#include "engine/renderer/descriptions/Shader.hpp"

OpenGLDevice::OpenGLDevice(SDL_Window *window_handle) : window(window_handle) {}

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

    if (!init_glad())
        return false;

    if (!init_texture_pipeline())
        return false;

    if (!init_triangle_pipeline())
        return false;

    if (!init_rect_pipeline())
        return false;

    if (!init_open_gl_state())
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

void OpenGLDevice::set_viewport(Rect2D rect)
{
    glViewport(rect.x, rect.y, rect.w, rect.h);
}

std::unique_ptr<Texture> OpenGLDevice::create_texture(const std::string &path)
{
    SDL_Surface *surface = IMG_Load(path.c_str());

    if (!surface)
    {
        LOG_ERROR("Unable to create surface: {}", SDL_GetError());
        return nullptr;
    }

    SDL_Surface *rgba_surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
    SDL_DestroySurface(surface);

    if (!rgba_surface)
    {
        LOG_ERROR("Unable to create surface: {}", SDL_GetError());
        return nullptr;
    }

    int width = rgba_surface->w;
    int height = rgba_surface->h;

    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA8,
        width,
        height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        rgba_surface->pixels
    );
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    SDL_DestroySurface(rgba_surface);

    if (texture_id == 0)
    {
        LOG_ERROR("Unable to create texture from image in path: '{}'", path);
        return nullptr;
    }

    LOG_DEBUG("OpenGL Texture Created.");

    return std::make_unique<OpenGLTexture>(texture_id, width, height);
}

void OpenGLDevice::draw_texture(Texture *texture, Rect2D rect)
{
    auto *gl_texture = static_cast<OpenGLTexture *>(texture);

    if (!gl_texture || !gl_texture->is_valid())
        return;

    GLuint handle = gl_texture->get_native_handle();

    Vector4D tex_color(1.0f, 1.0f, 1.0f, 1.0f);

    Matrix4 model = Matrix4::translation(Vector3D(rect.x, rect.y, 0.0f)) *
                    Matrix4::scale(Vector3D(rect.w, rect.h, 1.0f));

    Matrix4 projection = Matrix4::orthographic(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
    Matrix4 view = Matrix4::identity();

    texture_shader.use();
    texture_shader.set("model", GLMConverter::to_glm(model));
    texture_shader.set("view", GLMConverter::to_glm(view));
    texture_shader.set("projection", GLMConverter::to_glm(projection));
    texture_shader.set("texColor", GLMConverter::to_glm(tex_color));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, handle);
    texture_shader.set("ourTexture", 0);
    texture_mesh.draw();
}

void OpenGLDevice::draw_rect(Rect2D rect, Color color)
{
    Matrix4 model = Matrix4::translation(Vector3D(rect.x, rect.y, 0.0f)) *
                    Matrix4::scale(Vector3D(rect.w, rect.h, 1.0f));

    Matrix4 projection = Matrix4::orthographic(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
    Matrix4 view = Matrix4::identity();

    Vector4D rect_color(color.r, color.g, color.b, color.a);

    rect_shader.use();
    rect_shader.set("model", GLMConverter::to_glm(model));
    rect_shader.set("view", GLMConverter::to_glm(view));
    rect_shader.set("projection", GLMConverter::to_glm(projection));
    rect_shader.set("rectColor", GLMConverter::to_glm(rect_color));
    rect_mesh.draw();
}

bool OpenGLDevice::init_glad()
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

bool OpenGLDevice::init_open_gl_state()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    return true;
}

bool OpenGLDevice::init_texture_pipeline()
{
    // clang-format off
    constexpr float VERTICES[] = {
        // positions        // UV
        0.0f, 0.0f, 0.0f,   1.0f, 0.0f,   // top left
        1.0f, 0.0f, 0.0f,   0.0f, 0.0f,   // top right
        1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // bottom right
        0.0f, 1.0f, 0.0f,   1.0f, 1.0f    // bottom left 
    };
    // clang-format on

    // clang-format off
    constexpr GLuint INDICES[] = {
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
        make_mesh_description<float>(VERTICES, INDICES, layout, PrimitiveType::Triangles);

    if (!texture_mesh.init(desc))
        return false;

    const std::string VERTEX_SHADER_SOURCE = R"(
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

    const std::string FRAGMENT_SHADER_SOURCE = R"(
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
        {ShaderStage::Vertex,   VERTEX_SHADER_SOURCE  },
        {ShaderStage::Fragment, FRAGMENT_SHADER_SOURCE}
    };

    ShaderDescription shader_desc = make_shader_description(sources);

    if (!texture_shader.init(shader_desc))
        return false;

    LOG_DEBUG("OpenGL Pipeline: Texture Pipeline Initialized.");
    return true;
}

bool OpenGLDevice::init_triangle_pipeline()
{
    // clang-format off
    constexpr float VERTICES[] = {
        // positions   // colors
         0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   // bottom left
         0.0f,  0.5f,  0.0f, 0.0f, 1.0f    // top 
    };
    // clang-format on

    // clang-format off
    constexpr uint32_t INDICES[] = {
        0, 1, 2
    };
    // clang-format on

    VertexAttribute position = {.type = VertexType::Float, .count = 2, .offset = 0};
    VertexAttribute color = {.type = VertexType::Float, .count = 3, .offset = 2 * sizeof(float)};

    VertexLayout layout{
        .attributes{position, color}
    };

    MeshDescription desc =
        make_mesh_description<float>(VERTICES, INDICES, layout, PrimitiveType::Triangles);

    if (!triangle_mesh.init(desc))
        return false;

    const std::string VERTEX_SHADER_SOURCE = R"(
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

    const std::string FRAGMENT_SHADER_SOURCE = R"(
    #version 460 core
    out vec4 fragColor;
    in vec3 triangleColor;

    void main()
    {
        fragColor = vec4(triangleColor, 1.0);
    }
    )";

    ShaderSource sources[] = {
        {ShaderStage::Vertex,   VERTEX_SHADER_SOURCE  },
        {ShaderStage::Fragment, FRAGMENT_SHADER_SOURCE}
    };

    ShaderDescription shader_desc = make_shader_description(sources);

    if (!triangle_shader.init(shader_desc))
        return false;

    LOG_DEBUG("OpenGL Pipeline: Triangle Pipeline Initialized.");
    return true;
}

bool OpenGLDevice::init_rect_pipeline()
{
    // clang-format off
    constexpr float VERTICES[] = {
         1.0f,  1.0f, // bottom right
         1.0f,  0.0f, // top right
         0.0f,  0.0f, // top left
         0.0f,  1.0f  // bottom left
    };
    // clang-format on

    // clang-format off
    constexpr uint32_t INDICES[] = {
        0, 1, 3,
        1, 2, 3
    };
    // clang-format on

    VertexAttribute position = {.type = VertexType::Float, .count = 2, .offset = 0};

    VertexLayout layout{.attributes{position}};

    MeshDescription desc =
        make_mesh_description<float>(VERTICES, INDICES, layout, PrimitiveType::Triangles);

    if (!rect_mesh.init(desc))
        return false;

    const std::string VERTEX_SHADER_SOURCE = R"(
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

    const std::string FRAGMENT_SHADER_SOURCE = R"(
    #version 460 core
    out vec4 fragColor;

    uniform vec4 rectColor;

    void main()
    {
        fragColor = rectColor;
    }
    )";

    ShaderSource sources[] = {
        {ShaderStage::Vertex,   VERTEX_SHADER_SOURCE  },
        {ShaderStage::Fragment, FRAGMENT_SHADER_SOURCE}
    };

    ShaderDescription shader_desc = make_shader_description(sources);

    if (!rect_shader.init(shader_desc))
        return false;

    LOG_DEBUG("OpenGL Pipeline: Rectangle Pipeline Initialized.");
    return true;
}
