#ifndef SORTBYXASC_H
#define SORTBYXASC_H
#include <QtGui>
class sortByXAsc
{
public:
    sortByXAsc();
    bool operator() (const double p1, const double p2)
    {
        return p1 < p2;
    }
};

#endif // SORTBYXASC_H
