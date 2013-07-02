#include "stdInclude.h"

static ALLEGRO_DISPLAY *display = nullptr;
static ALLEGRO_TIMER *timer = nullptr;
static ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
static ALLEGRO_EVENT ev;
static ALLEGRO_KEYBOARD_STATE keyState;
static ALLEGRO_FONT *font = nullptr;

void CreateAllegroDisplay();
void Initialize();
void StartSimulator();
void Terminate();