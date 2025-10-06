#include "./Point.hpp"
ld lineDist(Line L, Point p) {
    return (L.e - L.s).cross(p - L.s)/(L.e - L.s).abs();
}