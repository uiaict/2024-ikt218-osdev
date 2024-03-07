// Header file to defines the frequencies of the notes in the music player. 
// Sourced from: https://perara.notion.site/Assignment-5-Music-Player-ef529c6c32724b7ab626297d0dc9b34d
#ifndef UIAOS_FREQUENCIES_H
#define UIAOS_FREQUENCIES_H

#include "libc/stdint.h"

// Note frequencies (in Hz)
#define C0 16
#define Cs0 17
#define D0 18
#define Ds0 19
#define E0 21
#define F0 22
#define Fs0 23
#define G0 25
#define Gs0 26
#define A0 27
#define As0 29
#define B0 31

#define C1 33
#define Cs1 35
#define D1 37
#define Ds1 39
#define E1 41
#define F1 44
#define Fs1 46
#define G1 49
#define Gs1 52
#define A1 55
#define As1 58
#define B1 62

#define C2 65
#define Cs2 69
#define D2 73
#define Ds2 78
#define E2 82
#define F2 87
#define Fs2 92
#define G2 98
#define Gs2 104
#define A2 110
#define As2 117
#define B2 123

#define C3 131
#define Cs3 139
#define D3 147
#define Ds3 156
#define E3 165
#define F3 175
#define Fs3 185
#define G3 196
#define Gs3 208
#define A3 220
#define As3 233
#define B3 247

#define C4 262
#define Cs4 277
#define D4 294
#define Ds4 311
#define E4 330
#define F4 349
#define Fs4 370
#define G4 392
#define Gs4 415
#define A4 440
#define As4 466
#define B4 494

#define C5 523
#define Cs5 554
#define D5 587
#define Ds5 622
#define E5 659
#define F5 698
#define Fs5 740
#define G5 784
#define Gs5 831
#define A5 880
#define As5 932
#define B5 988

#define C6 1047
#define Cs6 1109
#define D6 1175
#define Ds6 1245
#define E6 1319
#define F6 1397
#define Fs6 1480
#define G6 1568
#define Gs6 1661

#define A6 1760
#define As6 1865
#define B6 1976

#define C7 2093
#define Cs7 2217
#define D7 2349
#define Ds7 2489
#define E7 2637
#define F7 2794
#define Fs7 2960
#define G7 3136
#define Gs7 3322
#define A7 3520
#define As7 3729
#define B7 3951

#define C8 4186
#define Cs8 4435
#define D8 4699
#define Ds8 4978
#define E8 5274
#define F8 5588
#define Fs8 5919
#define G8 6272
#define Gs8 6645
#define A8 7040
#define As8 7459
#define B8 7902
#define C9 8372
#define Cs9 8870
#define D9 9397
#define Ds9 9956
#define E9 10548
#define F9 11175
#define Fs9 11839
#define G9 12543
#define Gs9 13290
#define A9 14080
#define As9 14917
#define B9 15804

#define A_SHARP4 466
#define G_SHARP4 415
#define R 0 // R (no sound)

typedef struct{
    uint32_t frequency;
    const char* name;
} NoteName;

static NoteName noteNames[] = {
    {16, "C0"},
    {17, "Cs0"},
    {18, "D0"},
    {19, "Ds0"},
    {21, "E0"},
    {22, "F0"},
    {23, "Fs0"},
    {25, "G0"},
    {26, "Gs0"},
    {27, "A0"},
    {29, "As0"},
    {31, "B0"},
    {33, "C1"},
    {35, "Cs1"},
    {37, "D1"},
    {39, "Ds1"},
    {41, "E1"},
    {44, "F1"},
    {46, "Fs1"},
    {49, "G1"},
    {52, "Gs1"},
    {55, "A1"},
    {58, "As1"},
    {62, "B1"},
    {65, "C2"},
    {69, "Cs2"},
    {73, "D2"},
    {78, "Ds2"},
    {82, "E2"},
    {87, "F2"},
    {92, "Fs2"},
    {98, "G2"},
    {104, "Gs2"},
    {110, "A2"},
    {117, "As2"},
    {123, "B2"},
    {131, "C3"},
    {139, "Cs3"},
    {147, "D3"},
    {156, "Ds3"},
    {165, "E3"},
    {175, "F3"},
    {185, "Fs3"},
    {196, "G3"},
    {208, "Gs3"},
    {220, "A3"},
    {233, "As3"},
    {247, "B3"},
    {262, "C4"},
    {277, "Cs4"},
    {294, "D4"},
    {311, "Ds4"},
    {330, "E4"},
    {349, "F4"},
    {370, "Fs4"},
    {392, "G4"},
    {415, "Gs4"},
    {440, "A4"},
    {466, "As4"},
    {494, "B4"},
    {523, "C5"},
    {554, "Cs5"},
    {587, "D5"},
    {622, "Ds5"},
    {659, "E5"},
    {698, "F5"},
    {740, "Fs5"},
    {784, "G5"},
    {831, "Gs5"},
    {880, "A5"},
    {932, "As5"},
    {988, "B5"},
    {1047, "C6"},
    {1109, "Cs6"},
    {1175, "D6"},
    {1245, "Ds6"},
    {1319, "E6"},
    {1397, "F6"},
    {1480, "Fs6"},
    {1568, "G6"},
    {1661, "Gs6"},
    {1760, "A6"},
    {1865, "As6"},
    {1976, "B6"},
    {2093, "C7"},
    {2217, "Cs7"},
    {2349, "D7"},
    {2489, "Ds7"},
    {2637, "E7"},
    {2794, "F7"},
    {2960, "Fs7"},
    {3136, "G7"},
    {3322, "Gs7"},
    {3520, "A7"},
    {3729, "As7"},
    {3951, "B7"},
    {4186, "C8"},
    {4435, "Cs8"},
    {4699, "D8"},
    {4978, "Ds8"},
    {5274, "E8"},
    {5588, "F8"},
    {5919, "Fs8"},
    {6272, "G8"},
    {6645, "Gs8"},
    {7040, "A8"},
    {7459, "As8"},
    {7902, "B8"},
    {8372, "C9"},
    {8870, "Cs9"},
    {9397, "D9"},
    {9956, "Ds9"},
    {10548, "E9"},
    {11175, "F9"},
    {11839, "Fs9"},
    {12543, "G9"},
    {13290, "Gs9"},
    {14080, "A9"},
    {14917, "As9"},
    {15804, "B9"},
    {466, "A_SHARP4"},
    {415, "G_SHARP4"},
    {0, "Rest"}
};

#endif //UIAOS_FREQUENCIES_H
