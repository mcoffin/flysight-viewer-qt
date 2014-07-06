#ifndef PLOTVALUE_H
#define PLOTVALUE_H

#include <math.h>

#include <QColor>
#include <QString>

#include "datapoint.h"

#define METERS_TO_FEET 3.28084
#define MPS_TO_MPH     2.23694
#define MPS_TO_KMH     3.6

class PlotValue: public QObject
{
    Q_OBJECT

public:
    typedef enum
    {
        Metric,
        Imperial
    } Units;

    virtual const QString title(Units units) = 0;
    virtual const QColor color() = 0;
    virtual double value(const DataPoint &dp, Units units) = 0;
};

class PlotElevation: public PlotValue
{
public:
    PlotElevation() {}
    const QString title(Units units)
    {
        if (units == Metric) return tr("Elevation (m)") ;
        else                 return tr("Elevation (ft)") ;
    }
    const QColor color() { return Qt::black ; }
    double value(const DataPoint &dp, Units units)
    {
        if (units == Metric) return dp.z;
        else                 return dp.z * METERS_TO_FEET;
    }
};

class PlotVerticalSpeed: public PlotValue
{
public:
    PlotVerticalSpeed() {}
    const QString title(Units units)
    {
        if (units == Metric) return tr("Vertical Speed (km/h)") ;
        else                 return tr("Vertical Speed (mph)") ;
    }
    const QColor color() { return Qt::red ; }
    double value(const DataPoint &dp, Units units)
    {
        if (units == Metric) return dp.velD * MPS_TO_KMH;
        else                 return dp.velD * MPS_TO_MPH;
    }
};

class PlotHorizontalSpeed: public PlotValue
{
public:
    PlotHorizontalSpeed() {}
    const QString title(Units units)
    {
        if (units == Metric) return tr("Horizontal Speed (km/h)") ;
        else                 return tr("Horizontal Speed (mph)") ;
    }
    const QColor color() { return Qt::green ; }
    double value(const DataPoint &dp, Units units)
    {
        if (units == Metric) return sqrt(dp.velE * dp.velE + dp.velN * dp.velN) * MPS_TO_KMH;
        else                 return sqrt(dp.velE * dp.velE + dp.velN * dp.velN) * MPS_TO_MPH;
    }
};

class PlotTotalSpeed: public PlotValue
{
public:
    PlotTotalSpeed() {}
    const QString title(Units units)
    {
        if (units == Metric) return tr("Total Speed (km/h)") ;
        else                 return tr("Total Speed (mph)") ;
    }
    const QColor color() { return Qt::blue ; }
    double value(const DataPoint &dp, Units units)
    {
        if (units == Metric) return sqrt(dp.velE * dp.velE + dp.velN * dp.velN + dp.velD * dp.velD) * MPS_TO_KMH;
        else                 return sqrt(dp.velE * dp.velE + dp.velN * dp.velN + dp.velD * dp.velD) * MPS_TO_MPH;
    }
};

class PlotDiveAngle: public PlotValue
{
public:
    PlotDiveAngle() {}
    const QString title(Units units)
    {
        Q_UNUSED(units);
        return tr("Dive Angle (deg)") ;
    }
    const QColor color() { return Qt::cyan ; }
    double value(const DataPoint &dp, Units units)
    {
        Q_UNUSED(units);
        const double pi = 3.14159265359;
        return atan2(dp.velD, sqrt(dp.velE * dp.velE + dp.velN * dp.velN)) / pi * 180;
    }
};

class PlotCurvature: public PlotValue
{
public:
    PlotCurvature() {}
    const QString title(Units units)
    {
        Q_UNUSED(units);
        return tr("Curvature (deg/s)") ;
    }
    const QColor color() { return Qt::magenta ; }
    double value(const DataPoint &dp, Units units)
    {
        Q_UNUSED(units);
        return dp.curv;
    }
};

class PlotGlideRatio: public PlotValue
{
public:
    PlotGlideRatio() {}
    const QString title(Units units)
    {
        Q_UNUSED(units);
        return tr("Glide Ratio") ;
    }
    const QColor color() { return Qt::yellow ; }
    double value(const DataPoint &dp, Units units)
    {
        Q_UNUSED(units);
        if (dp.velD != 0) return sqrt(dp.velE * dp.velE + dp.velN * dp.velN) / dp.velD;
        else              return 0;
    }
};

#endif // PLOTVALUE_H
