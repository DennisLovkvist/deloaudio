#include <stdio.h>
#include <string.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <unistd.h>
#include "deloaudio.h"



int main()
{
    ALCdevice *device;
    ALCcontext *context;
    
    deloaudio_init(device, context);


    SoundData sound;

    deloaudio_load_from_file(&sound, "test.wav");

    SoundSource sound_source;


    deloaudio_generate_source(&sound_source);
    deloaudio_play_sound(&sound_source, &sound);

    sleep(5);

    return 0;

/*

alDeleteSources(1, &source);
alDeleteBuffers(1, &buffer_id);
device = alcGetContextsDevice(context);
alcMakeContextCurrent(NULL);
alcDestroyContext(context);
alcCloseDevice(device);
*/
}