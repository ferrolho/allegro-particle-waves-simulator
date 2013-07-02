#pragma once

#include "stdInclude.h"
#include "SlideBar.h"

class Simulator
{
public:
	static Simulator *GetInstance();

	void CreateAllegroDisplay();
	void LoadFonts();
	void Initialize();
	void TrackMouse();
	void StartSimulator();
	void Terminate();

	ALLEGRO_FONT *font;

	double mouse_x, mouse_y;
	bool left_mouse_button_pressed;
	bool left_mouse_button_released;
	
private:
	static Simulator *instance;

	ALLEGRO_DISPLAY *display;
	ALLEGRO_TIMER *timer;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_EVENT ev;
	ALLEGRO_KEYBOARD_STATE keyState;

	bool done, draw;
	ALLEGRO_COLOR ParticleColor;
	bool ShowParticlePath;
	double ParticleSpeed;
	double ParticleDelay;
	double ParticleRadius;
	double ParticlePathDiameter;
	double DistanceBetweenPathCenters;
	unsigned int MatrixSize;
	vector<SlideBar*> slides;
	SlideBar *SpeedSlide;
};