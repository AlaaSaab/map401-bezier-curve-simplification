#include <stdio.h>
#include "geometrie2d.h"

void test_distance_point_segments1(){
    Point P,A,B;
    printf("Entrez les coordonnees du point P: ");
    scanf("%lf %lf", &P.x, &P.y);
    printf("\nEntrez les coordonnees du point A: ");
    scanf("%lf %lf", &A.x, &A.y);
    printf("\nEntrez les coordonnees du point B: ");
    scanf("%lf %lf", &B.x, &B.y);

    double distance = distance_point_segments(P, A, B);
    printf("La distance entre P et le segment [AB] est: %f\n", distance);

}

void test_distance_point_segments2() {
    Point P, A, B;
    double d;

    // Test 1 : Point sur le segment
    P.x = 2; P.y = 2;
    A.x = 0; A.y = 0;
    B.x = 4; B.y = 4;
    d = distance_point_segments(P, A, B);
    printf("Test 1 (Point sur le segment) : %f (Attendu: 0.000000)\n", d);

    // Test 2 : Point à gauche du segment
    P.x = 0; P.y = 3;
    d = distance_point_segments(P, A, B);
    printf("Test 2 (Point à gauche du segment) : %f (Attendu: ~2.12)\n", d);

    // Test 3 : Point à droite du segment
    P.x = 5; P.y = 1;
    d = distance_point_segments(P, A, B);
    printf("Test 3 (Point à droite du segment) : %f (Attendu: ~2.82)\n", d);

    // Test 4 : Point sur une extrémité du segment (A)
    P.x = 0; P.y = 0;
    d = distance_point_segments(P, A, B);
    printf("Test 4 (Point sur l'extrémité A) : %f (Attendu: 0.000000)\n", d);

    // Test 5 : Point sur une extrémité du segment (B)
    P.x = 4; P.y = 4;
    d = distance_point_segments(P, A, B);
    printf("Test 5 (Point sur l'extrémité B) : %f (Attendu: 0.000000)\n", d);

    // Test 6 : Segment réduit à un point
    A.x = B.x = 3;
    A.y = B.y = 3;
    P.x = 6; P.y = 3;
    d = distance_point_segments(P, A, B);
    printf("Test 6 (Segment réduit à un point) : %f (Attendu: 3.000000)\n", d);
}

int main() {
    test_distance_point_segments1();
    test_distance_point_segments2();
    return 0;
}
