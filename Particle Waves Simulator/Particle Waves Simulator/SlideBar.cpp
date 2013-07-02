#include "SlideBar.h"
#include "Simulator.h"

SlideBar::SlideBar(const char* Label, float X, float Y, float Width, double Min, double Default, double Max)
{
	label = Label;

	label_x = X;
	label_y = Y;

	slide_x1 = X;
	slide_x2 = slide_x1 + Width;
	slide_y1 = label_y + 20;
	slide_y2 = slide_y1 + 10;

	min_value = Min;
	default_value = Default;
	max_value = Max;
	current_value = default_value;
}

void SlideBar::Draw()
{
	//al_draw_text(font, Black, label_x, label_y, NULL, label);
	al_draw_text(font, Black, 20, 20, NULL, "man");
	al_draw_filled_rectangle(slide_x1, slide_y1, slide_x2, slide_y2, Gray);
}

SlideBar::~SlideBar(void)
{
}