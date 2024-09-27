#ifndef EMC_POSE_H
#define EMC_POSE_H

typedef struct {
    double x, y, z;
} PmCartesian;

typedef struct EmcPose {
    PmCartesian tran;
    double a, b, c;
    double u, v, w;
} EmcPose;

#endif
