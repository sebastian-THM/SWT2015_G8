#include "view_qt.h"
#include <QApplication>
#include "parser.h"
#include "controller.h"
#include "dispatchtable.h"
#include "renderarea.h"

RenderArea* RenderArea::Instance;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    View_QT w;
    w.show();

    //Controller DispatchTable und Parser erstellen
    Controller C;
    DispatchTable D;
    Parser P;

    //Verbindungen herstellen

    //Parser->Controller
    QObject::connect(&P,SIGNAL(FileOpened()),&C,SLOT(inNewFileOpend()));
    QObject::connect(&P,SIGNAL(FileInvalid()),&C,SLOT(inFileInvalid()));
    QObject::connect(&P,SIGNAL(FileNameInvalid()),&C,SLOT(inFileNameInvalid()));
    //Verbindung Controller->Parser
    QObject::connect(&C,SIGNAL(GetNextOpcode()),&P,SLOT(GetNextOpcode()));
    QObject::connect(&C,SIGNAL(OpenFile(std::string)),&P,SLOT(OpenFile(std::string)));


    //Parser->DispatchTable
    QObject::connect(&P,SIGNAL(SendOpcode(std::string,std::string)),&D,SLOT(Dispatch(std::string,std::string)));
    //DispatchTable einrichten
    D.AddFunction("LASER",&C,&(C.inLaser));
    D.AddFunction("MOVE",&C,&(C.inMove));

    //Controller->GUI
    QObject::connect(&C,SIGNAL(LaserCut(int,int)),RenderArea::Instance,SLOT(Cut(int,int)));
    QObject::connect(&C,SIGNAL(LaserMove(int,int)),RenderArea::Instance,SLOT(Move(int,int)));
    QObject::connect(&C,SIGNAL(LaserOff()),RenderArea::Instance,SLOT(Off));
    QObject::connect(&C,SIGNAL(LaserOn()),RenderArea::Instance,SLOT(On));
    QObject::connect(&C,SIGNAL(ResetGUI()),RenderArea::Instance,SLOT(Reset()));
    QObject::connect(&C,SIGNAL(Error(std::string)),RenderArea::Instance,SLOT(ShowError(std::string)));

    //GUI->Controller
    QObject::connect(RenderArea::Instance,SIGNAL(DrawingDone()),&C,SLOT(inMoveDone()));
    QObject::connect(RenderArea::Instance,SIGNAL(SendOpenFile(std::string)),&C,SLOT(inNewFileName(std::string)));
    QObject::connect(RenderArea::Instance,SIGNAL(SendStart()),&C,SLOT(inStart()));
    QObject::connect(RenderArea::Instance,SIGNAL(SendPause()),&C,SLOT(inPause()));
    return a.exec();
}
