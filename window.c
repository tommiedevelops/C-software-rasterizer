#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#define WIDTH 800
#define HEIGHT 600

int main() { 
	// Initialise SDL
	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("SDL_Init Error: %s", SDL_GetError());
		return 1;
	}	

	// Create window
	SDL_Window* window = SDL_CreateWindow(
		"SDL2_Pixel_Buffer",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIDTH, HEIGHT, 0	
	);

	// Create renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Create texture
	SDL_Texture* texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STREAMING,
		WIDTH, HEIGHT
	);
	
	uint32_t framebuffer[WIDTH * HEIGHT] = {0};
	framebuffer[100 + 100 * WIDTH] = 0xFF0000FF;	
	bool running = true;
	SDL_Event event;
	while(running) {
		// Event handling
		while (SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) running = false;	
		}	
		
		// Update texture with framebuffer pixels
		SDL_UpdateTexture(texture, NULL, framebuffer, WIDTH * sizeof(uint32_t));
		
		// Draw
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}
	
	// Clean Up
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
