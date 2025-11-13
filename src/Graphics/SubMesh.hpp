#ifndef MG3TR_SRC_GRAPHICS_SUBMESH_HPP_INCLUDED
#define MG3TR_SRC_GRAPHICS_SUBMESH_HPP_INCLUDED

#include <Math/Vector2.hpp>
#include <Math/Vector3.hpp>

#include <glad/glad.h>

#include <vector>

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
        SubMesh(const std::vector<Vector3> &vertices,
                const std::vector<Vector3> &normals,
                const std::vector<Vector2> &uvs,
                const std::vector<std::uint32_t> &indices);
        
        SubMesh(std::vector<Vector3> &&vertices,
                std::vector<Vector3> &&normals,
                std::vector<Vector2> &&uvs,
                std::vector<std::uint32_t> &&indices);

        virtual ~SubMesh();

        SubMesh(const SubMesh &);
        SubMesh(SubMesh &&);
        
        SubMesh& operator=(const SubMesh &);
        SubMesh& operator=(SubMesh &&);

        std::vector<Vector3>& GetVertices();
        const std::vector<Vector3>& GetVertices() const;

        std::vector<Vector3>& GetNormals();
        const std::vector<Vector3>& GetNormals() const;

        std::vector<Vector2>& GetUvs();
        const std::vector<Vector2>& GetUvs() const;

        std::vector<unsigned>& GetIndices();
        const std::vector<unsigned>& GetIndices() const;

        GLuint GetVAO() const;
        GLuint GetVBOVertices() const;
        GLuint GetVBONormals() const;
        GLuint GetVBOUVs() const;
        GLuint GetIBO() const;

    private:
        void CopyFrom(const SubMesh &other);
        void MoveFrom(SubMesh &&other);
    };
}

#endif // MG3TR_SRC_GRAPHICS_SUBMESH_HPP_INCLUDED
