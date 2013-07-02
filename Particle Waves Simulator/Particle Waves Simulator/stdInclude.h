#pragma once

/* Allegro 5 stuff */
#include "allegro5/allegro5.h"
#include "allegro5\allegro_native_dialog.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_font.h"
#include "allegro5\allegro_ttf.h"

/* standard includes */
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

/* user friendly names */
#define Black al_map_rgb(0, 0, 0)
#define DarkGray al_map_rgb(64, 64, 64)
#define Gray al_map_rgb(128, 128, 128)
#define Blue al_map_rgb(0, 0, 255)
#define Green al_map_rgb(0, 255, 0)
#define Red al_map_rgb(255, 0, 0)
#define Yellow al_map_rgb(255, 255, 0)
#define White al_map_rgb(255, 255, 255)

/* global variables */
#define ProgramTitle "Particle Waves Simulator"
#define ScreenWidth 800
#define ScreenHeight 600
const double FPS = 90.0;

/* fonts */
#define ConsolaTTF "res//fonts//consola.ttf"