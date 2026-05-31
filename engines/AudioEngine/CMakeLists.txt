add_subdirectory(dependencies/PortAudio portaudio)

add_library(AudioEngine STATIC
    include/AudioEngine.h
    include/Device.h
    # include/RingBuffer.h
    include/SampleSound.h
    include/Sound.h
    include/StreamHandler.h
    # include/Synth/EasingMath.h
    # include/Synth/Envelope.h
    include/Synth/Oscillator.h
    # include/Synth/Modulator.h
    include/Synth/Synth.h
    include/Synth/SynthSound.h

    src/AudioEngine.cpp
    src/Device.cpp
    # src/RingBuffer.cpp
    src/SampleSound.cpp
    src/Sound.cpp
    src/StreamHandler.cpp
    # src/Synth/EasingMath.cpp
    # src/Synth/Envelope.cpp
    src/Synth/Oscillator.cpp
    # src/Synth/Modulator.cpp
    src/Synth/Synth.cpp
    src/Synth/SynthSound.cpp
)

target_include_directories(AudioEngine PUBLIC
    include
    include/Synth
    dependencies/PortAudio/include
)

target_link_libraries(AudioEngine PRIVATE
    portaudio_static
)




