#include "main.h"
#include "simulationManager.h"
#include "simulationState.h"
#include <iostream>



int main()
{
    SimulationManager simulationManager(&RUN, 900, 900, 300, 240);

    SimulationState simulationState(simulationManager); //Aqu� se escribe el c�digo
    
    while (RUN)
    {
        simulationManager.Update();
    }

    return 0;
}



