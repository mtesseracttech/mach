//
// Created by mtesseract on 6/27/19.
//

#ifndef MACH_MODEL_HPP
#define MACH_MODEL_HPP

#include <auxiliary/VectorUtils.hpp>
#include <auxiliary/logging/LogUtils.hpp>
#include <math/linalg/LinAlgTypes.hpp>
#include <map>
#include <iterator>


namespace mach {
	template<typename T>
	class Model {
	public:
		std::vector<uint32_t> m_indices;
		std::vector<Vector<T, 3>> m_vertices;
		std::vector<Vector<T, 3>> m_normals;
		std::vector<Vector<T, 2>> m_texture_coords;

	protected:
		Vector3<T> face_to_normal(const Vector<T, 3> &p_p0, const Vector<T, 3> &p_p1, const Vector<T, 3> &p_p2) {
			Vector3<T> w0 = (p_p1 - p_p0).normalized();
			Vector3<T> w1 = (p_p2 - p_p0).normalized();
			return Vector3<T>::cross(w0, w1).normalized();
		}

	public:

		virtual bool load_from_file(const std::string &p_filename) = 0;

		void generate_normals() {
			std::vector<Vector<T, 3>> normals;
			normals.reserve(m_indices.size());

			for (size_t i = 0; i < m_indices.size(); i += 3) {
				Vector3<T> p0 = m_vertices[m_indices[i + 0]];
				Vector3<T> p1 = m_vertices[m_indices[i + 1]];
				Vector3<T> p2 = m_vertices[m_indices[i + 2]];
				Vector3<T> n = face_to_normal(p0, p1, p2);
				normals.push_back(n);
				normals.push_back(n);
				normals.push_back(n);
			}

			std::map<uint32_t, Vector<T, 3>> aggregate_normals_map;
			for (size_t i = 0; i < normals.size(); ++i) {
				auto it = aggregate_normals_map.find(m_indices[i]);
				if (it == aggregate_normals_map.end()) {
					aggregate_normals_map.insert(std::pair<uint32_t, Vector<T, 3>>(m_indices[i], normals[i]));
				} else {
					it->second += normals[i];
				}
			}

			m_normals.resize(m_vertices.size());
			for (const auto &aggregate_normal_pair : aggregate_normals_map) {
				m_normals[static_cast<size_t>(aggregate_normal_pair.first)] = aggregate_normal_pair.second.normalized();
			}
		}


	};
}


#endif //MACH_MODEL_HPP
