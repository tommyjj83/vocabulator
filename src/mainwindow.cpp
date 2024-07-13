/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 03. 07. 2024
 */

#include <QFileDialog>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

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
    ui->btnModifyVocabularyFile->setDisabled(true); // Not yet implemented
    ui->btnModifyVocabularyFile->setStyleSheet("QPushButton { background : lightGray }");
}

void MainWindow::on_btnCheckTranslation_clicked() {
    configure_training_widget(false);

    QFont font = ui->labelResult->font();
    font.setPointSize(font.pointSize() + (size().width() + size().height())  / 600);
    ui->labelResult->setFont(font);

    QString translation = ui->lineEditTranslation->text();
    if (m_application.check_translation(translation.toStdString()) == true) {
        QString answer = "Correct! All possible translations are:\n";
        answer += m_application.get_all_translations();
        ui->labelResult->setText(answer);
        ui->labelResult->setStyleSheet("QLabel { color : green; }");
    } else {
        QString answer = "Incorrect. The correct translation is:\n";
        answer += m_application.get_all_translations();
        ui->labelResult->setText(answer);
        ui->labelResult->setStyleSheet("QLabel { color : red; }");
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


// Inspired by stack overflow: https://stackoverflow.com/questions/42652738/how-to-automatically-increase-decrease-text-size-in-label-in-qt
void MainWindow::show_next_translation() {
    QString text = m_application.get_word_to_translate().data();
    QRect label_rectangle = ui->labelWordToTranslate->contentsRect();
    QFont font = ui->labelWordToTranslate->font();
    QFontMetrics font_metrics(font);
    QRect proposed_rectangle = font_metrics.boundingRect(label_rectangle, Qt::TextWordWrap, text);

    int size = font.pointSize();
    int step = proposed_rectangle.width() > label_rectangle.width() || proposed_rectangle.height() > label_rectangle.height() ? -1 : 1;   // decide whether to increase or decrease

    while (true) {
        size += step;
        font.setPointSize(size);
        font_metrics = std::move(QFontMetrics(font));
        proposed_rectangle = font_metrics.boundingRect(label_rectangle, Qt::TextWordWrap, text);

        if (step < 0) {
            if (proposed_rectangle.width() < label_rectangle.width() && proposed_rectangle.height() < label_rectangle.height()) {
                break;
            }
        } else {
            if (proposed_rectangle.width() > label_rectangle.width() || proposed_rectangle.height() > label_rectangle.height()) {
                size -= step;   // It's already too big, so make it one smaller
                font.setPointSize(size);
                break;
            }
        }

        if (size <= 1) {    // Cannot be made smaller
            break;
        }
    }

    if (font.pointSize() > 60) {
        font.setPointSize(60);
    }
    ui->labelWordToTranslate->setFont(font);
    ui->labelWordToTranslate->setText(text);
}


void MainWindow::on_btnNextTranslation_clicked() {
    configure_training_widget(true);
    m_application.update();
    show_next_translation();
}


void MainWindow::configure_training_widget(bool before_submitting_translation) {
    if (before_submitting_translation == true) {
        ui->btnCheckTranslation->setDisabled(false);
        ui->btnCheckTranslation->setStyleSheet("QPushButton { background : white }");

        ui->btnNextTranslation->setDisabled(true);
        ui->btnNextTranslation->setStyleSheet("QPushButton { background : lightGray }");

        ui->lineEditTranslation->setReadOnly(false);
        ui->lineEditTranslation->setStyleSheet("QLineEdit { background : white }");

        ui->lineEditTranslation->clear();
        ui->labelResult->clear();
    } else {
        ui->btnCheckTranslation->setDisabled(true);
        ui->btnCheckTranslation->setStyleSheet("QPushButton { background : lightGray }");

        ui->btnNextTranslation->setDisabled(false);
        ui->btnNextTranslation->setStyleSheet("QPushButton { background : white }");

        ui->lineEditTranslation->setReadOnly(true);
        ui->lineEditTranslation->setStyleSheet("QLineEdit { background : lightGray }");
    }
}


void MainWindow::on_btnHome_clicked() {
    ui->mainStackedWidget->setCurrentWidget(ui->welcomePage);
}

