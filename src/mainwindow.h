/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 03. 07. 2024
 */

#pragma once

#include <QMainWindow>
#include "Application.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /**
     * This function sets up the GUI
     */
    void init();

private slots:
    void on_btnCheckTranslation_clicked();

    void on_btnSelectVocabularyFile_clicked();

    void on_btnPractice_clicked();

    void on_btnModifyVocabularyFile_clicked();

    void on_btnNextTranslation_clicked();

    void on_btnHome_clicked();

private:
    Ui::MainWindow *ui;
    Application m_application;

    /**
     * This function handles showing the next translation to the user
     */
    void show_next_translation();

    /**
     * Configures the training widget, such that is disables/enables some buttons, clears labels and such
     * @param[in] before_submitting_translation True, if user should be able to insert his translation. False, if the state
     * of the widget should be appropriate to the state after submitting his translation
     */
    void configure_training_widget(bool before_submitting_translation);
};
