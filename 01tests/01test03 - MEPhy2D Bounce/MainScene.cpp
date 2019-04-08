// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#include <MainScene.h>
#include <me/render/Mesh.h>
#include <me/factory/PixelShaderFactories.h>
#include <me/factory/VertexShaderFactory.h>
#include <me/object/component/BBoxRendererComponent.h>
#include <me/object/component/CameraComponent.h>
#include <me/phy/PhySceneComponent.h>
#include <unify/Parameters.h>

using namespace me;
using namespace render;
using namespace scene;

MainScene::MainScene( me::game::Game * gameInstance )
	:Scene( gameInstance, "main" )
{	
}

void MainScene::OnStart()
{
	Effect::ptr color3DEffect = GetManager< Effect >()->Add( "color3d", unify::Path( "EffectColor.me_effect" ) );
	Effect::ptr textured3DEffect = GetManager< Effect >()->Add( "color3d", unify::Path( "EffectTextured.me_effect" ) );

	// Add an object to act as a camera...
	object::Object * camera = GetObjectAllocator()->NewObject( "camera" );
	camera->GetFrame().SetPosition( unify::V3< float >( 0, 5, -17 ) );
	camera->GetFrame().LookAt( unify::V3< float >( 0, 0, 0 ) );

	// Add a camera component to the camera object
	auto * cameraComponent = new object::component::CameraComponent();
	cameraComponent->SetProjection( unify::MatrixPerspectiveFovLH( 3.141592653589f / 4.0f, 800 / 600, 1, 1000 ) );
	camera->AddComponent( object::component::IObjectComponent::ptr( cameraComponent ) );

	auto createObject = [&]( float x, float y, float z, Geometry::ptr geometry )->me::object::Object*
	{
		static int objectIndex = 0;
		std::string objectName = "object " + unify::Cast< std::string >( objectIndex++ );
		auto object = GetObjectAllocator()->NewObject( objectName );
		object->GetFrame().SetPosition( unify::V3< float >( x, y, z ) );
		AddGeometryComponent( object, geometry );
		return object;
	};

	// Create objects...
	Geometry::ptr meshGround;
	Geometry::ptr meshCube;
	Geometry::ptr meshSphere;

	auto shapeCreator = GetManager< Geometry >()->GetFactory( "me_shape" );

	{
		using namespace unify;
		Parameters parameters{
			{ "type", (std::string)"box" },
			{ "effect", color3DEffect },
			{ "size3", Size3< float >( 10.0f, 1.0f, 10.0f ) },
			{ "diffuses", std::vector< Color >{
			ColorRed(), ColorGreen(), ColorBlue(), ColorYellow(), ColorCyan(), ColorMagenta()
		} },
		};

		meshGround = shapeCreator->Produce( parameters );
	}

	{
		using namespace unify;
		Parameters parameters{
			{ "type", (std::string)"box" },
			{ "effect", color3DEffect },
			{ "size3", Size3< float >( 1.0f, 1.0f, 1.0f ) },
			{ "diffuses", std::vector< Color >{
			ColorRed(), ColorGreen(), ColorBlue(), ColorYellow(), ColorCyan(), ColorMagenta()
		} },
		};

		meshCube = shapeCreator->Produce( parameters );
	}

	{
		using namespace unify;
		Parameters parameters{
			{ "type", (std::string)"sphere" },
			{ "effect", color3DEffect },
			{ "radius", 0.5f },
			{ "diffuse", ColorRed()
			} };

		meshSphere = shapeCreator->Produce( parameters );
	}

	// Add objects...
	auto groundObject = createObject( 0, -1, 0, meshGround );
	auto cube1Object = createObject( -5.0f, 0, 0, meshCube );
	auto cube2Object = createObject( 5.0f, 0, 0, meshCube );
	auto sphereObject = createObject( 0.0f, 0, 0, meshSphere );

	auto physicsComponent = GetGame()->GetComponent( "MEPhy2D" );

	// Create physics scene...
	//auto physicsSceneComponent = GetComponentT< mephy2d::SceneComponent >();
	auto physicsSceneComponent = GetComponent("MEPhy2DSceneComponenet" );
	if( !physicsSceneComponent )
	{
		/*
		physicsSceneComponent = new me::phy::PhySceneComponent( GetGame()->GetOS() );
		AddComponent( me::scene::ISceneComponent::ptr( physicsSceneComponent ) );
		
		auto ground = physicsSceneComponent->AddEntity( groundObject );
		auto cube1 = physicsSceneComponent->AddEntity( cube1Object );
		auto cube2 = physicsSceneComponent->AddEntity( cube2Object );
		auto sphere = physicsSceneComponent->AddEntity( sphereObject );

		ground->AttachEntityOn( cube1 );
		ground->AttachEntityOn( cube2 );
		ground->AttachEntityOn( sphere );
		*/
	}
}

void MainScene::OnUpdate( const UpdateParams & params )
{
	// Use of camera controls to simplify camera movement...
	object::Object * camera = FindObject( "camera" );
	

	camera->GetFrame().Orbit( unify::V3< float >( 0, 0, 0 ), unify::V2< float >( 1, 0 ), unify::AngleInRadians( params.GetDelta().GetSeconds() ) );
	camera->GetFrame().LookAt( unify::V3< float >( 0, 0, 0 ), unify::V3< float >( 0, 1, 0 ) );
}
