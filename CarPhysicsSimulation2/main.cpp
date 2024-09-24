#include "main.h"
#include "simulationManager.h"
#include "simulationState.h"
#include <iostream>



int main()
{
    SimulationManager simulationManager(&RUN, 900, 900, 5, 240);

    SimulationState simulationState(simulationManager); //Aquí se escribe el código (pasa callbacks desde el manager)
    
    while (RUN)
    {
        simulationManager.Update();
    }

    return 0;
}



