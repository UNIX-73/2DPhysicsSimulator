#include "TimerManager.h"
#include <iostream>
#include <thread>

// Constructor que inicializa los tiempos de step de f�sica y frames por segundo.
TimerManager::TimerManager(double stepsPerSecond, double fps)
{
    // Calculamos la duraci�n de cada step de f�sica usando chrono.
    stepDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(1.0 / stepsPerSecond));

    // Inicializamos los tiempos de inicio.
    start = std::chrono::high_resolution_clock::now();
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::nanoseconds(0);

    // Calculamos cu�ntos steps de f�sica deben ocurrir antes de actualizar el frame.
    framesPerStep = static_cast<int>(fps / stepsPerSecond);
    if (framesPerStep <= 0) {
        framesPerStep = 1;  // Aseguramos al menos un frame por step.
    }

    stepCount = 0; // Inicializamos el contador de steps.
}

// M�todo para actualizar el temporizador.
void TimerManager::UpdateTimer()
{
    // Calculamos el tiempo actual.
    current = std::chrono::high_resolution_clock::now();

    // Calculamos el tiempo transcurrido desde el �ltimo step de f�sica.
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(current - end);

    // Si ha pasado suficiente tiempo para ejecutar un nuevo step de f�sica.
    if (elapsed >= stepDuration)
    {
        // Ajuste del tiempo de 'end' para mayor precisi�n.
        end += stepDuration;

        // Imprimir el tiempo de desfase corregido (convertimos a duraci�n).

        stepCount++;   // Incrementamos el contador de steps.

        // Ejecutamos la funci�n callback del step de f�sica.
        if (stepFunction)
        {
            stepFunction();
        }

        // Si ha alcanzado el n�mero de steps necesarios para mostrar un nuevo frame.
        if (stepCount >= framesPerStep)
        {
            stepCount = 0;
            
            if (graphicFunction)
            {
                graphicFunction();
            }
        }
    }
}

// M�todo para registrar una funci�n de callback para los steps de f�sica.
void TimerManager::SetStepFunction(const std::function<void()>& stepFunction)
{
    this->stepFunction = stepFunction;
}

void TimerManager::SetGraphicFunction(const std::function<void()>& graphicFunction)
{
    this->graphicFunction = graphicFunction;
}
