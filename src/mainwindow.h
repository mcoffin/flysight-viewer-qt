#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QVector>

#include "dataplot.h"
#include "datapoint.h"
#include "plotvalue.h"

class DataView;
class QCPRange;
class QCustomPlot;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_actionImport_triggered();
    void on_actionExit_triggered();

    void on_actionElevation_triggered();
    void on_actionVerticalSpeed_triggered();
    void on_actionHorizontalSpeed_triggered();
    void on_actionTotalSpeed_triggered();
    void on_actionDiveAngle_triggered();
    void on_actionCurvature_triggered();
    void on_actionGlideRatio_triggered();

    void on_actionPan_triggered();
    void on_actionZoom_triggered();
    void on_actionMeasure_triggered();
    void on_actionZero_triggered();
    void on_actionGround_triggered();

    void on_actionTime_triggered();
    void on_actionDistance2D_triggered();
    void on_actionDistance3D_triggered();

    void onDataPlot_zoom(const QCPRange &range);
    void onDataPlot_pan(double xBegin, double xEnd);
    void onDataPlot_measure(double xBegin, double xEnd);
    void onDataPlot_zero(double xMark);
    void onDataPlot_ground(double xMark);

    void onDataPlot_mark(double xMark);
    void onDataPlot_clear();    

    void onTopView_mousePress(QMouseEvent *event);
    void onTopView_mouseRelease(QMouseEvent *event);
    void onTopView_mouseMove(QMouseEvent *event);

    void onLeftView_mouseMove(QMouseEvent *event);
    void onFrontView_mouseMove(QMouseEvent *event);

    void on_actionImportGates_triggered();
    void on_actionPreferences_triggered();

private:
    typedef enum {
        Time = 0,
        Distance2D,
        Distance3D
    } XAxisType;

    typedef enum {
        Elevation = 0,
        VerticalSpeed,
        HorizontalSpeed,
        TotalSpeed,
        DiveAngle,
        Curvature,
        GlideRatio,
        yaLast
    } YAxisType;

    Ui::MainWindow       *m_ui;
    QVector< DataPoint >  m_data;

    QVector< PlotValue* > m_xValues;
    XAxisType             m_xAxis;

    QVector< PlotValue* > m_yValues;

    double                m_xPlot, m_yPlot[yaLast];
    double                m_xView, m_yView, m_zView;
    bool                  m_markActive;

    QPoint                m_topViewBeginPos;
    bool                  m_topViewPan;
    double                m_viewDataRotation;

    PlotValue::Units      m_units;

    QVector< DataPoint >  m_waypoints;

    double                m_timeStep;

    DataView             *mLeftView;
    DataView             *mTopView;
    DataView             *mFrontView;

    DataPlot::Tool        mPrevTool;

    void writeSettings();
    void readSettings();

    void initPlot();
    void initViews();

    double getDistance(const DataPoint &dp1, const DataPoint &dp2) const;
    double getBearing(const DataPoint &dp1, const DataPoint &dp2) const;

    void initPlotData();
    void updatePlotData();
    void updateYRanges();

    void updateViewData();
    void setViewRange(QCustomPlot *plot,
                      double xMin, double xMax,
                      double yMin, double yMax);
    void addNorthArrow(QCustomPlot *plot);

    double getXValue(const DataPoint &dp, XAxisType axis);

    int findIndexBelowX(double x);
    int findIndexAboveX(double x);

    int findIndexBelowT(double t);
    int findIndexAboveT(double t);

    void onView_mouseMove(DataView *view, QMouseEvent *event);

    static double distSqrToLine(const QPointF &start, const QPointF &end,
                                const QPointF &point, double &mu);

    void updateTool();
    void updateBottom(XAxisType xAxis);
    void updateBottomActions();

    DataPoint interpolateData(double x);
    void mark(const DataPoint &dp);
};

#endif // MAINWINDOW_H
