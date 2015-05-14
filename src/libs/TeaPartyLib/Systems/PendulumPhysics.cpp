#include "PendulumPhysics.h"

#include "../Archetypes/NodeCamera.h"

#include "../Components/GamePhase.h"
#include "../Components/Pendular.h"
#include "../Components/PlayerReference.h"
#include "../Components/Position.h"
#include "../Components/Physics.h"
#include "../Components/Speed.h"

#include "../globals.h"

#include <aunteater/Engine.h>


using namespace TeaParty;
using namespace System;
using namespace Archetype;
using aunteater::ArchetypeTypeSet;
using aunteater::Engine;

struct NodePendulum
{
    static const aunteater::ArchetypeTypeSet gComponentTypes;
};

const ArchetypeTypeSet NodePendulum::gComponentTypes = {
    &typeid(Component::Pendular),
    &typeid(Component::Physics),
    &typeid(Component::PivotReference)
};

void PendulumPhysics::addedToEngine(Engine &aEngine)
{
    mPendulums = &aEngine.getNodes<NodePendulum>();
}

void PendulumPhysics::update(double aTime)
{
    for (aunteater::Node &pendulum : *mPendulums)
    {
        constexpr double frameTime = 1/60.;

        aunteater::weak_entity pivot = pendulum.get<Component::PivotReference>().entity;
        double horizontalSpeed = pivot->get<Component::Speed>()->vX;
        double & previousPivotSpeed = pendulum.get<Component::Pendular>().pivotPreviousSpeed.x;
        double horizontalAccel = (horizontalSpeed - previousPivotSpeed) / frameTime;

        double & thetaSpeed = pendulum.get<Component::Pendular>().thetaSpeed;
        double & theta = pendulum.get<Component::Pendular>().theta;
        double L = pendulum.get<Component::Pendular>().length;
        double b = pendulum.get<Component::Pendular>().damping;
        double m = pendulum.get<Component::Physics>().mass;

        double thetaAccel = -std::cos(theta)/L*horizontalAccel - b/(m*std::pow(L, 2)) * thetaSpeed - 9.8/L * std::sin(theta);

        // update previous speed, theta speed, theta
        previousPivotSpeed = horizontalSpeed;
        thetaSpeed += thetaAccel * frameTime;
        theta += thetaSpeed * frameTime;

        pendulum.get<Component::Physics>().mForces.push_back({-m*L*std::sin(thetaAccel), 0.});
    }
}