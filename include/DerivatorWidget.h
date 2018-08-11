#ifndef DERIVATORWIDGET_H
#define DERIVATORWIDGET_H

#define MAX_VALUES 1000 // Drops
#include "qcustomplot.h"


class DerivatorWidget : public QWidget
{
    public:
        DerivatorWidget(double rangeX = -1);
        virtual ~DerivatorWidget();

        void add(double x, double y);
        void clear();

    protected:
        void rescale(double x);

    private:
        QCustomPlot *m_plotter;
        QCPAxisRect *m_axis, *m_dAxis;
        QCPGraph *m_graph, *m_dGraph;

        /* Values */
        QVector<double> m_X;
        QVector<double> m_Y, m_dY;

        double m_rangeX;
};

#endif // DERIVATORWIDGET_H
