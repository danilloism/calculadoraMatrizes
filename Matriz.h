#ifndef MATRIZ_H
#define MATRIZ_H
#include<QString>

namespace dnn {

class Matriz
{
private:
    int quantidadeDeLinhas;
    int quantidadeDeColunas;
    int *ptMatriz;

public:
    Matriz(int quantidadeDeLinhas, int quantidadeDeColunas);
    ~Matriz(){if(ptMatriz) delete[] ptMatriz;}
    int getQuantidadeDeColunas()const{return this->quantidadeDeColunas;}
    int getQuantidadeDeLinhas()const{return this->quantidadeDeLinhas;}
    void setElemento(int linha, int coluna, int valor);
    int getElemento(int linha, int coluna)const;
    QString getMatriz()const;
    Matriz* operator +(Matriz const * const objeto)const;
    Matriz* operator -(Matriz const * const objeto)const;
    Matriz* operator *(Matriz const * const objeto)const;
    Matriz* gerarTransposta()const;
    Matriz* multiplicarPorK(int k)const;
    bool operator ==(Matriz const * const objeto)const;
    bool operator !=(Matriz const * const objeto)const;
    bool ehTriangularSuperior()const;
    bool ehTriangularInferior()const;
    bool ehSimetrica()const;
    bool ehIdentidade()const;
    bool ehOrtogonal()const;
    bool ehDePermutacao()const;
    Matriz* potenciacao(int potencia)const;
};

}



#endif // MATRIZ_H
