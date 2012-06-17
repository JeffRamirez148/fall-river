#include "AudioManager.h"


AudioManager* AudioManager::GetInstance()
{
	static AudioManager s_Instance;

	return &s_Instance;
}

AudioManager::AudioManager(void)
{
	// General
	_result = FMOD::System_Create(&_sys);
	_sys->setOutput(FMOD_OUTPUTTYPE_DSOUND ); 
	_sys->init(32, FMOD_INIT_NORMAL, 0);
	_sys->getMasterChannelGroup( &_masterChannel);
	_sys->set3DSettings(1.0f,1.0f,1.0f);
	_lastpos.x = 0.0f;
	_lastpos.y = 0.0f;
	_lastpos.z = 0.0f;

	_forward.x = 0.0f;
	_forward.y = 0.0f;
	_forward.z = 1.0f;

	_up.x = 0.0f;
	_up.y = 1.0f;
	_up.z = 0.0f;

	_vel.x = 0.0f;
	_vel.y = 0.0f;
	_vel.z = 0.0f;

	listenerpos.x = 0.0f;
	listenerpos.y = 0.0f;
	listenerpos.z = 0.0f;

	// Sound
	_sfxVolume = 1.0f;
	_sfxMute = false;

	// Music
	_musicVolume = 1.0f;
	_musicMute = false;
	_t = 0;

	_result = _sys->getDriverCaps(0, &_caps, 0, &_speakermode);
	_result = _sys->setSpeakerMode(_speakermode);
}

AudioManager::~AudioManager(void)
{
	for( unsigned int i = 0; i < _sfxSound.size(); ++i)
		_sfxSound[i]->noise->release();
	for( unsigned int i = 0; i < _musicSound.size(); ++i)
		_musicSound[i]->noise->release();
	_result = _sys->release();
}

// Sound
void AudioManager::playSound(int aSoundID)
{
	if(!_sfxMute)
	{
		_result = _sys->playSound(FMOD_CHANNEL_FREE, _sfxSound[aSoundID]->noise, true, &_sfxSound[aSoundID]->channel); 
        _result = _sfxSound[aSoundID]->channel->set3DAttributes(&_sfxSound[aSoundID]->pos, &_sfxSound[aSoundID]->vel);
        _result = _sfxSound[aSoundID]->channel->setPaused(false);
	}
}

int	AudioManager::RegisterSound(char* filePath)
{
	sound* tmp = new sound;
	tmp->id = _sfxSound.size();
	tmp->looping = false;
	tmp->pos.x = 0;
	tmp->pos.y = 0;
	tmp->pos.z = 0;
	tmp->channel->setVolume(1.0f);
	_result = _sys->createSound(filePath, FMOD_3D_LINEARROLLOFF,NULL, &tmp->noise); 
	_result = tmp->noise->set3DMinMaxDistance(0.5f, 1000.0f);

	_sfxSound.push_back(tmp);
	return tmp->id;
}

// Music
void AudioManager::playMusic(int aSoundID)
{
	if(!_musicMute)
	{
		_result = _sys->playSound(FMOD_CHANNEL_FREE, _musicSound[aSoundID]->noise, false, &_musicSound[aSoundID]->channel); 
		_sys->update();
	}
}

int	AudioManager::registerMusic(char* aFilePath)
{
	sound* tmp = new sound;
	tmp->id = _musicSound.size();
	tmp->looping = false;
	tmp->pos.x = 0;
	tmp->pos.y = 0;
	tmp->pos.z = 0;
	tmp->channel->setVolume(1.0f);
	_result = _sys->createSound(aFilePath, FMOD_3D_LINEARROLLOFF,NULL, &tmp->noise); 
	_result = tmp->noise->set3DMinMaxDistance(0.5f, 1000.0f);

	_musicSound.push_back(tmp);
	return tmp->id;
}

// Update Everybody
void AudioManager::Update(float fElapsedTime)
{
	for( unsigned int i = 0; i < _sfxSound.size(); ++i)
	{
		_sfxSound[i]->channel->set3DAttributes(&_sfxSound[i]->pos, &_sfxSound[i]->vel);
		//_sfxSound[i]->noise->setMusicSpeed(sqrt((((7+_sfxSound[i]->humidity)/(5+_sfxSound[i]->humidity) )*_gasConstant*_sfxSound[i]->temperature)/_sfxSound[i]->molecularWeight));
	}
	
	for( unsigned int i = 0; i < _musicSound.size(); ++i)
	{
		_musicSound[i]->channel->set3DAttributes(&_musicSound[i]->pos, &_musicSound[i]->vel);
		//_musicSound[i]->noise->setMusicSpeed(sqrt((((7+_musicSound[i]->humidity)/(5+_musicSound[i]->humidity) )*_gasConstant*_musicSound[i]->temperature)/_musicSound[i]->molecularWeight));
	}

	_vel.x = (listenerpos.x - _lastpos.x) * (1000 / 50);
    _vel.y = (listenerpos.y - _lastpos.y) * (1000 / 50);
    _vel.z = (listenerpos.z - _lastpos.z) * (1000 / 50);

    _lastpos = listenerpos;

	_result = _sys->set3DListenerAttributes(0, &listenerpos, &_vel, &_forward, &_up);
	_sys->update();

	_t += (30 * (1.0f / (float)50));
	//Sleep(49);
}
