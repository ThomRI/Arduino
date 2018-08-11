#ifndef MULTIPLOT_H
#define MULTIPLOT_H

#define MAX_VALUES 1000
#include "qcustomplot.h"

#include <QVector>
#include <QList>
#include <QtDebug>

class MultiPlot : public QWidget
{
    public:
        MultiPlot(int nbrPlots, double rangeX = -1);
        virtual ~MultiPlot();

        void add(double x, const QList<float> &values);
        void clear();

    protected:

    private:
        QCustomPlot *m_plotter;
        QList<QCPAxisRect *> *m_axes;
        QList<QCPGraph *>    *m_graphs;

        QVector<double> m_X;
        QList<QVector<double> *> m_Yvalues;

        int m_nbrPlots;
        double m_rangeX;
};

#endif // MULTIPLOT_H
