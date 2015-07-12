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
    //Klassenvariable Instance setzen
    //Instance Zeigt auf das zuletzt erzeugte Objekt von RenderArea
    //Nötig, um in main() auf ein GUI-Objekt zuzugreifen.
    //ui ist in view_qt private und damit aus main nicht erreichbar.
    //view_qt kann nicht geändert werden, da automatisch erzeugt, aus den Daten des GUI-Editors.
    Instance = this;
    Laserstate = 0;
}
//Diese Funktion berechnet die zu Zeichnenden Punkte
//das Errechnete wird dann an das paintEvent weiter gegeben
void RenderArea::UpdateLine()
{
    double perc,dist;
    static int distdone;
    if (CurrentLine != NULL)
    {
        distdone ++;
        dist = sqrt((CurrentLine->dx()*CurrentLine->dx())+(CurrentLine->dy()*CurrentLine->dy()));
        perc = distdone/dist;
        //Damit die träge bewegung des Lasers dargestellt werden kann
        //muss immer eine Teillinie im 10 Milisekunde Tackt gezeichnet werden
        //Hier wird im else Zweig die Teillinie berechnet
        //Wenn die Linie ganz gezeichnet ist(perc größer als 1), wird CurrentLine in die
        //LineList gespeichert
        if (perc > 1)
        {
            LaserPos = CurrentLine->p2();
            LineList.append(CurrentLine);
            CurrentLine = NULL;
            delete Drawline;
            Drawline = NULL;
            emit DrawingDone();
        }
        //wenn es nicht feritg gezeichnet wurde dann
        //setzt die neune Kordinaten für Drawline
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
        //rufe funktion paintEvent auf
        repaint();
    }
    else
    {
        if (Drawline != NULL)
        {
           delete Drawline;
           Drawline = NULL;
        }
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
            //rufe funktion paintEvent auf
            repaint();
        }
        else
        {
            distdone = 0;
        }
    }
}
//paintEvent ist algemein für die Zeichnung der der Linien zuständig
//und visualisiert die Zustände
void RenderArea::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QLine *L;
    p.setPen(Qt::black);
    //Zeichnet alle in der Listen enthaltenden Lininien in Schwarz
    foreach (L, LineList)
    {
        p.drawLine(*L);
    }
    //Hier wird die aktuelle Linie gezeichnet
    //
    if (Drawline != NULL)
    {
        p.setPen(Qt::red);
        p.drawLine(*Drawline);
    }
    p.setPen(Qt::green);
    //Zeichnet ein Kreis zum bestimmen der Position des Laserkopfs
    p.drawEllipse(LaserPos, 2 ,2);
    //Status Display
    p.setPen(Qt::black);
    p.setBrush(Qt::white);
    //Zeichnet linkes Rechteck in weiss
    p.drawRect(0,height()-14,100,13);

    //Legt die Farbe fest
    switch (Laserstate)
    {
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
    //Zeichnet ein Rechteck neber das weisse Rechteck
    //mit der festgelegten farbe
    p.drawRect(50,height()-14,50,13);
    //schreibt State: in das Linke Rechteck
    p.drawText(2,height()-3,"State:");
    //zeichnet den den Jeweiligen Status in das rechte Rechteck
    switch (Laserstate)
    {
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

//Die nächsten 4 Funktionen sind für das festlegen
//der Aktuellen zuständig für das paintEvent zuständig
//und verarbeiten die Anweisungen vom Controller
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

//GUI zurücksetzen
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
    if(Drawline)
    {
        delete Drawline;
        Drawline = NULL;
    }
    LineList.clear();
    LaserPos.setX(0);
    LaserPos.setY(0);
    LastPoint.setX(0);
    LastPoint.setY(0);
    Laserstate = 0;
    Timer->start(10);
    repaint();
}

//Fehlermeldungen vom Controller anzeigen
void RenderArea::ShowError(std::string Msg)
{
    QMessageBox::information(this, QString("Fehler"), QString(Msg.c_str()));

}
