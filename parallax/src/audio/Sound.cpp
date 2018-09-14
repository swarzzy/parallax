#include "Sound.h"
#include "../resources/Resources.h"
#include "../window/Window.h"

namespace prx {
	
	void set_flag_and_destroy_on_finish(ga_Handle* in_handle, void* in_context);

	Sound::Sound(std::string_view filepath, ga_Mixer* gaMixer)
		:m_FilePath(filepath), m_Playing(false), m_gaMixer(gaMixer) {
		int dotPos = filepath.find_last_of('.');
		std::string path(filepath);
		
		m_Sound = gau_load_sound_file(path.c_str(), path.substr(dotPos + 1).c_str());
		
		if (m_Sound == nullptr) {
			std::stringstream ss;
			ss << "RESOURCE MANAGER: Failed to load audio from file: " << path;
			Log::message(ss.str(), LOG_ERROR);
			ASSERT(false);
		}
	}

	Sound::~Sound() {
		ga_sound_release(m_Sound);
	}

	void Sound::play() const {
		if (!m_Playing) {
			gc_int32 quit = 0;
			m_Handle = gau_create_handle_sound(m_gaMixer, m_Sound, &set_flag_and_destroy_on_finish, &quit, nullptr);
			m_Handle->sound = reinterpret_cast<uintptr_t>(this);
			m_Playing = true;
		}
		ga_handle_play(m_Handle);
	}

	void Sound::loop() const {
		if (!m_Playing) {
			gau_SampleSourceLoop* loopSrc;
			gc_int32 quit = 0;
			m_Handle = gau_create_handle_sound(m_gaMixer, m_Sound, &set_flag_and_destroy_on_finish, &quit, &loopSrc);
			m_Handle->sound = reinterpret_cast<uintptr_t>(this);
			m_Playing = true;
		}
		ga_handle_play(m_Handle);
	}

	void Sound::pause() const {
		if (m_Playing == true)
			ga_handle_stop(m_Handle);
	}

	void Sound::stop() const {
		if (m_Playing == true) {
			ga_handle_stop(m_Handle);
			ga_handle_destroy(m_Handle);
			m_Playing = false;
		}
	}

	void set_flag_and_destroy_on_finish(ga_Handle* in_handle, void* in_context) {
		Sound* ptr = reinterpret_cast<Sound*>(in_handle->sound);
		ptr->stop();
	}
}
