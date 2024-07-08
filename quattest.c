#include <stdio.h>
#include <math.h>
#include "b_3d.h"
#include "b_math.h"

int main(void) {
	quat q[100];
	vec3 euler;

	/*
	*/
	q[0] = quat_set(1.0f,2.0f,3.0f,4.0f);
	q[1] = quat_set(5.0f,6.0f,7.0f,8.0f);

	quat_print(q[0], "q0");
	quat_print(q[1], "q1");

	q[2] = quat_negate(q[0]);
	quat_print(q[2], "negated q0");

	q[3] = quat_conj(q[0]);
	quat_print(q[3], "conj q0");

	q[4] = quat_addReal(q[0], 2.0f);
	quat_print(q[4], "addReal q0");

	q[5] = quat_add(q[0], q[1]);
	quat_print(q[5], "add q0 + q1");

	q[6] = quat_scale(q[0], 2.0f);
	quat_print(q[6], "scale q0 * 2");

	euler.x = deg2rad(10.0);
	euler.y = deg2rad(10.0);
	euler.z = deg2rad(10.0);
	q[7] = quat_fromEuler(euler);
	quat_print(q[7], "euler");

	euler = quat_toEuler(q[7]);
	vec3_printf(euler, "toEuler");

	return 0;
}
