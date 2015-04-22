#include "NodeCamera.h"

#include "../Components/PlayerReference.h"
#include "../Components/Position.h"


using namespace TeaParty::Archetype;
using aunteater::ArchetypeTypeSet;
using namespace TeaParty;

const ArchetypeTypeSet NodeCamera::gComponentTypes = {
    &typeid(Component::Position),
    &typeid(Component::PlayerReference)
};


