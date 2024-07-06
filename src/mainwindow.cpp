/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 03. 07. 2024
 */

#include <QFileDialog>
#include <QMessageBox>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init() {
    setWindowTitle("Vocabulator");
    ui->labelError->setStyleSheet("QLabel { color : red; }");
    ui->btnModifyVocabularyFile->setDisabled(true);
}

void MainWindow::on_btnCheckTranslation_clicked()
{
}

void MainWindow::on_btnSelectVocabularyFile_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open File"),"~",tr("Vocabulary data files (*.vdf)"));
    if (file.isNull()) {
        return;
    }

    try {
        m_application.load_vocabulary_from_file(file.toStdString());
    } catch (const std::invalid_argument & exception) {
        ui->labelFileSelected->clear();
        ui->labelError->setText(QString{exception.what()});
        return;
    } catch (const std::logic_error & exception) {
        ui->labelFileSelected->clear();
        ui->labelError->setText(QString{exception.what()});
        return;
    }

    ui->labelFileSelected->setText(file);
    ui->labelError->clear();
}


void MainWindow::on_btnPractice_clicked()
{
    if (!m_application.is_ready()) {
        ui->labelError->setText("You must select file with vocabulary first!");
        return;
    }

    ui->mainStackedWidget->setCurrentWidget(ui->volcabularyTrainer);
}


void MainWindow::on_btnModifyVocabularyFile_clicked() {
    // Not implemented yet
}


void MainWindow::show_next_translation() {

}
