#ifndef _TeaParty_Component_Physics_h
#define _TeaParty_Component_Physics_h

#include "../Vec2.h"

#include <aunteater/Component.h>
#include <vector>

namespace TeaParty { namespace Component {
class Physics : public aunteater::Component
{
public:
	Physics() :
		aIsOnGround(true)
	{}

	void addForce(Vec2 aForce)
	{
		mForces.push_back(aForce);
	}

	bool aIsOnGround;
	std::vector<Vec2> mForces;
private:
	COMP_CLONE(Physics)
};
}}
#endif  // #ifdef