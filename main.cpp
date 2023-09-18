#include <SDL2/SDL.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <cmath>
#include <complex>
#include <cstdlib>
#include <fmt/core.h>
#include <fmt/format.h>
#include <iostream>

#define NO_ERROR (0)

const static int w = 1200;
const static int h = 960;

int init_SDL(SDL_Window *&window, SDL_Renderer *&renderer) {
  if (SDL_Init(SDL_INIT_EVERYTHING) < NO_ERROR) {
    fmt::print("failed to init sdl, {}", SDL_GetError());
    return -1;
  }

  window = SDL_CreateWindow("First window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, 0);
  if (!window) {
    fmt::print("failed to create window, {}", SDL_GetError());
    return -1;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    fmt::print("failed to create renderer, {}", SDL_GetError());
    return -1;
  }
  return 0;
}

int is_in_set(std::complex<double> c) {
  std::complex<double> z{0, 0};
  for (int i = 0; i < 250; i++) {
    z = std::pow(z, 2) + c;
    if (std::norm(z) > 10) {
      return i;
    }
  }
  return 0;
}

int main() {
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;

  if (init_SDL(window, renderer) < NO_ERROR) {
    exit(-1);
  }

  std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

  for (double x = 0; x < 1.0; x += 0.001) {
    for (double y = 0; y < 1.0; y += 0.001) {
      double px = std::lerp(-2.0, 2.0, x);
      double py = std::lerp(-2.0, 2.0, y);

      int iter = is_in_set(std::complex(px, py));
      if (iter == 0) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawPointF(renderer, x * 1000, y * 1000);
      } else {
        SDL_SetRenderDrawColor(renderer,
                               3 * iter % 255,
                               3 * iter % 255,
                               3 * iter % 255, 255);
        SDL_RenderDrawPointF(renderer, x * 1000, y * 1000);
      }
    }
  }

  std::chrono::steady_clock::time_point stopTime = std::chrono::steady_clock::now();
  double dt = std::chrono::duration_cast<std::chrono::duration<double>>(stopTime - startTime).count();

  SDL_RenderPresent(renderer);
  bool is_running = true;
  SDL_Event event;
  while (is_running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        is_running = false;
      }
    }
    SDL_Delay(16);
  }

  fmt::print("time taken: {} seconds", dt);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
