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

void MainWindow::on_btnCheckTranslation_clicked() {
    configure_training_widget(false);

    QString translation = ui->lineEditTranslation->text();
    if (m_application.check_translation(translation.toStdString()) == true) {
        QString answer = "Correct! All possible translations are:\n";
        answer += m_application.get_all_translations();
        ui->labelResult->setText(answer);
    } else {
        QString answer = "Incorrect. The correct translation is:\n";
        answer += m_application.get_all_translations();
        ui->labelResult->setText(answer);
    }
}

void MainWindow::on_btnSelectVocabularyFile_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open File"),"/home/tommy",tr("Vocabulary data files (*.vdf)"));
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
    configure_training_widget(true);
    show_next_translation();
}


void MainWindow::on_btnModifyVocabularyFile_clicked() {
    // Not implemented yet
}


void MainWindow::show_next_translation() {
    ui->labelWordToTranslate->setText(m_application.get_word_to_translate().data());
}

void MainWindow::on_btnNextTranslation_clicked() {
    configure_training_widget(true);
    m_application.update();
    show_next_translation();
}


void MainWindow::configure_training_widget(bool before_submitting_translation) {
    if (before_submitting_translation == true) {
        ui->btnCheckTranslation->setDisabled(false);
        ui->btnNextTranslation->setDisabled(true);
        ui->lineEditTranslation->setReadOnly(false);
        ui->lineEditTranslation->clear();
        ui->labelResult->clear();
    } else {
        ui->btnCheckTranslation->setDisabled(true);
        ui->btnNextTranslation->setDisabled(false);
        ui->lineEditTranslation->setReadOnly(true);
    }
}

