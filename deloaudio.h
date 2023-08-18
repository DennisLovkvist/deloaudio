#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#include <AL/al.h>
#include <AL/alc.h>

typedef struct SoundData SoundData;
struct SoundData
{
    unsigned int id;
    ALsizei size, freq;
    ALenum format;
    ALboolean loop;
    ALvoid *data;
    ALuint buffer_id;
};


typedef struct SoundSource SoundSource;
struct SoundSource
{
    unsigned int id;
    SoundData *sound_data;
    ALuint source;
    ALuint source_state;
};

int deloaudio_init(ALCdevice *device, ALCcontext *context);
int deloaudio_generate_source(SoundSource *sound_source);
int deloaudio_load_from_file(SoundData *sound, char *file);
int deloaudio_load_from_file_ogg(SoundData *sound, char *file);
void deloaudio_play_sound(SoundSource *sound_source, SoundData *sound);