#include <SDL.h>
#include <iostream>

int main(int argc,char* argv[]) {

    std::cout << "number args: " << argc << std::endl;
    for (int i = 0;i < argc;i++) std::cout << i << " - " << argv[i] << std::endl;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("Color",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,765,255,SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window,0,-1);

    int width,height;
    SDL_GetRendererOutputSize(renderer,&width,&height);

    unsigned char complementaire(0);
    SDL_Rect marker = {0,0,5,5};
    SDL_Rect current = {510,50,50,50};

    SDL_Rect complementaireBar = {382,200,255,10};
    SDL_Rect cursor = {382,190,30,30};

    SDL_Event event;
    do {

        bool upadte(true);

        SDL_PollEvent(&event);

        if (event.type == SDL_KEYDOWN) {

            if (event.key.keysym.sym == SDLK_RIGHT && complementaire < 255) {

                cursor.x++;
                complementaire = cursor.x-382;
                SDL_RenderClear(renderer);
                upadte = true; 

            }
            
            if (event.key.keysym.sym == SDLK_LEFT && complementaire > 0) {
                
                cursor.x--;
                complementaire = cursor.x-382;
                SDL_RenderClear(renderer);
                upadte = true; 

            }

        }

        if (event.type == SDL_MOUSEBUTTONDOWN) {

            if (event.button.button == SDL_BUTTON_LEFT) {
            
                if (event.button.x < 255 && event.button.y < 255) {

                    marker.x = event.button.x;
                    marker.y = event.button.y;
                    SDL_RenderClear(renderer);
                    upadte = true;

                }

                if (complementaireBar.x <= event.button.x && complementaireBar.y <= event.button.y && complementaireBar.x + complementaireBar.w >= event.button.x && complementaireBar.y + complementaireBar.h >= event.button.y) {

                    cursor.x = event.button.x;
                    complementaire = cursor.x-382;
                    SDL_RenderClear(renderer);
                    upadte = true; 

                }

            }

        }

        if (upadte) {

            for (unsigned int i = 0;i < 255;i++) {

                for (unsigned int j = 0;j < 255;j++) {

                    SDL_SetRenderDrawColor(renderer,i,j,complementaire,255);
                    SDL_RenderDrawPoint(renderer,i,j);

                }

            }

            upadte = false;

        }

        SDL_SetRenderDrawColor(renderer,120,120,120,255);
        SDL_RenderFillRect(renderer,&marker);

        SDL_SetRenderDrawColor(renderer,marker.x,marker.y,complementaire,255);
        SDL_RenderFillRect(renderer,&current);

        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderFillRect(renderer,&complementaireBar);

        SDL_SetRenderDrawColor(renderer,0,0,255,255);
        SDL_RenderFillRect(renderer,&cursor);

        SDL_SetRenderDrawColor(renderer,0,0,0,255);

        SDL_RenderPresent(renderer);

        //SDL_Delay(1000/60);

    } while (event.type != SDL_QUIT);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

}