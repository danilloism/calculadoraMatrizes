#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    matA(0),
    matB(0)
{
    ui->setupUi(this);
    ui->textEditMatA->setReadOnly(true);
    ui->textEditMatB->setReadOnly(true);
    ui->textEditSaida->setReadOnly(true);
    this->setFixedSize(QSize(678, 657));
    ui->pushButtonAdicao->setDisabled(true);
    ui->pushButtonMultiplicacao->setDisabled(true);
    ui->pushButtonMultiplicarAPorK->setDisabled(true);
    ui->pushButtonMultiplicarBPorK->setDisabled(true);
    ui->pushButtonSubtracao->setDisabled(true);
    ui->pushButtonTranspostaA->setDisabled(true);
    ui->pushButtonTranspostaB->setDisabled(true);
    ui->pushButtonPotenciacaoA->setDisabled(true);
    ui->pushButtonPotenciacaoB->setDisabled(true);
}

MainWindow::~MainWindow()
{
    if(matA) delete matA;
    if(matB) delete matB;
    delete ui;
}

void MainWindow::on_pushButtonCriarMatrizA_clicked()
{
    try {
        int QuantidadeDeLinhas = ui->lineEditQLinhasMatA->text().toInt();
        int QuantidadeDeColunas = ui->lineEditQColunasMatA->text().toInt();

        if(matA) delete matA;
        matA = new dnn::Matriz(QuantidadeDeLinhas,QuantidadeDeColunas);

        for(int l=0;l<QuantidadeDeLinhas;l++)
        {
            for(int c=0;c<QuantidadeDeColunas;c++)
            {
                int elemento = QInputDialog::getInt(this,"Leitura",
                                                    "Matriz A [ "+QString::number(l)+", "+
                                                    QString::number(c)+"] = ");
                matA->setElemento(l,c,elemento);
            }
        }
        ui->textEditMatA->setText(matA->getMatriz());

        ui->pushButtonMultiplicarAPorK->setDisabled(false);
        ui->pushButtonTranspostaA->setDisabled(false);
        ui->pushButtonPotenciacaoA->setDisabled(false);
        if(matB){
            ui->pushButtonMultiplicacao->setDisabled(false);
            ui->pushButtonAdicao->setDisabled(false);
            ui->pushButtonSubtracao->setDisabled(false);
        }


        QTableWidgetItem *matATriangularSuperior = new QTableWidgetItem((matA->ehTriangularSuperior()) ? "Sim" : "Não");
        QTableWidgetItem *matATriangularInferior = new QTableWidgetItem((matA->ehTriangularInferior() ? "Sim" : "Não"));
        QTableWidgetItem *matASimetrica = new QTableWidgetItem((matA->ehSimetrica()) ? "Sim" : "Não");
        QTableWidgetItem *matAIdentidade = new QTableWidgetItem((matA->ehIdentidade()) ? "Sim" : "Não");
        QTableWidgetItem *MatAOrtogonal = new QTableWidgetItem((matA->ehOrtogonal()) ? "Sim" : "Não");
        QTableWidgetItem *MatADePermutacao = new QTableWidgetItem((matA->ehDePermutacao()) ? "Sim" : "Não");

        if(matB){
            QTableWidgetItem *matAIgualB = new QTableWidgetItem(((*matA)==matB) ? "Sim" : "Não");
            QTableWidgetItem *matADiferenteB = new QTableWidgetItem(((*matA)!=matB) ? "Sim" : "Não");
            QTableWidgetItem *matBIgualA = new QTableWidgetItem(((*matB)==matA) ? "Sim" : "Não");
            QTableWidgetItem *matBDiferenteA = new QTableWidgetItem(((*matB)!=matA) ? "Sim" : "Não");

            ui->tableWidgetSaida->setItem(6,0,matAIgualB);
            ui->tableWidgetSaida->setItem(7,0,matADiferenteB);
            ui->tableWidgetSaida->setItem(6,1,matBIgualA);
            ui->tableWidgetSaida->setItem(7,1,matBDiferenteA);
        }


        ui->tableWidgetSaida->setItem(0,0,matATriangularSuperior);
        ui->tableWidgetSaida->setItem(1,0,matATriangularInferior);
        ui->tableWidgetSaida->setItem(2,0,matASimetrica);
        ui->tableWidgetSaida->setItem(3,0,matAIdentidade);
        ui->tableWidgetSaida->setItem(4,0,MatAOrtogonal);
        ui->tableWidgetSaida->setItem(5,0,MatADePermutacao);
    } catch (QString &erro) {
        QMessageBox::warning(this,"Erro!",erro);
    } catch (std::bad_alloc &erro){
        QMessageBox::warning(this,"Erro!","Problema na alocação de memória.");
    }

}

void MainWindow::on_pushButtonCriarMatrizB_clicked()
{
    try {
        int QuantidadeDeLinhas = ui->lineEditQLinhasMatB->text().toInt();
        int QuantidadeDeColunas = ui->lineEditQColunasMatB->text().toInt();

        if(matB) delete matB;
        matB = new dnn::Matriz(QuantidadeDeLinhas,QuantidadeDeColunas);

        for(int l=0;l<QuantidadeDeLinhas;l++)
        {
            for(int c=0;c<QuantidadeDeColunas;c++)
            {
                int elemento = QInputDialog::getInt(this,"Leitura",
                                                    "Matriz B [ "+QString::number(l)+", "+
                                                    QString::number(c)+"] = ");
                matB->setElemento(l,c,elemento);
            }
        }
        ui->textEditMatB->setText(matB->getMatriz());

        ui->pushButtonMultiplicarBPorK->setDisabled(false);
        ui->pushButtonTranspostaB->setDisabled(false);
        ui->pushButtonPotenciacaoB->setDisabled(false);
        if(matA){
            ui->pushButtonMultiplicacao->setDisabled(false);
            ui->pushButtonAdicao->setDisabled(false);
            ui->pushButtonSubtracao->setDisabled(false);
        }

        QTableWidgetItem *matBTriangularSuperior = new QTableWidgetItem((matB->ehTriangularSuperior()) ? "Sim" : "Não");
        QTableWidgetItem *matBTriangularInferior = new QTableWidgetItem((matB->ehTriangularInferior() ? "Sim" : "Não"));
        QTableWidgetItem *matBSimetrica = new QTableWidgetItem((matB->ehSimetrica()) ? "Sim" : "Não");
        QTableWidgetItem *matBIdentidade = new QTableWidgetItem((matB->ehIdentidade()) ? "Sim" : "Não");
        QTableWidgetItem *MatBOrtogonal = new QTableWidgetItem((matB->ehOrtogonal()) ? "Sim" : "Não");
        QTableWidgetItem *MatBDePermutacao = new QTableWidgetItem((matB->ehDePermutacao()) ? "Sim" : "Não");

        if(matA){
            QTableWidgetItem *matBIgualA = new QTableWidgetItem(((*matB)==matA) ? "Sim" : "Não");
            QTableWidgetItem *matBDiferenteA = new QTableWidgetItem(((*matB)!=matA) ? "Sim" : "Não");
            QTableWidgetItem *matAIgualB = new QTableWidgetItem(((*matA)==matB) ? "Sim" : "Não");
            QTableWidgetItem *matADiferenteB = new QTableWidgetItem(((*matA)!=matB) ? "Sim" : "Não");

            ui->tableWidgetSaida->setItem(6,1,matBIgualA);
            ui->tableWidgetSaida->setItem(7,1,matBDiferenteA);
            ui->tableWidgetSaida->setItem(6,0,matAIgualB);
            ui->tableWidgetSaida->setItem(7,0,matADiferenteB);
        }


        ui->tableWidgetSaida->setItem(0,1,matBTriangularSuperior);
        ui->tableWidgetSaida->setItem(1,1,matBTriangularInferior);
        ui->tableWidgetSaida->setItem(2,1,matBSimetrica);
        ui->tableWidgetSaida->setItem(3,1,matBIdentidade);
        ui->tableWidgetSaida->setItem(4,1,MatBOrtogonal);
        ui->tableWidgetSaida->setItem(5,1,MatBDePermutacao);
    } catch (QString &erro) {
        QMessageBox::warning(this,"Erro!",erro);
    } catch (std::bad_alloc &erro){
        QMessageBox::warning(this,"Erro!","Problema na alocação de memória.");
    }
}

void MainWindow::on_pushButtonAdicao_clicked()
{
    try {
        dnn::Matriz *mat = (*matA) + matB;
        ui->textEditSaida->setText(mat->getMatriz());

        delete mat;
    } catch (std::bad_alloc&){
        QMessageBox::warning(this,"Erro!","Problema na alocação de memória.");
    } catch (QString &erro) {
        QMessageBox::warning(this,"Erro!",erro);
    }
}

void MainWindow::on_pushButtonSubtracao_clicked()
{
    try {
        dnn::Matriz *mat = (*matA) - matB;
        ui->textEditSaida->setText(mat->getMatriz());

        delete mat;
    } catch (std::bad_alloc&){
        QMessageBox::warning(this,"Erro!","Problema na alocação de memória.");
    } catch (QString &erro) {
        QMessageBox::warning(this,"Erro!",erro);
    }
}

void MainWindow::on_pushButtonTranspostaA_clicked()
{
    try {
        dnn::Matriz *mat = matA->gerarTransposta();
        ui->textEditSaida->setText(mat->getMatriz());

        delete mat;
    } catch (std::bad_alloc&){
        QMessageBox::warning(this,"Erro!","Problema na alocação de memória.");
    } catch (QString &erro) {
        QMessageBox::warning(this,"Erro!",erro);
    }
}

void MainWindow::on_pushButtonTranspostaB_clicked()
{
    try {
        dnn::Matriz *mat = matB->gerarTransposta();
        ui->textEditSaida->setText(mat->getMatriz());

        delete mat;
    } catch (std::bad_alloc&){
        QMessageBox::warning(this,"Erro!","Problema na alocação de memória.");
    } catch (QString &erro) {
        QMessageBox::warning(this,"Erro!",erro);
    }
}

void MainWindow::on_pushButtonMultiplicarAPorK_clicked()
{
    try {
        int k = QInputDialog::getInt(this,"Leitura","k = ");

        dnn::Matriz *mat = matA->multiplicarPorK(k);
        ui->textEditSaida->setText(mat->getMatriz());

        delete mat;
    } catch (std::bad_alloc&){
        QMessageBox::warning(this,"Erro!","Problema na alocação de memória.");
    } catch (QString &erro) {
        QMessageBox::warning(this,"Erro!",erro);
    }
}

void MainWindow::on_pushButtonMultiplicarBPorK_clicked()
{
    try {
        int k = QInputDialog::getInt(this,"Leitura","k = ");

        dnn::Matriz *mat = matB->multiplicarPorK(k);
        ui->textEditSaida->setText(mat->getMatriz());

        delete mat;
    } catch (std::bad_alloc&){
        QMessageBox::warning(this,"Erro!","Problema na alocação de memória.");
    } catch (QString &erro) {
        QMessageBox::warning(this,"Erro!",erro);
    }
}

void MainWindow::on_pushButtonMultiplicacao_clicked()
{
    try {
        dnn::Matriz *mat = (*matA) * matB;
        ui->textEditSaida->setText(mat->getMatriz());

        delete mat;
    } catch (std::bad_alloc&){
        QMessageBox::warning(this,"Erro!","Problema na alocação de memória.");
    } catch (QString &erro) {
        QMessageBox::warning(this,"Erro!",erro);
    }
}

void MainWindow::on_pushButtonPotenciacaoA_clicked()
{
    try {
        int potencia = QInputDialog::getInt(this,"Leitura",
                                            "Potência:");

        dnn::Matriz *mat = matA->potenciacao(potencia);
        ui->textEditSaida->setText(mat->getMatriz());

        delete mat;
    } catch (QString &e) {
        QMessageBox::warning(this,"Erro",e);
    }
}

void MainWindow::on_pushButtonPotenciacaoB_clicked()
{
    try {
        int potencia = QInputDialog::getInt(this,"Leitura",
                                            "Potência:");

        dnn::Matriz *mat = matB->potenciacao(potencia);
        ui->textEditSaida->setText(mat->getMatriz());

        delete mat;
    } catch (QString &e) {
        QMessageBox::warning(this,"Erro",e);
    }
}
