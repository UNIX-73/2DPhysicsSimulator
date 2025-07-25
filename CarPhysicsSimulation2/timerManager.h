#pragma once

#include <chrono>
#include <functional> // Necesario para std::function

class TimerManager
{
public:
    // Constructor que inicializa los tiempos de step de f�sica y frames por segundo.
    TimerManager(unsigned int substeps, double fps);

    // Actualiza el temporizador.
    void UpdateTimer();

    // Registra una funci�n de callback que se ejecutar� en cada step de f�sica.
    void SetStepFunction(const std::function<void()>& stepFunction);
    void SetGraphicFunction(const std::function<void()>& graphicFunction);

private:
    unsigned int substepsPerFrame = 1;

    std::chrono::nanoseconds frameDuration;  // Duraci�n de un step de f�sica en nanosegundos.
    std::chrono::nanoseconds elapsed;       // Duraci�n del tiempo transcurrido desde el �ltimo step.
    std::chrono::time_point<std::chrono::high_resolution_clock> start; // Tiempo del �ltimo step de f�sica.
    std::chrono::time_point<std::chrono::high_resolution_clock> end;   // Tiempo del �ltimo frame mostrado.
    std::chrono::time_point<std::chrono::high_resolution_clock> current; // Tiempo actual.

    //debug
    int frameCount = 0;      // Contador de steps.
    double fps = 0.0;
    std::chrono::nanoseconds totalElapsedTime = std::chrono::nanoseconds(0);
    std::chrono::nanoseconds physicsDuration = std::chrono::nanoseconds(0);

    std::function<void()> stepFunction; // Funci�n callback que se ejecuta en cada step de f�sica.
    std::function<void()> graphicFunction;
};
