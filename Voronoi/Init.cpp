#include <iostream>

#include "Init.h"
#include "Shapes.h"
#include "Parameters.h"

void initAll(parameters* settings, std::vector<site>* siteVector) {
	for (int i = 0; i < settings->numSites; i++) {
		siteVector->emplace_back(site(settings));
	}
}