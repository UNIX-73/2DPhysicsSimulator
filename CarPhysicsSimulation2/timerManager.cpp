#include "TimerManager.h"
#include <iostream>
#include <thread>

// Constructor que inicializa los tiempos de step de f�sica y frames por segundo.
TimerManager::TimerManager(unsigned int substeps, double fps)
{
    // Calculamos la duraci�n de cada frame (intervalo de tiempo entre frames gr�ficos).
    frameDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(1.0 / fps));

    // Calculamos los substeps que ocurren por cada frame.
    substepsPerFrame = substeps;

    // Inicializamos los tiempos de inicio.
    start = std::chrono::high_resolution_clock::now();
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::nanoseconds(0);
    this->fps = fps;
}

// M�todo para actualizar el temporizador.
void TimerManager::UpdateTimer()
{
    // Calculamos el tiempo actual.
    current = std::chrono::high_resolution_clock::now();

    // Calculamos el tiempo transcurrido desde el �ltimo frame.
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(current - end);

    // Si ha pasado suficiente tiempo para actualizar el frame.
    if (elapsed >= frameDuration)
    {
        // Ajustamos el tiempo de 'end' para reflejar el tiempo actual.
        end += frameDuration;

        // Ejecutamos la funci�n gr�fica si est� configurada.
        if (graphicFunction)
        {
            graphicFunction();
        }

        // Medir el tiempo antes de ejecutar los substeps de f�sica.
        auto physicsStart = std::chrono::high_resolution_clock::now();

        // Ejecutamos la funci�n de substeps (steps de f�sica).
        if (stepFunction)
        {
            for (int i = 0; i < substepsPerFrame; i++)  // Ejecutamos los substeps.
            {
                stepFunction();
            }
        }

        // Medir el tiempo despu�s de ejecutar los substeps de f�sica.
        auto physicsEnd = std::chrono::high_resolution_clock::now();

        // Calcular el tiempo que tom� la simulaci�n f�sica en este frame.
        auto physicsFrameTime = std::chrono::duration_cast<std::chrono::nanoseconds>(physicsEnd - physicsStart);

        // Acumulamos el tiempo total de la f�sica durante este frame.
        physicsDuration += physicsFrameTime;

        // Acumulamos el tiempo total transcurrido.
        totalElapsedTime += frameDuration;

        // Verificamos si ha pasado un segundo (1e9 nanosegundos).
        if (totalElapsedTime >= std::chrono::nanoseconds(1000000000))
        {
            // Calculamos el porcentaje de tiempo que tom� la f�sica durante este segundo.
            double physicsTimePercentage = (static_cast<double>(physicsDuration.count()) / totalElapsedTime.count()) * 100.0;

            // Printeamos el porcentaje de tiempo dedicado a la simulaci�n f�sica.
            std::cout << "Physics Time: " << physicsTimePercentage << "%" << std::endl;

            // Reseteamos los acumuladores.
            totalElapsedTime = std::chrono::nanoseconds(0);
            physicsDuration = std::chrono::nanoseconds(0);
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
