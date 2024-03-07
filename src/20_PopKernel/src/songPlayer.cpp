// Source file for songPlayer based on the Per-Arne Andersen's pseudo code from: https://perara.notion.site/Assignment-5-Music-Player-ef529c6c32724b7ab626297d0dc9b34d
extern "C" {
    
    #include "pit.h"
    #include "libc/stdio.h"
    #include "io.h"
}

#include "songPlayer/song.h"
#include "songPlayer/frequencies.h"

// Enable the speaker
void enableSpeaker() {
    
     uint8_t state = inb(PC_SPEAKER_PORT);              // Get the current state of the speaker
                                  
    if ((state & 3) != 3) {                             // If the speaker is not already enabled, enable it
        outb(PC_SPEAKER_PORT, state | 3);               // Set the last two bits to 1
    }
   
}

// Disable the speaker
void disableSpeaker() {
    uint8_t state = inb(PC_SPEAKER_PORT);               // Get the current state of the speaker

    if ((state & 3) != 0) {                             // If the speaker is not already disabled, disable it
        outb(PC_SPEAKER_PORT, state & 0xFC);            // Set the last two bits to 0
    }
}

// Plays a sound with the given frequency
void playSound(uint32_t frequency) {

    if (frequency == 0) {                               // Return if the frequency is 0
        return;
    }

    uint16_t divisor = PIT_BASE_FREQUENCY / frequency;  // Calculate the divisor for the PIT

    outb(PIT_CMD_PORT, 0xB6);                           // Set the PIT to mode 3 and low/hi-byte access

    outb(PIT_CHANNEL2_PORT, (uint8_t)(divisor & 0xFF));             // Send the low byte to the PIT
    outb(PIT_CHANNEL2_PORT, (uint8_t)((divisor >> 8) & 0xFF));      // Send the high byte to the PIT

    uint8_t state = inb(PC_SPEAKER_PORT);               // Get the current state of the speaker
    state |= 0b11;                                      // Set state to the correct value
    outb(PC_SPEAKER_PORT, state);                       // Set the state of the speaker
}   

// Stops the sound
void stopSound() {
    uint8_t state = inb(PC_SPEAKER_PORT);               // Get the current state of the speaker

    state &= ~0b10;                                     // Set the state to the correct value

    outb(PC_SPEAKER_PORT, state);                       // Stop the sound
}

// Gets the name of a note based on its frequency
const char* getNoteName(uint32_t frequency) {
    for (size_t i = 0; i < sizeof(noteNames) / sizeof(NoteName); i++) {
        if (noteNames[i].frequency == frequency) {
            return noteNames[i].name;
        }
    }

    return "Unknown";
}

// Plays a song
void playSongImpl(Song *song) {
    
    enableSpeaker();                                    // Enable the speaker

    // Loop through all notes
    for (size_t i = 0; i < song->length; i++) {
        Note* note = &song->notes[i];

        // Get the note name
        const char* noteName = getNoteName(note->frequency);    

        // Print note information
        printf("Playing note %s with frequency %u Hz for %u ms\n", noteName, note->frequency, note->duration);


        playSound(note->frequency);                    // Play the note
        sleepInterrupt(note->duration);                // Sleep for the duration of the note
        stopSound();                                   // End the note
    }

    
    disableSpeaker();                                   // Disable the speaker          
}

void playSong(Song *song) {
    playSongImpl(song);
}

// Creates a new SongPlayer instance
SongPlayer* createSongPlayer() {
    auto* player = new SongPlayer();                    // Create a new SongPlayer object
    player->playSong = playSongImpl;                    // Set the playSong function pointer to the playSongImpl function
    return player;                                      // Return the new SongPlayer object
}
