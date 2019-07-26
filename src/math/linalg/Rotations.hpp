//
// Created by mtesseract on 6/11/19.
//

#ifndef MACH_ROTATIONS_HPP
#define MACH_ROTATIONS_HPP

#include <math/util/MathUtils.hpp>

namespace mach {
	enum RotationOrder {
		PHB,
		PBH,
		HPB,
		HBP,
		BPH,
		BHP
	};

	template<typename T, RotationOrder O = PHB>
	static T combine_rotations(const T &p_pitch, const T &p_heading, const T &p_bank) {
		switch (O) {
			case PHB:
				return p_pitch * p_heading * p_bank;
			case PBH:
				return p_pitch * p_bank * p_heading;
			case HPB:
				return p_heading * p_pitch * p_bank;
			case HBP:
				return p_heading * p_bank * p_pitch;
			case BPH:
				return p_bank * p_pitch * p_heading;
			case BHP:
				return p_bank * p_heading * p_pitch;
		}
	}

	template<typename T>
	static T clamp_angle(const T &p_angle, const T &p_min, const T &p_max) {
		const T full_rotation = math::pi * 2.0;

		T angle = std::fmod(p_angle, full_rotation);
		if ((angle >= -full_rotation) && (angle <= full_rotation)) {
			if (angle < -full_rotation) {
				angle += full_rotation;
			}
			if (angle > full_rotation) {
				angle -= full_rotation;
			}
		}
		return std::clamp(angle, p_min, p_max);
	}

	template<typename T>
	struct AngleAxis {
		T theta;
		Vector<T, 3> n;
	};

	template<typename T, RotationOrder O = PHB>
	struct EulerAngles {
		union {
			struct {
				T pitch, heading, bank;
			};
			Vector<T, 3> m_angles;
		};

		static constexpr RotationOrder order() {
			return O;
		};

		static constexpr std::array<size_t, 3> index_oder() {
			switch (O) {
				case PHB:
					return {0, 1, 2};
				case PBH:
					return {0, 2, 1};
				case HPB:
					return {1, 0, 2};
				case HBP:
					return {1, 2, 0};
				case BPH:
					return {2, 0, 1};
				case BHP:
					return {2, 1, 0};
			}
		}
	};


}

#endif //MACH_ROTATIONS_HPP
