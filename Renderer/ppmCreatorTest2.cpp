#include "color.h"
#include "vec3.h"
#include "ray.h"

#include <iostream>

double hitSphereTest(const point3& sphereCenter, double radius, const ray& ray){
    vec3 cq = sphereCenter - ray.origin(); // (C-Q) from (C-(Q+td)) = (-td dot (C-Q))
    
    auto a = ray.direction().length_squared(); // Solved from quadratic formula, t^2 * (raydirection)^2
    auto h = dot(ray.direction(),cq); // Solved from quadratic formula, t * (-2d dot (C-Q))
    auto c = cq.length_squared() - radius*radius; // Solved from quadratic formula, 1 * (C-Q) dot (C-Q) - r^2
    auto discriminant = h*h - a*c; // Discriminant < 0 - Ray has missed the sphere.
    

    // Returning real quadratic solution for normal map coloring
    if (discriminant < 0){
        return -1.0; // imaginary number !
    } else{
        return ((h - std::sqrt(discriminant))/(a)); // quadratic formula
    }
}


color rayColor(const ray& ray){
    // get time at which ray has hit sphere.
    auto t = hitSphereTest(point3(0,0,-1), 0.5, ray);
    if (t > 0.0) {
        vec3 N = unitVector(ray.at(t) - vec3(0,0,-1));
        return 0.5*color(N.x()+1, N.y()+1, N.z()+1);
    }
    // want to Lerp using value = (1-t)*startVal + t * endVal for 0 <= t <= 1
    vec3 unitVectorDir = unitVector(ray.direction());
    auto a = 0.5 * (unitVectorDir.y() + 1.0);
    return (1.0 - a)*color(1.0,1.0,1.0)+a*color(0.5,0.7,1.0); // changes background color gradient 
}


int main() {

    // Image
    auto aspectRatio = 16.0 / 9.0; // 16:9 ratio
    int imageWidth = 400;


    // Calculate Image Resolution
    int imageHeight = int(imageWidth / aspectRatio);
    imageHeight = (imageHeight < 1) ? 1 : imageHeight; // if less than 1, make 1. if not, OK.

    // Camera variables
    auto focalLen = 1.0;
    auto viewportHeight = 2.0;
    auto viewportWidth = viewportHeight * (double(imageWidth)/imageHeight);
    auto cameraCenter = point3(0,0,0); // TODO: Add controls to camera

    // Calculate full vectors across horizontal and vertical
    auto viewportHorizontal = vec3(viewportWidth,0,0);
    auto viewportVertical = vec3(0,-viewportHeight,0);

    // Divide into unit vectors
    auto pixelViewportHorizontal = viewportHorizontal / imageWidth;
    auto pixelViewportVertical = viewportVertical / imageHeight;

    // Locate top left pixel
    auto viewportTopLeft = cameraCenter - vec3(0,0,focalLen) - viewportHorizontal/2 - viewportVertical/2; 
    //    Top Left       = Where camera - z pos from plane   - half of both full vector dimensions  
    auto pixel00Location = viewportTopLeft + 0.5 * (pixelViewportHorizontal + pixelViewportVertical);
    // accounting for width of pixel

    // Render ppm

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = 0; j <imageHeight; j++) {
        std::cerr << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
        for (int i = 0; i < imageWidth; i++) {
            // find pixel's center and direction based on top left pixel calculated before
            auto pixelCenter = pixel00Location + (i * pixelViewportHorizontal) + (j * pixelViewportVertical); 
            auto rayDir = pixelCenter - cameraCenter; // Direct vector from camera to pixel's center
            ray r(cameraCenter,rayDir);
            color pixelColor = rayColor(r); // color.h creating a color then writing it to stdout
            writeColor(std::cout, pixelColor);
        }
    }
    std::cerr << "\rDone.                 \n";
}