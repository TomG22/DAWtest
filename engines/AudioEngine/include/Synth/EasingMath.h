#pragma once

/**
 * Class description...
 */

#include <cmath>
#include <vector>

class EasingMath {
public:
    /**
     * Constructor for Math class
     */
    EasingMath();

    /**Easing Style Functions**/
    
    enum EasingStyle {  
        linear,
        sineIn,
        sineOut,
        sineInOut,
        bezierQuad,
        bezierCubic
    };

    /**
     * 
     */
    double lerp(double x, double ax, double ay, double bx, double by);
    std::vector<double> lerp(double ax, double ay, double bx, double by);
    std::vector<double> lerp(double xi, double xf, double ax, double ay, double bx, double by);

    /**
     * 
     */
    double easeSineIn(double x, double ax, double ay, double bx, double by);
    std::vector<double> easeSineIn(double ax, double ay, double bx, double by);
    std::vector<double> easeSineIn(double xi, double xf, double ax, double ay, double bx, double by);

    /**
     * 
     */
    double easeSineOut(double x, double ax, double ay, double bx, double by);
    std::vector<double> easeSineOut(double ax, double ay, double bx, double by);
    std::vector<double> easeSineOut(double xi, double xf, double ax, double ay, double bx, double by);

    /**
     * 
     */
    double easeSineInOut(double x, double ax, double ay, double bx, double by);
    std::vector<double> easeSineInOut(double ax, double ay, double bx, double by);
    std::vector<double> easeSineInOut(double xi, double xf, double ax, double ay, double bx, double by);

    /**
     * 
     */
    double easeQuadBezier(double x, double ax, double ay, double bx, double by, double cx, double cy);
    std::vector<double> easeQuadBezier(double ax, double ay, double bx, double by, double cx, double cy);
    std::vector<double> easeQuadBezier(double xi, double xf, double ax, double ay, double bx, double by, double cx, double cy);

    /**
     * 
     */
    double easeCubicBezier(double x, double ax, double ay, double bx, double by, double c1x, double c1y, double c2x, double c2y);
    std::vector<double> easeCubicBezier(double ax, double ay, double bx, double by, double c1x, double c1y, double c2x, double c2y);
    std::vector<double> easeCubicBezier(double xi, double xf, double ax, double ay, double bx, double by, double c1x, double c1y, double c2x, double c2y);
};