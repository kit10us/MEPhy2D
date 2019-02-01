// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#include <MEWinMain.h>
#include <me/game/Game.h>
#include <MainScene.h>

using namespace me;

/*
#ifdef _DEBUG
#pragma comment( lib, "../../../extensions/Debug/MEPhy2D.lib" )
#else
#pragma comment( lib, "../../../extensions/Release/MEPhy2D.lib" )
#endif
*/

class MyGame : public game::Game
{
public:
	MyGame()
		: Game( "Main", unify::Path( "mephy2d.xml" ) )
	{
	}

	void AddScenes( scene::SceneManager * sceneManager ) override
	{
		sceneManager->AddScene( me::scene::IScene::ptr( new MainScene( this ) ) );
	}
} myGame;

RegisterGame( myGame );
