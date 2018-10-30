#include <audio/Sound.h>

#include <utils/log/Log.h>
#include <window/Window.h>
#include "audio/AudioEngine.h"

namespace prx {
	
	void set_flag_and_destroy_on_finish(ga_Handle* in_handle, void* in_context);

	Sound::Sound(std::string_view filepath)
		: Resource(filepath),
		  m_gaMixer(AudioEngine::getInstance()->getMixer()), 
		  m_Gain(1.0f), 
		  m_Pan(0.0), 
		  m_Pitch(1.0), 
		  m_Playing(false) 
	{}

	Sound::~Sound() {
		if (m_Sound != nullptr) {
			if (m_Playing)
				stop();
			ga_sound_release(m_Sound);
			m_Sound = nullptr;
		}
	}

	void Sound::play() const {
		if (m_Sound != nullptr) {
			if (!m_Playing) {
				gc_int32 quit = 0;
				m_Handle = gau_create_handle_sound(m_gaMixer, m_Sound, &set_flag_and_destroy_on_finish, &quit, nullptr);
				ga_handle_setParamf(m_Handle, GA_HANDLE_PARAM_GAIN, m_Gain);
				ga_handle_setParamf(m_Handle, GA_HANDLE_PARAM_PAN, m_Pan);
				ga_handle_setParamf(m_Handle, GA_HANDLE_PARAM_PITCH, m_Pitch);
				// It might be extremely dangerous but who knows 
				m_Handle->soundClassInstanceAddress = reinterpret_cast<uintptr_t>(this);
				m_Playing = true;
			}
			ga_handle_play(m_Handle);
		}
	}

	void Sound::loop() const {
		if (m_Sound != nullptr) {
			if (!m_Playing) {
				gau_SampleSourceLoop* loopSrc;
				gc_int32 quit = 0;
				m_Handle = gau_create_handle_sound(m_gaMixer, m_Sound, &set_flag_and_destroy_on_finish, &quit, &loopSrc);
				ga_handle_setParamf(m_Handle, GA_HANDLE_PARAM_GAIN, m_Gain);
				ga_handle_setParamf(m_Handle, GA_HANDLE_PARAM_PAN, m_Pan);
				ga_handle_setParamf(m_Handle, GA_HANDLE_PARAM_PITCH, m_Pitch);
				m_Handle->soundClassInstanceAddress = reinterpret_cast<uintptr_t>(this);
				m_Playing = true;
			}
			ga_handle_play(m_Handle);
		}
	}

	void Sound::pause() const {
		if (m_Sound != nullptr) {
			if (m_Playing == true) {
				ga_handle_stop(m_Handle);
			}
		}
	}

	void Sound::stop() const {
		if (m_Sound != nullptr) {
			if (m_Playing == true) {
				ga_handle_stop(m_Handle);
				ga_handle_destroy(m_Handle);
				m_Playing = false;
			}
		}
	}

	void Sound::initInternal() {
		size_t dotPos = m_FilePath.find_last_of('.');

		m_Sound = gau_load_sound_file(m_FilePath.c_str(), m_FilePath.substr(dotPos + 1).c_str());

		if (m_Sound == nullptr) {
			PRX_ERROR("SOUND: Failed to load audio from file/n-> PATH: ", m_FilePath);
		}
	}

	void Sound::destroyInternal() {
		if (m_Sound != nullptr) {
			if (m_Playing)
				stop();
			ga_sound_release(m_Sound);
			m_Sound == nullptr;
		}
	}

	void set_flag_and_destroy_on_finish(ga_Handle* in_handle, void* in_context) {
		Sound* ptr = reinterpret_cast<Sound*>(in_handle->soundClassInstanceAddress);
		ptr->stop();
	}
}