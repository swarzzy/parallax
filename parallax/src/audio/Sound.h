#pragma once
#ifndef _PARALLAX_AUDIO_SOUND_H_
#define _PARALLAX_AUDIO_SOUND_H_

#include <string>

#include <gorilla-audio/ga.h>
#include <gorilla-audio/gau.h>

namespace prx {
	class Window;

	class Sound {
	private:
		std::string			m_FilePath;
		mutable bool		m_Playing;
		ga_Mixer*			m_gaMixer;

		ga_Sound*			m_Sound;
		mutable ga_Handle*	m_Handle;


	public:
		Sound(std::string_view filepath, ga_Mixer* gaMixer);
		~Sound();

		void play() const;
		void loop() const;
		void pause() const;
		void stop() const;

		inline std::string_view getFilePath() const { return m_FilePath; }

	private:
		friend static void set_flag_and_destroy_on_finish(ga_Handle* in_handle, void* in_context);
	};
}
#endif
