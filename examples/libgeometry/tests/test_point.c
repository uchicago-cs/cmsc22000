#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "point.h"

Test(point, new)
{
    point_t *p;

    p = point_new(42.0, 37.0);

    cr_assert_not_null(p, "point_new() failed");

    cr_assert_eq(p->x, 42, "point_new() didn't set x");
    cr_assert_eq(p->y, 37, "point_new() didn't set y");
}


Test(point, init)
{
    point_t p;
    int rc;

    rc = point_init(&p, 42, 37);

    cr_assert_eq(rc, SUCCESS, "point_init() failed");

    cr_assert_eq(p.x, 42, "point_init() didn't set x");
    cr_assert_eq(p.y, 37, "point_init() didn't set y");
}

Test(point, free)
{
    point_t *p;
    int rc;

    p = point_new(42.0, 37.0);

    cr_assert_not_null(p, "point_new() failed");

    rc = point_free(p);

    cr_assert_eq(rc, SUCCESS, "point_free() failed");
}


void check_distance(double x1, double y1, double x2, double y2, double expected)
{
    point_t p1, p2;
    double distance;

    point_init(&p1, x1, y1);
    point_init(&p2, x2, y2);

    distance = point_distance(&p1, &p2);

    cr_assert_float_eq(distance, expected, 1e-6,
                       "Expected distance between (%.2f, %.2f) and (%.2f, %.2f) to be %.6f (got %.6f)",
                       x1, y1, x2, y2, expected, distance);
}


Test(point, unit_distance)
{
    check_distance(0.0, 0.0,  0.0,  1.0, 1.0);
    check_distance(0.0, 0.0,  1.0,  0.0, 1.0);
    check_distance(0.0, 0.0,  0.0, -1.0, 1.0);
    check_distance(0.0, 0.0, -1.0,  0.0, 1.0);

    check_distance( 0.0,  1.0, 0.0, 0.0, 1.0);
    check_distance( 1.0,  0.0, 0.0, 0.0, 1.0);
    check_distance( 0.0, -1.0, 0.0, 0.0, 1.0);
    check_distance(-1.0,  0.0, 0.0, 0.0, 1.0);

}

Test(point, distance1)
{
    check_distance(0.0, 0.0,  1.0,  1.0, 1.414213562);
    check_distance(0.0, 0.0, -1.0,  1.0, 1.414213562);
    check_distance(0.0, 0.0,  1.0, -1.0, 1.414213562);
    check_distance(0.0, 0.0, -1.0, -1.0, 1.414213562);

    check_distance( 1.0,  1.0, 0.0, 0.0, 1.414213562);
    check_distance(-1.0,  1.0, 0.0, 0.0, 1.414213562);
    check_distance( 1.0, -1.0, 0.0, 0.0, 1.414213562);
    check_distance(-1.0, -1.0, 0.0, 0.0, 1.414213562);
}

Test(point, distance_cross_x_axis)
{
    check_distance(3.0, -1.0, 3.0, 1.0, 2.0);
}

Test(point, distance_cross_y_axis)
{
    check_distance(-1.0, 3.0, 1.0, 3.0, 2.0);
}

Test(point, distance_cross_both_axis)
{
    check_distance(-2.0, -1.0, 1.0, 3.0, 5.0);
}



void check_intersect(double p1x, double p1y,
                     double q1x, double q1y,
                     double p2x, double p2y,
                     double q2x, double q2y, bool expected)
{
    point_t p1, q1, p2, q2;
    bool intersect;

    point_init(&p1, p1x, p1y);
    point_init(&q1, q1x, q1y);
    point_init(&p2, p2x, p2y);
    point_init(&q2, q2x, q2y);

    intersect = segment_intersect(&p1, &q1, &p2, &q2);

    cr_assert_eq(intersect, expected,
                 "Segments (%.2f, %.2f) -> (%.2f, %.2f) and (%.2f, %.2f) -> (%.2f, %.2f) %s but "
                 "segment_intersect returned %s",
                  p1x, p1y, q1x, q1y, p2x, p2y, q2x, q2y,
                 expected? "intersect":"do not intersect",
                 intersect? "true":"false");
}

Test(point, intersection_right_angle)
{
    check_intersect(-1, 0, 1,  0,
                     0, 1, 0, -1,
                    true);
}

Test(point, intersection_angle)
{
    check_intersect(-1, 0, 1, 0,
                    -1,-1, 1, 1,
                    true);
}

Test(point, intersection_overlap1)
{
    check_intersect(0, 0, 5, 0,
                    0, 0, 2, 0,
                    true);
}

Test(point, intersection_overlap2)
{
    check_intersect(0, 0, 5, 0,
                    2, 0, 3, 0,
                    true);
}

Test(point, no_intersection_parallel)
{
    check_intersect(2,  2, 4, 2,
                    2, 10, 4, 10,
                    false);
}

Test(point, no_intersection)
{
    check_intersect(-1, 0, 1, 0,
                     0, 2, 0, 4,
                    false);
}

Test(point, no_intersection_connected)
{
    check_intersect(0, 0, 0, 2,
                    0, 2, 2, 2,
                    false);
}
