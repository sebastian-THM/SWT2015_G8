#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QtMath>
#include <QList>
#include <QPoint>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = 0);
    bool AddLine(QLine *L);


signals:
    void DrawingDone();

public slots:
    void UpdateLine();
    void Cut(int x, int y);
    void Move(int x, int y);
    void Reset();

private:
    QList<QLine *> LineList;
    QLine * CurrentLine = NULL;
    QLine * Drawline = NULL;
    QTimer * Timer = NULL;
    QPoint LastPoint;
    QPoint LaserPos;
    QLine * MovePath = NULL;
    void paintEvent(QPaintEvent *);
};

#endif // RENDERAREA_H
