#include "PointCounter.h"

#include "../Archetypes/Colliders.h"

#include "../Components/BallsPoint.h"
#include "../Components/Pendular.h"
#include "../Components/Position.h"

#include "../globals.h"

using namespace TeaParty;
using namespace Archetype;
using namespace System;

struct NodePointCounter
{
    static const aunteater::ArchetypeTypeSet gComponentTypes;
};

const aunteater::ArchetypeTypeSet NodePointCounter::gComponentTypes = {
    &typeid(Component::Pendular),
    &typeid(Component::Position)
};

#define PERFECT_TIME 3.
#define DEAD_ZONE 10.

void PointCounter::addedToEngine(aunteater::Engine &aEngine)
{
	mNodeList = &aEngine.getNodes<NodePointCounter>();
}

double resultingX(double x)
{
    x -= X_ROOM/2;
    x = std::abs(x);

    if(x <= DEAD_ZONE)
    {
        return 1;
    }

    return x;
}

void PointCounter::update(double time)
{
	for (aunteater::Node node : *mNodeList)
	{
        double & x = node.get<Component::Position>().coords.x;
        aunteater::weak_entity & ballsDisplay = node.get<Component::Pendular>().pointCounter;


        ballsDisplay->get<Component::BallsPoint>()->point += std::abs(MAX_POINT / PERFECT_TIME / 60. / resultingX(x)) ;
	}
}