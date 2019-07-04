//
// Created by mtesseract on 7/4/19.
//

#ifndef MACH_ASSETCACHE_HPP
#define MACH_ASSETCACHE_HPP

#include <map>
#include <memory>
#include <auxiliary/logging/Logger.hpp>

namespace mach::cache {
	template<typename T>
	class AssetCache {
		std::map<std::string, std::shared_ptr<T>> m_lookup_map;

		AssetCache() = default;

	public:
		static auto &get() {
			static AssetCache cache;
			return cache;
		}

		AssetCache(const AssetCache &) = delete;

		AssetCache(AssetCache &&) = delete;

		AssetCache &operator=(const AssetCache &) = delete;

		AssetCache &operator=(AssetCache &&) = delete;

		std::shared_ptr<T> load_asset(const std::string &p_name) {
			auto it = m_lookup_map.find(p_name);
			if (it != m_lookup_map.end()) {
				return it->second;
			} else {
				try {
					std::shared_ptr<T> asset = std::make_shared<T>(T(p_name));
					m_lookup_map.insert(std::make_pair(p_name, asset));
					return asset;
				} catch (std::exception &ex) {
					Logger::log("Asset Loader: " + std::string(ex.what()));
					return nullptr;
				}
			}
		}

		void clear() {
			std::stringstream ss;
			ss << "Clearing out" << m_lookup_map.size() << " entries from the " << typeid(T).name() << "cache";
			Logger::log(ss.str(), Info);
			m_lookup_map.clear();
		}
	};
}

#endif //MACH_ASSETCACHE_HPP
