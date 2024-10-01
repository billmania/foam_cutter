#include <stdio.h>
#include "emcpos.h"
#include "kinematics.h"

int main(void)
{
    double j[3] = {0.0};
    int function_result = -1;

    EmcPose pos = {{0.0, 0.0, 0.0}, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    KINEMATICS_FORWARD_FLAGS fflags = 0UL;
    KINEMATICS_INVERSE_FLAGS iflags = 0UL;

    for (double x = 0.0; x <= 100.0; x += 10.0) {
        for (double y = 0.0; y <= 100.0; y += 10.0) {
            pos.tran.x = x;
            pos.tran.y = y;
            function_result = kinematicsInverse(&pos, &j, &iflags, &fflags);
            if (function_result != 0) {
                printf("kinematicsInverse returned %d\n", function_result);
            } else {
                printf(
                    "kinematicsInverse: Axes: %0.3f, %0.3f Joints: %0.3f, %0.3f\n",
                    pos.tran.x,
                    pos.tran.y,
                    j[0],
                    j[1]
                    );
            }
        }
    }
}
