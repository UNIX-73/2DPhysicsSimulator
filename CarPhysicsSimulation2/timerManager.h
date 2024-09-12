#pragma once

#include <chrono>
#include <functional> // Necesario para std::function

class TimerManager
{
public:
    // Constructor que inicializa los tiempos de step de física y frames por segundo.
    TimerManager(double stepsPerSecond, double fps);

    // Actualiza el temporizador.
    void UpdateTimer();

    // Registra una función de callback que se ejecutará en cada step de física.
    void SetStepFunction(const std::function<void()>& stepFunction);
    void SetGraphicFunction(const std::function<void()>& graphicFunction);

private:
    std::chrono::nanoseconds stepDuration;  // Duración de un step de física en nanosegundos.
    std::chrono::nanoseconds elapsed;       // Duración del tiempo transcurrido desde el último step.
    std::chrono::time_point<std::chrono::high_resolution_clock> start; // Tiempo del último step de física.
    std::chrono::time_point<std::chrono::high_resolution_clock> end;   // Tiempo del último frame mostrado.
    std::chrono::time_point<std::chrono::high_resolution_clock> current; // Tiempo actual.

    int framesPerStep;  // Número de steps por frame.
    int stepCount;      // Contador de steps.

    std::function<void()> stepFunction; // Función callback que se ejecuta en cada step de física.
    std::function<void()> graphicFunction;
};
