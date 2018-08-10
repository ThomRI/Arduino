#include "../include/DerivatorWidget.h"

DerivatorWidget::DerivatorWidget(double rangeX) :
    m_rangeX(rangeX)
{
    /* Creating interface */
    m_plotter = new QCustomPlot(this);
    m_plotter->plotLayout()->clear();

    m_axis = new QCPAxisRect(m_plotter);
    m_dAxis = new QCPAxisRect(m_plotter);

    m_graph = m_plotter->addGraph(m_axis->axis(QCPAxis::atBottom), m_axis->axis(QCPAxis::atLeft));
    m_dGraph = m_plotter->addGraph(m_dAxis->axis(QCPAxis::atBottom), m_dAxis->axis(QCPAxis::atLeft));

    m_plotter->plotLayout()->addElement(0, 0, m_axis);
    m_plotter->plotLayout()->addElement(1, 0, m_dAxis);

    QCPMarginGroup *marginGroup = new QCPMarginGroup(m_plotter);
    m_axis->setMarginGroup(QCP::msLeft, marginGroup);
    m_dAxis->setMarginGroup(QCP::msLeft, marginGroup);

    /* Qt Layout */
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_plotter);

    setLayout(layout);

}

void DerivatorWidget::add(double x, double y)
{
    m_X.append(x);
    m_Y.append(y);

    /* Erasing some values */
    if(m_X.size() > MAX_VALUES) {
        m_X.erase(m_X.begin());

        m_Y.erase(m_Y.begin());
        m_dY.erase(m_dY.begin());
    }

    /* Derivative computations */
    if(m_Y.size() <= 1 || m_X.size() <= 1) m_dY.append(0.0);
    else {
        int i = m_X.size() - 1;
        m_dY.append( (m_Y.at(i) - m_Y.at(i - 1)) / (m_X.at(i) - m_X.at(i - 1)) );
    }

    m_graph->setData(m_X, m_Y);
    m_dGraph->setData(m_X, m_dY);

    rescale(x);
    m_plotter->replot();
}

void DerivatorWidget::rescale(double x)
{
    m_axis->axis(QCPAxis::atLeft)->rescale();
    m_dAxis->axis(QCPAxis::atLeft)->rescale();

    if(m_rangeX < 0) {
        m_axis->axis(QCPAxis::atBottom)->rescale();
        m_dAxis->axis(QCPAxis::atBottom)->rescale();
    }
    else {
        m_axis->axis(QCPAxis::atBottom)->setRange(x - m_rangeX, x);
        m_dAxis->axis(QCPAxis::atBottom)->setRange(x - m_rangeX, x);
    }
}

void DerivatorWidget::clear()
{
    m_X.clear();
    m_Y.clear();
    m_dY.clear();

    m_plotter->replot();
}

DerivatorWidget::~DerivatorWidget()
{
    //dtor
}
