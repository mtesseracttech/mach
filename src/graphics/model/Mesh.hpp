//
// Created by mtesseract on 6/27/19.
//

#ifndef MACH_MESH_HPP
#define MACH_MESH_HPP

#include <auxiliary/VectorUtils.hpp>
#include <auxiliary/logging/LogUtils.hpp>
#include <math/linalg/LinAlgTypes.hpp>
#include <map>
#include <iterator>
#include <vector>
#include "Vertex.hpp"
#include "graphics/material/Texture.hpp"


namespace mach::gfx {

	template<typename AttribType, typename = std::enable_if_t<std::is_floating_point<AttribType>::value>>
	class Mesh {
	public:
		std::vector<Vertex<AttribType>> m_vertices;
		std::vector<unsigned int> m_indices;
		std::vector<Texture> m_textures;

		Mesh(std::vector<Vertex<AttribType>> p_vertices,
		     std::vector<uint32_t> p_indices,
		     std::vector<Texture> p_textures) {
			m_vertices = p_vertices;
			m_indices = p_indices;
			m_textures = p_textures;
			generate_buffers();
		}

		void draw(const OpenGLShader &p_shader) {
			uint32_t diffuse_idx = 1, specular_idx = 1;
			for (uint32_t i = 0; i < m_textures.size(); i++) {
				glActiveTexture(GL_TEXTURE0 + i);
				std::string number;
				std::string name = m_textures[i].m_type;
				if (name == "texture_diffuse")
					number = std::to_string(diffuse_idx++);
				else if (name == "texture_specular")
					number = std::to_string(specular_idx++);

				p_shader.set_val<int>(std::string("material.").append(name).append(number), i);
				glBindTexture(GL_TEXTURE_2D, m_textures[i].m_id);
			}
			glActiveTexture(GL_TEXTURE0);
			glBindVertexArray(m_vao_id);
			glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}

	private:
		uint32_t m_vao_id;
		uint32_t m_vbo_id;
		uint32_t m_ebo_id;

		void generate_buffers() {
			glGenVertexArrays(1, &m_vao_id);
			glGenBuffers(1, &m_vbo_id);
			glGenBuffers(1, &m_ebo_id);

			glBindVertexArray(m_vao_id);
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
			glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex<AttribType>), m_vertices.data(),
			             GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo_id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(uint32_t), m_indices.data(),
			             GL_STATIC_DRAW);

			if constexpr (std::is_same<AttribType, float>::value) {
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex<AttribType>),
				                      (void *) offsetof(Vertex<AttribType>, m_position));
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex<AttribType>),
				                      (void *) offsetof(Vertex<AttribType>, m_normal));
				glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex<AttribType>),
				                      (void *) offsetof(Vertex<AttribType>, m_tex_coords));

			} else if constexpr (std::is_same<AttribType, double>::value) {
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, sizeof(Vertex<AttribType>),
				                      (void *) offsetof(Vertex<AttribType>, m_position));
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, sizeof(Vertex<AttribType>),
				                      (void *) offsetof(Vertex<AttribType>, m_normal));
				glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, 2, GL_DOUBLE, GL_FALSE, sizeof(Vertex<AttribType>),
				                      (void *) offsetof(Vertex<AttribType>, m_tex_coords));
			} else {
				throw NotImplemented("No other attribute types except for float and double are implemented");
			}

//			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}


//	public:
//		std::vector<uint32_t> m_indices;
//		std::vector<Vector<T, 3>> m_vertices;
//		std::vector<Vector<T, 3>> m_normals;
//		std::vector<Vector<T, 2>> m_texture_coords;
//
//	protected:
//		Vector3<T> face_to_normal(const Vector<T, 3> &p_p0, const Vector<T, 3> &p_p1, const Vector<T, 3> &p_p2) {
//			Vector3<T> w0 = (p_p1 - p_p0).normalized();
//			Vector3<T> w1 = (p_p2 - p_p0).normalized();
//			return Vector3<T>::cross(w0, w1).normalized();
//		}
//
//	public:
//
//
//		void generate_normals() {
//			std::vector<Vector<T, 3>> normals;
//			normals.reserve(m_indices.size());
//
//			for (size_t i = 0; i < m_indices.size(); i += 3) {
//				Vector3<T> p0 = m_vertices[m_indices[i + 0]];
//				Vector3<T> p1 = m_vertices[m_indices[i + 1]];
//				Vector3<T> p2 = m_vertices[m_indices[i + 2]];
//				Vector3<T> n = face_to_normal(p0, p1, p2);
//				normals.push_back(n);
//				normals.push_back(n);
//				normals.push_back(n);
//			}
//
//			std::map<uint32_t, Vector<T, 3>> aggregate_normals_map;
//			for (size_t i = 0; i < normals.size(); ++i) {
//				auto it = aggregate_normals_map.find(m_indices[i]);
//				if (it == aggregate_normals_map.end()) {
//					aggregate_normals_map.insert(std::pair<uint32_t, Vector<T, 3>>(m_indices[i], normals[i]));
//				} else {
//					it->second += normals[i];
//				}
//			}
//
//			m_normals.resize(m_vertices.size());
//			for (const auto &aggregate_normal_pair : aggregate_normals_map) {
//				m_normals[static_cast<size_t>(aggregate_normal_pair.first)] = aggregate_normal_pair.second.normalized();
//			}
//		}


	};
}


#endif //MACH_MESH_HPP
