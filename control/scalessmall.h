#ifndef SCALESSMALL_H
#define SCALESSMALL_H

#include "control/scales.h"


class ScalesSmall : public Scales
{

    public:
        ScalesSmall();

    private:
        void serialStrConver2Data(QString msg);
};

#endif // SCALESSMALL_H
