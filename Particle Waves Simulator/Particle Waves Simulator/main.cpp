#include "stdInclude.h"

ALLEGRO_DISPLAY *display = nullptr;
ALLEGRO_EVENT ev;
ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
ALLEGRO_TIMER *timer = nullptr;

void CreateAllegroDisplay()
{
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	display = al_create_display(ScreenWidth, ScreenHeight);
	if (!display)
	{
		al_show_native_message_box(display, "Error", "Display Settings", "Couldn't create a display.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}
	/* setting new window title */
	al_set_window_title(display, ProgramTitle);
}

void Initialize()
{
	cout << endl;
	cout << "##############################" << endl;
	cout << "##                          ##" << endl;
	cout << "##    STARTING SIMULATOR    ##" << endl;
	cout << "##                          ##" << endl;
	cout << "##############################" << endl;
	cout << endl;
	cout << "-------------" << endl;
	cout << "Activity Log:" << endl;
	cout << "-------------" << endl;

	cout << "Starting Allegro 5..." << endl;
	if (!al_init())
	{ al_show_native_message_box(NULL, NULL, "Could not initialize Allegro 5", NULL, NULL, NULL); }

	cout << "Initializing add ons..." << endl;
	al_init_primitives_addon();
	cout << "Installing devices..." << endl;
	al_install_mouse();
	al_install_keyboard();

	cout << "Creating display..." << endl;
	CreateAllegroDisplay();

	cout << "Creating timers..." << endl;
	timer = al_create_timer(1.0 / FPS);

	cout << "Creating event queues..." << endl;
	event_queue = al_create_event_queue();

	cout << "Registering event sources..." << endl;
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());	

	cout << "Starting timers..." << endl;
	al_start_timer(timer);
}

void Terminate()
{
	cout << "Deallocating memory and quitting..." << endl;
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
}

int main ()
{
	Initialize();

	cout << "Initializing variables..." << endl;

	vector<double> temp (MatrixSize);
	vector<vector<double> > angles;
	for (unsigned int i = 0; i < MatrixSize; i++)
	{
		angles.push_back(temp);
		for (unsigned int j = 0; j < MatrixSize; j++)
			angles[i][j] = i*ParticleDelay + j*ParticleDelay;
	}


	cout << endl << "Initial matrix:";
	for (unsigned int i = 0; i < MatrixSize; i++)
	{
		cout << endl;
		for (unsigned int j = 0; j < MatrixSize; j++)
			cout << angles[i][j] << " ";
	}
	cout << endl << endl;


	bool done = false;
	bool draw = true;

	cout << "Starting control cycle..." << endl;
	while (!done)
	{
		al_wait_for_event(event_queue, & ev);
		
		/* --- UPDATING --- */
		if (ev.type == ALLEGRO_EVENT_TIMER || draw)
		{
			for (unsigned int i = 0; i < MatrixSize; i++)
				for (unsigned int j = 0; j < MatrixSize; j++)
					angles[i][j] += ParticleSpeed;

			draw = true;
		}

		/* --- now drawing --- */
		if (draw && al_event_queue_is_empty(event_queue))
		{
			for (unsigned int i = 0; i < MatrixSize; i++)
			{
				for (unsigned int j = 0; j < MatrixSize; j++)
				{
					if (ShowParticlePath)
						al_draw_circle(i*DistanceBetweenPathCenters, j*DistanceBetweenPathCenters, ParticlePathDiameter, Black, 1.0);

					double particle_x = cos(angles[i][j])*ParticlePathDiameter + j*DistanceBetweenPathCenters;
					double particle_y = sin(angles[i][j])*ParticlePathDiameter + i*DistanceBetweenPathCenters;
					al_draw_filled_circle(particle_x, particle_y, ParticleRadius, Black);
				}
			}

			/* side-bar */
			al_draw_filled_rectangle(600, 0, 800, 600, Black);

			al_flip_display();
			al_clear_to_color(White);
			draw = false;
		}

		/* if window is closed */
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			cout << "Close button pressed..." << endl;
			done = true;
		}
	}

	Terminate();

	return 0;
}