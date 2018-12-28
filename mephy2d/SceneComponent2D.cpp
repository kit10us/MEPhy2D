// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#include <mephy2d/SceneComponent2D.h>
#include <mephy2d/Entity.h>

using namespace mephy2d;

MEPHY2D_API char* SceneComponent::Name()
{
	return "MEPhy2DSceneComponent";
}

MEPHY2D_API SceneComponent::SceneComponent( me::os::IOS * os )
	: me::phy::PhySceneComponent( os, "MEPhy2DSceneComponent" )
{
}

SceneComponent::~SceneComponent()
{																	 
}

me::phy::Entity* SceneComponent::AddEntity( me::object::Object * object )
{
	auto * entity = new mephy2d::Entity();
	m_entities.push_back( entity );
	return entity;
}

void SceneComponent::OnEarlyUpdate( const me::UpdateParams & params )
{
	for( auto * entity : m_entities )
	{
		entity->UpdateEntities();
	}
}

void SceneComponent::OnLateUpdate( const me::UpdateParams & params )
{
}
