//
// Created by mtesseract on 6/26/19.
//

#ifndef MACH_MESH_HPP
#define MACH_MESH_HPP

#include <math/linalg/LinAlgTypes.hpp>
#include <vector>
#include <glad/glad.h>
#include <graphics/model/Model.hpp>


namespace mach::gfx {
	template<typename T>
	class Mesh {
	public:
		Mesh(const Model<T> &p_model) : m_vertices(p_model.m_vertices),
		                                m_normals(p_model.m_normals),
		                                m_indices(p_model.m_indices),
		                                m_uvs(p_model.m_texture_coords) {}

	protected:
		std::vector<uint32_t> m_indices;
		std::vector<Vector<T, 3>> m_vertices;
		std::vector<Vector<T, 3>> m_normals;
		std::vector<Vector<T, 3>> m_uvs;

		uint32_t m_vbo_id = 0;
		uint32_t m_vao_id = 0;
		uint32_t m_ebo_id = 0;
	public:

		void generate_buffers() {
			glGenVertexArrays(1, &m_vao_id);
			glGenBuffers(1, &m_vbo_id);
			glGenBuffers(1, &m_ebo_id);
			// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
			glBindVertexArray(m_vao_id);

			glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
			glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vector<T, 3>), m_vertices.data(),
			             GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo_id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(uint32_t), m_indices.data(),
			             GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
			glEnableVertexAttribArray(0);

			// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		void draw() {
			glBindVertexArray(m_vao_id);
			glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
			glBindVertexArray(0);
		}
	};
}


#endif //MACH_MESH_HPP
