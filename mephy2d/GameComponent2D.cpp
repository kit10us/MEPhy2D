// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#include <mephy2d/GameComponent2D.h>
#include <me/scene/SceneManager.h>

using namespace mephy2d;

char* GameComponent::Name()
{
	return "MEPhy2D";
}

GameComponent::GameComponent()
	: me::game::GameComponent( Name() )
{
}

GameComponent::~GameComponent()
{																	 
}