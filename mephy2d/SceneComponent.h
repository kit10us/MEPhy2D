// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#pragma once 

#include <MEPhy2D.h>
#include <me/phy/Entity.h>
#include <me/phy/PhySceneComponent.h>

namespace mephy2d
{
	class SceneComponent : public me::phy::PhySceneComponent
	{
	public:
		static char* Name();

		SceneComponent( me::os::IOS * os );
		~SceneComponent();

		me::phy::Entity* AddEntity( me::object::Object * object );

	public: // ISceneComponent...
		void OnEarlyUpdate( const me::UpdateParams & params ) override;
		void OnLateUpdate( const me::UpdateParams & params ) override;

	private:
		std::list< me::phy::Entity* > m_entities;
	};
}
