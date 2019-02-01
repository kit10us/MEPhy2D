// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#include <mephy2d/SceneManagerComponent.h>
#include <mephy2d/SceneComponent.h>
#include <mephy2d/Entity.h>
#include <me/game/Game.h>

using namespace mephy2d;

char* SceneManagerComponent::Name()
{
	return "MEPhy2DSceneManagerComponent";
}

SceneManagerComponent::SceneManagerComponent()
	: me::scene::component::SceneManagerComponent( "MEPhy2DSceneManagerComponent" )
{
}

SceneManagerComponent::~SceneManagerComponent()
{																	 
}

me::scene::component::ISceneComponent::ptr SceneManagerComponent::CreateSceneComponent( std::string type )
{
	if ( unify::string::StringIs( type, "MEPhy2DSceneComponent" ) )
	{
		return me::scene::component::ISceneComponent::ptr{ new SceneComponent( GetSceneManager()->GetGame()->GetOS() ) }; 
	}

	return me::scene::component::SceneManagerComponent::CreateSceneComponent( type );
}
