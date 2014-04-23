/*
 * vector_arithmetic.cpp
 *
 * Operations for the defined structure VECTOR, PLANE and LINE, and matrix arithmetics.
 *  Created on: Apr 23, 2014
 *      Author: xzhu
 */

#include <math.h>
#include <stdio.h>
#include <string.h>
#include "mcce.h"


double avv(VECTOR v1, VECTOR v2)
{
	double t;
	v1 = vector_normalize(v1); v2 = vector_normalize(v2);
	t = v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
	if (t>1.0) t = 1.0;
	else if (t < -1.0) t = -1.0;
	return acos(t);
}


float app(PLANE plane1, PLANE plane2)
{
	return avv(plane1.t, plane2.t);
}


float all(LINE line1, LINE line2)
{
	return avv(line1.t, line2.t);
}


double avvvv(VECTOR v1, VECTOR v2, VECTOR v3, VECTOR v4)
{
	return app(plane_3v(v1, v2, v3), plane_3v(v2, v3, v4));
}


double dvv(VECTOR v1, VECTOR v2)
{
	double dx, dy, dz;
	dx = v2.x- v1.x;
	dy = v2.y- v1.y;
	dz = v2.z- v1.z;
	return sqrt(dx*dx+dy*dy+dz*dz);
}


double ddvv(VECTOR v1, VECTOR v2)
{
	double dx, dy, dz;
	dx = v2.x- v1.x;
	dy = v2.y- v1.y;
	dz = v2.z- v1.z;
	return dx*dx+dy*dy+dz*dz;
}


/*******************************************************************************
 * NAME
 *        det3 - determinant of a 3 by 3 matrix
 *
 * SYNOPSIS
 *        #include <mcce.h>
 *
 *        float det3(float m[][3]);
 *
 * DESCRIPTION
 *        The det3() function returns the determinant of a 3 by 3 matrix.
 *
 * SEE ALSO
 *        det4
 *
 * EXAMPLE
 *        float det;
 *        float M[3][3];
 *        ...
 *        det = det3(M);
 *
 * AUTHOR
 *        Junjun Mao, 05/26/2003
 *******************************************************************************/
float det3(float m[][3])
{
	return m[0][0]*m[1][1]*m[2][2]
	     - m[0][0]*m[1][2]*m[2][1]
	     + m[0][1]*m[1][2]*m[2][0]
	     - m[0][1]*m[1][0]*m[2][2]
	     + m[0][2]*m[1][0]*m[2][1]
	     - m[0][2]*m[1][1]*m[2][0];
}


/*******************************************************************************
 * NAME
 *        det4 - determinant of a 4 by 4 matrix
 *
 * SYNOPSIS
 *        #include <mcce.h>
 *
 *        float det4(float m[][4]);
 *
 * DESCRIPTION
 *        The det4() function returns the determinant of a 4 by 4 matrix.
 *
 * SEE ALSO
 *        det3
 *
 * EXAMPLE
 *        float det;
 *        float M[4][4];
 *        ...
 *        det = det4(M);
 *
 * AUTHOR
 *        Junjun Mao, 05/26/2003
 *******************************************************************************/
float det4(float m[][4])
{
	return (m[0][0] * m[1][1] - m[0][1] * m[1][0]) * (m[2][2] * m[3][3] - m[2][3] * m[3][2])
			- (m[0][0] * m[1][2] - m[0][2] * m[1][0]) * (m[2][1] * m[3][3] - m[2][3] * m[3][1])
			+ (m[0][0] * m[1][3] - m[0][3] * m[1][0]) * (m[2][1] * m[3][2] - m[2][2] * m[3][1])
			+ (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * (m[2][0] * m[3][3] - m[2][3] * m[3][0])
			- (m[0][1] * m[1][3] - m[0][3] * m[1][1]) * (m[2][0] * m[3][2] - m[2][2] * m[3][0])
			+ (m[0][2] * m[1][3] - m[0][3] * m[1][2]) * (m[2][0] * m[3][1] - m[2][1] * m[3][0]);
}


/*******************************************************************************
 * NAME
 *        dll - distance between two lines
 *
 * SYNOPSIS
 *        #include <math.h>
 *        #include <mcce.h>
 *
 *        float dll(LINE line1, LINE line2);
 *
 * DESCRIPTION
 *        The dll() function returns the distance between two lines.
 *
 * RETURN VALUE
 *        The dll() function returns a floating point number.
 *
 * SEE ALSO
 *        dpp
 *
 * DEPENDENCY
 *        det3
 *
 * EXAMPLE
 *        #include <math.h>
 *        #include <mcce.h>
 *        ...
 *        LINE line1, line2;
 *        float d;
 *        ...
 *        d=dll(line1, line2);
 *
 * AUTHOR
 *        Junjun Mao, 05/28/2003
 *******************************************************************************/
float dll(LINE line1, LINE line2)
/* distance between two lines */
{
	float M[3][3];
	float t1, t2, t3, t4;

	M[0][0] = line2.p0.x - line1.p0.x;
	M[0][1] = line2.p0.y - line1.p0.y;
	M[0][2] = line2.p0.z - line1.p0.z;
	M[1][0] = line1.t.x;
	M[1][1] = line1.t.y;
	M[1][2] = line1.t.z;
	M[2][0] = line2.t.x;
	M[2][1] = line2.t.y;
	M[2][2] = line2.t.z;

	t1=det3(M);
	t2=line1.t.y * line2.t.z - line2.t.y * line1.t.z;
	t3=line1.t.z * line2.t.x - line2.t.z * line1.t.x;
	t4=line1.t.x * line2.t.y - line2.t.x * line1.t.y;

	return fabs(t1/sqrt(t2*t2+t3*t3+t4*t4));
}


/*******************************************************************************
 * NAME
 *        vector_normalize - normalize a vector
 *
 * SYNOPSIS
 *        #include <math.h>
 *        #include <mcce.h>
 *
 *        VECTOR vector_normalize(VECTOR v);
 *
 * DESCRIPTION
 *        The vector_normalize() function returns the normalized vector of the
 *        passed in vector, or returns (0,0,0) when error occurs.
 *
 * RETURN VALUE
 *        The returned value is in VECTOR type.
 *
 * EXAMPLE
 *        #include <math.h>
 *        #include <mcce.h>
 *        ...
 *        VECTOR v1, v2;
 *        ...
 *        v2=vector_normalize(v1);
 *
 * AUTHOR
 *        Junjun Mao, 05/28/2003
 *******************************************************************************/
VECTOR vector_normalize(VECTOR v)
{
	VECTOR vn;
	float d;
	d = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
	if (d < 1.0e-20) {
		vn.x = 0.0;
		vn.y = 0.0;
		vn.z = 0.0;
	}
	else {
		vn.x = v.x/d;
		vn.y = v.y/d;
		vn.z = v.z/d;
	}
	return vn;
}


/*******************************************************************************
 * NAME
 *        vector_vminusv - vector minus vector
 *
 * SYNOPSIS
 *        #include <mcce.h>
 *
 *        VECTOR vector_vminusv(VECTOR v1, VECTOR v2);
 *
 * DESCRIPTION
 *        The vector_vminusv() function returns the resulted vector of v1 minus
 *        v2.
 *
 * RETURN VALUE
 *        The returned value is in VECTOR type.
 *
 * SEE ALSO
 *        vector_vplusv, vector_vxv
 *
 * EXAMPLE
 *        #include <mcce.h>
 *        ...
 *        VECTOR v1, v2, v3;
 *        ...
 *        v3=vector_vminusv(v1, v2);
 *
 * AUTHOR
 *        Junjun Mao, 05/28/2003
 *******************************************************************************/
VECTOR vector_vminusv(VECTOR v1, VECTOR v2)
{
	VECTOR z;
	z.x = v1.x - v2.x;
	z.y = v1.y - v2.y;
	z.z = v1.z - v2.z;
	return z;
}


/*******************************************************************************
 * NAME
 *        vector_vplusv - vector plus vector
 *
 * SYNOPSIS
 *        #include <mcce.h>
 *
 *        VECTOR vector_vplusv(VECTOR v1, VECTOR v2);
 *
 * DESCRIPTION
 *        The vector_vplusv() function returns the resulted vector of v1 plus v2.
 *
 * RETURN VALUE
 *        The returned value is in VECTOR type.
 *
 * SEE ALSO
 *        vector_vminusv, vector_vxv
 *
 * EXAMPLE
 *        #include <math.h>
 *        #include <mcce.h>
 *        ...
 *        VECTOR v1, v2, v3;
 *        ...
 *        v3=vector_vplusv(v1, v2);
 *
 * AUTHOR
 *        Junjun Mao, 05/28/2003
 *******************************************************************************/
VECTOR vector_vplusv(VECTOR v1, VECTOR v2)
{
	VECTOR z;
	z.x = v1.x + v2.x;
	z.y = v1.y + v2.y;
	z.z = v1.z + v2.z;
	return z;
}


/*******************************************************************************
 * NAME
 *        vector_vxv - cross product of two vectors
 *
 * SYNOPSIS
 *        #include <mcce.h>
 *
 *        VECTOR vector_vxv(VECTOR v1, VECTOR v2);
 *
 * DESCRIPTION
 *        The vector_vxv() function returns the resulted cross product of vector
 *        of v1 and vector v2.
 *
 * RETURN VALUE
 *        The returned value is in VECTOR type.
 *
 * SEE ALSO
 *        vector_vplusv, vector_vminusv
 *
 * EXAMPLE
 *        #include <mcce.h>
 *        ...
 *        VECTOR v1, v2, v3;
 *        ...
 *        v3=vector_vxv(v1, v2);
 *
 * AUTHOR
 *        Junjun Mao, 05/28/2003
 *******************************************************************************/
VECTOR vector_vxv(VECTOR v1, VECTOR v2)
{
	VECTOR z;
	z.x = v1.y*v2.z - v1.z*v2.y;
	z.y = v1.z*v2.x - v1.x*v2.z;
	z.z = v1.x*v2.y - v1.y*v2.x;
	return z;
}


/*******************************************************************************
 * NAME
 *        line_2v - make a line from two vectors
 *
 * SYNOPSIS
 *        #include <mcce.h>
 *
 *        LINE line_2v(VECTOR v1, VECTOR v2);
 *
 * DESCRIPTION
 *        The line_2v() function returns a LINE object passing two points, from
 *        v1 to v2.
 *
 * RETURN VALUE
 *        The line_2v() function returns a structure in LINE type.
 *
 * SEE ALSO
 *        plane_3v
 *
 * DEPENDENCY
 *       vector_normalize
 *
 * EXAMPLE
 *        #include <mcce.h>
 *        ...
 *        VECTOR v1, v2;
 *        LINE line;
 *        ...
 *        line=line_2v(v1, v2);
 *
 * AUTHOR
 *        Junjun Mao, 05/28/2003
 *******************************************************************************/
LINE line_2v(VECTOR v1, VECTOR v2)
{
	LINE line;
	line.p0 = v1;
	line.t = vector_normalize(vector_vminusv(v2, v1));
	return line;
}


/*******************************************************************************
 * NAME
 *        geom_3v_onto_3v - geometry superimpose function
 *
 * SYNOPSIS
 *        #include <stdio.h>
 *        #include <string.h>
 *        #include <mcce.h>
 *
 *        GEOM geom_3v_onto_3v(VECTOR v1, VECTOR v2, VECTOR v3, VECTOR t1,
 *                             VECTOR t2, VECTOR t3);
 *
 * DESCRIPTION
 *        The geom_3v_onto_3v() function superimposes point v1 to t1, then line
 *        v1-v2 to t1-t2,  then plane  v1-v2-v3  to  t1-t2-t3,  and returns the
 *        transformation in a GEOM object.
 *
 * RETUERN VALUE
 *        The geom_3v_onto_3v() function returns a GEOM object.
 *
 * SEE ALSO
 *        geom_reset, geom_dump, geom_move, geom_roll, geom_inverse, geom_apply,
 *        all, avv, line_3v, plane_3v
 *
 * EXAMPLE
 *        #include <stdio.h>
 *        #include <string.h>
 *        #include <mcce.h>
 *
 *        int main()
 *        {  GEOM recorder;
 *           VECTOR v1, v2, v3, t1, t2, t3;
 *           v1.x = 0.0; v1.y = 0.0; v1.z = 0.0;
 *           v2.x = 1.0; v2.y = 0.0; v2.z = 0.0;
 *           v3.x = 0.0; v3.y = 1.0; v3.z = 0.0;
 *
 *           t1.x = 0.0; t1.y = 0.0; t1.z = 0.0;
 *           t2.x = 0.0; t2.y = 0.0; t2.z = 1.0;
 *           t3.x = 0.0; t3.y = 1.0; t3.z = 0.0;
 *
 *           recorder = geom_3v_onto_3v(v1, v2, v3, t1, t2, t3);
 *           geom_dump(recorder);
 *
 *           return 0;
 *        }
 *
 * DEPENDENCY
 *        geom_reset, geom_move, geom_roll, geom_apply, all, avv, line_2v,
 *        plane_3v
 *
 * AUTHOR
 *        Junjun Mao, 05/27/2003
 *******************************************************************************/
GEOM geom_3v_onto_3v(VECTOR v1, VECTOR v2, VECTOR v3, VECTOR t1, VECTOR t2, VECTOR t3)
{
	GEOM op;
	float angle;
	LINE axis;
	VECTOR v123;
	PLANE plane_v123, plane_t123;

	/* step 1, superimpose v1 to t1 */
	geom_reset(&op);
	geom_move(&op, vector_vminusv(t1, v1));

	/* step 2, align v1-v2 to t1-t2 */
	angle = all(line_2v(v1, v2), line_2v(t1, t2));
	axis.p0 = t1;
	axis.t  = vector_normalize(vector_vxv(vector_vminusv(v2, v1), vector_vminusv(t2, t1)));
	geom_roll(&op, angle, axis);

	/* normal direction of plane v123 should be updated */
	geom_apply(op, &v1);
	geom_apply(op, &v2);
	geom_apply(op, &v3);
	plane_v123 = plane_3v(v1, v2, v3);
	plane_t123 = plane_3v(t1, t2, t3);
	v123 = plane_v123.t;

	/*step 3, align v1-v2-v3 to t1-t2-t3 */
	angle = avv(v123, plane_t123.t);
	axis.p0 = t1;
	axis.t  = vector_normalize(vector_vxv(v123, plane_t123.t));
	geom_roll(&op, angle, axis);

	return op;
}


void geom_roll(GEOM *op, float phi, LINE axis)
{  /*--- "Rotate about an arbitrary axis"  CRC Math handbook 4th edition */
	VECTOR v;
	float t, SIN, COS;
	int i, j;
	float m1[4][4], m2[4][4], m3[4][4];

	/* extreme contidions */
	t = fabs(axis.t.x) + fabs(axis.t.y) + fabs(axis.t.z);
	if ((fabs(phi) < 1.0E-8) || t <1.0E-8) return;


	/* translate to (0,0,0) */
	m1[0][0] = 1.0; m1[0][1] = 0.0; m1[0][2] = 0.0; m1[0][3] = -axis.p0.x;
	m1[1][0] = 0.0; m1[1][1] = 1.0; m1[1][2] = 0.0; m1[1][3] = -axis.p0.y;
	m1[2][0] = 0.0; m1[2][1] = 0.0; m1[2][2] = 1.0; m1[2][3] = -axis.p0.z;
	m1[3][0] = 0.0; m1[3][1] = 0.0; m1[3][2] = 0.0; m1[3][3] = 1.0;
	mxm4(m1, op->M, m2);

	/* rotate */
	v = axis.t;

	SIN = sin(phi); COS = cos(phi);

	m1[0][0] = v.x*v.x*(1.0-COS) + COS;
	m1[0][1] = v.x*v.y*(1.0-COS) - v.z*SIN;
	m1[0][2] = v.x*v.z*(1.0-COS) + v.y*SIN;

	m1[1][0] = v.x*v.y*(1.0-COS) + v.z*SIN;
	m1[1][1] = v.y*v.y*(1.0-COS) + COS;
	m1[1][2] = v.y*v.z*(1.0-COS) - v.x*SIN;

	m1[2][0] = v.x*v.z*(1.0-COS) - v.y*SIN;
	m1[2][1] = v.y*v.z*(1.0-COS) + v.x*SIN;
	m1[2][2] = v.z*v.z*(1.0-COS) + COS;

	m1[0][3] = 0.0; m1[1][3] = 0.0; m1[2][3] = 0.0; m1[3][3] = 1.0;
	m1[3][0] = 0.0; m1[3][1] = 0.0; m1[3][2] = 0.0;

	mxm4(m1, m2, m3);

	/* translate back */
	m1[0][0] = 1.0; m1[0][1] = 0.0; m1[0][2] = 0.0; m1[0][3] = axis.p0.x;
	m1[1][0] = 0.0; m1[1][1] = 1.0; m1[1][2] = 0.0; m1[1][3] = axis.p0.y;
	m1[2][0] = 0.0; m1[2][1] = 0.0; m1[2][2] = 1.0; m1[2][3] = axis.p0.z;
	m1[3][0] = 0.0; m1[3][1] = 0.0; m1[3][2] = 0.0; m1[3][3] = 1.0;
	mxm4(m1, m3, m2);

	/* load the result in m2 */
	for (i=0; i<4; i++)
		for (j=0; j<4; j++)
			op->M[i][j] = m2[i][j];

	return;
}


/*******************************************************************************
 * NAME
 *        geom_apply - apply geometry transformation to a vector
 *
 * SYNOPSIS
 *        #include <mcce.h>
 *
 *        void geom_apply(GEOM op, VECTOR *v)
 *
 * DESCRIPTION
 *        The geom_apply() applies the transformation recorded in transformation
 *        recorder op to a vector. To apply the transformation to atoms, use
 *        geom_apply_atoms()
 *
 * SEE ALSO
 *        geom_reset, geom_dump, geom_move, geom_roll, geom_3v_onto_3v,
 *        geom_apply_atoms()
 *
 * EXAMPLE
 *        #include <stdio.h>
 *        #include <mcce.h>
 *
 *        int main()
 *        {  GEOM recorder;
 *           VECTOR v1, v2;
 *
 *           v.x = 1.0; v.y = 1.0; v.z = 1.0;
 *           geom_reset(&recorder);
 *           geom_move(&recorder, v);
 *           geom_apply(&v);
 *
 *           return 0;
 *        }
 *
 * AUTHOR
 *        Junjun Mao, 05/27/2003
 *******************************************************************************/
void geom_apply(GEOM op, VECTOR *v)
{
	float vh[4];

	vh[0] = v->x;
	vh[1] = v->y;
	vh[2] = v->z;
	vh[3] = 1.0;

	v->x = op.M[0][0]*vh[0] + op.M[0][1]*vh[1] + op.M[0][2]*vh[2] + op.M[0][3]*vh[3];
	v->y = op.M[1][0]*vh[0] + op.M[1][1]*vh[1] + op.M[1][2]*vh[2] + op.M[1][3]*vh[3];
	v->z = op.M[2][0]*vh[0] + op.M[2][1]*vh[1] + op.M[2][2]*vh[2] + op.M[2][3]*vh[3];

	return;
}

/*******************************************************************************
 * NAME
 *        geom_inverse - geometry transformation inverse function
 *
 * SYNOPSIS
 *        #include <stdio.h>
 *        #include <string.h>
 *        #include <mcce.h>
 *
 *        void geom_inverse(GEOM *op);
 *
 * DESCRIPTION
 *        The geom_inverse() function reverses the transformation recorded in the
 *        operation recorder op by inverting the passed in transformation matrix.
 *
 * SEE ALSO
 *        geom_reset, geom_dump, geom_move, geom_roll, geom_3v_onto_3v
 *
 * EXAMPLE
 *        #include <stdio.h>
 *        #include <string.h>
 *        #include <mcce.h>
 *
 *        int main()
 *        {  GEOM recorder;
 *           VECTOR v;
 *
 *           v.x = 1.0; v.y = 1.0; v.z = 1.0;
 *           geom_reset(&recorder);
 *           geom_move(&recorder, v);
 *           geom_inverse(&op);
 *           geom_dump(recorder);
 *
 *           return 0;
 *        }
 *
 * DEPENDENCY
 *        det4
 *
 * AUTHOR
 *        Junjun Mao, 05/27/2003
 *******************************************************************************/
void geom_inverse(GEOM *op)
{
	float t[4][4];
	float s;		/* the determinant of this matrix */

	memcpy(t, op->M, 16*sizeof(float));

	s = det4(t);

	op->M[0][0] = (t[1][1] * (t[2][2] * t[3][3] - t[2][3] * t[3][2]) +
			t[1][2] * (t[2][3] * t[3][1] - t[2][1] * t[3][3]) +
			t[1][3] * (t[2][1] * t[3][2] - t[2][2] * t[3][1])) / s;

	op->M[0][1] = (t[2][1] * (t[0][2] * t[3][3] - t[0][3] * t[3][2]) +
			t[2][2] * (t[0][3] * t[3][1] - t[0][1] * t[3][3]) +
			t[2][3] * (t[0][1] * t[3][2] - t[0][2] * t[3][1])) / s;

	op->M[0][2] = (t[3][1] * (t[0][2] * t[1][3] - t[0][3] * t[1][2]) +
			t[3][2] * (t[0][3] * t[1][1] - t[0][1] * t[1][3]) +
			t[3][3] * (t[0][1] * t[1][2] - t[0][2] * t[1][1])) / s;

	op->M[0][3] = (t[0][1] * (t[1][3] * t[2][2] - t[1][2] * t[2][3]) +
			t[0][2] * (t[1][1] * t[2][3] - t[1][3] * t[2][1]) +
			t[0][3] * (t[1][2] * t[2][1] - t[1][1] * t[2][2])) / s;

	op->M[1][0] = (t[1][2] * (t[2][0] * t[3][3] - t[2][3] * t[3][0]) +
			t[1][3] * (t[2][2] * t[3][0] - t[2][0] * t[3][2]) +
			t[1][0] * (t[2][3] * t[3][2] - t[2][2] * t[3][3])) / s;

	op->M[1][1] = (t[2][2] * (t[0][0] * t[3][3] - t[0][3] * t[3][0]) +
			t[2][3] * (t[0][2] * t[3][0] - t[0][0] * t[3][2]) +
			t[2][0] * (t[0][3] * t[3][2] - t[0][2] * t[3][3])) / s;

	op->M[1][2] = (t[3][2] * (t[0][0] * t[1][3] - t[0][3] * t[1][0]) +
			t[3][3] * (t[0][2] * t[1][0] - t[0][0] * t[1][2]) +
			t[3][0] * (t[0][3] * t[1][2] - t[0][2] * t[1][3])) / s;

	op->M[1][3] = (t[0][2] * (t[1][3] * t[2][0] - t[1][0] * t[2][3]) +
			t[0][3] * (t[1][0] * t[2][2] - t[1][2] * t[2][0]) +
			t[0][0] * (t[1][2] * t[2][3] - t[1][3] * t[2][2])) / s;

	op->M[2][0] = (t[1][3] * (t[2][0] * t[3][1] - t[2][1] * t[3][0]) +
			t[1][0] * (t[2][1] * t[3][3] - t[2][3] * t[3][1]) +
			t[1][1] * (t[2][3] * t[3][0] - t[2][0] * t[3][3])) / s;

	op->M[2][1] = (t[2][3] * (t[0][0] * t[3][1] - t[0][1] * t[3][0]) +
			t[2][0] * (t[0][1] * t[3][3] - t[0][3] * t[3][1]) +
			t[2][1] * (t[0][3] * t[3][0] - t[0][0] * t[3][3])) / s;

	op->M[2][2] = (t[3][3] * (t[0][0] * t[1][1] - t[0][1] * t[1][0]) +
			t[3][0] * (t[0][1] * t[1][3] - t[0][3] * t[1][1]) +
			t[3][1] * (t[0][3] * t[1][0] - t[0][0] * t[1][3])) / s;

	op->M[2][3] = (t[0][3] * (t[1][1] * t[2][0] - t[1][0] * t[2][1]) +
			t[0][0] * (t[1][3] * t[2][1] - t[1][1] * t[2][3]) +
			t[0][1] * (t[1][0] * t[2][3] - t[1][3] * t[2][0])) / s;

	op->M[3][0] = (t[1][0] * (t[2][2] * t[3][1] - t[2][1] * t[3][2]) +
			t[1][1] * (t[2][0] * t[3][2] - t[2][2] * t[3][0]) +
			t[1][2] * (t[2][1] * t[3][0] - t[2][0] * t[3][1])) / s;

	op->M[3][1] = (t[2][0] * (t[0][2] * t[3][1] - t[0][1] * t[3][2]) +
			t[2][1] * (t[0][0] * t[3][2] - t[0][2] * t[3][0]) +
			t[2][2] * (t[0][1] * t[3][0] - t[0][0] * t[3][1])) / s;

	op->M[3][2] = (t[3][0] * (t[0][2] * t[1][1] - t[0][1] * t[1][2]) +
			t[3][1] * (t[0][0] * t[1][2] - t[0][2] * t[1][0]) +
			t[3][2] * (t[0][1] * t[1][0] - t[0][0] * t[1][1])) / s;

	op->M[3][3] = (t[0][0] * (t[1][1] * t[2][2] - t[1][2] * t[2][1]) +
			t[0][1] * (t[1][2] * t[2][0] - t[1][0] * t[2][2]) +
			t[0][2] * (t[1][0] * t[2][1] - t[1][1] * t[2][0])) / s;
	return;
}


/*******************************************************************************
 * NAME
 *        geom_move - geometry translation function
 *
 * SYNOPSIS
 *        #include <stdio.h>
 *        #include <string.h>
 *        #include <mcce.h>
 *
 *        void geom_move(GEOM *op, VECTOR v);
 *
 * DESCRIPTION
 *        The geom_move()  function records a translation  defined by vector v to
 *        the geometry operation recorder op so the translation can be applied to
 *        multiple points later by geom_apply.
 *
 * SEE ALSO
 *        geom_reset, geom_dump, geom_roll, geom_inverse, geom_3v_onto_3v,
 *        geom_apply
 *
 * EXAMPLE
 *        #include <stdio.h>
 *        #include <string.h>
 *        #include <mcce.h>
 *
 *        int main()
 *        {  GEOM recorder;
 *           VECTOR v;
 *
 *           v.x = 1.0; v.y = 2.0; v.z = 3.0;
 *
 *           geom_reset(&recorder);
 *           geom_move(&recorder, v);
 *           geom_dump(recorder);
 *
 *           return 0;
 *        }
 *
 * DEPENDENCY
 *        mxm4
 *
 * AUTHOR
 *        Junjun Mao, 05/26/2003
 *******************************************************************************/
void geom_move(GEOM *op, VECTOR v)
{
	int i, j;
	float m1[4][4], m2[4][4];

	/* translation */
	m1[0][0] = 1.0; m1[0][1] = 0.0; m1[0][2] = 0.0; m1[0][3] = v.x;
	m1[1][0] = 0.0; m1[1][1] = 1.0; m1[1][2] = 0.0; m1[1][3] = v.y;
	m1[2][0] = 0.0; m1[2][1] = 0.0; m1[2][2] = 1.0; m1[2][3] = v.z;
	m1[3][0] = 0.0; m1[3][1] = 0.0; m1[3][2] = 0.0; m1[3][3] = 1.0;

	/* apply translation */
	mxm4(m1, op->M, m2);

	/* load the geom operation */
	for (i=0; i<4; i++)
		for (j=0; j<4; j++)
			op->M[i][j] = m2[i][j];

	return;
}


/*******************************************************************************
 * NAME
 *        geom_reset - reset geometry operation recorder
 *
 * SYNOPSIS
 *        #include <string.h>
 *        #include <mcce.h>
 *
 *        void geom_reset(GEOM *op)
 *
 * DESCRIPTION
 *        The geom_reset() function resets the transformation matrix and history
 *        records of the geometry  operation recorder op.  It is  recommended to
 *        call this function  for newly defined GEOM object  because c  does not
 *        initialize a non-static varaible.
 *
 * SEE ALSO
 *        geom_dump, geom_move, geom_roll, geom_inverse, geom_3v_onto_3v,
 *        geom_apply
 *
 * EXAMPLE
 *        #include <string.h>
 *        #include <mcce.h>
 *
 *        int main()
 *        {  GEOM recorder;
 *           geom_reset(&recorder);
 *           return 0;
 *        }
 *
 * AUTHOR
 *        Junjun Mao, 05/26/2003
 *******************************************************************************/
void geom_reset(GEOM *op)
{
	op->M[0][0] = 1.0; op->M[0][1] = 0.0; op->M[0][2] = 0.0; op->M[0][3] = 0.0;
	op->M[1][0] = 0.0; op->M[1][1] = 1.0; op->M[1][2] = 0.0; op->M[1][3] = 0.0;
	op->M[2][0] = 0.0; op->M[2][1] = 0.0; op->M[2][2] = 1.0; op->M[2][3] = 0.0;
	op->M[3][0] = 0.0; op->M[3][1] = 0.0; op->M[3][2] = 0.0; op->M[3][3] = 1.0;
	return;
}


/*******************************************************************************
 * NAME
 *        mxm4 - cross product of two 4 by 4 matrices
 *
 * SYNOPSIS
 *        #include <mcce.h>
 *
 *        void mxm4(float m1[][4], float m2[][4], float m3[][4]);
 *
 * DESCRIPTION
 *        The mxm4() function calculates the cross product of matrices m1[4][4]
 *        and m2[4][4], and stores the resulted 4 by 4 matrix in m3[4][4].
 *
 * EXAMPLE
 *        #include <mcce.h>
 *
 *        int main()
 *        {  float MA[4][4] = {{ 1,  2,  3,  4},
 *                             { 5,  6,  7,  8},
 *                             { 9, 10, 11, 12},
 *                             {13, 13, 15, 16}};
 *           float MB[4][4] = {{16, 15, 14, 13},
 *                             {12, 11, 10,  9},
 *                             { 8,  7,  6,  5},
 *                             { 4,  3,  2,  1}};
 *           float MC[4][4];
 *
 *           mxm4(MA, MB, MC);
 *
 *           return 0;
 *        }
 *
 * AUTHOR
 *        Junjun Mao, 05/26/2003
 *******************************************************************************/
void mxm4(float m1[4][4], float m2[4][4], float m3[4][4])
{
	m3[0][0]=m1[0][0]*m2[0][0]+m1[0][1]*m2[1][0]+m1[0][2]*m2[2][0]+m1[0][3]*m2[3][0];
	m3[0][1]=m1[0][0]*m2[0][1]+m1[0][1]*m2[1][1]+m1[0][2]*m2[2][1]+m1[0][3]*m2[3][1];
	m3[0][2]=m1[0][0]*m2[0][2]+m1[0][1]*m2[1][2]+m1[0][2]*m2[2][2]+m1[0][3]*m2[3][2];
	m3[0][3]=m1[0][0]*m2[0][3]+m1[0][1]*m2[1][3]+m1[0][2]*m2[2][3]+m1[0][3]*m2[3][3];

	m3[1][0]=m1[1][0]*m2[0][0]+m1[1][1]*m2[1][0]+m1[1][2]*m2[2][0]+m1[1][3]*m2[3][0];
	m3[1][1]=m1[1][0]*m2[0][1]+m1[1][1]*m2[1][1]+m1[1][2]*m2[2][1]+m1[1][3]*m2[3][1];
	m3[1][2]=m1[1][0]*m2[0][2]+m1[1][1]*m2[1][2]+m1[1][2]*m2[2][2]+m1[1][3]*m2[3][2];
	m3[1][3]=m1[1][0]*m2[0][3]+m1[1][1]*m2[1][3]+m1[1][2]*m2[2][3]+m1[1][3]*m2[3][3];

	m3[2][0]=m1[2][0]*m2[0][0]+m1[2][1]*m2[1][0]+m1[2][2]*m2[2][0]+m1[2][3]*m2[3][0];
	m3[2][1]=m1[2][0]*m2[0][1]+m1[2][1]*m2[1][1]+m1[2][2]*m2[2][1]+m1[2][3]*m2[3][1];
	m3[2][2]=m1[2][0]*m2[0][2]+m1[2][1]*m2[1][2]+m1[2][2]*m2[2][2]+m1[2][3]*m2[3][2];
	m3[2][3]=m1[2][0]*m2[0][3]+m1[2][1]*m2[1][3]+m1[2][2]*m2[2][3]+m1[2][3]*m2[3][3];

	m3[3][0]=m1[3][0]*m2[0][0]+m1[3][1]*m2[1][0]+m1[3][2]*m2[2][0]+m1[3][3]*m2[3][0];
	m3[3][1]=m1[3][0]*m2[0][1]+m1[3][1]*m2[1][1]+m1[3][2]*m2[2][1]+m1[3][3]*m2[3][1];
	m3[3][2]=m1[3][0]*m2[0][2]+m1[3][1]*m2[1][2]+m1[3][2]*m2[2][2]+m1[3][3]*m2[3][2];
	m3[3][3]=m1[3][0]*m2[0][3]+m1[3][1]*m2[1][3]+m1[3][2]*m2[2][3]+m1[3][3]*m2[3][3];

	return;
}


/*******************************************************************************
 * NAME
 *        line_3v - make a plane from three points
 *
 * SYNOPSIS
 *        #include <mcce.h>
 *
 *        PLANE plane_3v(VECTOR v1, VECTOR v2, VECTOR v3);
 *
 * DESCRIPTION
 *        The plane_3v() function returns a PLANE object passing three points.
 *        The normal direction is defined by the cross product of direction v1
 *        to v2 and the direction of v2 to v3.
 *
 * RETURN VALUE
 *        The plane_3v() function returns a structure in PLANE type.
 *
 * SEE ALSO
 *        line_2v
 *
 * DEPENDENCY
 *       vector_normalize, vector_vxv, vector_vminusv
 *
 * EXAMPLE
 *        #include <mcce.h>
 *        ...
 *        VECTOR v1, v2, v3;
 *        PLANE p;
 *        ...
 *        p=plane_3p(v1, v2, v3);
 *
 * AUTHOR
 *        Junjun Mao, 05/28/2003
 *******************************************************************************/
PLANE plane_3v(VECTOR v1, VECTOR v2, VECTOR v3)
{
	PLANE plane;
	plane.p0 = v1;
	plane.t = vector_normalize(vector_vxv(vector_vminusv(v2, v1),vector_vminusv(v3, v2)));
	return plane;
}


/*******************************************************************************
 * NAME
 *        vdotv - dot product of two vectors
 *
 * SYNOPSIS
 *        #include <mcce.h>
 *
 *        double vdotv(VECTOR v1, VECTOR v2);
 *
 * DESCRIPTION
 *        The vdotv() returns the dot product of two vectors.  If the two vectors
 *        are  normalized  vectors,  the  dot product  is the cosine of the angle
 *        between two vectors.
 *
 * RETURN VALUE
 *        The returned floating point number is the dot product of two vectors.
 *
 * SEE ALSO
 *        vector_vxv
 *
 * EXAMPLE
 *        #include <stdio.h>
 *        #include <mcce.h>
 *        ...
 *        VECTOR v1, v2;
 *        float phi_cos;
 *        ...
 *        v1 = vector_normalize(v1);
 *        v2 = vector_normalize(v2);
 *        phi_cos = vdotv(v1, v2);
 *
 * AUTHOR
 *        Junjun Mao, 05/28/2003
 *******************************************************************************/
double vdotv(VECTOR v1, VECTOR v2)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}
