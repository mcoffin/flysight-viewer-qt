#ifndef FLARESCORING_H
#define FLARESCORING_H

#include "scoringmethod.h"

class MainWindow;

class FlareScoring : public ScoringMethod
{
public:
    FlareScoring(MainWindow *mainWindow);

    double windowBottom(void) const { return mWindowBottom; }
    void setWindowBottom(double windowBottom);

    double score(const QVector< DataPoint > &result);
    QString scoreAsText(double score);

    void prepareDataPlot(DataPlot *plot);

    bool getWindowBounds(const QVector< DataPoint > &result,
                         DataPoint &dpBottom, DataPoint &dpTop);

    void optimize() { ScoringMethod::optimize(mMainWindow, mWindowBottom); }

private:
    MainWindow *mMainWindow;

    double      mWindowBottom;

signals:

public slots:
};

#endif // FLARESCORING_H
