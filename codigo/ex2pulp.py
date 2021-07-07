from __future__ import annotations
from pulp import LpVariable, LpProblem, LpMinimize, LpStatus, LpStatusOptimal, value


class P:
    A = (0.30, 0.20, 0.40, 0.20)
    B = (0.20, 0.60, 0.30, 0.40)
    C = (0.40, 0.15, 0.25, 0.30)

Cs  = (20, 30, 20, 15)
Max = (0.30, 0.40, 1.0, 1.0)

class Q:
    A = 0.20
    B = 0.30
    C = 0.20


r1 = LpVariable("r1", 0, Max[0])
r2 = LpVariable("r2", 0, Max[1])
r3 = LpVariable("r3", 0, Max[2])
r4 = LpVariable("r4", 0, Max[3])
R = [r1, r2, r3, r4]

prob = LpProblem("mistura", LpMinimize)
prob += Cs[0] * R[0] + Cs[1] * R[1] + Cs[2] * R[2] + Cs[3] * R[3]

prob += P.A[0] * R[0] + P.A[1] * R[1] + P.A[2] * R[2] + P.A[3] * R[3] == Q.A
prob += P.B[0] * R[0] + P.B[1] * R[1] + P.B[2] * R[2] + P.B[3] * R[3] >= Q.B
prob += P.C[0] * R[0] + P.C[1] * R[1] + P.C[2] * R[2] + P.C[3] * R[3] >= Q.C
prob += R[0] + R[1] + R[2] + R[3] == 1.0

print(prob)

status = prob.solve()
if status != LpStatusOptimal:
    raise ValueError(status, LpStatus[status])

for var in R:
    print(var.name, value(var))
