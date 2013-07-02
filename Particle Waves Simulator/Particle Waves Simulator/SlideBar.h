#pragma once

#include "stdInclude.h"

class SlideBar
{
public:
	SlideBar(const char* Name, int Precision, float X, float Y, float Width, double Min, double Default, double Max);

	bool currentValueChanged();

	double getCurrentValue() { return current_value; }
	double getSlidePos() { return slide_pos; }

	void refreshSlidePosCoord();
	void updateSlide();

	void Draw();

	~SlideBar(void);

private:
	const char* label;
	int precision;

	double min_value;
	double default_value;
	double max_value;
	double current_value;
	double prev_current_value;

	bool slide_is_active;
	double slide_x1, slide_y1;
	double slide_x2, slide_y2;
	double slide_pos;

	float label_x, label_y;
	float bar_width;
	float bar_x1, bar_y1;
	float bar_x2, bar_y2;
};