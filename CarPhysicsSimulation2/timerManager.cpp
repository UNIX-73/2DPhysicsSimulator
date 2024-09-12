#include "TimerManager.h"
#include <iostream>
#include <thread>

// Constructor que inicializa los tiempos de step de física y frames por segundo.
TimerManager::TimerManager(double stepsPerSecond, double fps)
{
    // Calculamos la duración de cada step de física usando chrono.
    stepDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(1.0 / stepsPerSecond));

    // Inicializamos los tiempos de inicio.
    start = std::chrono::high_resolution_clock::now();
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::nanoseconds(0);

    // Calculamos cuántos steps de física deben ocurrir antes de actualizar el frame.
    framesPerStep = static_cast<int>(fps / stepsPerSecond);
    if (framesPerStep <= 0) {
        framesPerStep = 1;  // Aseguramos al menos un frame por step.
    }

    stepCount = 0; // Inicializamos el contador de steps.
}

// Método para actualizar el temporizador.
void TimerManager::UpdateTimer()
{
    // Calculamos el tiempo actual.
    current = std::chrono::high_resolution_clock::now();

    // Calculamos el tiempo transcurrido desde el último step de física.
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(current - end);

    // Si ha pasado suficiente tiempo para ejecutar un nuevo step de física.
    if (elapsed >= stepDuration)
    {
        // Ajuste del tiempo de 'end' para mayor precisión.
        end += stepDuration;

        // Imprimir el tiempo de desfase corregido (convertimos a duración).

        stepCount++;   // Incrementamos el contador de steps.

        // Ejecutamos la función callback del step de física.
        if (stepFunction)
        {
            stepFunction();
        }

        // Si ha alcanzado el número de steps necesarios para mostrar un nuevo frame.
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

// Método para registrar una función de callback para los steps de física.
void TimerManager::SetStepFunction(const std::function<void()>& stepFunction)
{
    this->stepFunction = stepFunction;
}

void TimerManager::SetGraphicFunction(const std::function<void()>& graphicFunction)
{
    this->graphicFunction = graphicFunction;
}
