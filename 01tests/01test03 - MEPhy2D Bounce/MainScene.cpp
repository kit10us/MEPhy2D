// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#include <MainScene.h>
#include <me/render/Mesh.h>
#include <me/factory/PixelShaderFactories.h>
#include <me/factory/VertexShaderFactory.h>
#include <me/object/component/BBoxRendererComponent.h>
#include <me/object/component/CameraComponent.h>
#include <sg/ShapeCreators.h>

#include <me/phy/PhySceneComponent.h>

using namespace me;
using namespace render;
using namespace scene;

MainScene::MainScene( me::game::Game * gameInstance )
	:Scene( gameInstance, "main" )
{	
}

void MainScene::OnStart()
{
	Effect::ptr color3DEffect = GetManager< Effect >()->Add( "color3d", unify::Path( "EffectColor.effect" ) );
	Effect::ptr textured3DEffect = GetManager< Effect >()->Add( "color3d", unify::Path( "EffectTextured.effect" ) );

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

	{
		sg::CubeParameters cubeParameters;
		cubeParameters.SetEffect( color3DEffect );
		cubeParameters.SetSize( unify::Size3< float >( 10, 1, 10 ) );
		cubeParameters.SetDiffuseFaces( unify::ColorRed(), unify::ColorGreen(), unify::ColorBlue(), unify::ColorYellow(), unify::ColorCyan(), unify::ColorMagenta() );
		meshGround = sg::CreateShape( GetOS()->GetRenderer( 0 ), cubeParameters );
	}

	{
		sg::CubeParameters cubeParameters;
		cubeParameters.SetEffect( color3DEffect );
		cubeParameters.SetSize( unify::Size3< float >( 1, 1, 1 ) );
		cubeParameters.SetDiffuseFaces( unify::ColorRed(), unify::ColorGreen(), unify::ColorBlue(), unify::ColorYellow(), unify::ColorCyan(), unify::ColorMagenta() );
		meshCube = sg::CreateShape( GetOS()->GetRenderer( 0 ), cubeParameters );
	}

	{

		sg::SphereParameters sphereParameters;
		sphereParameters.SetEffect( color3DEffect );
		sphereParameters.SetRadius( 0.5f );
		sphereParameters.SetDiffuse( unify::ColorRed() );
		meshSphere = sg::CreateShape( GetOS()->GetRenderer( 0 ), sphereParameters );
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
