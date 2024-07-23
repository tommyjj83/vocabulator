/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 03. 07. 2024
 */

#include <QCloseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(std::mt19937 & rng, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_application{rng}
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

    ui->labelCorrectTranslationsCnt->setText("0");
    ui->labelCorrectTranslationsCnt->setStyleSheet("QLabel { color : green; }");

    ui->labelIncorrectTranslationsCnt->setText("0");
    ui->labelIncorrectTranslationsCnt->setStyleSheet("QLabel { color : red; }");

    ui->btnModifyVocabularyFile->setDisabled(true); // Not yet implemented
    ui->btnModifyVocabularyFile->setStyleSheet("QPushButton { background : lightGray }");

    ui->labelFileSelected->setText("No file selected");
}

void MainWindow::on_btnCheckTranslation_clicked() {
    configure_training_widget(false);

    QString translation = ui->lineEditTranslation->text();
    const TranslationUnit & current_unit = m_application.m_trainer->get_current();
    if (current_unit.check_translation(translation.toStdString()) == true) {
        QString answer = "Correct! All possible translations are:\n";
        answer += current_unit.get_all_translations();
        ui->labelResult->setText(answer);
        ui->labelResult->setStyleSheet("QLabel { color : green; }");
        increase_status_counter(true);
    } else {
        QString answer = "Incorrect. The correct translation is:\n";
        answer += current_unit.get_all_translations();
        ui->labelResult->setText(answer);
        ui->labelResult->setStyleSheet("QLabel { color : red; }");
        increase_status_counter(false);
    }
}

void MainWindow::on_btnSelectVocabularyFile_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open File"),"/home/tommy",tr("Vocabulary data files (*.vdf)"));
    if (file.isNull()) {
        return;
    }

    try {
        m_application.save_vocabulary_to_file();
    } catch (const std::logic_error & exception) {
        std::string message = exception.what();
        message += "\n\nDo you want to load new file WITHOUT saving the previous one?";
        QMessageBox::StandardButton answer = QMessageBox::critical(nullptr, "Error", message.c_str(), QMessageBox::Yes | QMessageBox::No);

        if (answer == QMessageBox::No) {
            return;
        }
    }

    try {
        m_application.load_vocabulary_from_file(file.toStdString());
    } catch (const std::invalid_argument & exception) {
        ui->labelFileSelected->setText("No file selected");
        ui->labelError->setText(QString{exception.what()});
        return;
    } catch (const std::logic_error & exception) {
        ui->labelFileSelected->setText("No file selected");
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

    show_stacked_widget_trainer();
}


void MainWindow::on_btnModifyVocabularyFile_clicked() {
    // Not implemented yet
}


// Inspired by stack overflow: https://stackoverflow.com/questions/42652738/how-to-automatically-increase-decrease-text-size-in-label-in-qt
void MainWindow::show_next_translation() {
    QString text = m_application.m_trainer->get_current().m_word_to_translate.c_str();
    int point_size = find_largest_point_size(text, ui->labelWordToTranslate, Qt::TextWordWrap);

    point_size = point_size > 60 ? 60 : point_size == 0 ? 1 : point_size;
    QFont font = ui->labelWordToTranslate->font();
    font.setPointSize(point_size);

    ui->labelWordToTranslate->setFont(font);
    ui->labelWordToTranslate->setText(text);
}


void MainWindow::on_btnNextTranslation_clicked() {
    configure_training_widget(true);
    m_application.m_trainer->update();
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
    show_stacked_widget_welcome_page();
}


int MainWindow::find_largest_point_size(const QString & text, const QWidget *widget, int flags) {
    QRect label_rectangle = widget->contentsRect();
    QFont font = widget->font();
    QFontMetrics font_metrics(font);
    QRect proposed_rectangle = font_metrics.boundingRect(label_rectangle, flags, text);

    int size = font.pointSize();
    int step = proposed_rectangle.width() > label_rectangle.width() || proposed_rectangle.height() > label_rectangle.height() ? -1 : 1;   // decide whether to increase or decrease

    while (true) {
        size += step;
        font.setPointSize(size);
        font_metrics = std::move(QFontMetrics(font));
        proposed_rectangle = font_metrics.boundingRect(label_rectangle, flags, text);

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
            size = 0;
            break;
        }
    }

    return size;
}


void MainWindow::resizeEvent(QResizeEvent *event) {
    int point_size_offset = (size().width() + size().height()) / 600;   // Default point size + magic

    QFont font = ui->labelResult->font();
    font.setPointSize(11 + point_size_offset);
    ui->labelResult->setFont(font);

    font = ui->labelError->font();
    font.setPointSize(11 + point_size_offset);
    ui->labelError->setFont(font);

    font = ui->labelFileSelected->font();
    font.setPointSize(11 + point_size_offset);
    ui->labelFileSelected->setFont(font);

    font = ui->label_3->font();
    font.setPointSize(11 + point_size_offset);
    ui->label_3->setFont(font);

    font = ui->label_4->font();
    font.setPointSize(11 + point_size_offset);
    ui->label_4->setFont(font);

    font = ui->labelCorrectTranslationsCnt->font();
    font.setPointSize(11 + point_size_offset);
    ui->labelCorrectTranslationsCnt->setFont(font);

    font = ui->labelIncorrectTranslationsCnt->font();
    font.setPointSize(11 + point_size_offset);
    ui->labelIncorrectTranslationsCnt->setFont(font);

    font = ui->label->font();
    font.setPointSize(11 + point_size_offset);
    ui->label->setFont(font);
}


void MainWindow::show_stacked_widget_trainer() {
    ui->mainStackedWidget->setCurrentWidget(ui->volcabularyTrainer);
    configure_training_widget(true);
    show_next_translation();
}


void MainWindow::show_stacked_widget_welcome_page() {
    ui->mainStackedWidget->setCurrentWidget(ui->welcomePage);
}


void MainWindow::increase_status_counter(bool translation_is_correct) {
    QLabel * label = translation_is_correct ? ui->labelCorrectTranslationsCnt : ui->labelIncorrectTranslationsCnt;
    size_t value = std::stoi(label->text().toStdString());
    ++value;
    label->setText(std::to_string(value).c_str());
}


void MainWindow::closeEvent(QCloseEvent * event) {
    try {
        m_application.save_vocabulary_to_file();
    } catch (const std::logic_error & exception) {
        std::string message = exception.what();
        message += "\n\nDo you want to quit WITHOUT saving?";
        QMessageBox::StandardButton result =
                QMessageBox::critical(nullptr, "Error", message.c_str(), QMessageBox::Yes | QMessageBox::No);

        if (result == QMessageBox::No) {
            event->ignore();
        }
    }
}
