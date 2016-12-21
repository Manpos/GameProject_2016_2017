#pragma once
//Class used to load and clip a texture
//#include <SDL.h>
//#include <iostream>
//#include <SDL_image.h>
//
//
//SDL_Rect SpriteClips[11];
//LTexture SpriteSheetTexture;
//
//class LTexture {
//private:
//	SDL_Texture* mTexture;
//
//	//Image dimensions
//	int mWidth;
//	int mHeight;
//
//public:
//	//Initializes values
//	LTexture();
//
//	//Frees memory
//	~LTexture();
//
//	//Deallocates texture
//	void free();
//
//	//Renders texture at given point
//	void render(int x, int y, SDL_Rect* clip = NULL) {
//		//Set rendering space and render to screen
//		SDL_Rect renderQuad = { x, y, mWidth, mHeight };
//
//		//Set clip rendering dimensions
//		if (clip != NULL)
//		{
//			renderQuad.w = clip->w;
//			renderQuad.h = clip->h;
//		}
//
//		//Render to screen
//		//SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
//	};
//	
//	//Gets image dimensions
//	int getWidth();
//	int getHeight();
//};