#include <SDL.h>
#include <SDL_image.h>
#include <vector>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SPRITE_COUNT = 5;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
std::vector<SDL_Texture*> sprites;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }

    window = SDL_CreateWindow("Sprite Animation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        return false;
    }

    // Initialize SDL_image
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        return false;
    }

    return true;
}

bool loadSprites() {
    for (int i = 1; i <= SPRITE_COUNT; i++) {
        std::string path = std::to_string(i) + ".png";
        SDL_Surface* loadedSurface = IMG_Load(path.c_str());
        if (!loadedSurface) {
            return false;
        }

        SDL_Texture* loadedTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        SDL_FreeSurface(loadedSurface);
        if (!loadedTexture) {
            return false;
        }

        sprites.push_back(loadedTexture);
    }

    return true;
}

void close() {
    for (SDL_Texture* sprite : sprites) {
        SDL_DestroyTexture(sprite);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* args[]) {
    if (!init()) {
        return 1;
    }

    if (!loadSprites()) {
        return 1;
    }

    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        // Rendering all sprites in different positions for demonstration
        for (int i = 0; i < SPRITE_COUNT; i++) {
            int x = 50 + i * 150;
            int y = 200;
            SDL_Rect renderQuad = { x, y, 100, 100 };  // Assuming each sprite is 100x100 pixels
            SDL_RenderCopy(renderer, sprites[i], NULL, &renderQuad);
        }

        SDL_RenderPresent(renderer);
    }

    close();

    return 0;
}
