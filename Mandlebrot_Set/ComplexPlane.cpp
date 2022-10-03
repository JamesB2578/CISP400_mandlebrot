#include "ComplexPlane.h"
#include <cmath>
#include <iostream>
#include <complex>
#include <sstream>
using namespace std;

ComplexPlane::ComplexPlane(double aspectRatio)
{
	m_aspectRatio = aspectRatio;
	m_view.setSize(BASE_WIDTH, -BASE_HEIGHT * m_aspectRatio);
	m_view.setCenter(0.0, 0.0);
	m_zoomCount = 0;
}

void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	double sizeX = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	double sizeY = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_view.setSize(sizeX, sizeY);
}

void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	double sizeX = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	double sizeY = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_view.setSize(sizeX, sizeY);
}

void ComplexPlane::setCenter(Vector2f coord)
{
	m_view.setCenter(coord.x, coord.y);
}

View ComplexPlane::getView()
{
	return m_view;
}

void ComplexPlane::setMouseLoactaion(Vector2f coord)
{
	m_mouseLocation.x = coord.x;
	m_mouseLocation.y = coord.y;
}

void ComplexPlane::loadText(Text& text)
{
	stringstream ss;
	ss << "Mandelbrot Set\n" << "Center: (" << m_view.getCenter().x << ", " << m_view.getCenter().y << ")\n"
		<< "Cursor: (" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")\n"
		<< "Left-click to Zoom in\nRight-click to Zoom out";
	text.setString(ss.str());
}

 size_t ComplexPlane::countIterations(Vector2f coord)
{
	complex<double> c(coord.x, coord.y);
	complex<double> z(0, 0);
	size_t i = 0;

	while (abs(z) < 2 && i < MAX_ITER)
	{
		z = z * z + c;
		i++;
	}

	return i;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{

	for (int i = 64; i > 0; i--)
	{
		if (count == MAX_ITER)
		{
			r = 0;
			g = 0;
			b = 0;
		}
		else if (count == i)
		{
			r = 188 - ((i * 16) + 8);
			g = 188 - ((i * 8) + 4);
			b = 250;
		}
	}
}
