#include "Simulator.h"

Simulator *Simulator::instance = nullptr;

Simulator *Simulator::GetInstance()
{
	if (!instance)
	{
		instance = new Simulator();
	}

	return instance;
}

void Simulator::CreateAllegroDisplay()
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

void Simulator::LoadFonts()
{
	font = al_load_font(ConsolaTTF, 14, NULL);
	if (!font)
	{
		al_show_native_message_box(Simulator::GetInstance()->display, "Error", "Could not load font file.", "Have you included the resources in the same directory of the program?", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}
}

void Simulator::Initialize()
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
	al_init_font_addon();
	al_init_ttf_addon();
	cout << "Installing devices..." << endl;
	al_install_mouse();
	al_install_keyboard();

	cout << "Creating display..." << endl;
	CreateAllegroDisplay();
	cout << "Loading fonts..." << endl;
	LoadFonts();

	cout << "Creating timers..." << endl;
	timer = al_create_timer(1.0 / FPS);

	cout << "Creating event queues..." << endl;
	event_queue = al_create_event_queue();

	cout << "Registering event sources..." << endl;
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());	

	cout << "Initializing variables..." << endl;
	done = false;
	draw = true;
	ParticleColor = Blue;
	ShowParticlePath = true;
	ParticleSpeed = 0.03;
	ParticleDelay = 0.15;
	ParticleRadius = 3;
	ParticlePathDiameter = 23;
	DistanceBetweenPathCenters = 26;
	MatrixSize = ScreenHeight/DistanceBetweenPathCenters + 2;

	SpeedSlide = new SlideBar("Particles Speed:", 610, 20, 180, -0.1, ParticleSpeed, 0.1);
	slides.push_back(SpeedSlide);
		
	cout << "Starting timers..." << endl;
	al_start_timer(timer);
}

void Simulator::TrackMouse()
{
	if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
	{
		mouse_x = ev.mouse.x;
		mouse_y = ev.mouse.y;

		draw = true;
	}
	if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	{
		if (ev.mouse.button & 1)
		{
			//cout << "* Left mouse button pressed *" << endl;
			left_mouse_button_pressed = true;
			left_mouse_button_released = false;
			draw = true;
		}
	}
	if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	{
		if (ev.mouse.button & 1)
		{
			cout << "* Left mouse button released *" << endl;
			left_mouse_button_pressed = false;
			left_mouse_button_released = true;
			draw = true;
		}
	}
}

void Simulator::StartSimulator()
{
	Initialize();

	cout << "Initializing particles..." << endl;
	vector<double> temp (MatrixSize);
	vector<vector<double> > angles;
	for (unsigned int i = 0; i < MatrixSize; i++)
	{
		angles.push_back(temp);
		for (unsigned int j = 0; j < MatrixSize; j++)
			angles[i][j] = i*ParticleDelay + j*ParticleDelay;
	}

	cout << "Starting control cycle..." << endl;
	while (!done)
	{
		al_wait_for_event(event_queue, & ev);
		al_get_keyboard_state(&keyState);

		TrackMouse();
		
		/* --- UPDATING --- */
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE)
			{
				if (ShowParticlePath)
					ShowParticlePath = false;
				else
					ShowParticlePath = true;
			}
		}

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			for (SlideBar* obj : slides)
				obj->updateSlide();
			//SpeedSlide->updateSlide();

			/* updating particles */
			for (unsigned int i = 0; i < MatrixSize; i++)
				for (unsigned int j = 0; j < MatrixSize; j++)
					angles[i][j] += SpeedSlide->getCurrentValue();

			draw = true;
		}

		/* --- now drawing --- */
		if (draw && al_event_queue_is_empty(event_queue))
		{
			double particle_x, particle_y;
			for (unsigned int i = 0; i < MatrixSize; i++)
			{
				for (unsigned int j = 0; j < MatrixSize; j++)
				{
					if (ShowParticlePath)
						al_draw_circle(i*DistanceBetweenPathCenters, j*DistanceBetweenPathCenters, ParticlePathDiameter, Black, 1.0);

					particle_x = cos(angles[i][j])*ParticlePathDiameter + j*DistanceBetweenPathCenters;
					particle_y = sin(angles[i][j])*ParticlePathDiameter + i*DistanceBetweenPathCenters;
					al_draw_filled_circle(particle_x, particle_y, ParticleRadius, ParticleColor);
				}
			}

			/* side-bar */
			al_draw_line(600, 0, 600, 600, Black, 1.0);
			al_draw_filled_rectangle(600, 0, 800, 600, DarkGray);

			/* slide bars */
			for (SlideBar* obj : slides)
				obj->Draw();
			//SpeedSlide->Draw();

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
}

void Simulator::Terminate()
{
	cout << "Deallocating memory and quitting..." << endl;
	for (SlideBar* obj : slides)
		delete obj;
	al_destroy_font(font);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);
	delete instance;
}