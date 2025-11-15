#include "SubMesh.hpp"

#include <Constants/GraphicsConstants.hpp>
#include <Graphics/API/GraphicsAPISingleton.hpp>
#include <Utils/ExceptionWithStacktrace.hpp>


template <typename TVector>
static MG3TR::TVBOID CreateVBO(const std::vector<TVector> &std_vector, const unsigned location)
{
    const void *const std_vector_pointer = reinterpret_cast<const void*>(&std_vector[0]);
    const std::size_t std_vector_size = sizeof(std_vector[0]) * std_vector.size();
    const std::size_t vector_size = TVector::Size();

    auto& api = MG3TR::GraphicsAPISingleton::GetInstance().GetGraphicsAPI();
    const MG3TR::TVBOID vbo = api.CreateVBO(std_vector_pointer, std_vector_size, vector_size, location);

    return vbo;
}

static MG3TR::TIBOID CreateIBO(const std::vector<unsigned> &indices)
{
    const void *const indices_pointer = reinterpret_cast<const void*>(&indices[0]);
    const std::size_t indices_size = sizeof(indices[0]) * indices.size();

    auto& api = MG3TR::GraphicsAPISingleton::GetInstance().GetGraphicsAPI();
    MG3TR::TIBOID ibo = api.CreateIBO(indices_pointer, indices_size);

    return ibo;
}

namespace MG3TR
{
    SubMesh::SubMesh(const std::vector<Vector3> &vertices,
                     const std::vector<Vector3> &normals,
                     const std::vector<Vector2> &uvs,
                     const std::vector<std::uint32_t> &indices)
        : m_vertices(vertices),
          m_normals(normals),
          m_uvs(uvs),
          m_indices(indices)
    {
        Construct();
    }

    SubMesh::SubMesh(std::vector<Vector3> &&vertices,
                     std::vector<Vector3> &&normals,
                     std::vector<Vector2> &&uvs,
                     std::vector<std::uint32_t> &&indices)
        : m_vertices(vertices),
          m_normals(normals),
          m_uvs(uvs),
          m_indices(indices)
    {
        Construct();
    }
    
    SubMesh::~SubMesh()
    {
        auto& api = GraphicsAPISingleton::GetInstance().GetGraphicsAPI();

        if (m_vbo_uvs > 0)
        {
            api.DeleteVBO(m_vbo_uvs);
        }
        if (m_vbo_normals > 0)
        {
            api.DeleteVBO(m_vbo_normals);
        }
        if (m_vbo_vertices > 0)
        {
            api.DeleteVBO(m_vbo_vertices);
        }
        if (m_vao > 0)
        {
            api.DeleteVAO(m_vao);
        }
    }

    SubMesh::SubMesh(const SubMesh &other)
    {
        CopyFrom(other);
    }

    SubMesh& SubMesh::operator=(const SubMesh &other)
    {
        CopyFrom(other);
        return *this;
    }

    SubMesh::SubMesh(SubMesh &&other)
    {
        MoveFrom(std::move(other));
    }

    SubMesh& SubMesh::operator=(SubMesh &&other)
    {
        MoveFrom(std::move(other));
        return *this;
    }

    std::vector<Vector3>& SubMesh::GetVertices()
    {
        return m_vertices;
    }

    const std::vector<Vector3>& SubMesh::GetVertices() const
    {
        return m_vertices;
    }

    std::vector<Vector3>& SubMesh::GetNormals()
    {
        return m_normals;
    }

    const std::vector<Vector3>& SubMesh::GetNormals() const
    {
        return m_normals;
    }

    std::vector<Vector2>& SubMesh::GetUvs()
    {
        return m_uvs;
    }

    const std::vector<Vector2>& SubMesh::GetUvs() const
    {
        return m_uvs;
    }

    std::vector<unsigned>& SubMesh::GetIndices()
    {
        return m_indices;
    }

    const std::vector<unsigned>& SubMesh::GetIndices() const
    {
        return m_indices;
    }

    TVAOID SubMesh::GetVAO() const
    {
        return m_vao;
    }

    TVBOID SubMesh::GetVBOVertices() const
    {
        return m_vbo_vertices;
    }

    TVBOID SubMesh::GetVBONormals() const
    {
        return m_vbo_normals;
    }

    TVBOID SubMesh::GetVBOUVs() const
    {
        return m_vbo_uvs;
    }

    TIBOID SubMesh::GetIBO() const
    {
        return m_ibo;
    }

    void SubMesh::Construct()
    {
        if (m_vertices.empty() || m_indices.empty())
        {
            throw ExceptionWithStacktrace("Cannot create mesh with no vertices or no triangles!");
        }

        auto& api = GraphicsAPISingleton::GetInstance().GetGraphicsAPI();

        m_vao = api.CreateVAO();

        m_vbo_vertices = CreateVBO(m_vertices, MeshConstants::k_vertices_location);
        m_vbo_normals = CreateVBO(m_normals, MeshConstants::k_normals_location);
        m_vbo_uvs = CreateVBO(m_uvs, MeshConstants::k_uvs_location);

        m_ibo = CreateIBO(m_indices);
    }
    
    void SubMesh::CopyFrom(const SubMesh &other)
    {
        m_vertices = other.m_vertices;
        m_normals = other.m_normals;
        m_uvs = other.m_uvs;
        m_indices = other.m_indices;
        
        Construct();
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
