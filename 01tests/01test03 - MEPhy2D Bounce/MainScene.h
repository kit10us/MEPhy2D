// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#pragma once

#include <me/scene/Scene.h>
#include <me/render/RenderMethod.h>
#include <me/render/VertexUtil.h>

class MainScene : public me::scene::Scene
{
public:
	MainScene( me::game::Game * gameInstance );

	unify::Result<> OnStart() override;
	unify::Result<> OnUpdate( const me::UpdateParams & params ) override;
};
