#pragma once

struct parameters{
	const int windowHeight = 1000,
		windowWidth = 1600;
	const bool keyRepeat = true;
	const int frameRate = 60;
	int numSites = 10;

	// Visual parameters. 
	//		Sweepline is a horizontal straight line
	//		Sites are displayed as circles
	//		Each site has a corresponding parabolic arc. The "arcResolution" determines what the horizontal distance is (in pixels) between the vertices used to draw the parabola.
	const float sweepLineThickness = 1;
	float siteRadius = 2.f;
	int arcResolution = 1;
	bool drawArcs = true;
	bool drawBeach = true;

	parameters() {
	}

	// Avoid duplication
	parameters(const parameters&) = delete;
};