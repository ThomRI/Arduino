#include "../include/MultiPlot.h"

MultiPlot::MultiPlot(int nbrPlots, double rangeX) :
    m_nbrPlots(nbrPlots), m_rangeX(rangeX)
{
    m_plotter = new QCustomPlot();
    m_plotter->plotLayout()->clear();

    m_axes = new QList<QCPAxisRect *>();
    m_graphs = new QList<QCPGraph *>();

    /* Creating axes and graphs */
    QCPMarginGroup *marginGroup = new QCPMarginGroup(m_plotter);
    for(int i = 0;i < nbrPlots;i++) {
        QCPAxisRect *axis = new QCPAxisRect(m_plotter);
        m_axes->append(axis);
        m_graphs->append(m_plotter->addGraph(axis->axis(QCPAxis::atBottom), axis->axis(QCPAxis::atLeft)));

        m_Yvalues.append(new QVector<double>());

        m_plotter->plotLayout()->addElement(i, 0, axis);
        axis->setMarginGroup(QCP::msLeft, marginGroup);
    }
    qDebug() << "Created axes and graphs";

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_plotter);

    setLayout(layout);
}

void MultiPlot::add(double x, const QList<float> &values)
{
    if(values.size() < m_nbrPlots) {
        qDebug() << "Warning : attempted to plot " << values.size() << " value(s) (" << m_nbrPlots << " expected ).";
        return;
    }

    //qDebug() << values[0] << " " << values[1];

    /* X axis */
    m_X.append(x);
    bool erase = m_X.size() > MAX_VALUES;
    if(erase) m_X.erase(m_X.begin());

    /* Y axes */
    for(int i = 0;i < m_nbrPlots;i++) {
        QVector<double> *datas = m_Yvalues.at(i);
        QCPGraph *graph = m_graphs->at(i);
        QCPAxisRect *axis = m_axes->at(i);

        datas->append(values.at(i));

        /* Erasing some values */
        if(erase)
            datas->erase(datas->begin());

        /* Updating graphs */
        graph->setData(m_X, *datas);

        /* Rescaling */
        axis->axis(QCPAxis::atLeft)->rescale();
        if(m_rangeX < 0) {
            axis->axis(QCPAxis::atBottom)->rescale();
        } else {
            axis->axis(QCPAxis::atBottom)->setRange(x - m_rangeX, x);
        }
    }

    m_plotter->replot();
}

void MultiPlot::clear()
{
    m_X.clear();

    for(int i = 0;i < m_nbrPlots;i++) {
        m_Yvalues.at(i)->clear();
    }
}

MultiPlot::~MultiPlot()
{
    //dtor
}
