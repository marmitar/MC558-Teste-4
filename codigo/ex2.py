from __future__ import annotations
from itertools import combinations
from typing import Iterator, Optional


pA1, pA2, pA3, pA4 = (0.30, 0.20, 0.40, 0.20)
pB1, pB2, pB3, pB4 = (0.20, 0.60, 0.30, 0.40)
pC1, pC2, pC3, pC4 = (0.40, 0.15, 0.25, 0.30)

c1, c2, c3, c4 = (20, 30, 20, 15)

u1, u2, u3, u4 = (0.30, 0.40, 1.00, 1.00)

qA, qB, qC = (0.20, 0.30, 0.20)


def close(a: float, b: float) -> bool:
    return a - b < 1e-9

def evaluate(r1: float, r2: float, r3: float, r4: float) -> Optional[float]:
    if not (0 <= r1 <= u1 and 0 <= r2 <= u2 and 0 <= r3 <= u3 and 0 <= r4 <= u4):
        return None
    elif not close(r1 + r2 + r3 + r4, 1.0):
        return None
    elif not close(pA1 * r1 + pA2 * r2 + pA3 * r3 + pA4 * r4, qA):
        return None
    elif not (pB1 * r1 + pB2 * r2 + pB3 * r3 + pB4 * r4 >= qB):
        return None
    elif not (pC1 * r1 + pC2 * r2 + pC3 * r3 + pC4 * r4 >= qC):
        return None

    return c1 * r1 + c2 * r2 + c3 * r3 + c4 * r4


Point = tuple[float, float, float, float]
Line = tuple[float, float, float]

def intersection(a: Line, b: Line) -> Optional[tuple[float, float]]:
    (a1, b1, c1), (a2, b2, c2) = a, b
    ap, bp, cp = b1*c2-b2*c1, a2*c1-a1*c2, a1*b2-a2*b1
    if close(cp, 0):
        return None
    return ap/cp, bp/cp

def extrema() -> Iterator[Point]:
    r3c = - (pA1 - pA4) / (pA3 - pA4), - (pA2 - pA4) / (pA3 - pA4), (qA - pA4) / (pA3 - pA4)
    r4c = - 1 - r3c[0], - 1 - r3c[1], 1 - r3c[2]

    lines: list[Line] = [
        # lower bounds
        (1, 0, 0), (0, 1, 0), (-r3c[0], -r3c[1], -r3c[2]), (-r4c[0], -r4c[1], -r4c[2]),
        # upper bounds
        (1, 0, u1), (0, 1, u2), (-r3c[0], -r3c[1], u3 - r3c[2]), (-r4c[0], -r4c[1], u4 - r4c[2]),
        # inequalities
        (pB1 - r3c[0]*pB3 - r4c[0]*pB4, pB2 - r3c[1]*pB3 - r4c[1]*pB4, qB - r3c[2]*pB3 - r4c[2]*pB4),
        (pC1 - r3c[0]*pC3 - r4c[0]*pC4, pC2 - r3c[1]*pC3 - r4c[1]*pC4, qB - r3c[2]*pC3 - r4c[2]*pC4)
    ]

    for l1, l2 in combinations(lines, 2):
        x = intersection(l1, l2)
        if x is None:
            continue
        r1, r2 = x
        r3 = r3c[0] * r1 + r3c[1] * r2 + r3c[2]
        r4 = r4c[0] * r1 + r4c[1] * r2 + r4c[2]
        yield r1, r2, r3, r4


def solve() -> Point:
    minima: Optional[float] = None
    point: Optional[Point] = None

    for r1, r2, r3, r4 in extrema():
        val = evaluate(r1, r2, r3, r4)
        if val is not None and (minima is None or val < minima):
            minima = val
            point = r1, r2, r3, r4

    if point is None:
        raise ValueError("Infeasible")
    return point


print(solve())
