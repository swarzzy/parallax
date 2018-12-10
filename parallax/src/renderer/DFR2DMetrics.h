#pragma once

#include "../Common.h"
#include <future>

namespace prx {
	class DFR2DMetrics final {
		PRX_DISALLOW_COPY_AND_MOVE(DFR2DMetrics)
	public:
		friend class DefferedRenderer2D;
	public:
		enum class Blocks : unsigned int {
			setProjectionMatrix = 0,
			setAmbientLight,
			submitLight,
			begin,
			drawRenderable,
			drawString,
			end,
			flush,
			genLightVolumeCircleInternal,
			fillLightBuffers,
			geometryPass,
			ambientPass,
			lightningPass,
			_SIZE
		};

	private:
		inline static std::string s_MethodsNames[static_cast<unsigned int>(Blocks::_SIZE)] = {
			"setProjectionMatrix",
			"setAmbientLight",
			"submitLight",
			"begin",
			"drawRenderable",
			"drawString",
			"end",
			"flush",
			"genLightVolumeCircleInternal",
			"fillLightBuffers",
			"geometryPass",
			"ambientPass",
			"lightningPass"
		};

		inline static size_t s_CurrentFrameCounters[static_cast<unsigned int>(Blocks::_SIZE)];

	public:

		static void newFrame() {
			memset(s_CurrentFrameCounters, 0, sizeof(size_t) * static_cast<unsigned int>(Blocks::_SIZE));
		}

		static size_t getCyCounter(DFR2DMetrics::Blocks block) {
			return s_CurrentFrameCounters[static_cast<unsigned int>(block)];
		}

		static std::string getMethodName(DFR2DMetrics::Blocks block) {
			return s_MethodsNames[static_cast<unsigned int>(block)];
		}

		static std::string getFormatted(DFR2DMetrics::Blocks block) {
			std::stringstream out;
			out << s_MethodsNames[static_cast<unsigned int>(block)] << " : " << s_CurrentFrameCounters[static_cast<unsigned int>(block)] << " cy";
			return out.str();
		}

		static std::string getFormatted() {
			std::stringstream out;
			for (int i = 0; i < static_cast<unsigned int>(Blocks::_SIZE); i++)
			out << s_MethodsNames[i] << " : " << s_CurrentFrameCounters[i] << " cy\n";
			return out.str();
		}
	};
}
#define DFR2D_BEGIN_TIMED_BLOCK(name)	size_t DFR2D_METRICS_CURRENT_CYCLES_COUNTER_##name = __rdtsc()
#define DFR2D_END_TIMED_BLOCK(name)		prx::DFR2DMetrics::s_CurrentFrameCounters[static_cast<unsigned int>(prx::DFR2DMetrics::Blocks::##name)] \
										+= __rdtsc() - DFR2D_METRICS_CURRENT_CYCLES_COUNTER_##name
