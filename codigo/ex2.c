#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

static const double pA[] = {0.30, 0.20, 0.40, 0.20};
static const double pB[] = {0.20, 0.60, 0.30, 0.40};
static const double pC[] = {0.40, 0.15, 0.25, 0.30};

static const double c[] = {20, 30, 20, 15};
static const double u[] = {0.30, 0.40, 1.00, 1.00};
static const double q[] = {0.20, 0.30, 0.20};


#define const_fn static const inline __attribute__((const, hot, nothrow))
#define unlikely(x)    (__builtin_expect((x), 0))

typedef struct line {
    double a, b, c;
} line_t;

const_fn line_t r3_line(void) {
    const double pA1 = pA[0], pA2 = pA[1], pA3 = pA[2], pA4 = pA[3];
    const double qA = q[0];

    const double r34 = pA3 - pA4;
    const double r31 = - (pA1 - pA4) / r34;
    const double r32 = - (pA2 - pA4) / r34;
    const double r3c = (qA - pA4) / r34;

    return (line_t) {.a = r31, .b = r32, .c = r3c};
}

const_fn line_t r4_line(void) {
    const line_t r3 = r3_line();

    const double r41 = - 1 - r3.a;
    const double r42 = - 1 - r3.b;
    const double r4c = 1 - r3.c;

    return (line_t) {.a = r41, .b = r42, .c = r4c};
}

const_fn line_t get_line(const double l[5]) {
    const line_t r3 = r3_line();
    const line_t r4 = r4_line();

    return (line_t) {
        .a = l[0] - r3.a * l[2] - r4.a * l[3],
        .b = l[1] - r3.a * l[2] - r4.a * l[3],
        .c = l[4] - r3.a * l[2] - r4.a * l[3],
    };
}

#define MAX 10

struct line_array {
    line_t line[MAX];
};

const_fn struct line_array get_lines(void) {
    const double plane[MAX][5] = {
        {1, 0, 0, 0, 0}, {0, 1, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 1, 0},
        {1, 0, 0, 0, u[0]}, {0, 1, 0, 0, u[1]}, {0, 0, 1, 0, u[2]}, {0, 0, 0, 1, u[3]},
        {pB[0], pB[1], pB[2], pB[3], q[1]}, {pC[0], pC[1], pC[2], pC[3], q[2]}
    };

    struct line_array arr;
    for (unsigned i = 0; i < MAX; i++) {
        arr.line[i] = get_line(plane[i]);
    }
    return arr;
}

typedef struct point {
    double r[4];
} point_t;

const_fn bool close(double a, double b) {
    return a - b < 1e-9;
}

const_fn point_t intersection(line_t l1, line_t l2) {
    const double a = l1.b * l2.c - l2.b * l1.c;
    const double b = l2.a * l1.c - l1.a * l2.c;
    const double c = l1.a * l2.b - l2.a * l1.b;

    const double r1 = close(c, 0)? 0 : a / c;
    const double r2 = close(c, 0)? 0 : b / c;
    const line_t r3l = r3_line();
    const double r3 = r3l.a * r1 + r3l.b * r2 + r3l.c;
    const line_t r4l = r4_line();
    const double r4 = r4l.a * r1 + r4l.b * r2 + r4l.c;

    return (point_t) { .r = {r1, r2, r3, r4} };
}

const_fn double feasible(const point_t p) {
    const double r1 = p.r[0], r2 = p.r[1], r3 = p.r[2], r4 = p.r[3];
    const double u1 = u[0], u2 = u[1], u3 = u[2], u4 = u[3];
    const double pA1 = pA[0], pA2 = pA[1], pA3 = pA[2], pA4 = pA[3];
    const double pB1 = pB[0], pB2 = pB[1], pB3 = pB[2], pB4 = pB[3];
    const double pC1 = pC[0], pC2 = pC[1], pC3 = pC[2], pC4 = pC[3];
    const double qA = q[0], qB = q[1], qC = q[2];

    return (
        (r1 >= 0 && r1 <= u1) &&
        (r2 >= 0 && r2 <= u2) &&
        (r3 >= 0 && r3 <= u3) &&
        (r4 >= 0 && r4 <= u4) &&
        close(r1 + r2 + r3 + r4, 1) &&
        close(pA1 * r1 + pA2 * r2 + pA3 * r3 + pA4 * r4, qA) &&
        (pB1 * r1 + pB2 * r2 + pB3 * r3 + pB4 * r4 >= qB) &&
        (pC1 * r1 + pC2 * r2 + pC3 * r3 + pC4 * r4 >= qC)
    );
}

const_fn double evaluate(point_t p) {
    if unlikely(!feasible(p)) return nan("");

    const double r1 = p.r[0], r2 = p.r[1], r3 = p.r[2], r4 = p.r[3];
    const double c1 = c[0], c2 = c[1], c3 = c[2], c4 = c[3];

    return c1 * r1 + c2 * r2 + c3 * r3 + c4 * r4;
}

const_fn point_t solve(void) {
    struct line_array arr = get_lines();

    double max = nan("");
    point_t res = {.r = {0, 0, 0, 0}};
    for (unsigned i = 0; i < MAX; i++) {
        for (unsigned j = 0; j < MAX; j++) {
            if unlikely(i == j) continue;
            const point_t p = intersection(arr.line[i], arr.line[j]);
            const double v = evaluate(p);

            if (isnan(max) || v > max) {
                max = v;
                res = p;
            }
        }
    }

    if unlikely(isnan(max)) {
        fprintf(stderr, "Infeasible\n");
        exit(EXIT_FAILURE);
    }
    return res;
}

int main(void) {
    const point_t p = solve();

    printf("r1 = %f\n", p.r[0]);
    printf("r2 = %f\n", p.r[1]);
    printf("r3 = %f\n", p.r[2]);
    printf("r4 = %f\n", p.r[3]);
}
