// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#include <mephy2d/Entity.h>

using namespace mephy2d;

Entity::Entity()
	: me::phy::Entity( "MePhy2DEntity", true, false )
{
}

Entity::Entity( Entity & entity )
	: me::phy::Entity( entity )
{
}

Entity::~Entity()
{
}

void Entity::UpdateEntities()
{
	for( auto * entity : m_attachedEntities )
	{
		entity->MoveTo( unify::V2< float >{ 0, 0 } );
	}
}

void Entity::MoveTo( unify::V3< float > position )
{
	m_object->GetFrame().SetPosition( position );
}

void Entity::AttachEntityOn( Entity * entity )
{
	m_attachedEntities.push_back( entity );
}

void Entity::OnAttach( me::object::Object * object )
{
	m_object = object;
}

void Entity::OnDetach( me::object::Object * objecct )
{
	m_object = nullptr;
}

me::object::component::IObjectComponent::ptr Entity::Duplicate()
{
	auto duplicate = new Entity( *this );
	return me::object::component::IObjectComponent::ptr( duplicate );
}
