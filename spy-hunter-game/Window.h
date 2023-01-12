#pragma once


#include"SDL.h"


class Window
{
public:
	static int const WINDOW_WIDTH = 640;
	static int const WINDOW_HEIGHT = 480;
	
	static int const FRAME_RATE = 144;
	static int constexpr FRAME_DELAY = 1000 / FRAME_RATE;

	Window(SDL* sdl);
	void setInitialSettings();
	
	double calculateWorldTime();
	double calculateDelta();
	void calculateFPS();
	
	void maintainConstantFPS();
	void incrementFramesCount();
	void resetTime();

	// get / set
	int getFrameStartTime();
	int getFrameFinishTime();
	double getDelta();
	double getWorldTime();
	double getFpsTimer();
	double getFps();
	
	void setDelta(double delta);
	void setWorldTime(double time);
	void setFpsTimer(double fpsTimer);
	void setFps(double fps);

private:
	SDL* sdl;
	
	Uint32 frameStartTime;
	int frameFinishTime;
	int frames;
	double delta;
	double worldTime;
	double fpsTimer;
	double fps;
};

