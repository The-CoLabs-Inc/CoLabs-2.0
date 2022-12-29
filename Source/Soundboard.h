// SPDX-License-Identifier: GPLv3-or-later WITH Appstore-exception
// Copyright (C) 2020 Jesse Chappell



#pragma once

#include "vector"
#include "JuceHeader.h"
#include "SoundboardButtonColors.h"

/**
 * A sound file that can be played on a soundboard.
 *
 * @author Hannah Schellekens, Sten Wessel
 */
class SoundSample
{
public:

#if (JUCE_IOS || JUCE_MAC)
    /**
     * The file extensions of sound file types that are supported by the soundboard.
     */
    constexpr static const char SUPPORTED_EXTENSIONS[] = "*.wav;*.flac;*.aif;*.ogg;*.mp3;*.m4a;*.caf";
#else
    /**
     * The file extensions of sound file types that are supported by the soundboard.
     */
    constexpr static const char SUPPORTED_EXTENSIONS[] = "*.wav;*.flac;*.aif;*.ogg;*.mp3";
#endif

    enum PlaybackBehaviour {
        /**
         * Plays sample simultaneously over other samples that are already playing.
         */
        SIMULTANEOUS = 0,

        /**
         * Stops playback of all other samples before playing this sample (except BACKGROUND ones)
         */
        BACK_TO_BACK = 1,

        /**
         * Plays sample simultaneously over other samples that are already playing, and does not get stopped
         * by BACK_TO_BACK playback samples.
         */
        BACKGROUND = 2
    };

    enum ButtonBehaviour {
        TOGGLE = 0,
        HOLD = 1,
        ONE_SHOT = 2
    };

    enum ReplayBehaviour {
        REPLAY_FROM_START = 0,
        CONTINUE_FROM_LAST_POSITION = 1
    };

    /**
     * @param name The name representing the sound sample.
     * @param filePath The absolute file path of the underlying sound file.
     * @param loop Whether the sample should loop on playback.
     * @param buttonColour The colour of the sample button in RGB value with an alpha of 0.
     * @param hotkeyCode The keycode for the hotkey to play this sample, -1 for no hotkey.
     * @param playbackBehaviour The playback behaviour.
     * @param buttonBehaviour The button behaviour.
     * @param replayBehaviour The replay behaviour.
     * @param gain The playback gain for the sound sample.
     */
    SoundSample(
            String name,
            String filePath,
            bool loop = false,
            uint32 buttonColour = SoundboardButtonColors::DEFAULT_BUTTON_COLOUR,
            int hotkeyCode = -1,
            PlaybackBehaviour playbackBehaviour = PlaybackBehaviour::SIMULTANEOUS,
            ButtonBehaviour buttonBehaviour = ButtonBehaviour::TOGGLE,
            ReplayBehaviour replayBehaviour = ReplayBehaviour::REPLAY_FROM_START,
            float gain = 1.0
    );

    String getName() const;

    void setName(String newName);

    /**
     * @return The absolute file path of the underlying sound file.
     */
    String getFilePath() const;

    /**
     * @param filePath The absolute file path of the underlying sound file.
     */
    void setFilePath(String filePath);

    bool isLoop() const;

    void setLoop(bool newLoop);

    /**
     * @return 0xRRGGBB without alpha value.
     */
    [[nodiscard]] int getButtonColour() const;

    /**
     * @param newRgb 0xRRGGBB without alpha value.
     */
    void setButtonColour(int newRgb);

    /**
     * @return The KeyCode of the hotkey, -1 for no hotkey.
     */
    [[nodiscard]] int getHotkeyCode() const;

    /**
     * @param keyCode The Key code for the hotkey, -1 for no hotkey.
     */
    void setHotkeyCode(int keyCode);

    [[nodiscard]] PlaybackBehaviour getPlaybackBehaviour() const;

    void setPlaybackBehaviour(PlaybackBehaviour newBehaviour);

    [[nodiscard]] ButtonBehaviour getButtonBehaviour() const;

    void setButtonBehaviour(ButtonBehaviour newBehaviour);

    [[nodiscard]] ReplayBehaviour getReplayBehaviour() const;

    void setReplayBehaviour(ReplayBehaviour newBehaviour);

    [[nodiscard]] double getLastPlaybackPosition() const;

    void setLastPlaybackPosition(double position);

    [[nodiscard]] float getGain() const { return gain; }

    void setGain(float newGain) { this->gain = newGain; }

    /**
     * Serialize the sound sample.
     *
     * @return Tree-shaped data structure representing the instance.
     */
    ValueTree serialize() const;

    /**
     * Converts a serialized tree data structure back into a SoundSample instance.
     *
     * @param [in] tree The serialization tree data structure. Must be of the same format as is generated by serialize().
     * @return The deserialized SoundSample instance.
     */
    static SoundSample deserialize(ValueTree tree);

private:
    /**
     * Key for the root node in the serialization tree data structure.
     */
    constexpr static const char SAMPLE_KEY[] = "soundSample";

    /**
     * Key for the name property of the root node in the serialization tree data structure.
     */
    constexpr static const char NAME_KEY[] = "name";

    /**
     * Key for the file path property of the root node in the serialization tree data structure.
     */
    constexpr static const char FILE_PATH_KEY[] = "filePath";

    /**
     * Key for the loop property of the root node in the serialization tree data structure.
     */
    constexpr static const char LOOP_KEY[] = "loop";

    /**
     * Key for the button colour property of the root node in the serialization tree data structure.
     */
    constexpr static const char BUTTON_COLOUR_KEY[] = "buttonColour";

    /**
     * Key for the hotkey property of the root node in the serialization tree data structure.
     */
    constexpr static const char HOTKEY_KEY[] = "hotkey";

    /**
     * Key for the playback behaviour property of the root node in the serialization tree data structure.
     */
    constexpr static const char PLAYBACK_BEHAVIOUR_KEY[] = "playbackBehaviour";

    constexpr static const char BUTTON_BEHAVIOUR_KEY[] = "buttonBehaviour";

    constexpr static const char REPLAY_BEHAVIOUR_KEY[] = "replayBehaviour";

    /**
     * Key for the gain property of the root node in the serialization tree data structure.
     */
    constexpr static const char GAIN_KEY[] = "gain";

    /**
     * The name representing the sound sample.
     */
    String name;

    /**
     * The absolute file path of the underlying sound file.
     */
    String filePath;

    /**
     * Whether the sample should loop (indefinitely).
     */
    bool loop;

    /**
     * The argb colour the sample button must have with 0 alpha value.
     */
    uint32 buttonColour = SoundboardButtonColors::DEFAULT_BUTTON_COLOUR;

    /**
     * Keycode for the hotkey, -1 for no hotkey.
     */
    int hotkeyCode = -1;

    /**
     * See SoundSample::PlaybackBehaviour.
     */
    PlaybackBehaviour playbackBehaviour;

    ButtonBehaviour buttonBehaviour;

    ReplayBehaviour replayBehaviour;

    /**
     * Playback position where the sample last stopped playing.
     */
    double lastPlaybackPosition;

    /**
     * Playback gain.
     */
    float gain = 1.0;
};

/**
 * A named collection of ordered sound samples.
 *
 * @author Hannah Schellekens, Sten Wessel
 */
class Soundboard
{
public:
    /**
     * Create a new soundboard with the given name.
     *
     * @param name The name of the soundboard.
     */
    explicit Soundboard(String name);

    String getName() const;

    void setName(String);

    /**
     * Get the list of sound samples that are part of this soundboard.
     */
    std::vector<SoundSample>& getSamples();

    /**
     * Serialize the soundboard.
     *
     * @return Tree-shaped data structure representing the instance.
     */
    ValueTree serialize() const;

    /**
     * Converts a serialized tree data structure back into a Soundboard instance.
     *
     * @param [in] tree The serialization tree data structure. Must be of the same format as is generated by serialize().
     * @return The deserialized Soundboard instance.
     */
    static Soundboard deserialize(ValueTree tree);

private:
    /**
     * Key for the root node in the serialization tree data structure.
     */
    constexpr static const char SOUNDBOARD_KEY[] = "soundboard";

    /**
     * Key for the name property of the root node in the serialization tree data structure.
     */
    constexpr static const char NAME_KEY[] = "name";

    /**
     * Key for the samples child node container in the serialization tree data structure.
     */
    constexpr static const char SAMPLES_KEY[] = "samples";

    /**
     * The name of the soundboard.
     */
    String name;

    /**
     * All the sounds that are available on the soundboard.
     */
    std::vector<SoundSample> samples;
};
