#include "main.h"
#include "simulationManager.h"
#include "simulationState.h"
#include <iostream>



int main()
{
    SimulationManager simulationManager(&RUN, 900, 900, 6000.0, 240.0);

    SimulationState simulationState(simulationManager); //Aqu� se escribe el c�digo
    
    while (RUN)
    {
        simulationManager.Update();
    }

    return 0;
}



