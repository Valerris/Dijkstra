#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QRegExp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_OpenFile_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, QString::fromUtf8("Открыть файл"), QDir::currentPath(),"*.txt");
    if(filePath.isEmpty()) return;
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }
    QTextStream in(&file);
    QString s; bool ok;
    //strNumbers = in.readAll();
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            in >> s;
            distances[i][j] = s.toInt(&ok, 10);
        }
    }
    file.close();
    fClosed = false;
    ui->statusBar->showMessage("Файл был открыт");
}

void MainWindow::on_SaveFile_triggered()
{
    if(!fClosed)
    {
        QString filePath = QFileDialog::getSaveFileName(this, QString::fromUtf8("Сохранить файл"), QDir::currentPath(), ".txt");
        if(filePath.isEmpty()) return;
        QFile file(filePath.append(".txt"));
        if(!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(0, "error", file.errorString());
        }
        file.close();
        ui->statusBar->showMessage("Файл сохранён");
    }
    else
    {
    QString filePath = QFileDialog::getSaveFileName(this, QString::fromUtf8("Сохранить файл"), QDir::currentPath(), ".txt");
    if(filePath.isEmpty()) return;
    QFile file(filePath.append(".txt"));
    bool ok;
    if(!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }
    QTextStream out(&file);
    out << QString("Кратчайший путь от вершины ") << start.toInt(&ok, 10) << QString(" до вершины ") << end.toInt(&ok, 10) << ": " << start.toInt(&ok, 10) << " ";
    for(; countCpy >= 0; countCpy--)//в обратном порядке проходимся по промежуточным вершинам до начальной
    {
        out  << prom[countCpy] << " ";//запись в файл
    }
    out << end.toInt(&ok, 10) << endl;
    out << QString("\r\nКратчайшее расстояние: ") << distanse[end.toInt(&ok, 10)];
    file.close();    
    countCpy = 0;
    ui->statusBar->showMessage("Файл сохранён");
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->label_3->clear();
    ui->label_5->clear();
    bool ok;
    start = ui->lineEdit->text();
    end = ui->lineEdit_2->text();

    QRegExp e("\\d+");
    if(fClosed)
        QMessageBox::information(0, "Предупреждение", "Откройте файл");
    else if(e.exactMatch(start) && e.exactMatch(end) && start.toInt(&ok, 10) >= 0 && start.toInt(&ok, 10) < SIZE && end.toInt(&ok, 10) >= 0 && end.toInt(&ok, 10) < SIZE)
    {
            //ИНИЦИАЛИЗАЦИЯ МАССИВОВ FIKS,min_WEG,distanse

            for (int i = 0; i < SIZE; i++)//перебираем вершины, i - номер вершины
                {
                    if (i != start.toInt(&ok, 10)) //если вершина не начальная
                        FIKS[i] = 0; // значит она непосещенная
                    else
                        FIKS[i] = 1;// иначе посещенная
                        min_WEG[i] = start.toInt(&ok, 10);//заносим номер начальной вершины в массив номеров вершин, входящих в минимальный маршрут
                        distanse[i] = distances[start.toInt(&ok, 10)][i];//заполняем массив текущих меток соответствующими значениями массива расстояний между вершинами
                }
        //получается, что посещена только 1 вершина -  исходная, минимальный путь в нее равен бесконечно большому числу
            for (int i = 0; i< SIZE - 1; i++)
                {
                    min_metka = 1000; // минимальная метка - бесконечно больше число
                    for (int j = 0; j<SIZE; j++) //ищем среди непосещенных вершин вершину с минимальной меткой
                        {
                        if (FIKS[j] == 1) //если вершина посещена

                                            continue;//переходим на следующую итерацию

                        if (distanse[j] <= min_metka)//если кратчайшее расстояние до вершины меньше минимальной метки
                                                {
                                                    min_metka = distanse[j];//минимальной меткой становится кратчайшее расстояние до вершины
                                                    number = j;//запомнили номер вершины с минимальной меткой
                                                }
                                        }
                                    FIKS[number] = 1;//вершина с минимальной текущей меткой теперь посещенная
                                    for (int n = 0; n< SIZE; n++)
                                        {
                                            if (FIKS[n] == 1) //если вершина посещенная
                                            continue;//переходим на следующую итерацию
                                            if (distanse[number ] + distances[number ][n] < distanse[n])// если расстояние в n-ю вершину через вершину с номером
                                // минимальной текущей метки меньше, чем величина текущей минимальной метки n-й вершины, то метка n-й вершины изменяется
                                                {
                                                    distanse[n] = distanse[number] + distances[number ][n];//и становится равна расстоянию в n-ю вершину
                                // через вершину с номером вершины минимальной текущей метки
                                                    min_WEG[n] = number ;// n-ый элемент массива минимального маршрута равен номеру вершины с минимальной текущей меткой
                                                }
                                        }
                                }
                            temp = min_WEG[end.toInt(&ok, 10)];//присваиваем переменной номер конечной вершины
                            while(temp != start.toInt(&ok, 10))//пока не дойдем до начальной вершины
                                {
                                    prom[count] = temp;//сохраняем в массив промежуточных вершин путь в нее
                                    temp = min_WEG[temp];//присваиваем значение предыдущей вершины
                                    count++;//увелчиваем счетчик промежуточных вершин
                                }
                            count--;
        QString str;
        str += start + " ";
        countCpy = count;

        for(; count >= 0; count--)//в обратном порядке проходимся по промежуточным вершинам до начальной
        {
             str += QString::number(prom[count]) + " ";
        }
        str += end;
        ui->label_3->setText(str);
        ui->label_start->setText(start);
        ui->label_end->setText(end);
        if(distanse[end.toInt(&ok, 10)] < 1000)
            ui->label_5->setText(QString::number(distanse[end.toInt(&ok, 10)]));
        else
            ui->label_5->setText(QString("Бесконечность"));
        ui->statusBar->showMessage("Путь рассчитан, сохраните файл");

        str = "";
        count = 0;
    }
    else
        QMessageBox::information(0, "Предупреждение", "Проверьте правильность введённой информации");
}
