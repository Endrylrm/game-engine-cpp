#include "engine/backend/OpenGL/graphics/OpenGLRenderer.hpp"

#include <SDL3_image/SDL_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <engine/backend/OpenGL/graphics/OpenGLTexture.hpp>
#include <engine/core/log/Log.hpp>

OpenGLRenderer::OpenGLRenderer(SDL_Window *windowHandle) : window(windowHandle) {}

OpenGLRenderer::~OpenGLRenderer()
{
    if (shaderProgram)
        glDeleteProgram(shaderProgram);

    if (ebo)
        glDeleteBuffers(1, &ebo);

    if (vbo)
        glDeleteBuffers(1, &vbo);

    if (vao)
        glDeleteVertexArrays(1, &vao);

    if (context)
        SDL_GL_DestroyContext(context);

    LOG_DEBUG("OpenGL Renderer destroyed.");

    shaderProgram = 0;
    ebo = 0;
    vbo = 0;
    vao = 0;
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

    /*
    if (!initTrianglePipeline())
        return false; */

    /*
    if (!initQuadPipeline())
        return false; */

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
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &ebo);

    if (!vbo || !vao || !ebo)
    {
        LOG_ERROR("Failed to create OpenGL texture buffers.");
        return false;
    }

    // clang-format off
    constexpr float vertices[] = {
        // positions        // colors           // UV
        0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // top left
        1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // top right
        1.0f, 1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f,   // bottom right
        0.0f, 1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f    // bottom left 
    };
    // clang-format on

    // clang-format off
    constexpr GLuint indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    // clang-format on

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float))
    );
    glEnableVertexAttribArray(1);

    // Texture coordinates
    glVertexAttribPointer(
        2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void *>(6 * sizeof(float))
    );
    glEnableVertexAttribArray(2);

    const char *vertexShaderSource = R"(
    #version 460 core
    layout (location = 0) in vec3 aPosition;
    layout (location = 1) in vec3 aColor;
    layout (location = 2) in vec2 aTexCoord;

    out vec3 ourColor;
    out vec2 TexCoord;

    uniform mat4 projection;
    uniform mat4 transform;

    void main()
    {
        gl_Position = projection * transform * vec4(aPosition, 1.0);
        ourColor = aColor;
        TexCoord = aTexCoord;
    }
    )";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        LOG_ERROR("Vertex Shader compilation failed:\n{}", infoLog);
        glDeleteShader(vertexShader);
        return false;
    }

    const char *fragmentShaderSource = R"(
    #version 460 core
    out vec4 FragColor;
  
    in vec3 ourColor;
    in vec2 TexCoord;

    uniform sampler2D ourTexture;

    void main()
    {
        FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
    }
    )";

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        LOG_ERROR("Fragment Shader compilation failed:\n{}", infoLog);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return false;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        LOG_ERROR("Linking Shaders failed:\n{}", infoLog);

        glDeleteProgram(shaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return false;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    LOG_DEBUG("OpenGL Pipeline: Texture Pipeline Initialized.");
    return true;
}

bool OpenGLRenderer::initTrianglePipeline()
{
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    if (!vbo || !vao)
    {
        LOG_ERROR("Failed to create OpenGL triangle buffers.");
        return false;
    }

    // clang-format off
    constexpr float vertices[] = {
        // positions   // colors
         0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   // bottom left
         0.0f,  0.5f,  0.0f, 0.0f, 1.0f    // top 
    };
    // clang-format on

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void *>(2 * sizeof(float))
    );
    glEnableVertexAttribArray(1);

    const char *vertexShaderSource = R"(
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

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        LOG_ERROR("Vertex Shader compilation failed:\n{}", infoLog);
        glDeleteShader(vertexShader);
        return false;
    }

    const char *fragmentShaderSource = R"(
    #version 460 core
    out vec4 fragColor;
    in vec3 triangleColor;

    void main()
    {
        fragColor = vec4(triangleColor, 1.0);
    }
    )";

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        LOG_ERROR("Fragment Shader compilation failed:\n{}", infoLog);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return false;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        LOG_ERROR("Linking Shaders failed:\n{}", infoLog);

        glDeleteProgram(shaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return false;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    LOG_DEBUG("OpenGL Pipeline: Triangle Pipeline Initialized.");
    return true;
}

bool OpenGLRenderer::initQuadPipeline()
{
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &ebo);

    if (!vbo || !vao || !ebo)
    {
        LOG_ERROR("Failed to create OpenGL triangle buffers.");
        return false;
    }

    // clang-format off
    constexpr float vertices[] = {
         0.5f,  0.5f, // top right
         0.5f, -0.5f, // bottom right
        -0.5f, -0.5f, // bottom left
        -0.5f,  0.5f  // top left
    };
    // clang-format on

    // clang-format off
    constexpr GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };
    // clang-format on

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    const char *vertexShaderSource = R"(
    #version 460 core
    layout (location = 0) in vec2 aPosition;

    void main()
    {
        gl_Position = vec4(aPosition, 0.0, 1.0);
    }
    )";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        LOG_ERROR("Vertex Shader compilation failed:\n{}", infoLog);
        glDeleteShader(vertexShader);
        return false;
    }

    const char *fragmentShaderSource = R"(
    #version 460 core
    out vec4 quadColor;

    void main()
    {
        quadColor = vec4(0.0, 0.0, 1.0, 1.0);
    }
    )";

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        LOG_ERROR("Fragment Shader compilation failed:\n{}", infoLog);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return false;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        LOG_ERROR("Linking Shaders failed:\n{}", infoLog);

        glDeleteProgram(shaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return false;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    LOG_DEBUG("OpenGL Pipeline: Quad Pipeline Initialized.");
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

    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(x, y, 0.0f));
    transform = glm::scale(transform, glm::vec3(w, h, 1.0f));

    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

    glUseProgram(shaderProgram);
    GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
    GLint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glBindTexture(GL_TEXTURE_2D, handle);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void OpenGLRenderer::drawTexture(Texture *texture, Rect2D rect)
{
    drawTexture(texture, rect.x, rect.y, rect.w, rect.h);
}

void OpenGLRenderer::drawRect(
    float x, float y, float w, float h, uint8_t r, uint8_t g, uint8_t b, uint8_t a
)
{
}

void OpenGLRenderer::drawRect(Rect2D rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {}

void OpenGLRenderer::clear()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRenderer::present()
{
    SDL_GL_SwapWindow(window);
}
