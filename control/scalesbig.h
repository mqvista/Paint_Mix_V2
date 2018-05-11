#ifndef SCALESBIG_H
#define SCALESBIG_H

#include "control/scales.h"


class ScalesBig : public Scales
{
    public:
        ScalesBig();

    private:
        void serialStrConver2Data();
        void splitData(QString msg);
};

#endif // SCALESBIG_H
