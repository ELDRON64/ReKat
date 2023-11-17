#include <AL/al.h>
#include <AL/alc.h>

#include <iostream>

static void list_audio_devices(const ALCchar *devices)
{
        const ALCchar *device = devices, *next = devices + 1;
        size_t len = 0;

        std::cout << "Devices list:\n";
        std::cout << "----------\n";
        while (device && *device != '\0' && next && *next != '\0') {
                std::cout << "%s\n", device;
                len = strlen(device);
                device += (len + 1);
                next += (len + 2);
        }
        std::cout << "----------\n";
}

int main( ) {
    std::cout << "start\n";
    ALCdevice *device;

    device = alcOpenDevice(NULL);
    if (!device) { std::cout << "cant start\n"; return 0;}

    bool E = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
    if (E == AL_FALSE) { } 
    else { list_audio_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER)); }
        
    std::cout << "end\n";
    return 0;
}
