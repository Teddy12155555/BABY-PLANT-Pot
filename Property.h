// include headers
#include "Pitches.h"

// Define pins
#define AisObstaclePin 2
#define BisObstaclePin 3
#define CisObstaclePin 4
#define SPEAKER_PIN 0
// Melody
// A A B A G B 高音C
int meledy[7] = {NOTE_A3, NOTE_A3, NOTE_B3, NOTE_A3, NOTE_G3, NOTE_B3, NOTE_A4};
int noteDurations[7] = {
    4, 4, 4, 4, 4, 4, 4};

// Speaker play func
void PlayTone(int tones, int Melody[], int Durations[])
{
    for (int thisNote = 0; thisNote < tones; thisNote++)
    {
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(SPEAKER_PIN, melody[thisNote], noteDuration);
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(SPEAKER_PIN);
    }
}