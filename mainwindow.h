#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDir>
#include <QFileDialog>
#include <QMap>
#include <QTextStream>

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_OpenFile_triggered();
    void on_SaveFile_triggered();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    //BinaryTree bn; // Объект дерева
    QString strNumbers; // строка в которую считываются цифры с файла
    //Dijkstra
    QString start; //начальная вершина
    QString end;// конечная вершина
    int min_metka;//минимальная метка вершины (кратчайший путь в нее)
    int number;//номер вершины с минимальной текущей меткой
    static const int SIZE = 10;
    int FIKS[SIZE]; // массив посещенных вершин
    int distanse[SIZE]; // массив текущих меток вершин (кратчайших расстояний)
    int min_WEG[SIZE]; // массив номеров вершин, входящих в минимальный маршрут
    int distances[SIZE][SIZE]; // массив расстояний между вершинами
    int prom[SIZE]; //массив промежуточных вершин
    int count = 0, countCpy = 0;//счетчик промежуточных вершин
    int temp;
    bool fClosed = true;
};

#endif // MAINWINDOW_H
