#ifndef KINEMATICS_H
#define KINEMATICS_H

#include <stddef.h>
#include <stdint.h>
#include "emcpos.h"

typedef uint32_t hal_u32_t;
typedef float hal_float_t;

#define HAL_IN 15
#define HAL_OUT 32
#define HAL_RO 64
#define HAL_RW HAL_RO | 128
#define KINS_NOT_SWITCHABLE

typedef int bool;

typedef enum {
    KINEMATICS_IDENTITY = 1,/* forward=inverse, both well-behaved */
    KINEMATICS_FORWARD_ONLY,/* forward but no inverse */
    KINEMATICS_INVERSE_ONLY,/* inverse but no forward */
    KINEMATICS_BOTH         /* forward and inverse both */
} KINEMATICS_TYPE;

typedef unsigned long int KINEMATICS_FORWARD_FLAGS;
typedef unsigned long int KINEMATICS_INVERSE_FLAGS;

int kinematicsForward(const double *, EmcPose *,
                      const KINEMATICS_FORWARD_FLAGS *,
                      KINEMATICS_INVERSE_FLAGS *);
#endif
