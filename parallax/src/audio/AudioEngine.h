#pragma once
#include "../utils/Singleton.h"
#include "../Common.h"

#ifdef PARALLAX_ENABLE_AUDIO
#include "../ext/gorilla/ga.h"
#include "../ext/gorilla/gau.h"
#endif

namespace prx {
#ifdef PARALLAX_ENABLE_AUDIO
	class AudioEngine final : public Singleton<AudioEngine> {
		PRX_DISALLOW_COPY_AND_MOVE(AudioEngine)
	public:
		friend class Singleton<AudioEngine>;

	private:
		gau_Manager*	m_gaManager;
		ga_Mixer*		m_gaMixer;

		inline AudioEngine();

	public:
		inline ~AudioEngine();

		inline ga_Mixer* getMixer() noexcept;
		inline gau_Manager* getManager() noexcept;
	};

	AudioEngine::AudioEngine() {
	
		gc_result result = gc_initialize(nullptr);

		m_gaManager = gau_manager_create_custom(GA_DEVICE_TYPE_OPENAL, GAU_THREAD_POLICY_MULTI, 4, 512);
		m_gaMixer = gau_manager_mixer(m_gaManager);

		if (result == GC_ERROR_GENERIC || m_gaMixer == nullptr || m_gaManager == nullptr)
			PRX_FATAL("AUIO ENGINE: Failed to initialize audio system!");
	}

	AudioEngine::~AudioEngine() {
		gau_manager_destroy(m_gaManager);

		//auto result = ga_mixer_destroy(m_gaMixer);

		//if (result == GC_ERROR_GENERIC)
			//PRX_ERROR("Failed to destroy Gorilla Audio mixer");

		auto result = gc_shutdown();

		if (result == GC_ERROR_GENERIC)
			PRX_ERROR("AUDIO ENGINE: Failed to shut down Gorilla Audio library");
	}

	inline ga_Mixer* AudioEngine::getMixer() noexcept {
		return m_gaMixer;
	}

	inline gau_Manager* AudioEngine::getManager() noexcept {
		return m_gaManager;
	}
#else

	typedef struct {} ga_Mixer;
	typedef struct {} gau_Manager;

	class AudioEngine final : public Singleton<AudioEngine> {
		PRX_DISALLOW_COPY_AND_MOVE(AudioEngine)
	public:
		friend class Singleton<AudioEngine>;

		inline AudioEngine() {};

	public:
		inline ~AudioEngine() {};

		inline ga_Mixer* getMixer() noexcept { return nullptr; };
		inline gau_Manager* getManager() noexcept { return nullptr; };
	};

#endif
}