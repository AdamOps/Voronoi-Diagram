#pragma once
#include "RedBlackTree.h"
#include "VoronoiEvents.h"

void executeCircleEvent(RBTree& beachfront, voronoiEvent currEvent);

void executeSiteEvent(RBTree& beachfront, voronoiEvent currEvent);

void addCircleEvent();

void removeCircleEvent();