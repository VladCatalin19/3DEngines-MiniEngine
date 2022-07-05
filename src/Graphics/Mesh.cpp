#include "Mesh.hpp"

#include <Constants/GraphicsConstants.hpp>
#include <Constants/JSONConstants.hpp>
#include <Graphics/Material.hpp>
#include <Graphics/SubMesh.hpp>
#include <Graphics/Texture.hpp>
#include <Math/Matrix4x4.hpp>
#include <Math/Vector2.hpp>
#include <Math/Vector3.hpp>

#include <Utils/CatchAndRethrowExceptions.hpp>  // CATCH_RETHROW_EXCEPTIONS
#include <Utils/PrintGLErrors.hpp>              // PRINT_GL_ERRORS_IF_ANY

#include <assimp/Importer.hpp>
#include <assimp/material.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/vector3.h>

#include <iostream>             // std::cout, std::endl
#include <stdexcept>            // std::logic_error
#include <memory>               // std::move, std::unique_ptr
#include <vector>               // std::vector

static Assimp::Importer s_importer;

static const aiScene* ReadAssimpSceneFromFile(const std::string &path_to_file) try
{
    unsigned flags = aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_Triangulate;
    const aiScene *scene = s_importer.ReadFile(path_to_file, flags);

    if (scene == nullptr)
    {
        throw std::logic_error("Could not read mesh from \"" + path_to_file + "\": "
                                + s_importer.GetErrorString());
    }
    return scene;
}
CATCH_RETHROW_EXCEPTIONS

static auto ConvertAssimpVerticesToMeshVertices(const aiMesh &mesh) try
{
    std::vector<MG3TR::Vector3> vertices;
    vertices.reserve(mesh.mNumVertices);

    for (unsigned vertex_index = 0; vertex_index < mesh.mNumVertices; ++vertex_index)
    {
        const aiVector3D &vertex_position = mesh.mVertices[vertex_index];
        vertices.push_back( { vertex_position.x, vertex_position.y, vertex_position.z } );
    }
    return vertices;
}
CATCH_RETHROW_EXCEPTIONS

static auto ConvertAssimpNormalsToMeshNormals(const aiMesh &mesh) try
{
    if (!mesh.HasNormals())
    {
        return std::vector<MG3TR::Vector3>();
    }

    std::vector<MG3TR::Vector3> normals;
    normals.reserve(mesh.mNumVertices);

    for (unsigned vertex_index = 0; vertex_index < mesh.mNumVertices; ++vertex_index)
    {
        const aiVector3D &vertex_normal = mesh.mNormals[vertex_index];
        normals.push_back( { vertex_normal.x, vertex_normal.y, vertex_normal.z } );
    }
    return normals;
}
CATCH_RETHROW_EXCEPTIONS

static auto ConvertAssimpUVCoordinatesToMeshUVCoordinates(const aiMesh &mesh) try
{
    if (!mesh.HasTextureCoords(0))
    {
        return std::vector<MG3TR::Vector2>();
    }

    std::vector<MG3TR::Vector2> uvs;
    uvs.reserve(mesh.mNumVertices);

    for (unsigned vertex_index = 0; vertex_index < mesh.mNumVertices; ++vertex_index)
    {
        const aiVector3D &vertex_uv = mesh.mTextureCoords[0][vertex_index];
        uvs.push_back( { vertex_uv.x, vertex_uv.y } );
    }
    return uvs;
}
CATCH_RETHROW_EXCEPTIONS

static auto ConvertAssimpFacesToMeshTriangleIndices(const aiMesh &mesh) try
{
    std::vector<unsigned> indices;
    indices.reserve(mesh.mNumFaces * 3);

    for (unsigned face_index = 0; face_index < mesh.mNumFaces; ++face_index)
    {
        const aiFace &face = mesh.mFaces[face_index];

        switch (face.mNumIndices)
        {
            case 3:
            case 4:
            {
                for (unsigned index = 0; index < face.mNumIndices; ++index)
                {
                    indices.push_back(face.mIndices[index]);
                }
            }
            break;

            default:
            {
                std::cout << "Warning: Will not parse face with " << face.mNumIndices << " indices." << std::endl;
            }
        }
    }

    return indices;
}
CATCH_RETHROW_EXCEPTIONS

static auto ConvertAssimpMaterialsToMeshMaterials(const aiScene &scene) try
{
    if (!scene.HasMaterials())
    {
        return std::vector<MG3TR::Material>();
    }

    std::vector<MG3TR::Material> materials;
    materials.reserve(scene.mNumMaterials);

    for (unsigned material_index = 0; material_index < scene.mNumMaterials; ++material_index)
    {
        const aiMaterial *assimp_material = scene.mMaterials[material_index];
        if (assimp_material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
        {
            MG3TR::Material material;

            aiString path;
            aiReturn return_code = assimp_material->GetTexture(aiTextureType_DIFFUSE, 0, &path);
            if (return_code != AI_SUCCESS)
            {
                throw std::logic_error("Could not get difuse texture.");
            }

            material.m_diffuse_texture = std::make_shared<MG3TR::Texture>(path.C_Str());

            materials.push_back(material);
        }
    }

    return materials;
}
CATCH_RETHROW_EXCEPTIONS

namespace MG3TR
{
    Mesh::Mesh(const std::vector<Vector3> &vertices,
               const std::vector<Vector3> &normals,
               const std::vector<Vector2> &uvs,
               const std::vector<unsigned> &indices) try
    {
        Construct(vertices, normals, uvs, indices);
    }
    CATCH_RETHROW_EXCEPTIONS
    
    Mesh::Mesh(const std::string &path_to_file) try
    {
        Construct(path_to_file);
    }
    CATCH_RETHROW_EXCEPTIONS

    Mesh::Mesh(const Mesh &other) try
        : m_submeshes(other.m_submeshes),
          m_materials(other.m_materials),
          m_path_to_file(other.m_path_to_file)
    {

    }
    CATCH_RETHROW_EXCEPTIONS

    Mesh& Mesh::operator=(const Mesh &other) try
    {
        m_submeshes = other.m_submeshes;
        m_path_to_file = other.m_path_to_file;
        m_materials = other.m_materials;

        return *this;
    }
    CATCH_RETHROW_EXCEPTIONS

    Mesh& Mesh::operator=(Mesh &&other) try
    {
        m_submeshes = std::move(other.m_submeshes);
        m_path_to_file = std::move(other.m_path_to_file);
        m_materials = std::move(other.m_materials);

        return *this;
    }
    CATCH_RETHROW_EXCEPTIONS
    
    nlohmann::json Mesh::Serialize() const try
    {
        namespace Constants = MeshJSONConstants;

        nlohmann::json json;

        if (!m_path_to_file.empty())
        {
            json[Constants::k_parent_node][Constants::k_path_to_file_attribute] = m_path_to_file;
        }
        else
        {
            throw std::logic_error("Cannot serialize mesh not read from file.");
        }

        return json;
    }
    CATCH_RETHROW_EXCEPTIONS
    
    void Mesh::Deserialize(const nlohmann::json &json) try
    {
        namespace Constants = MeshJSONConstants;

        if (json.at(Constants::k_parent_node).contains(Constants::k_path_to_file_attribute))
        {
            std::string path = json[Constants::k_parent_node][Constants::k_path_to_file_attribute];
            Construct(path);
        }
    }
    CATCH_RETHROW_EXCEPTIONS
    
    void Mesh::LateBindAfterDeserialization([[maybe_unused]] Scene &scene) 
    {
        
    }
    
    void Mesh::Construct(const std::vector<Vector3> &vertices,
                           const std::vector<Vector3> &normals,
                           const std::vector<Vector2> &uvs,
                           const std::vector<std::uint32_t> &indices) try
    {
        m_path_to_file = "";
        if (!vertices.empty() && !indices.empty())
        {
            m_submeshes.push_back(SubMesh(vertices, normals, uvs, indices));
        }
    }
    CATCH_RETHROW_EXCEPTIONS
    
    void Mesh::Construct(const std::string &path_to_file) try
    {
        m_path_to_file = path_to_file;

        const aiScene *scene = ReadAssimpSceneFromFile(path_to_file);

        m_submeshes.reserve(scene->mNumMeshes);

        for (unsigned mesh_index = 0; mesh_index < scene->mNumMeshes; ++mesh_index)
        {
            const aiMesh *mesh = scene->mMeshes[mesh_index];

            auto vertices = ConvertAssimpVerticesToMeshVertices(*mesh);
            auto normals = ConvertAssimpNormalsToMeshNormals(*mesh);
            auto uvs = ConvertAssimpUVCoordinatesToMeshUVCoordinates(*mesh);
            auto indices = ConvertAssimpFacesToMeshTriangleIndices(*mesh);

            m_submeshes.push_back(SubMesh(vertices, normals, uvs, indices));
        }

        m_materials = ConvertAssimpMaterialsToMeshMaterials(*scene);
    }
    CATCH_RETHROW_EXCEPTIONS
}
