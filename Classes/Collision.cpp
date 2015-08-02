#include "Collision.h"

USING_NS_CC;

Collision::Collision() {

}

Collision::~Collision() {
	//delete plex_t;
}

void Collision::setThePlex(string src) {
	Image* imag = new Image();
	imag->initWithImageFile(src);
	unsigned char *data_ = imag->getData();
	
	w = imag->getHeight();
	plex_t = new unsigned int[imag->getHeight()*imag->getWidth()];
	all = imag->getHeight()*imag->getWidth();

	for (int i = 0; i < imag->getWidth(); i++) {
		for (int j = 0; j < imag->getHeight(); j++) {
			int pa = 4 * ((imag->getHeight() - j - 1) * imag->getWidth() + i) + 3;
			plex_t[i*imag->getHeight() + j] = data_[pa];
		}
	}
	delete imag;
	//CCTextureCache::sharedTextureCache()->removeAllTextures();
}

unsigned int Collision::getThePlexByPoint(int psx, int psy) {
	int x = (psx - 1) * w + psy;
	if (x < 0) {
		x = 0;
	}
	if (x >= all) {
		x = all - 1;
	}
	return plex_t[x];
}