#include "mainwindow.h"
#include <QApplication>

#include "SqlDatum/sqlfield.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SqlField::initSpecialTypeList();

    MainWindow w;
    w.show();

    return a.exec();
}

/*PoupouH:

class Poupou
{
public:
    Poupou(QString name = ""); //Constructeur
    ~Poupou();

    void TrancherOrteil();

private:
    int nombreOrteil;
    float *monpointer;

    QString m_name;
}

PoupouCpp:

#include "Poupou.h"

Poupou::Poupou(QString name)
{
    nombreOrteil = 4;
    monpointer = new float;
    m_name = name;
}

Poupou::~Poupou()
{
    delete monpointer;
}

void Poupou::TrancherOrteil()
{
    if(nombreOrteil > 0)
        nombreOrteil --;
    else
        qInfo()<<"ERROR NUMBER OF ORTEIL INSUFISANT";
}

C++:

   #include "Poupou.h"

Poupou* gregoire;
gregoire = new Poupou("King of Pou");
//gregoire.nombreOrteil = 3;
gregoire->TrancherOrteil();
delete gregoire;

Poupou Watson;

if(blabla)
{
    int mavariable  = 5;
    mavariable *= 3;
    print(mavariable);
} */


