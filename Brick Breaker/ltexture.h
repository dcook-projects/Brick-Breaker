#pragma once

#include <string>
#include <SDL.h>
#include <SDL_image.h>

struct App;

class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(App& app, std::string path);

	//Creates image from font string
	bool loadFromRenderedText(App& app, std::string textureText, SDL_Color textColor);

	//Deallocates texture
	void free();

	//Renders texture at given point
	void render(App& app, int x, int y, SDL_Rect* clip = nullptr);
	void render(App& app, const SDL_Rect& renderQuad, SDL_Rect* clip = nullptr);

	//Gets image dimensions
	int getWidth();
	int getHeight();

	//The actual hardware texture
	SDL_Texture* mTexture;
private:
	int mWidth;
	int mHeight;
};