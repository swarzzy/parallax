#pragma once
#ifndef _PARALLAX_AUDIO_SOUND_H_
#define _PARALLAX_AUDIO_SOUND_H_

#include <string>

#include "../ext/gorilla-audio/ga.h"
#include "../ext/gorilla-audio/gau.h"

namespace prx {
	class Window;

	class Sound {
	private:
		std::string			m_FilePath;
		
		ga_Mixer*			m_gaMixer;
		
		ga_Sound*			m_Sound;
		mutable ga_Handle*	m_Handle;

		float				m_Gain;
		float				m_Pan;
		float				m_Pitch;

		mutable bool		m_Playing;


	public:
		Sound(std::string_view filepath, ga_Mixer* gaMixer);
		~Sound();

		void play() const;
		void loop() const;
		void pause() const;
		void stop() const;

		inline void setGain	(float gain) {
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
		inline void setPan	(float pan)	{
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
		inline void setPitch(float pitch) { m_Pitch = pitch; }

		inline std::string_view getFilePath() const { return m_FilePath; }

	private:
		friend static void set_flag_and_destroy_on_finish(ga_Handle* in_handle, void* in_context);
	};
}
#endif
