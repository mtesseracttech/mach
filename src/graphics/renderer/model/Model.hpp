//
// Created by mtesseract on 7/3/19.
//

#ifndef MACH_MODEL_HPP
#define MACH_MODEL_HPP

#include <string>
#include <graphics/renderer/shaders/OpenGLShader.hpp>
#include "Mesh.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Vertex.hpp"

namespace mach::gfx {
	template<typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
	class Model {
		std::vector<Texture> m_textures_loaded;
		std::vector<Mesh<T>> m_meshes;
		std::string m_texture_directory;
		std::string m_model_directory;

	public:
		explicit Model(const std::string &p_model_name) {
			std::string model_file_path = "../res/models/" + p_model_name;
			std::string textures_file_path = "../res/textures/" + p_model_name;

			Assimp::Importer import;
			const aiScene *scene = import.ReadFile(model_file_path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
				std::stringstream ss;
				ss << "Assimp: " << import.GetErrorString();
				throw std::runtime_error(ss.str());
			}
			m_model_directory = model_file_path.substr(0, model_file_path.find_last_of('/'));
			m_texture_directory = textures_file_path.substr(0, textures_file_path.find_last_of('/'));
			process_node(scene->mRootNode, scene);
		}

		void process_node(aiNode *p_node, const aiScene *p_scene) {
			for (unsigned int i = 0; i < p_node->mNumMeshes; i++) {
				aiMesh *mesh = p_scene->mMeshes[p_node->mMeshes[i]];
				m_meshes.push_back(process_mesh(mesh, p_scene));
			}

			for (unsigned int i = 0; i < p_node->mNumChildren; i++) {
				process_node(p_node->mChildren[i], p_scene);
			}
		}

		void draw(const OpenGLShader &p_shader) {
			for (auto &mesh : m_meshes) {
				mesh.draw(p_shader);
			}
		}

	private:

		unsigned int texture_from_file(const char *p_path, const std::string &p_directory, bool p_gamma) {
			std::string filename = std::string(p_path);
			filename = p_directory + '/' + filename;

			unsigned int texture_id;
			glGenTextures(1, &texture_id);

			int width, height, nr_components;
			unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nr_components, 0);
			if (data) {
				GLenum format = 0;
				if (nr_components == 1) {
					format = GL_RED;
				} else if (nr_components == 3) {
					format = GL_RGB;
				} else if (nr_components == 4) {
					format = GL_RGBA;
				}

				glBindTexture(GL_TEXTURE_2D, texture_id);
				glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				stbi_image_free(data);
			} else {
				stbi_image_free(data);
				throw std::runtime_error("Texture failed to load at path: " + std::string(p_path));
			}

			return texture_id;
		}

		Mesh<T> process_mesh(aiMesh *p_mesh, const aiScene *p_scene) {
			std::vector<Vertex<T>> vertices;
			std::vector<uint32_t> indices;
			std::vector<Texture> textures;

			for (uint32_t i = 0; i < p_mesh->mNumVertices; i++) {
				Vertex<T> vertex;
				Vector3<T> vector;
				vector.x = p_mesh->mVertices[i].x;
				vector.y = p_mesh->mVertices[i].y;
				vector.z = p_mesh->mVertices[i].z;
				vertex.m_position = vector;
				vector.x = p_mesh->mNormals[i].x;
				vector.y = p_mesh->mNormals[i].y;
				vector.z = p_mesh->mNormals[i].z;
				vertex.m_normal = vector;
				if (p_mesh->mTextureCoords[0]) {
					Vector2<T> uv;
					uv.x = p_mesh->mTextureCoords[0][i].x;
					uv.y = p_mesh->mTextureCoords[0][i].y;
					vertex.m_tex_coords = uv;
				} else {
					vertex.m_tex_coords = Vector2<T>(0.0, 0.0);
				}
				vertices.push_back(vertex);
			}
			// process indices
			for (uint32_t i = 0; i < p_mesh->mNumFaces; i++) {
				aiFace face = p_mesh->mFaces[i];
				for (uint32_t j = 0; j < face.mNumIndices; j++) {
					indices.push_back(face.mIndices[j]);
				}
			}

			if (p_mesh->mMaterialIndex >= 0) {
				aiMaterial *material = p_scene->mMaterials[p_mesh->mMaterialIndex];
				std::vector<Texture> diffuse_maps = load_material_textures(material, aiTextureType_DIFFUSE, "texture_diffuse");
				textures.insert(textures.end(), diffuse_maps.begin(), diffuse_maps.end());
				std::vector<Texture> specular_maps = load_material_textures(material, aiTextureType_SPECULAR, "texture_specular");
				textures.insert(textures.end(), specular_maps.begin(), specular_maps.end());
				std::vector<Texture> normal_maps = load_material_textures(material, aiTextureType_HEIGHT, "texture_normal");
				textures.insert(textures.end(), normal_maps.begin(), normal_maps.end());
				std::vector<Texture> height_maps = load_material_textures(material, aiTextureType_AMBIENT, "texture_height");
				textures.insert(textures.end(), height_maps.begin(), height_maps.end());
			}
			return Mesh(vertices, indices, textures);
		}

		std::vector<Texture>
		load_material_textures(aiMaterial *p_material, aiTextureType p_type, const std::string &p_type_name) {
			std::vector<Texture> textures;
			for (unsigned int i = 0; i < p_material->GetTextureCount(p_type); i++) {
				aiString str;
				p_material->GetTexture(p_type, i, &str);
				bool skip = false;
				for (unsigned int j = 0; j < m_textures_loaded.size(); j++) {
					if (std::strcmp(m_textures_loaded[j].m_path.data(), str.C_Str()) == 0) {
						textures.push_back(m_textures_loaded[j]);
						skip = true;
						break;
					}
				}
				if (!skip) {   // if texture hasn't been loaded already, load it
					Texture texture;
					texture.m_id = texture_from_file(str.C_Str(), m_texture_directory, false);
					texture.m_type = p_type_name;
					texture.m_path = str.C_Str();
					textures.push_back(texture);
					m_textures_loaded.push_back(texture); // add to loaded textures
				}
			}
			return textures;
		}


	};
}

#endif //MACH_MODEL_HPP
