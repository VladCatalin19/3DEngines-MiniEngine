#include "SubMesh.hpp"

#include <Constants/GraphicsConstants.hpp>
#include <Utils/CatchAndRethrowExceptions.hpp>  // CATCH_RETHROW_EXCEPTIONS
#include <Utils/PrintGLErrors.hpp>              // PRINT_GL_ERRORS_IF_ANY

#include <glad/glad.h>          // GLuint, GLsizeiptr, glGenVertexArrays, glBindVertexArray,
                                // glGenBuffers, glBindBuffer, glBufferData, glEnableVertexAttribArray
                                // glVertexAttribPointer, glDeleteBuffers, glDeleteVertexArrays

#include <memory>                   // std::move

static GLuint GenerateVAO() noexcept
{
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    PRINT_GL_ERRORS_IF_ANY();

    glBindVertexArray(vao);
    PRINT_GL_ERRORS_IF_ANY();

    return vao;
}

template <typename TVector>
static GLuint GenerateVBO(const std::vector<TVector> &std_vector, GLuint location) noexcept
{
    if (std_vector.empty())
    {
        return static_cast<GLuint>(0);
    }

    GLuint vbo = 0;
    GLsizeiptr std_vector_size = sizeof(std_vector[0]) * std_vector.size();
    const void *std_vector_pointer = reinterpret_cast<const void*>(&std_vector[0]);
    constexpr GLint vector_size = TVector::Size();

    glGenBuffers(1, &vbo);
    PRINT_GL_ERRORS_IF_ANY();

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    PRINT_GL_ERRORS_IF_ANY();

    glBufferData(GL_ARRAY_BUFFER, std_vector_size, std_vector_pointer, GL_STATIC_DRAW);
    PRINT_GL_ERRORS_IF_ANY();

    glEnableVertexAttribArray(location);
    PRINT_GL_ERRORS_IF_ANY();

    glVertexAttribPointer(location, vector_size, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(0), nullptr);
    PRINT_GL_ERRORS_IF_ANY();

    return vbo;
}

static GLuint GenerateIBO(const std::vector<unsigned> &indices) noexcept
{
    if (indices.empty())
    {
        return static_cast<GLuint>(0);
    }

    GLuint ibo = 0;
    GLsizeiptr indices_size = sizeof(indices[0]) * indices.size();
    const void *indices_pointer = reinterpret_cast<const void*>(&indices[0]);

    glGenBuffers(1, &ibo);
    PRINT_GL_ERRORS_IF_ANY();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    PRINT_GL_ERRORS_IF_ANY();

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices_pointer, GL_STATIC_DRAW);
    PRINT_GL_ERRORS_IF_ANY();

    return ibo;
}

static void ResetOpenGLState() noexcept
{
    glEnableVertexAttribArray(0);
    PRINT_GL_ERRORS_IF_ANY();
}

namespace MG3TR
{
    SubMesh::SubMesh(const std::vector<Vector3> &vertices,
                     const std::vector<Vector3> &normals,
                     const std::vector<Vector2> &uvs,
                     const std::vector<std::uint32_t> &indices) try
        : m_vertices(vertices),
          m_normals(normals),
          m_uvs(uvs),
          m_indices(indices)
    {
        if (vertices.empty() || indices.empty())
        {
            throw std::logic_error("Cannot create mesh with no vertices or no triangles!");
        }

        m_vao = GenerateVAO();

        m_vbo_vertices = GenerateVBO(m_vertices, MeshConstants::k_vertices_location);
        m_vbo_normals = GenerateVBO(m_normals, MeshConstants::k_normals_location);
        m_vbo_uvs = GenerateVBO(m_uvs, MeshConstants::k_uvs_location);

        m_ibo = GenerateIBO(m_indices);

        ResetOpenGLState();
    }
    CATCH_RETHROW_EXCEPTIONS
    
    SubMesh::~SubMesh() noexcept
    {
        if (m_vbo_uvs > 0)
        {
            glDeleteBuffers(1, &m_vbo_uvs);
            PRINT_GL_ERRORS_IF_ANY();
        }
        if (m_vbo_normals > 0)
        {
            glDeleteBuffers(1, &m_vbo_normals);
            PRINT_GL_ERRORS_IF_ANY();
        }
        if (m_vbo_vertices > 0)
        {
            glDeleteBuffers(1, &m_vbo_vertices);
            PRINT_GL_ERRORS_IF_ANY();
        }
        if (m_vao > 0)
        {
            glDeleteVertexArrays(1, &m_vao);
            PRINT_GL_ERRORS_IF_ANY();
        }
    }

    SubMesh::SubMesh(const SubMesh &other) try
    {
        CopyFrom(other);
    }
    CATCH_RETHROW_EXCEPTIONS

    SubMesh& SubMesh::operator=(const SubMesh &other) try
    {
        CopyFrom(other);
        return *this;
    }
    CATCH_RETHROW_EXCEPTIONS

    SubMesh::SubMesh(SubMesh &&other) noexcept
    {
        MoveFrom(std::move(other));
    }

    SubMesh& SubMesh::operator=(SubMesh &&other) noexcept
    {
        MoveFrom(std::move(other));
        return *this;
    }

    
    void SubMesh::CopyFrom(const SubMesh &other)
    {
        m_vertices = other.m_vertices;
        m_normals = other.m_normals;
        m_uvs = other.m_uvs;
        m_indices = other.m_indices;
        
        m_vao = GenerateVAO();

        m_vbo_vertices = GenerateVBO(m_vertices, MeshConstants::k_vertices_location);
        m_vbo_normals = GenerateVBO(m_normals, MeshConstants::k_normals_location);
        m_vbo_uvs = GenerateVBO(m_uvs, MeshConstants::k_uvs_location);

        m_ibo = GenerateIBO(m_indices);

        ResetOpenGLState();
    }

    void SubMesh::MoveFrom(SubMesh &&other)
    {
        m_vertices = std::move(other.m_vertices);
        m_normals = std::move(other.m_normals);
        m_uvs = std::move(other.m_uvs);
        m_indices = std::move(other.m_indices);

        m_vao = other.m_vao;
        m_vbo_vertices = other.m_vbo_vertices;
        m_vbo_normals = other.m_vbo_normals;
        m_vbo_uvs = other.m_vbo_uvs;
        m_ibo = other.m_ibo;

        other.m_vao = 0;
        other.m_vbo_vertices = 0;
        other.m_vbo_normals = 0;
        other.m_vbo_uvs = 0;
        other.m_ibo = 0;
    }
}
