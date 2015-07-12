#include <QMessageBox>
#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent): QWidget(parent)
{
    //Timer erstellen
    Timer = new QTimer(this);
    connect(Timer, SIGNAL(timeout()),this, SLOT(UpdateLine()));
    //Timer mit 10 Milisikunden Initialisieren und Starten
    Timer->start(10);
    Drawline = NULL;
    LastPoint.setX(0);
    LastPoint.setY(0);
    Instance = this;
    Laserstate = 0;
}

void RenderArea::UpdateLine()
{
    double perc,dist;
    static int distdone;
    if (CurrentLine != NULL)
    {
        distdone ++;
        dist = sqrt((CurrentLine->dx()*CurrentLine->dx())+(CurrentLine->dy()*CurrentLine->dy()));
        perc = distdone/dist;
        if (perc > 1)
        {
            LaserPos = CurrentLine->p2();
            LineList.append(CurrentLine);
            CurrentLine = NULL;
            delete Drawline;
            Drawline = NULL;
            emit DrawingDone();
        }
        else
        {
            if(Drawline == NULL)
            {
                Drawline = new QLine();
            }
            Drawline->setP1(CurrentLine->p1());
            Drawline->setP2(QPoint(CurrentLine->x1()+(CurrentLine->dx()*perc),CurrentLine->y1()+(CurrentLine->dy()*perc)));
            LaserPos = Drawline->p2();
        }
        repaint();
    }
    else
    {
        if (MovePath != NULL)
        {
            distdone ++;
            dist = sqrt((MovePath->dx()*MovePath->dx())+(MovePath->dy()*MovePath->dy()));
            perc = distdone/dist;
            if (perc > 1)
            {

                delete MovePath;
                MovePath = NULL;
                emit DrawingDone();
            }
            else
            {
                LaserPos.setX(MovePath->x1()+(MovePath->dx()*perc));
                LaserPos.setY(MovePath->y1()+(MovePath->dy()*perc));
            }
            repaint();
        }
        else
        {
            distdone = 0;
        }
    }
}

void RenderArea::paintEvent(QPaintEvent *) {
        QPainter p(this);
        QLine *L;
        p.setPen(Qt::black);
        foreach (L, LineList)
        {
            p.drawLine(*L);
        }
        if (Drawline != NULL)
        {
            p.setPen(Qt::red);
            p.drawLine(*Drawline);
        }
        p.setPen(Qt::green);
        p.drawEllipse(LaserPos, 2 ,2);
        //Status Display
        p.setPen(Qt::black);
        p.setBrush(Qt::white);
        p.drawRect(0,height()-14,100,13);
        switch (Laserstate) {
        case 0:
            p.setBrush(Qt::darkBlue);
            break;
        case 1:
            p.setBrush(Qt::darkRed);
            break;
        case 2:
            p.setBrush(Qt::blue);
            break;
        case 3:
            p.setBrush(Qt::red);
            break;
        }
        p.drawRect(50,height()-14,50,13);
        p.drawText(2,height()-3,"State:");
        switch (Laserstate) {
        case 0:
            p.drawText(52,height()-3,"OFF");
            break;
        case 1:
            p.drawText(52,height()-3,"ON");
            break;
        case 2:
            p.drawText(52,height()-3,"MOVE");
            break;
        case 3:
            p.drawText(52,height()-3,"CUT");
            break;
        }
    }
void RenderArea::Cut(int x, int y)
{
    Laserstate = 3;
    QLine *pQLine = new QLine(LastPoint.x(),LastPoint.y(),x,y);
    LastPoint.setX(x);
    LastPoint.setY(y);
    AddLine(pQLine);
}

void RenderArea::Move(int x, int y)
{
    Laserstate = 2;
    MovePath = new QLine(LastPoint.x(),LastPoint.y(),x,y);
    LastPoint.setX(x);
    LastPoint.setY(y);
}

void RenderArea::On()
{
    Laserstate = 1;
}

void RenderArea::Off()
{
    Laserstate = 0;
}

bool RenderArea::AddLine(QLine *L)
{
    if(CurrentLine == NULL)
    {
        CurrentLine = L;
        return true;
    }
    return false;
}

void RenderArea::Reset()
{
    //Timer stoppen und alle Felder leeren
    Timer->stop();

    if(MovePath != NULL)
    {
        delete MovePath;
        MovePath = NULL;
    }
    if(CurrentLine != NULL)
    {
        delete CurrentLine;
        CurrentLine = NULL;
    }
    LineList.clear();
    LaserPos.setX(0);
    LaserPos.setY(0);
    LastPoint.setX(0);
    LastPoint.setY(0);
    Laserstate = 0;
    Timer->start(10);
}

void RenderArea::ShowError(std::string Msg)
{
    QMessageBox::information(this, QString("Fehler"), QString(Msg.c_str()));

}
