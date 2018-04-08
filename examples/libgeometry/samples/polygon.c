#include <stdio.h>
#include "polygon.h"

int main()
{
    polygon_t *poly;

    poly = polygon_new();

    polygon_add_xy(poly, 0.0, 0.0);
    polygon_add_xy(poly, 0.0, 2.0);
    polygon_add_xy(poly, 2.0, 2.0);
    polygon_add_xy(poly, 2.0, 0.0);

    printf("The perimeter is %.2f\n", polygon_perimeter(poly));
    printf("The area is %.2f\n", polygon_area(poly));
}
