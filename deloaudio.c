#include "deloaudio.h"

#include <sys/stat.h>
/*
void error_check()
{
    ALCenum error = alGetError();
    if (error != AL_NO_ERROR)
    {
        printf("%s\n", error);
    }
}*/
int deloaudio_init(ALCdevice *device, ALCcontext *context)
{
    device = alcOpenDevice(NULL);
    if (!device)
    {
        return 1;
    }

    context = alcCreateContext(device, NULL);
    if (!alcMakeContextCurrent(context))
    {
        return 1;
    }

    ALfloat listener[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };

    alListener3f(AL_POSITION, 0, 0, 1.0f);
    alListener3f(AL_VELOCITY, 0, 0, 0);
    alListenerfv(AL_ORIENTATION, listener);
}

int deloaudio_generate_source(SoundSource *sound_source)
{
    alGenSources((ALuint)1, &sound_source->source);
    alSourcef (sound_source->source, AL_PITCH, 1);
    alSourcef (sound_source->source, AL_GAIN,  1);
    alSource3f(sound_source->source, AL_POSITION, 0, 0, 0);
    alSource3f(sound_source->source, AL_VELOCITY, 0, 0, 0);
    alSourcei (sound_source->source, AL_LOOPING, AL_FALSE);
}
int deloaudio_load_from_file(SoundData *sound, char *file)
{
    SNDFILE *sndfile;
    SF_INFO sfinfo;

    sndfile = sf_open(file, SFM_READ, &sfinfo);
    if (!sndfile) 
    {
        // Handle file open error
    }

    // Read audio data
    sound->data = (short *)malloc(sfinfo.frames * sfinfo.channels * sizeof(short));
    sf_readf_short(sndfile, sound->data, sfinfo.frames);

    sf_close(sndfile);

    alGenBuffers(1, &sound->buffer_id);
    alBufferData(sound->buffer_id, AL_FORMAT_STEREO16, sound->data, sfinfo.frames * sfinfo.channels * sizeof(short), sfinfo.samplerate);

}

void deloaudio_play_sound(SoundSource *sound_source, SoundData *sound)
{
    alSourcei(sound_source->source, AL_BUFFER, sound->buffer_id);
    alSourcePlay(sound_source->source);
}