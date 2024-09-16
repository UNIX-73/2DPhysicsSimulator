#include "TimerManager.h"
#include <iostream>
#include <thread>

// Constructor que inicializa los tiempos de step de física y frames por segundo.
TimerManager::TimerManager(unsigned int substeps, double fps)
{
    // Calculamos la duración de cada frame (intervalo de tiempo entre frames gráficos).
    frameDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(1.0 / fps));

    // Calculamos los substeps que ocurren por cada frame.
    substepsPerFrame = substeps;

    // Inicializamos los tiempos de inicio.
    start = std::chrono::high_resolution_clock::now();
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::nanoseconds(0);
    this->fps = fps;
}

// Método para actualizar el temporizador.
void TimerManager::UpdateTimer()
{
    // Calculamos el tiempo actual.
    current = std::chrono::high_resolution_clock::now();

    // Calculamos el tiempo transcurrido desde el último frame.
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(current - end);

    // Si ha pasado suficiente tiempo para actualizar el frame.
    if (elapsed >= frameDuration)
    {
        // Ajustamos el tiempo de 'end' para reflejar el tiempo actual.
        end += frameDuration;

        // Ejecutamos la función gráfica si está configurada.
        if (graphicFunction)
        {
            graphicFunction();
        }

        // Medir el tiempo antes de ejecutar los substeps de física.
        auto physicsStart = std::chrono::high_resolution_clock::now();

        // Ejecutamos la función de substeps (steps de física).
        if (stepFunction)
        {
            for (int i = 0; i < substepsPerFrame; i++)  // Ejecutamos los substeps.
            {
                stepFunction();
            }
        }

        // Medir el tiempo después de ejecutar los substeps de física.
        auto physicsEnd = std::chrono::high_resolution_clock::now();

        // Calcular el tiempo que tomó la simulación física en este frame.
        auto physicsFrameTime = std::chrono::duration_cast<std::chrono::nanoseconds>(physicsEnd - physicsStart);

        // Acumulamos el tiempo total de la física durante este frame.
        physicsDuration += physicsFrameTime;

        // Acumulamos el tiempo total transcurrido.
        totalElapsedTime += frameDuration;

        // Verificamos si ha pasado un segundo (1e9 nanosegundos).
        if (totalElapsedTime >= std::chrono::nanoseconds(1000000000))
        {
            // Calculamos el porcentaje de tiempo que tomó la física durante este segundo.
            double physicsTimePercentage = (static_cast<double>(physicsDuration.count()) / totalElapsedTime.count()) * 100.0;

            // Printeamos el porcentaje de tiempo dedicado a la simulación física.
            std::cout << "Physics Time: " << physicsTimePercentage << "%" << std::endl;

            // Reseteamos los acumuladores.
            totalElapsedTime = std::chrono::nanoseconds(0);
            physicsDuration = std::chrono::nanoseconds(0);
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
