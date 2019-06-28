//
// Created by mtesseract on 6/26/19.
//

#ifndef MACH_MESH_HPP
#define MACH_MESH_HPP

#include <math/linalg/LinAlgTypes.hpp>
#include <vector>
#include <glad/glad.h>


namespace mach::gfx {
	template<typename T>
	class Mesh {
		std::vector<uint32_t> m_indices;
		std::vector<Vector3 < T>> m_vertices;
		std::vector<Vector3 < T>> m_normals;
		std::vector<Vector2 < T>> m_uvs;

		uint32_t m_vbo_id = 0;
		uint32_t m_vao_id = 0;
		uint32_t m_ebo_id = 0;
	public:

		void generate_buffers() {

		}

		void draw() {
			glBindVertexArray(m_vao_id);
			glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
			glBindVertexArray(0);
		}
	};
}


#endif //MACH_MESH_HPP
