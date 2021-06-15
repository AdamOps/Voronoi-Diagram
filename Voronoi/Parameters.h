#pragma once

struct parameters{
	const int windowHeight = 1000,
		windowWidth = 1600;
	const int frameRate = 60;
	const int numSites = 8;
	const float sweepLineThickness = 1;

	float siteRadius = 2.f;

	parameters() {
	}

	// Avoid duplication
	parameters(const parameters& copy) = delete;
};