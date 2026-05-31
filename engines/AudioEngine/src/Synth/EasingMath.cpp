#include "EasingMath.h"

EasingMath::EasingMath() {
	
}

double EasingMath::lerp(double x, double ax, double ay, double bx, double by) {
	return ay + (x - ax) * (by - ay)/(bx - ax);
}

std::vector<double> EasingMath::lerp(double ax, double ay, double bx, double by) {
	return lerp(ax, bx, ax, ay, bx, by);
}

std::vector<double> EasingMath::lerp(double xi, double xf, double ax, double ay, double bx, double by) {
	std::vector<double> data;
	for (int x = 0; x < xf - xi; x++) {
		data[x] = ay + (x - ax) * (by - ay)/(bx - ax);
	}
	return data;
}

double EasingMath::easeSineIn(double x, double ax, double ay, double bx, double by) {
	return by + (by - ay) * sin(M_PI/2 * (x - ax)/(bx - ax) - M_PI/2);
}

std::vector<double> EasingMath::easeSineIn(double ax, double ay, double bx, double by) {
	return easeSineIn(ax, bx, ax, ay, bx, by);
}

std::vector<double> EasingMath::easeSineIn(double xi, double xf, double ax, double ay, double bx, double by) {
	std::vector<double> data;
	for (int x = 0; x < xf - xi; x++) {
		data[x] = 	by + (by - ay) * sin(M_PI/2 * (x - ax)/(bx - ax) - M_PI/2);
	}
	return data;
}

double EasingMath::easeSineOut(double x, double ax, double ay, double bx, double by) {
	return ay + (by - ay) * sin(M_PI/2 * (x - ax)/(bx - ax));
}

std::vector<double> EasingMath::easeSineOut(double ax, double ay, double bx, double by) {
	return easeSineOut(ax, bx, ax, ay, bx, by);
}

std::vector<double> EasingMath::easeSineOut(double xi, double xf, double ax, double ay, double bx, double by) {
	std::vector<double> data;
	for (int x = 0; x < xf - xi; x++) {
		data[x] = 	ay + (by - ay) * sin(M_PI/2 * (x - ax)/(bx - ax));
	}
	return data;
}

double EasingMath::easeSineInOut(double x, double ax, double ay, double bx, double by) {
	return ay + (by - ay)/2 * (1 + sin(M_PI * (x - ax)/(bx - ax) - M_PI/2));
}

std::vector<double> EasingMath::easeSineInOut(double ax, double ay, double bx, double by) {
	return easeSineInOut(ax, bx, ax, ay, bx, by);
}

std::vector<double> EasingMath::easeSineInOut(double xi, double xf, double ax, double ay, double bx, double by) {
	std::vector<double> data;
	for (int x = 0; x < xf - xi; x++) {
		data[x] = 	ay + (by - ay)/2 * (1 + sin(M_PI * (x - ax)/(bx - ax) - M_PI/2));
	}
	return data;
}

double EasingMath::easeQuadBezier(double x, double ax, double ay, double bx, double by, double cx, double cy) {
	return pow(1 - (x - ax)/(bx - ax), 2) * ay + 2 * (1 - (x - ax)/(bx - ax)) * (x - ax)/(bx - ax) * cy + pow((x - ax)/(bx - ax), 2);
}

std::vector<double> EasingMath::easeQuadBezier(double ax, double ay, double bx, double by, double cx, double cy) {
	return easeCubicBezier(ax, bx, ax, ay, bx, by, cx, cy);
}

std::vector<double> EasingMath::easeQuadBezier(double xi, double xf, double ax, double ay, double bx, double by, double cx, double cy) {
	std::vector<double> data;
	for (int x = 0; x < xf - xi; x++) {
		data[x] = 	pow(1 - (x - ax)/(bx - ax), 2) * ay + 2 * (1 - (x - ax)/(bx - ax)) * (x - ax)/(bx - ax) * cy + pow((x - ax)/(bx - ax), 2);
	}
	return data;
}

double EasingMath::easeCubicBezier(double x, double ax, double ay, double bx, double by, double c1x, double c1y, double c2x, double c2y) {
	return pow(1 - (x - ax)/(bx - ax), 3) * ay
			+ 3 * (x - ax)/(bx - ax) * pow(1 - (x - ax)/(bx - ax), 2) * c1y
			+ 3 * pow((x - ax)/(bx - ax), 2) * (1 - (x - ax)/(bx - ax)) * c2y
			+ pow((x - ax)/(bx - ax), 3) * by;
}

std::vector<double> EasingMath::easeCubicBezier(double ax, double ay, double bx, double by, double c1x, double c1y, double c2x, double c2y) {
	return easeCubicBezier(ax, bx, ax, ay, bx, by, c1x, c1y, c2x, c2y);
}

std::vector<double> EasingMath::easeCubicBezier(double xi, double xf, double ax, double ay, double bx, double by, double c1x, double c1y, double c2x, double c2y) {
	std::vector<double> data;
	for (int x = 0; x < xf - xi; x++) {
		data[x] = pow(1 - (x - ax)/(bx - ax), 3) * ay
					+ 3 * (x - ax)/(bx - ax) * pow(1 - (x - ax)/(bx - ax), 2) * c1y
					+ 3 * pow((x - ax)/(bx - ax), 2) * (1 - (x - ax)/(bx - ax)) * c2y
					+ pow((x - ax)/(bx - ax), 3) * by;
	}
	return data;
}