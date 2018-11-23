#pragma once
#include "../../Common.h"
#include <string>

namespace prx::API {

	class PXDFR_GP_Shader {
		PRX_DISALLOW_COPY_AND_MOVE(PXDFR_GP_Shader)
	private:
		static const unsigned int	ATTRIB_COORDS_INDEX = 0;
		static const unsigned int	ATTRIB_DEPTH_INDEX = 1;
		static const unsigned int	ATTRIB_UV_INDEX = 2;
		static const unsigned int	ATTRIB_TEXID_INDEX = 3;
		static const unsigned int	ATTRIB_COLOR_INDEX = 4;

		static const unsigned int	OUPUT_LOCATION_COLOR = 0;
		static const unsigned int	OUPUT_LOCATION_POSITION = 0;

		inline static const std::string UNIFORM_SYS_PROJ_MAT = "sys_ProjectionMatrix";

		static const unsigned int TEXTURE_SLOTS_AVAILABLE = 32;
		inline static const std::string UNIFORM_SYS_TEXTURES= "sys_Textures";
		inline static const std::string UNIFORM_SYS_TEXTURES_BEGIN = "sys_Textures[0]";

		PXDFR_GP_Shader() = delete;

	public:
		static constexpr unsigned int attribCoordsIndex() {
			return ATTRIB_COORDS_INDEX;
		}

		static constexpr unsigned int attribDepthIndex() {
			return ATTRIB_DEPTH_INDEX;
		}

		static constexpr unsigned int attribUVIndex() {
			return ATTRIB_UV_INDEX;
		}

		static constexpr unsigned int attribTexIDIndex() {
			return ATTRIB_TEXID_INDEX;
		}

		static constexpr unsigned int attribColorIndex() {
			return ATTRIB_COLOR_INDEX;
		}

		static constexpr unsigned int colorTargetLocation() {
			return OUPUT_LOCATION_COLOR;
		}

		static constexpr unsigned int positionTargetLocation() {
			return OUPUT_LOCATION_POSITION;
		}

		static constexpr const std::string& uniformSysProjMat() {
			return UNIFORM_SYS_PROJ_MAT;
		}

		static constexpr unsigned int textureSlotsAvailable() {
			return TEXTURE_SLOTS_AVAILABLE;
		}

		static constexpr const std::string& uniformSysTexturesBegin() {
			return UNIFORM_SYS_TEXTURES_BEGIN;
		}

		static constexpr const std::string& uniformSysTextures() {
			return UNIFORM_SYS_TEXTURES;
		}
	};
}