#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QMenuBar>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    widDes = new WidgetGrafo(this);
    ui->verticalLayoutGrafo->addWidget(widDes);
    QActionArquivosRecentes = new Pilha<QAction*>;
    widDes->CarregaRecentes(QActionArquivosRecentes, this);
    QMenuArquivosRecentes = NULL;

    CriaAcao();
    CriaMenu();

    QString str = "<b></b>Seja bem vindo ao menor caminho grafo direcionado.";
    str = str + "<br /> Para plotar o seu grafo:<br /><b>Primeiro:</b> ";
    str = str + "desenhe todos os vertices com o click do mouse, sendo que cada ";
    str = str + "click gera um novo vertice";
    str = str + ". <br /><b>Segundo:</b> aperte a tecla de ";
    str = str + "espaço para plotar as suas arestas.";
    str = str + "<br /><br /><b>P.s.:</b> Você também pode carregar o grafo por um ";
    str = str + "arquivo .txt ou por um arquivo .Grafo salvo anteriomente";
    str = str + ".<br /><b>Obs.:</b> Sempre tenha uma distancia entre um click";
    str = str + " e outro para garanti uma melhor visualização do seu grafo.";
    str = str + "<br /><b>(Pressione F1 a qualquer momento para obter ajuda.)</b>";
    QMessageBox::information(this, tr("Informações"), str);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete widDes;
}

void MainWindow::on_pushButtonMenorCaminho_clicked()
{
    int Origem = QInputDialog::getInt(this, "Melhor Caminho - Origem", "Vertice de origem da aresta:");
    int Final = QInputDialog::getInt(this, "Melhor Caminho - Destino", "Vertice de destino da aresta:");

    if(Origem <= 0 || Final <= 0)
        QMessageBox::information(this, "Aviso", "Vertices digitados não existem ou campos ficarm em branco.");
    else
        widDes->MenorCaminho(Origem, Final);
    widDes->setFocus();
}

void MainWindow::on_pushButtonLimparMelhorCaminho_clicked()
{
    widDes->LimpaMenorCaminho();
    widDes->setFocus();
}

void MainWindow::CriaAcao()
{
    QActionNovo = new QAction(tr("&Novo"), this);
    QActionNovo->setShortcut(QKeySequence::New);
    connect(QActionNovo, SIGNAL(triggered()), this, SLOT(SlotNovo()));

    QActionAbrir = new QAction(tr("Abrir"), this);
    QActionAbrir->setShortcut(QKeySequence::Open);
    connect(QActionAbrir, SIGNAL(triggered()), this, SLOT(SlotAbrir()));

    QActionAbrirTxt = new QAction(tr("&Carregar do Arquivo de Texto"), this);
    connect(QActionAbrirTxt, SIGNAL(triggered()), this, SLOT(SlotAbrirTxt()));

    QActionSalvar = new QAction(tr("&Salvar"), this);
    QActionSalvar->setShortcut(QKeySequence::Save);
    connect(QActionSalvar, SIGNAL(triggered()), this, SLOT(SlotSalvar()));

    QActionExportar = new QAction(tr("&Exportar para imagem PNG"), this);
    QActionExportar->setShortcut(QKeySequence::SaveAs);
    connect(QActionExportar, SIGNAL(triggered()), this, SLOT(SlotExportar()));

    QActionClose = new QAction(tr("&Sair"), this);
    QActionClose->setShortcut(QKeySequence::Quit);
    connect(QActionClose, SIGNAL(triggered()), this, SLOT(SlotClose()));

    QActionAjuda = new QAction(tr("&Ajuda"), this);
    QActionAjuda->setShortcut(QKeySequence::HelpContents);
    connect(QActionAjuda, SIGNAL(triggered()), this, SLOT(SlotAjuda()));

    QActionSobre = new QAction(tr("&Sobre"), this);
    connect(QActionSobre, SIGNAL(triggered()), this, SLOT(SlotSobre()));
}
void MainWindow::CriaMenu()
{
    QMenuArquivo = menuBar()->addMenu("Arquivo");
    QMenuArquivo->addAction(QActionNovo);
    QMenuArquivo->addAction(QActionAbrir);
    QMenuArquivo->addAction(QActionAbrirTxt);
    QMenuArquivo->addSeparator();
    QMenuArquivo->addAction(QActionSalvar);
    QMenuArquivo->addSeparator();
    QMenuArquivo->addAction(QActionExportar);
    QMenuArquivo->addSeparator();
    QMenuArquivo->addAction(QActionClose);

    QMenuSobre = menuBar()->addMenu("Sobre");
    QMenuSobre->addAction(QActionAjuda);
    QMenuSobre->addAction(QActionSobre);

    CriaArquivosRecentes();
}

/* Desenvolvimento dos Slotes*/
void MainWindow::SlotNovo()
{
    delete widDes;
    widDes = new WidgetGrafo(this);
    ui->verticalLayoutGrafo->addWidget(widDes);
    widDes->setFocus();
}

void MainWindow::SlotAbrir()
{
    delete widDes;
    widDes = new WidgetGrafo(this);
    ui->verticalLayoutGrafo->addWidget(widDes);
    widDes->Abrir();
    widDes->setFocus();
}

void MainWindow::SlotAbrirTxt()
{
    delete widDes;
    widDes = new WidgetGrafo(this);
    ui->verticalLayoutGrafo->addWidget(widDes);
    widDes->CarregaPeloTxt();
    widDes->setFocus();
}

void MainWindow::SlotArquivosRecentes(QAction *QActionTigg)
{
    delete widDes;
    widDes = new WidgetGrafo(this);
    ui->verticalLayoutGrafo->addWidget(widDes);
    widDes->Abrir(QActionTigg->text());
    widDes->setFocus();
}

void MainWindow::SlotSalvar()
{
    widDes->Salvar();
    widDes->CarregaRecentes(QActionArquivosRecentes, this);
    CriaArquivosRecentes();
    widDes->setFocus();
}

void MainWindow::SlotExportar()
{
    QString Direc = QFileDialog::getSaveFileName(this, "Exportar para", "", "Arquivo de imagem(*.Png)");
    Direc = Direc + ".Png";

    QFile *File = new QFile(Direc);

    QPixmap pixmap(ui->widgetTelaGrafo->size());
    ui->widgetTelaGrafo->render(&pixmap);
    pixmap.save(File, "Png", 100);

    File->close();
    delete File;
}

void MainWindow::SlotClose()
{
    this->close();
}

void MainWindow::SlotAjuda()
{
    QString Ajuda = "<br /><b>Arquivo --> Novo = </b>Limpa a tela e abre uma nova area de trabalho em branco.<br />";
    Ajuda = Ajuda + "<br /><b>Arquivo --> Abrir = </b>Abre um arquivo .Grafo salvo anteriomente.<br />";
    Ajuda = Ajuda + "<br /><b>Arquivo --> Carrega do arquivo de texto = </b>Carrega o grafo de um arquivo de texto com layout pré-definido no trabalho<br />";
    Ajuda = Ajuda + "<br /><b>Arquivo --> Arquivos Salvo Recentes = </b>Mostra a lista de arquivos que forma salvos recentimente.<br />";
    Ajuda = Ajuda + "<br /><b>Arquivo --> Salvar = </b>Salvo o grafo no formato .Grafo para ser utilizado posteriomente.<br />";
    Ajuda = Ajuda + "<br /><b>Arquivo --> Exportar para imagem PNG = </b>Exporta uma imagem do seu grafo<br />";
    QMessageBox::information(this, "Ajuda", Ajuda);
}

void MainWindow::SlotSobre()
{
    QString Sobre = "Esse programa foi desenvolvido pelo aluno Jonlenes Silva ";
    Sobre = Sobre + "de Castro acadêmico de ciência da Computação da Puc-Go com ";
    Sobre = Sobre + "intuito de praticar as estrutoras de dados.";
    QMessageBox::about(this, "Sobre", Sobre);
}

void MainWindow::CriaArquivosRecentes()
{
    QAction *QActionAux;
    if(QMenuArquivosRecentes != NULL){
        QList<QAction*> List = QMenuArquivosRecentes->actions();
        foreach(QActionAux, List){
            QMenuArquivosRecentes->removeAction(QActionAux);
        }
    }else
        QMenuArquivosRecentes = QMenuArquivo->addMenu("&Arquivos Salvo Recentimente");

    while(!QActionArquivosRecentes->Empty()){
        QActionArquivosRecentes->Desempilhar(QActionAux);
        QMenuArquivosRecentes->addAction(QActionAux);
    }
    connect(QMenuArquivosRecentes, SIGNAL(triggered(QAction*)), SLOT(SlotArquivosRecentes(QAction*)));
}
