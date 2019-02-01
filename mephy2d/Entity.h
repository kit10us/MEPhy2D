// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#pragma once

#include <MEPhy2D.h>
#include <me/phy/Entity.h>

namespace mephy2d
{
	class Entity : public me::phy::Entity
	{
	public:
		Entity();
		Entity( Entity & entity );
		virtual ~Entity();

		/// <summary>
		///
		/// </summary>
		void AttachEntityOn( Entity * entity );

		/// <summary>
		///
		/// </summary>
		void UpdateEntities();

		/// <summary>
		///
		/// </summary>
		void MoveTo( unify::V3< float > position );

	public: // ObjectComponent...
		void OnAttach( me::object::Object * object ) override;
		void OnDetach( me::object::Object * objecct ) override;
		me::object::component::IObjectComponent::ptr Duplicate() override;

	public: // IComponent...

	private:
		me::object::Object * m_object;
		std::list< Entity * > m_attachedEntities;
	};
}
