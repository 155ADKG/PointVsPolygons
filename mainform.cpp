#include "mainform.h"
#include "ui_mainform.h"
#include "draw.h"

#include <QXmlStreamReader>
#include <QFileDialog>
#include <QMessageBox>

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);

}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::on_pushGenerate_clicked()
{
    ui->canvas->setPushGen(true);
    repaint();
}

void MainForm::on_comboBox_currentIndexChanged(int index)
{
    ui->canvas->setDrawWhat(index);
}

void MainForm::on_pushLoad_clicked()
{
    // Open file
    QFileDialog fdiag(0,trUtf8("Choose XML file"));

    fdiag.setDefaultSuffix("xml");
    fdiag.setFileMode(QFileDialog::AnyFile);

    QStringList filters;
    filters << "XML files (*.xml)";
    fdiag.setNameFilters(filters);

    if (!fdiag.exec()) return;

    QFile file(fdiag.selectedFiles()[0]);
    file.open(QIODevice::ReadOnly);

    ui->labelErr->clear();

    // Read XML
    QXmlStreamReader xml(file.readAll());

    int lvl = 0;
    TPolygons pols;
    TPolygon pol;
    QPoint p;

    while (!xml.atEnd())
    {
        xml.readNext();

        if(xml.tokenType() == QXmlStreamReader::StartElement)
        {

            if(xml.name().toString() == "pol" && lvl==1){
            }

            if(xml.name().toString() == "point" && lvl==2){

                QXmlStreamAttributes attr = xml.attributes();

                for(QXmlStreamAttributes::Iterator it=attr.begin(); it < attr.end(); it++)
                {
                    if(it->name().toString() == "x"){
                        p.setX(it->value().toInt());
                    }else if (it->name().toString() == "y"){
                        p.setY(it->value().toInt());
                    }
                }
                pol.push_back(p);
            }

            lvl += 1;
        }

        if(xml.tokenType() == QXmlStreamReader::EndElement)
        {
            lvl -= 1;
            if (lvl == 1){
                pols.push_back(pol);
                pol.clear();
            }
        }
    }

    //qDebug() << pols;
    ui->canvas->setPols(pols);

    repaint();

    if (xml.hasError())
    {
        QMessageBox::critical(this, "Read XML: ERROR", xml.errorString(), QMessageBox::Ok);
        ui->labelErr->setText("<font color='red'>XML error</font>");
    }

}
