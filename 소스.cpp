#define SDL_MAIN_HANDLED

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <math.h>

#define PI 3.1415926535897

SDL_Texture *loadTexture(SDL_Renderer *renderer, const char *file) {
	SDL_Surface *surface;
	SDL_Texture *texture;
	surface = SDL_LoadBMP(file);
	if (surface == NULL) {
		printf("cannot read file %s\n", file);
		return NULL;
	}
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL) {
		printf("cannot make texture\n");
	}

	SDL_FreeSurface(surface);
	return texture;
}

void drawTexture(SDL_Renderer *renderer, int x, int y, SDL_Texture *texture) {
	SDL_Rect src, dst;

	src.x = src.y = 0;
	SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);

	dst.x = x;
	dst.y = y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, texture, &src, &dst);
}

void stretchTextureEx(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Texture *texture, float angle) {
	SDL_Rect src, dst;
	SDL_Point center;

	src.x = src.y = 0;
	SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);

	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;

	center.x = w / 2;
	center.y = h / 2;

	SDL_RenderCopyEx(renderer, texture, &src, &dst, angle, &center, SDL_FLIP_NONE);
}

int main(int argc, char* argv[])
{
	int run = 1;

	SDL_Surface *surface = NULL;
	SDL_Texture *texture = NULL;
	SDL_Window *window = NULL;     //Window pointer
	SDL_Renderer *renderer = NULL; //Renderer pointer
	
	SDL_Event e;

	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		perror("SDL_Init falied\n");
		return 1;
	}

	window = SDL_CreateWindow("  ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE);  //Window Create ( TOP_name, x_position, y_position, width, height, flags )
	if (window == NULL) {
		printf("window error!");
		return 2;
	}

	if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
		printf("renderer error!");
		return 3;
	}
	
	SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);

	SDL_Texture *BG_texr;
	BG_texr = loadTexture(renderer, "bmps/BG.bmp");
	int LBorder = 25;
	int RBorder = 750;
	int UBorder = 30;
	int DBorder = 555;

	SDL_Texture *RedCar_texr;
	int R_on = 1;
	double RC_x = 200;
	double RC_y = 300;
	double RC_angle = 0;
	double RC_rad = 0;
	double RC_speed = 0;
	SDL_Texture *Rlaser_texr;
	double Rlaser_x = 0;
	double Rlaser_y = -5;
	double Rlaser_rad = 0;
	double Rlaser_angle = 0;
	double Rlaser_cool = 0;
	SDL_Texture *Rexp_texr;
	double Rexp_x = 0;
	double Rexp_y = -5;

	SDL_Texture *GreenCar_texr;
	int G_on = 1;
	double GC_x = 600;
	double GC_y = 300;
	double GC_angle = 180;
	double GC_rad = 0;
	double GC_speed = 0;
	SDL_Texture *Glaser_texr;
	double Glaser_x = 0;
	double Glaser_y = -5;
	double Glaser_rad = 0;
	double Glaser_angle = 0;
	double Glaser_cool = 0;
	SDL_Texture *Gexp_texr;
	double Gexp_x = 0;
	double Gexp_y = -5;

	surface = SDL_LoadBMP("bmps/red.bmp");
	if (SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF)) != 0) printf("color key error");
	RedCar_texr = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	surface = SDL_LoadBMP("bmps/Rexp.bmp");
	if (SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF)) != 0) printf("color key error");
	Rexp_texr = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	Rlaser_texr = loadTexture(renderer, "bmps/Rlaser.bmp");

	surface = SDL_LoadBMP("bmps/green.bmp");
	if (SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF)) != 0) printf("color key error");
	GreenCar_texr = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	surface = SDL_LoadBMP("bmps/Gexp.bmp");
	if (SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF)) != 0) printf("color key error");
	Gexp_texr = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	Glaser_texr = loadTexture(renderer, "bmps/Glaser.bmp");

	while (run) {

		while (SDL_PollEvent(&e) != 0) {
			switch (e.type) {
			case SDL_QUIT:
				run = 0;
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym) {
				case SDLK_ESCAPE:
					run = 0;
					break;
				case SDLK_r:
					if (G_on == 0 || R_on == 0) {
						R_on = 1;
						RC_x = 200;
						RC_y = 300;
						RC_angle = 0;
						RC_rad = 0;
						RC_speed = 0;
						Rlaser_x = 10000;
						Rlaser_y = 10000;
						G_on = 1;
						GC_x = 600;
						GC_y = 300;
						GC_angle = 180;
						GC_rad = 0;
						GC_speed = 0;
						Glaser_x = 10000;
						Glaser_y = 10000;
					}
				}
			}
		}

		//Rc movement
		if (keystate[SDL_SCANCODE_W]) {
			if (RC_speed < 3)
				RC_speed += 0.05;
		} else {
			if (RC_speed > 0)
				RC_speed -= 0.03;
		}
		if (keystate[SDL_SCANCODE_S]) {
			if (RC_speed > -2)
				RC_speed -= 0.05;
		} else {
			if (RC_speed < 0)
				RC_speed += 0.02;
		}
		if (keystate[SDL_SCANCODE_A]) {
			RC_angle -= 0.5 * RC_speed;
		}
		if (keystate[SDL_SCANCODE_D]) {
			RC_angle += 0.5 * RC_speed;
		}
		if (keystate[SDL_SCANCODE_LSHIFT]) {
			if (Rlaser_cool < 0 && R_on == 1) {
				Rlaser_angle = RC_angle;
				Rlaser_cool = 12;
				Rlaser_x = RC_x+7;
				Rlaser_y = RC_y+7;
			}
		}
		if (Rlaser_cool >= 0) {
			Rlaser_cool -= 0.1;
		}

		Rlaser_rad = Rlaser_angle * (PI / 180);
		Rlaser_x += cos(Rlaser_rad)*6;
		Rlaser_y += sin(Rlaser_rad)*6;

		RC_rad = RC_angle * (PI / 180);

		if (RC_x < LBorder) {
			RC_speed = 0;
			RC_x += 1;
		}
		else if (RC_x > RBorder) {
			RC_speed = 0;
			RC_x -= 1;
		}
		else if (RC_y < UBorder) {
			RC_speed = 0;
			RC_y += 1;
		}
		else if (RC_y > DBorder) {
			RC_speed = 0;
			RC_y -= 1;
		}
		else {
			RC_x += cos(RC_rad)*RC_speed;
			RC_y += sin(RC_rad)*RC_speed;
		}

		//Gc movement
		if (keystate[SDL_SCANCODE_UP]) {
			if (GC_speed < 3)
				GC_speed += 0.05;
		}
		else {
			if (GC_speed > 0)
				GC_speed -= 0.03;
		}
		if (keystate[SDL_SCANCODE_DOWN]) {
			if (GC_speed > -2)
				GC_speed -= 0.05;
		}
		else {
			if (GC_speed < 0)
				GC_speed += 0.02;
		}
		if (keystate[SDL_SCANCODE_LEFT]) {
			GC_angle -= 0.5 * GC_speed;
		}
		if (keystate[SDL_SCANCODE_RIGHT]) {
			GC_angle += 0.5 * GC_speed;
		}
		if (keystate[SDL_SCANCODE_RSHIFT]) {
			if (Glaser_cool < 0 && G_on == 1) {
				Glaser_angle = GC_angle;
				Glaser_cool = 12;
				Glaser_x = GC_x + 7;
				Glaser_y = GC_y + 7;
			}
		}
		if (Glaser_cool >= 0) {
			Glaser_cool -= 0.1;
		}

		Glaser_rad = Glaser_angle * (PI / 180);
		Glaser_x += cos(Glaser_rad) * 6;
		Glaser_y += sin(Glaser_rad) * 6;


		GC_rad = GC_angle * (PI / 180);

		if (GC_x < LBorder) {
			GC_speed = 0;
			GC_x += 1;
		}
		else if (GC_x > RBorder) {
			GC_speed = 0;
			GC_x -= 1;
		}
		else if (GC_y < UBorder) {
			GC_speed = 0;
			GC_y += 1;
		}
		else if (GC_y > DBorder) {
			GC_speed = 0;
			GC_y -= 1;
		}
		else {
			GC_x += cos(GC_rad)*GC_speed;
			GC_y += sin(GC_rad)*GC_speed;
		}

		if (Rlaser_x-7 > GC_x - 18 && Rlaser_x-7 < GC_x + 18) {
			if (Rlaser_y - 7 > GC_y - 18 && Rlaser_y - 7 < GC_y + 18) {
				printf("Red Win\n");
				G_on = 0;
				Gexp_x = GC_x;
				Gexp_y = GC_y;
			}
		}
		if (Glaser_x - 7 > RC_x - 18 && Glaser_x - 7 < RC_x + 18) {
			if (Glaser_y - 7 > RC_y - 18 && Glaser_y - 7 < RC_y + 18) {
				printf("Green Win\n");
				R_on = 0;
				Rexp_x = RC_x;
				Rexp_y = RC_y;
			}
		}

		drawTexture(renderer, 0, 0, BG_texr);

		stretchTextureEx(renderer, Rlaser_x, Rlaser_y, 9, 3, Rlaser_texr, Rlaser_angle);
		stretchTextureEx(renderer, Glaser_x, Glaser_y, 9, 3, Glaser_texr, Glaser_angle);

		if (R_on == 1)
			stretchTextureEx(renderer, RC_x, RC_y, 26, 18, RedCar_texr, RC_angle);
		else drawTexture(renderer, Rexp_x, Rexp_y, Rexp_texr);
		if (G_on == 1)
			stretchTextureEx(renderer, GC_x, GC_y, 25, 16, GreenCar_texr, GC_angle);
		else drawTexture(renderer, Gexp_x, Gexp_y, Gexp_texr);
		
		SDL_RenderPresent(renderer); // show the final render 윈도우에다가 렌더러 표시
		SDL_RenderClear(renderer); // clear the renderer 렌더러 초기화
		
		SDL_Delay(10);

		
	}


	SDL_Quit();
	return 0;
}

// 새로운 라이브러리 활용할때
// 프로젝트 설정에서 라이브러리 경로, 헤더파일 경로를 설정해줘야 하고
// 링커 설정에서 각각의 라이브러리 오브젝트를 연결해줘야한다

// dll 파일이 프로젝트 경로에 있어야 컴파일 하는 과정에서 정상적으로 실행되고
// 실행 파일 경로에 있어야 실행도 정상적으로 된다.

// SDL 이니셜라이징하고, 윈도우 만들고, 렌더러 만들고 메인 루프 만들었어 while ( run ) 조건문 설정
// 기본적인 종료 조건 등 만들고, 움직임 넣었어
