//
// Created by mtesseract on 6/27/19.
//

#ifndef MACH_WAVEFORMOBJ_HPP
#define MACH_WAVEFORMOBJ_HPP

#include "Model.hpp"

#include <string>
#include <algorithm>

#include <io/files/FileIO.hpp>
#include <auxiliary/parsing/ParserUtils.hpp>


namespace mach {
	template<typename T>
	class WaveformObj : public Model<T> {
	public:
		bool load_from_file(const std::string &p_filename) override {
			if (!io::FileIO::file_exists(p_filename)) {
				std::stringstream ss;
				ss << "File '" << p_filename << "' does not exist, cannot create a valid object";
				Logger::log(ss.str(), Error);
				return false;
			}
			std::ifstream file_stream(p_filename);
			if (!file_stream) {
				std::stringstream ss;
				ss << "Failed to read the OBJ file '" << p_filename << "': " << std::strerror(errno);
				Logger::log(ss.str(), Error);
				return false;
			}

			std::vector<Vector3<T>> vertices;
			std::vector<Vector3<T>> normals;
			std::vector<Vector2<T>> uvs;
			std::vector<FaceIndexTriplet> faces;

			size_t line_num = 1;
			std::string line;
			while (std::getline(file_stream, line)) {
				if (!line.empty()) {
					auto tokens = ParserUtils::tokenize(line, ' ');
					if (!tokens.empty()) {
						const std::string cmd = tokens[0];
						if (cmd == "v") {
							auto parsed = parse_coords_line<T>(tokens);
							if (parsed.size() >= 3) {
								vertices.emplace_back(Vector3<T>(parsed[0], parsed[1], parsed[2]));
							}
						} else if (cmd == "vn") {
							auto parsed = parse_coords_line<T>(tokens);
							if (parsed.size() >= 3) {
								normals.emplace_back(Vector3<T>(parsed[0], parsed[1], parsed[2]));
							}
						} else if (cmd == "vt") {
							auto parsed = parse_coords_line<T>(tokens);
							if (parsed.size() >= 2) {
								uvs.emplace_back(Vector2<T>(parsed[0], parsed[1]));
							}
						} else if (cmd == "f") {
							auto parsed = parse_face_line(tokens);
							faces.insert(faces.end(), parsed.begin(), parsed.end());
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
							std::stringstream ss;
							ss << "Unknown token on line " << line_num << ": " << cmd;
							Logger::log(ss.str(), Error);
						}
					}
				}
				++line_num;
			}

			std::vector<uint32_t> indices;

			std::map<FaceIndexTriplet, uint32_t> mapped_triplets;
			for (const auto &face : faces) {
				auto it = mapped_triplets.find(face);
				if (it == mapped_triplets.end()) {
					auto index = static_cast<uint32_t>(mapped_triplets.size());
					this->m_indices.push_back(index);
					this->m_vertices.push_back(vertices[face.m_v - 1]);
					if (face.has_tex_coords()) {
						this->m_texture_coords.push_back(uvs[face.m_uv - 1]);
					}
					if (face.has_normals()) {
						this->m_normals.push_back(normals[face.m_n - 1]);
					}
					mapped_triplets.insert(std::make_pair(face, index));
				} else {
					this->m_indices.push_back(it->second);
				}
			}
			return true;
		}

	private:
		enum TripletType {
			V,
			VT,
			VN,
			VTN,
		};

		struct FaceIndexTriplet {
			TripletType m_type;

			uint32_t m_v;
			uint32_t m_n;
			uint32_t m_uv;

			FaceIndexTriplet(TripletType p_type, uint32_t p_v, uint32_t p_n, uint32_t p_uv) : m_type(p_type), m_v(p_v),
			                                                                                  m_n(p_n), m_uv(p_uv) {}

			bool has_normals() const {
				return m_type == VN || m_type == VTN;
			}

			bool has_tex_coords() const {
				return m_type == VT || m_type == VTN;
			}

			friend std::ostream &operator<<(std::ostream &p_os, const FaceIndexTriplet &p_triplet) {
				switch (p_triplet.m_type) {
					case V:
						p_os << "v";
						break;
					case VN:
						p_os << "vn";
						break;
					case VT:
						p_os << "vt";
						break;
					case VTN:
						p_os << "vtn";
						break;
				}
				p_os << " triplet: " << p_triplet.m_v << "," << p_triplet.m_n << "," << p_triplet.m_uv;
				return p_os;
			}

			friend bool operator<(const FaceIndexTriplet &p_l, const FaceIndexTriplet &p_r) {
				return std::tie(p_l.m_type, p_l.m_v, p_l.m_n, p_l.m_uv)
				       < std::tie(p_r.m_type, p_r.m_v, p_r.m_n, p_r.m_uv);
			}
		};

	public:
		static TripletType get_face_triplet_type(std::vector<std::string> p_triplets) {
			switch (p_triplets.size()) {
				case 3:
					return V;
				case 6:
					return VT;
				case 9: {
					switch (p_triplets[1].size()) {
						case 0:
							return VN;
						default:
							return VTN;
					}
				}
				default:
					throw std::logic_error("Unknown face triplet type encountered");
			}
		}

		static std::vector<FaceIndexTriplet> parse_face_line(const std::vector<std::string> &p_tokens) {
			std::vector<std::string> tokens = VectorUtils::slice(p_tokens, 1, p_tokens.size() - 1);
			std::vector<std::string> triplets;
			for (const auto &token : tokens) {
				auto triplet = ParserUtils::tokenize(token, '/');
				triplets.insert(triplets.end(), triplet.begin(), triplet.end());
			}
			std::vector<uint32_t> triplets_parsed = ParserUtils::numbers_from_strings<uint32_t>(triplets);
			std::vector<FaceIndexTriplet> triangle;

			auto triplet_type = get_face_triplet_type(triplets);
			switch (triplet_type) {
				case V:
					for (int i = 0; i < 3; ++i) {
						triangle.push_back(FaceIndexTriplet(
								triplet_type,
								triplets_parsed[i * 1 + 0],
								0,
								0)
						);
					}
					break;
				case VT:
					for (int i = 0; i < 3; ++i) {
						triangle.push_back(FaceIndexTriplet(
								triplet_type,
								triplets_parsed[i * 2 + 0],
								0,
								triplets_parsed[i * 2 + 1])
						);
					}
					break;
				case VN:
					for (int i = 0; i < 3; ++i) {
						triangle.push_back(FaceIndexTriplet(
								triplet_type,
								triplets_parsed[i * 2 + 0],
								triplets_parsed[i * 2 + 1],
								0)
						);
					}
					break;
				case VTN:
					for (int i = 0; i < 3; ++i) {
						triangle.push_back(FaceIndexTriplet(
								triplet_type,
								triplets_parsed[i * 3 + 0],
								triplets_parsed[i * 3 + 1],
								triplets_parsed[i * 3 + 2])
						);
					}
			}
			return triangle;
		}

		template<typename V>
		static std::vector<V> parse_coords_line(const std::vector<std::string> &p_tokens) {
			return ParserUtils::numbers_from_strings<V>(VectorUtils::slice(p_tokens, 1, p_tokens.size() - 1));
		}
	};
}

#endif //MACH_WAVEFORMOBJ_HPP
