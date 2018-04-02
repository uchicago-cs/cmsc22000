#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include "polygon.h"

Test(polygon, new)
{
    polygon_t *poly;

    poly = polygon_new();

    cr_assert_not_null(poly, "polygon_new() failed");
}


Test(polygon, init)
{
    polygon_t poly;
    int rc;

    rc = polygon_init(&poly);

    cr_assert_eq(rc, SUCCESS, "polygon_init() failed");
}

Test(polygon, free)
{
    polygon_t *poly;
    int rc;

    poly = polygon_new();

    cr_assert_not_null(poly, "polygon_new() failed");

    rc = polygon_free(poly);

    cr_assert_eq(rc, SUCCESS, "polygon_free() failed");
}

polygon_t* create_polygon(unsigned int n_points, ...)
{
    polygon_t *poly;
    int rc;

    poly = polygon_new();
    cr_assert_not_null(poly, "polygon_new() failed");

    va_list args;
    va_start(args, n_points);

    for(unsigned int i = 0; i < n_points * 2; i+=2)
    {
        double x, y;
        x = va_arg(args, double);
        y = va_arg(args, double);

        rc = polygon_add_xy(poly, x, y);
        cr_assert_eq(rc, SUCCESS, "Could not add point (%.2f, %.2f)", x, y);
    }
    va_end(args);

    return poly;
}


Test(polygon, create_triangle)
{
    polygon_t *poly;

    poly = create_polygon(3,
                          0.0, 0.0,
                          3.0, 0.0,
                          3.0, 4.0);

    cr_assert_eq(poly->n_points, 3);
    cr_assert_eq(poly->points[0].x, 0);
    cr_assert_eq(poly->points[0].y, 0);
    cr_assert_eq(poly->points[1].x, 3);
    cr_assert_eq(poly->points[1].y, 0);
    cr_assert_eq(poly->points[2].x, 3);
    cr_assert_eq(poly->points[2].y, 4);
}

Test(polygon, create_square)
{
    polygon_t *poly;

    poly = create_polygon(4,
                          0.0, 0.0,
                          0.0, 2.0,
                          2.0, 2.0,
                          2.0, 0.0);

    cr_assert_eq(poly->n_points, 4);
    cr_assert_eq(poly->points[0].x, 0);
    cr_assert_eq(poly->points[0].y, 0);
    cr_assert_eq(poly->points[1].x, 0);
    cr_assert_eq(poly->points[1].y, 2);
    cr_assert_eq(poly->points[2].x, 2);
    cr_assert_eq(poly->points[2].y, 2);
    cr_assert_eq(poly->points[3].x, 2);
    cr_assert_eq(poly->points[3].y, 0);
}

Test(polygon, perimeter1)
{
    polygon_t *poly;
    double perimeter;

    poly = create_polygon(3,
                          0.0, 0.0,
                          3.0, 0.0,
                          3.0, 4.0);

    perimeter = polygon_perimeter(poly);

    cr_assert_float_eq(perimeter, 12.0, 1E-6);
}

Test(polygon, perimeter2)
{
    polygon_t *poly;
    double perimeter;

    poly = create_polygon(4,
                          0.0, 0.0,
                          0.0, 2.0,
                          2.0, 2.0,
                          2.0, 0.0);

    perimeter = polygon_perimeter(poly);

    cr_assert_float_eq(perimeter, 8.0, 1E-6);
}

Test(polygon, area1)
{
    polygon_t *poly;
    double area;

    poly = create_polygon(3,
                          0.0, 0.0,
                          3.0, 0.0,
                          3.0, 4.0);

    area = polygon_area(poly);

    cr_assert_eq(area, 6.0);
}

Test(polygon, area2)
{
    polygon_t *poly;
    double area;

    poly = create_polygon(4,
                          0.0, 0.0,
                          0.0, 2.0,
                          2.0, 2.0,
                          2.0, 0.0);

    area = polygon_area(poly);

    cr_assert_eq(area, 4.0);
}

