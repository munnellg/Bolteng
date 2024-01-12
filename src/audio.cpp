#include "audio.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>

#define DSI_FREQUENCY 44100

static SDL_AudioDeviceID audio_device;
static SDL_AudioSpec audio_spec;

int period = 1;
int amplitude = 0;

typedef void (*wave)(Uint16 *stream, int len);

static wave waveform;

void
audio_quit() {
    SDL_CloseAudioDevice(audio_device);
}

void
sawtooth(Uint16 *stream, int len) {
    static int counter = 0;
    for (int i = 0; i < len; i += 2) {
        Uint16 sample = (counter * amplitude) / period;
        stream[i] = sample;
        stream[i + 1] = sample;
        counter = (counter + 1) % period;
    }
}

void
square(Uint16 *stream, int len) {
    static int counter = 0;
    int amp = amplitude >> 1;
    for (int i = 0; i < len; i += 2) {
        Uint16 sample = (counter > period / 2)? amp : -amp;
        stream[i]     = sample;
        stream[i + 1] = sample;
        counter = (counter + 1) % period;
    }
}

void
triangle(Uint16 *stream, int len) {
    static int counter = 0;
    int amp = amplitude << 2;

    for (int i = 0; i < len; i += 2) {
        Uint16 sample = counter * (amp / period);

        if (counter > period / 2) { 
            sample = amp - sample;
        }
        sample = sample - amplitude / 2;
        stream[i]     = sample;
        stream[i + 1] = sample;
        counter = (counter + 1) % period;
    }
}

void
sine(Uint16 *stream, int len) {
    static int counter = 0;

    for (int i = 0; i < len; i += 2) {
        Uint16 sample = 2 * amplitude * sin(counter * (2.0 * 3.14) / period);
        stream[i]     = sample;
        stream[i + 1] = sample;
        counter = (counter + 1) % period;
    }
}

void
set_freq(int freq) {
    SDL_LockAudioDevice(audio_device);
    period = DSI_FREQUENCY / freq;
    SDL_UnlockAudioDevice(audio_device);
}

void
set_amplitude(int amp) {
    SDL_LockAudioDevice(audio_device);
    amplitude = amp;
    SDL_UnlockAudioDevice(audio_device);
}

int
get_amplitude() {
    return amplitude;
}

void
set_waveform(int select) {
    SDL_LockAudioDevice(audio_device);
    switch (select) {
        case AUDIO_SAWTOOTH:
            waveform = sawtooth;
            break;
        case AUDIO_SQUARE:
            waveform = square;
            break;
        case AUDIO_TRIANGLE:
            waveform = triangle;
            break;
        case AUDIO_SINE:
            waveform = sine;
            break;
    }
    SDL_UnlockAudioDevice(audio_device);
}

void
audio_callback(void* userdata, Uint8* stream, int len) {
    waveform((Uint16 *) stream, len / 2);
}

int
audio_init(struct Settings const &settings) {
    SDL_zero(audio_spec);

    waveform = square;

    audio_spec.freq = 44100; // samples per second
    audio_spec.format = AUDIO_S16SYS;
    audio_spec.channels = 2;
    audio_spec.samples = 1024;
    audio_spec.callback = audio_callback;

    audio_device = SDL_OpenAudioDevice(NULL, 0, &audio_spec, NULL, 0);

    SDL_PauseAudioDevice(audio_device, 0);

    return audio_device == 0;
}
