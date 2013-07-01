#pragma once

/* Allegro 5 stuff */
#include "allegro5/allegro5.h"
#include "allegro5\allegro_native_dialog.h"
#include "allegro5\allegro_primitives.h"

/* standard includes */
#include <iostream>

using namespace std;

/* global variables */
#define ProgramTitle "Particle Waves Simulator"
#define ScreenWidth 800
#define ScreenHeight 600
const float FPS = 90.0;

/* user friendly names */
#define Black al_map_rgb(0, 0, 0)
#define Blue al_map_rgb(0, 0, 255)
#define Green al_map_rgb(0, 255, 0)
#define Red al_map_rgb(255, 0, 0)
#define Yellow al_map_rgb(255, 255, 0)
#define White al_map_rgb(255, 255, 255)