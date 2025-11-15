#ifndef MG3TR_SRC_GRAPHICS_SUBMESH_HPP_INCLUDED
#define MG3TR_SRC_GRAPHICS_SUBMESH_HPP_INCLUDED

#include <Graphics/API/GraphicsTypes.hpp>
#include <Math/Vector2.hpp>
#include <Math/Vector3.hpp>

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

        TVAOID m_vao;
        TVBOID m_vbo_vertices;
        TVBOID m_vbo_normals;
        TVBOID m_vbo_uvs;
        TIBOID m_ibo;

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

        TVAOID GetVAO() const;
        TVBOID GetVBOVertices() const;
        TVBOID GetVBONormals() const;
        TVBOID GetVBOUVs() const;
        TIBOID GetIBO() const;

    private:
        void Construct();
        void CopyFrom(const SubMesh &other);
        void MoveFrom(SubMesh &&other);
    };
}

#endif // MG3TR_SRC_GRAPHICS_SUBMESH_HPP_INCLUDED
