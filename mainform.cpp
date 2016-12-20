#include "mainform.h"
#include "ui_mainform.h"
#include "draw.h"

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
    repaint();
}

void MainForm::on_comboBox_currentIndexChanged(int index)
{
    ui->canvas->setDrawWhat(index);
}
