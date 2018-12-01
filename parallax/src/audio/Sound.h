#pragma once
#ifndef _PARALLAX_AUDIO_SOUND_H_
#define _PARALLAX_AUDIO_SOUND_H_

#include <string>

#include "../resources/Resource.h"
#include "../Common.h"

#ifdef PARALLAX_ENABLE_AUDIO
#include "../ext/gorilla/ga.h"
#include "../ext/gorilla/gau.h"


namespace prx {
	class Window;

	class Sound final : public Resource {
		PRX_DISALLOW_COPY_AND_MOVE(Sound)
	private:
		ga_Mixer*			m_gaMixer;
		ga_Sound*			m_Sound;
		mutable ga_Handle*	m_Handle;

		float				m_Gain;
		float				m_Pan;
		float				m_Pitch;

		mutable bool		m_Playing;

	public:
		Sound(std::string_view filepath);
		~Sound();

		void play() const;
		void loop() const;
		void pause() const;
		void stop() const;

		inline void setGain(float gain) noexcept;
		inline void setPan(float pan) noexcept;
		inline void setPitch(float pitch) noexcept;

	private:
		void initInternal() override;
		void destroyInternal() override;

		friend static void set_flag_and_destroy_on_finish(ga_Handle* in_handle, void* in_context);
	};

	inline void Sound::setGain(float gain) noexcept {
		if (gain > 1.0) {
			m_Gain = 1.0;
			return;
		}
		if (gain < 0.0) {
			m_Gain = 0.0;
			return;
		}
		m_Gain = gain;
	}

	inline void Sound::setPan(float pan) noexcept {
		if (pan > 1.0) {
			m_Pan = 1.0;
			return;
		}
		if (pan < -1.0) {
			m_Pan = 0.0;
			return;
		}
		m_Pan = pan;
	}

	inline void Sound::setPitch(float pitch) noexcept {
		m_Pitch = pitch;
	}
}
#else
	namespace prx {
	class Sound final : public Resource {
		PRX_DISALLOW_COPY_AND_MOVE(Sound)
	public:
		Sound(std::string_view filepath) : Resource(filepath){};
		~Sound() {};

		void play() const {};
		void loop() const {};
		void pause() const {};
		void stop() const {};

		inline void setGain(float gain) noexcept {};
		inline void setPan(float pan) noexcept {};
		inline void setPitch(float pitch) noexcept {};
	};
}
#endif
#endif
