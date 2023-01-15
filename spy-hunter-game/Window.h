#pragma once


#include"SDL.h"


class Window
{
public:
	static int const WIDTH = 640;
	static int const HEIGHT = 480;

	static int const LINE_HEIGHT = 10;
	static int const BIG_LINE_HEIGHT = 14;
	
	static int const FRAME_RATE = 144;
	static int constexpr FRAME_DELAY = 1000 / FRAME_RATE;

	Window(SDL* sdl);
	void setInitialSettings();
	
	double calculateWorldTime(bool isPaused);
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
	Uint32 frameStartTimeSincePaused;
	int frameFinishTime;
	int frames;

	double delta;
	double worldTime;
	
	double fpsTimer;
	double fps;
};

