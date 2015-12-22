#include <GL/glu.h>
#include <GL/gl.h>

#include <math.h>
#include <stdio.h>

#include "cgvCamera.h"

// Constructors
cgvCamera::cgvCamera(cgvPoint3D _PV, cgvPoint3D _rp, cgvPoint3D _up,
	double _right, double _top,
	double _znear, double _zfar):zoomFactor(0.01), currentZoom(1)
{
	setCameraParameters(_PV, _rp, _up);
	setParallelParameters(_right, _top, _znear, _zfar);
}


cgvCamera::~cgvCamera () {}

void cgvCamera::setCameraParameters(cgvPoint3D _PV, cgvPoint3D _rp, cgvPoint3D _up) {
	PV = _PV;
	rp = _rp;
	up = _up;
}

void cgvCamera::getCameraParameters(cgvPoint3D& _PV, cgvPoint3D& _rp, cgvPoint3D& _up) {
	_PV = PV;
	_rp = rp;
	_up = up;
}

void cgvCamera::setParallelParameters(double _right, double _top,
	double _znear, double _zfar)
{
	xwmin = -_right; // left
	xwmax = _right;
	ywmin = -_top; // bottom
	ywmax = _top;
	znear = _znear;
	zfar = _zfar;

}


void cgvCamera::getParallelParameters(double& _xwmin, double& _xwmax, double& _ywmin, double& _ywmax,
										double& _znear, double& _zfar)
{
	_xwmin = xwmin;
	_xwmax = xwmax;
	_ywmin = ywmin;
	_ywmax = ywmax;
	_znear = znear;
	_zfar = zfar;
}



void cgvCamera::apply(cameraType type) {

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();



	if (type==CGV_PARALLEL) {
		glOrtho(xwmin, xwmax, ywmin, ywmax, znear, zfar);
	} else if (type==CGV_PERSPECTIVE) {
		glFrustum(xwmin, xwmax, ywmin, ywmax, znear, zfar);
	}

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(PV[X],PV[Y],PV[Z], rp[X],rp[Y],rp[Z], up[X],up[Y],up[Z]);
}

void cgvCamera::setZoomFactor(double factor) {
	zoomFactor = factor;
}

void cgvCamera::zoomIn() {}
void cgvCamera::zoomOut() {}


void cgvCamera::computePerspectiveParameters(double &fovy, double &aspect,
	double _xwmin, double _xwmax, double _ywmin, double _ywmax)
{

}
