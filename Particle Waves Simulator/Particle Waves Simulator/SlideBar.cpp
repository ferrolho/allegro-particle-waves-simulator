#include "SlideBar.h"
#include "Simulator.h"

SlideBar::SlideBar(const char* Label, int Precision, float X, float Y, float Width, double Min, double Default, double Max)
{
	label = Label;
	precision = Precision;

	label_x = X;
	label_y = Y;

	min_value = Min;
	default_value = Default;
	max_value = Max;
	current_value = default_value;

	bar_width = Width;
	bar_x1 = X;
	bar_x2 = bar_x1 + Width;
	bar_y1 = label_y + 20;
	bar_y2 = bar_y1 + 10;

	slide_is_active = false;
	refreshSlidePosCoord();
}

bool SlideBar::currentValueChanged()
{
	if (prev_current_value == current_value)
		return false;

	prev_current_value = current_value;
	return true;
}

void SlideBar::refreshSlidePosCoord()
{
	if (current_value > max_value)
		current_value = max_value;
	else if (current_value < min_value)
		current_value = min_value;
	
	if (-0.001 < current_value && current_value < 0.001)
		current_value = 0;

	slide_pos = bar_x1 + (bar_width*(current_value-min_value) / (max_value-min_value));
	slide_x1 = slide_pos - 4;
	slide_y1 = bar_y1 - 2;
	slide_x2 = slide_pos + 4;
	slide_y2 = bar_y2 + 2;
}

void SlideBar::updateSlide()
{
	if (Simulator::GetInstance()->left_mouse_button_pressed &&
		(slide_x1 < Simulator::GetInstance()->mouse_x && Simulator::GetInstance()->mouse_x < slide_x2) &&
		(slide_y1 < Simulator::GetInstance()->mouse_y && Simulator::GetInstance()->mouse_y < slide_y2))
	{ slide_is_active = true; }

	if (slide_is_active)
	{
		double x = Simulator::GetInstance()->mouse_x;
		double m = (max_value-min_value) / (bar_x2-bar_x1);
		double b = max_value - m*bar_x2;
		current_value = m*x + b;
	}

	if (Simulator::GetInstance()->left_mouse_button_released)
		slide_is_active = false;
	
	refreshSlidePosCoord();
}

void SlideBar::Draw()
{
	/* label */
	stringstream ss;
	if (current_value < 0)
		ss << label << "" << setprecision(precision) << current_value;
	else
		ss << label << " " << setprecision(precision) << current_value;
	al_draw_text(Simulator::GetInstance()->font, Black, label_x+2, label_y+1, NULL, ss.str().c_str());
	al_draw_text(Simulator::GetInstance()->font, White, label_x, label_y, NULL, ss.str().c_str());

	/* bar */
	al_draw_filled_rectangle(bar_x1, bar_y1, bar_x2, bar_y2, Black);
	al_draw_filled_rectangle(bar_x1+1, bar_y1+1, bar_x2-1, bar_y2-1, Gray);
	al_draw_line(bar_x1+1, bar_y1+2, bar_x2-1, bar_y1+2, DarkGray, 1.0);
	al_draw_line(bar_x1+1, bar_y2-1, bar_x2-1, bar_y2-1, LightGray, 1.0);

	/* min, default and max markers */
	al_draw_line(bar_x1+2, bar_y2+2, bar_x1+2, bar_y2+8, Black, 1.0);
	al_draw_line(bar_x1 + (bar_x2-bar_x1)/2, bar_y2+2, bar_x1 + (bar_x2-bar_x1)/2, bar_y2+6, Black, 1.0);
	al_draw_line(bar_x2-1, bar_y2+2, bar_x2-1, bar_y2+8, Black, 1.0);

	/* slide */
	al_draw_filled_rectangle(slide_x1, slide_y1, slide_x2, slide_y2, Black);
	al_draw_filled_rectangle(slide_pos-3, bar_y1-1, slide_pos+3, bar_y2+1, Gray);
	al_draw_line(slide_pos-3, bar_y1, slide_pos+3, bar_y1, LightGray, 1.0);
	al_draw_line(slide_pos-3, bar_y2+1, slide_pos+3, bar_y2+1, DarkGray, 1.0);
}

SlideBar::~SlideBar(void)
{
}