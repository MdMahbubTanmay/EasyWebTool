#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <string>

using namespace std;

string mt = "Hello bro";
int packet;
int gate = 0;
string cmd = "ping www.google.com -n 4";
string output;
char buffer[128];


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_submit_clicked()
{

    ui->label_2->setText("Preparing to Send Packets..");
    QApplication::processEvents();
    cmd = "ping "+mt+" -n "+to_string(packet) ;
    //ui->plainTextEdit_log->setPlainText(QString::fromStdString(cmd.c_str()));

    if(packet == 0)
    {
        ui->plainTextEdit_log->setPlainText("Error. Invalid Packet, enter valid numbers only");
        ui->label_2->setText("Log Pannel");
    }
    else
    {




        FILE *pipe = _popen(cmd.c_str(), "r");

        if(!pipe)
        {
            ui->plainTextEdit_log->setPlainText("Error Occured. Invalid site or no internet connection");
            ui->label_2->setText("Log Pannel");
        }
        else
        {
            QString logText;

            while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
            {
                logText += QString::fromStdString(buffer);

                ui->label_2->setText("Packet sent : " + QString::fromStdString(to_string(gate)));
                gate++;
                QApplication::processEvents();

            }

            ui->plainTextEdit_log->setPlainText("Summary:\n"+logText);
            gate = 0;
            ui->label_2->setText("Log Pannel");
        }
        _pclose(pipe);



    }


}


void MainWindow::on_plainTextEdit1_url_textChanged()
{
    mt = ui->plainTextEdit1_url->toPlainText().toStdString();
    ui->plainTextEdit_log->setPlainText(QString::fromStdString("Site Url :" + mt));
}


void MainWindow::on_plainTextEdit1_number_textChanged()
{

        packet = ui->plainTextEdit1_number->toPlainText().toInt();

    if(packet == 0)
        {
        ui->plainTextEdit_log->setPlainText("Error. Invalid Packet, enter valid numbers only");
    }
    else
    {
          ui->plainTextEdit_log->setPlainText(QString::fromStdString("Targated Site:" + mt +"\n"+"Packet : "+ to_string(packet)));
    }




}

