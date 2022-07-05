#ifndef MG3TR_SRC_GRAPHICS_SUBMESH_HPP_INCLUDED
#define MG3TR_SRC_GRAPHICS_SUBMESH_HPP_INCLUDED

#include <Math/Vector2.hpp>
#include <Math/Vector3.hpp>

#include <glad/glad.h>          // GLuint

#include <vector>               // std::vector

namespace MG3TR
{
    class SubMesh
    {
    private:
        std::vector<Vector3> m_vertices;
        std::vector<Vector3> m_normals;
        std::vector<Vector2> m_uvs;
        std::vector<unsigned> m_indices;

        GLuint m_vao;
        GLuint m_vbo_vertices;
        GLuint m_vbo_normals;
        GLuint m_vbo_uvs;
        GLuint m_ibo;

    public:
        SubMesh(const std::vector<Vector3> &vertices = {},
                const std::vector<Vector3> &normals = {},
                const std::vector<Vector2> &uvs = {},
                const std::vector<std::uint32_t> &indices = {});

        virtual ~SubMesh() noexcept;

        SubMesh(const SubMesh &);
        SubMesh& operator=(const SubMesh &);

        SubMesh(SubMesh &&) noexcept;
        SubMesh& operator=(SubMesh &&) noexcept;

        std::vector<Vector3>& GetVertices() noexcept { return m_vertices; }
        const std::vector<Vector3>& GetVertices() const noexcept { return m_vertices; }

        std::vector<Vector3>& GetNormals() noexcept { return m_normals; }
        const std::vector<Vector3>& GetNormals() const noexcept { return m_normals; }

        std::vector<Vector2>& GetUvs() noexcept { return m_uvs; }
        const std::vector<Vector2>& GetUvs() const noexcept { return m_uvs; }

        std::vector<unsigned>& GetIndices() noexcept { return m_indices; }
        const std::vector<unsigned>& GetIndices() const noexcept { return m_indices; }

        GLuint GetVAO() const noexcept { return m_vao; }
        GLuint GetVBOVertices() const noexcept { return m_vbo_vertices; }
        GLuint GetVBONormals() const noexcept { return m_vbo_normals; }
        GLuint GetVBOUVs() const noexcept { return m_vbo_uvs; }
        GLuint GetIBO() const noexcept { return m_ibo; }

    private:
        void CopyFrom(const SubMesh &other);
        void MoveFrom(SubMesh &&other);
    };
}

#endif // MG3TR_SRC_GRAPHICS_SUBMESH_HPP_INCLUDED
