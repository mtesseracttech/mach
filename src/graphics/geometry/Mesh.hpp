//
// Created by mtesseract on 6/26/19.
//

#ifndef MACH_MESH_HPP
#define MACH_MESH_HPP

#include <math/linalg/LinAlgTypes.hpp>
#include <vector>
#include <glad/glad.h>
#include <io/FileIO.hpp>
#include <auxiliary/parsing/ParserUtils.hpp>
#include <algorithm>
#include <auxiliary/VectorUtils.hpp>
#include <auxiliary/logging/LogUtils.hpp>

namespace mach::gfx {
	struct FaceIndexTriplet {
		FaceIndexTriplet(uint32_t i0, uint32_t i1, uint32_t i2) : m_faces{i0, i1, i2} {}

		std::array<uint32_t, 3> m_faces;
	};

	template<typename T>
	class Mesh {
		std::vector<uint32_t> m_indices;
		std::vector<Vector3<T>> m_vertices;
		std::vector<Vector3<T>> m_normals;
		std::vector<Vector2<T>> m_uvs;

		uint32_t m_vbo_id = 0;
		uint32_t m_vao_id = 0;
		uint32_t m_ebo_id = 0;
	public:
		void load_from_obj_file(const std::string &p_filename) {
			if (!io::FileIO::file_exists(p_filename)) return;
			std::ifstream file_stream(p_filename);
			if (!file_stream) {
				std::stringstream ss;
				ss << "Failed to read the OBJ file '" << p_filename << "': " << std::strerror(errno);
				Logger::log(ss.str(), Error);
				return;
			}

			std::vector<Vector3<T>> vertices;
			std::vector<Vector3<T>> normals;
			std::vector<Vector2<T>> uvs;
			std::vector<FaceIndexTriplet> faces;

			std::string line;
			while (std::getline(file_stream, line)) {
				if (!line.empty()) {
					auto tokens = ParserUtils::tokenize(line, ' ');
					if (!tokens.empty()) {
						const std::string cmd = tokens[0];
						if (cmd == "v") {
							auto parsed = parse_coords_line<T>(tokens);
							if (parsed.size() >= 3) {
								vertices.emplace_back(Vector3<T>(parsed[0], parsed[1], parsed[3]));
							}
						} else if (cmd == "vn") {
							auto parsed = parse_coords_line<T>(tokens);
							if (parsed.size() >= 3) {
								normals.emplace_back(Vector3<T>(parsed[0], parsed[1], parsed[3]));
							}
						} else if (cmd == "vt") {
							auto parsed = parse_coords_line<T>(tokens);
							if (parsed.size() >= 2) {
								uvs.emplace_back(Vector2<T>(parsed[0], parsed[1]));
							}
						} else if (cmd == "f") {

						} else if (cmd == "#") {
							/*Comment, not much to do here*/
						} else if (cmd == "mtllib") {
							/*Material file location*/
						} else if (cmd == "usemtl") {
							/*Use material for the element following this statement*/
						} else if (cmd == "o") {
							/*Object name*/
						} else if (cmd == "g") {
							/*Group name*/
						} else if (cmd == "s") {
							/*Smoothing enable/disable for smoothing group*/
						} else {

						}
					}
				}
			}

			Logger::log(to_str(vertices.size()), Info);
			Logger::log(to_str(normals.size()), Info);
			Logger::log(to_str(uvs.size()), Info);
			Logger::log(to_str(faces.size()), Info);
		}


		template<typename V>
		static std::vector<V> parse_coords_line(const std::vector<std::string> &p_tokens) {
			return ParserUtils::numbers_from_strings<V>(VectorUtils::slice(p_tokens, 1, p_tokens.size() - 1));
		}


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
