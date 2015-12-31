#ifndef __CGVTEXTURE
#define __CGVTEXTURE

#include <GL/glut.h>
#include <stdio.h>
#include "cgvInterfaceSDL.h"

class cgvTexture {

	protected:
		// Attributes
		unsigned int idTexture; // texture identifier
		unsigned int height,      // height of the texture
			          width;     // weight of the texture

		float tWidth, tHeight;
		SDL_Texture* img;
	public:
		// Default Constructors and destructor
		cgvTexture(){};
		cgvTexture(char *file); // Texture from a PNG/JPG/BMP/... file
		~cgvTexture();

		// Methods
		void apply(void); // bind the texture as the active texture
		void disable(void); //Disables it after applying

		float getWidth(){ return tWidth; };
		float getHeight(){ return tHeight; };

};

#endif
