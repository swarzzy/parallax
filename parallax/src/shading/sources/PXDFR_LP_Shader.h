#pragma once
#include "../../Common.h"
#include <string>

namespace prx::API {

	class PXDFR_LP_Shader {
		PRX_DISALLOW_COPY_AND_MOVE(PXDFR_LP_Shader)
	private:
		static const unsigned int	ATTRIB_COORDS_INDEX = 0;
		static const unsigned int	ATTRIB_UV_INDEX = 1;

		static const unsigned int	OUPUT_LOCATION_COLOR = 0;

		static const unsigned int	LIGHTS_BLOCK_BINDING_POINT = 0;

		inline static const std::string UNIFORM_SYS_PROJ_MAT = "sys_ProjectionMatrix";
		inline static const std::string UNIFORM_SYS_TEXTURE = "sys_Texture";

		inline static const std::string LIGHTS_UNIFORM_BLOCK_NAME = "ub_Lights";

		PXDFR_LP_Shader() = delete;

	public:
		static constexpr unsigned int attribCoordsIndex() {
			return ATTRIB_COORDS_INDEX;
		}


		static constexpr unsigned int attribUVIndex() {
			return ATTRIB_UV_INDEX;
		}

		static constexpr unsigned int colorTargetLocation() {
			return OUPUT_LOCATION_COLOR;
		}

		static constexpr unsigned int lightsUBBindingPoint() {
			return LIGHTS_BLOCK_BINDING_POINT;
		}

		static constexpr const std::string& uniformSysTexture() {
			return UNIFORM_SYS_TEXTURE;
		}

		static constexpr const std::string& uniformSysProjMat() {
			return UNIFORM_SYS_PROJ_MAT;
		}

		static constexpr const std::string& uniformBlockLights() {
			return LIGHTS_UNIFORM_BLOCK_NAME;
		}
	};
}