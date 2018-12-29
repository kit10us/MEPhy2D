// MELuaDLL.cpp : Defines the exported functions for the DLL application.
//

#include <MEPhy2D.h>
#include <mephy2d/GameComponent.h>
#include <me/game/IGame.h>
#include <memory.h>

void Deleter2D( mephy2d::GameComponent * component )
{
	delete component;
}

extern "C" MEPHY2D_API bool MELoader( me::game::IGame * gameInstance, const qxml::Element * element);

MEPHY2D_API bool MELoader( me::game::IGame * gameInstance, const qxml::Element * element )
{
	mephy2d::GameComponent * component = new mephy2d::GameComponent();
	gameInstance->AddComponent( me::game::component::IGameComponent::ptr( component, Deleter2D ) );

	return true;
}

