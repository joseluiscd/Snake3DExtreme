#include "cgvLight.h"

// Constructor methods

cgvLight::cgvLight() {
}

cgvLight::cgvLight(const unsigned int _idLight,
  				   const cgvPoint3D  & _position,
				   const cgvColor & cAmb, const cgvColor & cDif, const cgvColor & cEsp,
				   const double a0, const double a1, const double a2) {

  idLight = _idLight;

	position = _position;

	ambientColor = cAmb;
	diffuseColor = cDif;
	specularColor = cEsp;

	atten_a0 = a0;
	atten_a1 = a1;
	atten_a2 = a2;

	// Default values for point lights
	spotlight_direction = cgvPoint3D(0,0,0);
	spotlight_angle = 180; // with this angle the spotlight becomes a point light source
	spotlight_exponent = 0;

	on = true;
}

cgvLight::cgvLight(const unsigned int _idLight,
                   const cgvPoint3D & _position,
                   const cgvColor& cAmb, const cgvColor& cDif, const cgvColor& cEsp,
		           const double a0, const double a1, const double a2,
				   const cgvPoint3D& spotlight_dir, const double spotlight_ang, const double spotlight_exp) {

  idLight = _idLight;

	position = _position;

	ambientColor = cAmb;
	diffuseColor = cDif;
	specularColor = cEsp;

	atten_a0 = a0;
	atten_a1 = a1;
	atten_a2 = a2;

	spotlight_direction = spotlight_dir;
	spotlight_angle = spotlight_ang;
	spotlight_exponent = spotlight_exp;

	on = true;
}

// Public methods ----------------------------------------

cgvPoint3D& cgvLight::getPosition(void) {
	return position;
}

void cgvLight::setPosition(cgvPoint3D pos) {
	position = pos;
}


void cgvLight::set(const cgvColor & cAmb, const cgvColor & cDif, const cgvColor & cEsp) {
	ambientColor = cAmb;
	diffuseColor = cDif;
	specularColor = cEsp;
}

void cgvLight::setAmbient(const cgvColor & cAmb) {
	ambientColor = cAmb;
}

void cgvLight::setDiffuse(const cgvColor & cDif) {
	diffuseColor = cDif;
}

void cgvLight::setSpecular(const cgvColor & cEsp) {
	specularColor = cEsp;
}

cgvColor & cgvLight::getAmbient(void) {
	return ambientColor;
}

cgvColor & cgvLight::getDiffuse(void) {
	return diffuseColor;
}

cgvColor & cgvLight::getSpecular(void) {
	return specularColor;
}

void cgvLight::setAttenuation(double a0, double a1, double a2) {
	atten_a0 = a0;
	atten_a1 = a1;
	atten_a2 = a2;
}

void cgvLight::getAttenuation(double & a0, double & a1, double & a2) {
	a0 = atten_a0;
	a1 = atten_a1;
	a2 = atten_a2;
}

void cgvLight::switchOn(void) {
  on = true;
}

void cgvLight::switchOff(void) {
  on = false;
}

unsigned int cgvLight::is_On(void) {
  return on;
}

void cgvLight::apply(void) {

// Section A
// if the light is on
//	enable the light
//	set the position of the light
//	set ambient, diffuse and specular colors
//	set radial attenuation
//	set the spotlight parameters: direction, cutoff, exponent.

// If the light is off
//	disable the light

	if (on) {
		glEnable(idLight);
		//	enable the light
		float fposition[4] = { position[0], position[1], position[2], 1.0 };
		glLightfv(idLight, GL_POSITION, fposition);
		//	set ambient, diffuse and specular colors
		float fambient[4] = { ambientColor[0], ambientColor[1], ambientColor[2], ambientColor[3] };
		glLightfv(idLight, GL_AMBIENT, fambient);
		float fdiffuse[4] = { diffuseColor[0], diffuseColor[1], diffuseColor[2], diffuseColor[3] };
		glLightfv(idLight, GL_DIFFUSE, fdiffuse);
		float fspecular[4] = { specularColor[0], specularColor[1], specularColor[2], specularColor[3] };
		glLightfv(idLight, GL_SPECULAR, fspecular);

		//	set radial attenuation
		glLightf(idLight, GL_CONSTANT_ATTENUATION, atten_a0);
		glLightf(idLight, GL_LINEAR_ATTENUATION, atten_a1);
		glLightf(idLight, GL_QUADRATIC_ATTENUATION, atten_a2);

		//	set angular attenuation and the spotlight direction
		if (spotlight_angle <= 90.0) {
			glLightf(idLight, GL_SPOT_CUTOFF, spotlight_angle);
			glLightf(idLight, GL_SPOT_EXPONENT, spotlight_exponent);
			float fdirection[3] = { spotlight_direction[0], spotlight_direction[1], spotlight_direction[2] };
			glLightfv(idLight, GL_SPOT_DIRECTION, fdirection);
		}
	}
	else {
		glDisable(idLight);
	}

}
