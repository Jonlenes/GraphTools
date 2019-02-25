#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "WidgetGrafo.h"

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
    void on_pushButtonMenorCaminho_clicked();

    void on_pushButtonLimparMelhorCaminho_clicked();

    void SlotNovo();
    void SlotAbrir();
    void SlotAbrirTxt();
    void SlotArquivosRecentes(QAction *QActionTigg);
    void SlotSalvar();
    void SlotExportar();
    void SlotClose();
    void SlotAjuda();
    void SlotSobre();

private:
    void CriaMenu();
    void CriaAcao();
    void CriaArquivosRecentes();

    QMenu *QMenuArquivo;
    QMenu *QMenuSobre;
    QMenu *QMenuArquivosRecentes;

    QAction *QActionNovo;
    QAction *QActionAbrir;
    QAction *QActionAbrirTxt;
    Pilha<QAction*> *QActionArquivosRecentes;
    QAction *QActionSalvar;
    QAction *QActionExportar;
    QAction *QActionClose;

    QAction *QActionAjuda;
    QAction *QActionSobre;

    Ui::MainWindow *ui;
    WidgetGrafo *widDes;
    QWidget *WidTela;
};

#endif // MAINWINDOW_H
