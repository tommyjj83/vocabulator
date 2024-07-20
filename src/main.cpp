/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 03. 07. 2024
 */

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    std::random_device rd;
    std::mt19937 prng{rd()};
    MainWindow w(prng);

    w.init();
    w.show();
    return a.exec();
}
