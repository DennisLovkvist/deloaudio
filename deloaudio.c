
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include "deloaudio.h"

#define NULL 0

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
    alSourcef(sound_source->source, AL_PITCH, 1);
    alSourcef(sound_source->source, AL_GAIN, 1);
    alSource3f(sound_source->source, AL_POSITION, 0, 0, 0);
    alSource3f(sound_source->source, AL_VELOCITY, 0, 0, 0);
    alSourcei(sound_source->source, AL_LOOPING, AL_FALSE);
}


int deloaudio_load_from_file(SoundData *sound, char *file)
{
    alutLoadWAVFile(file, &sound->format, &sound->data, &sound->size, &sound->freq, &sound->loop);

    alGenBuffers((ALuint)1, &sound->buffer_id);

    alBufferData(sound->buffer_id, sound->format, sound->data, sound->size, sound->freq);
}

void deloaudio_play_sound(SoundSource *sound_source, SoundData *sound)
{
    alSourcei(sound_source->source, AL_BUFFER, sound->buffer_id);
    alSourcePlay(sound_source->source);
}