#include "cgvTexture.h"

// Constructor and destructor methods

cgvTexture::cgvTexture(char *file) {
	unsigned char *image;
	int width, height;
	cgvInterfaceSDL& inter = cgvInterfaceSDL::getInstance();

	// load the image in memory
	img = inter.getSDLTexture(file, width, height);
}

void cgvTexture::apply(void) {
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	SDL_GL_BindTexture(img, &tWidth, &tHeight)==0?0:throw cgvException("Error in the texture");
}

void cgvTexture::disable(){
	SDL_GL_UnbindTexture(img);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

cgvTexture::~cgvTexture() {
	SDL_DestroyTexture(img);
}
