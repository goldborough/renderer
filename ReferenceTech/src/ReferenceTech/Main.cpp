#define WIN32_LEAN_AND_MEAN
#define VC_LEANMEAN


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <windows.h>

#include <EngineUtilities/Util.h>

#include "Control/SimulationController.h"

// settings

MSG msg;

void main()
{
    DebugPrint("Main");
    
    SimulationController simulationController;
    SimulationConfig config;

    simulationController.Run(&config);
    
    simulationController.Shutdown();
}

/*
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{

	return 0;
}

*/

