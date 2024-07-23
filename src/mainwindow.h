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
    MainWindow(std::mt19937 & rng, QWidget *parent = nullptr);
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

    /**
     * This function finds the largest point size, where text will fit into the widget using given flags.
     * @param[in] text Text that is planned to be displayed in the widget
     * @param[in] widget Widget, for which the point size should be determined
     * @param[in] flags Text alignment flags to use when displaying the text in the widget, see QFontMetrics::boundingRect()
     * for more info about the values
     * @returns 0 if there is not small enough point size so that the text would fit into the widget, or number greater
     * than zero representing the largest point size found
     */
    static int find_largest_point_size(const QString & text, const QWidget * widget, int flags);

    /**
     * Event handler for every time the main window is resized
     * @param[in,out] event The event that occurred
     */
    void resizeEvent(QResizeEvent * event) override;

    /**
     * Function that handles change to the trainer stacked widget. It also modifies and sets all necessary parameters
     */
    void show_stacked_widget_trainer();

    /**
     * Function that handles change to the welcome page stacked widget. It also modifies and sets all necessary parameters
     */
    void show_stacked_widget_welcome_page();

    /**
     * Function increases counter of correct or incorrect translations
     * @param[in] translation_is_correct True, if counter of correct translations should increase by one, false if counter of
     * incorrect translations should increase by one
     */
    void increase_status_counter(bool translation_is_correct);

    /**
     * Handles actions necessary when main window closes
     * @param event Event
     */
    void closeEvent(QCloseEvent *event);
};
