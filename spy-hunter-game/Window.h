#pragma once


#include"SDL.h"


class Window
{
public:
	Window(SDL* sdl);
	void setInitialSettings();

	// get / set
	int getFrameStartTime();
	int getFrameFinishTime();
	int getFrames();
	double getDelta();
	double getWorldTime();
	double getFpsTimer();
	double getFps();
	
	void setFrameStartTime(int time);
	void setFrameFinishTime(int time);
	void setFrames(int frames);
	void setDelta(double delta);
	void setWorldTime(double time);
	void setFpsTimer(double fpsTimer);
	void setFps(double fps);

private:
	SDL* sdl;
	
	int frameStartTime;
	int frameFinishTime;
	int frames;
	double delta;
	double worldTime;
	double fpsTimer;
	double fps;
};

