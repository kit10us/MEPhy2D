// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#pragma once 

#include <MEPhy2D.h>
#include <me/phy/Entity.h>
#include <me/scene/component/SceneManagerComponent.h>

namespace mephy2d
{
	/// </summary>
	/// A phy2d scene manager component used to create physics scene components.
	/// <summary>
	class SceneManagerComponent : public me::scene::component::SceneManagerComponent
	{
	public:
		static char* Name();

		SceneManagerComponent();
		~SceneManagerComponent();

	private: // ISceneManagerComponent
		me::scene::component::ISceneComponent::ptr CreateSceneComponent( std::string type ) override;

	private:
		std::list< me::phy::Entity* > m_entities;
	};
}
