#include "Matriz.h"


namespace dnn {

Matriz::Matriz(int quantidadeDeLinhas, int quantidadeDeColunas):
    quantidadeDeLinhas(0),
    quantidadeDeColunas(0),
    ptMatriz(0)
{
    if(quantidadeDeLinhas<=0) throw QString("Quantidade de linhas fora do intervalo válido.");
    if(quantidadeDeColunas<=0) throw QString("Quantidade de colunas fora do intervalo válido.");

    try {
        ptMatriz = new int[quantidadeDeLinhas*quantidadeDeColunas];
        this->quantidadeDeLinhas=quantidadeDeLinhas;
        this->quantidadeDeColunas=quantidadeDeColunas;
    } catch (std::bad_alloc &erro) {
        throw QString("Matriz não foi criada.");
    }

}

void Matriz::setElemento(int linha, int coluna, int valor)
{
    if(linha<0 || coluna<0 || linha>=quantidadeDeLinhas || coluna>=quantidadeDeColunas)
        throw QString("Posição da linha ou coluna fora do intervalo válido.");

    int pos = linha*quantidadeDeColunas+coluna;
    *(ptMatriz+pos) = valor;

}

int Matriz::getElemento(int linha, int coluna) const
{
    if(linha<0 || coluna<0 || linha>=quantidadeDeLinhas || coluna>=quantidadeDeColunas)
        throw QString("Posição da linha ou coluna fora do intervalo válido.");

    int pos = linha*quantidadeDeColunas+coluna;
    return *(ptMatriz+pos);
}

QString Matriz::getMatriz() const
{
    QString saida = "";

    for(int linha=0;linha<quantidadeDeLinhas;linha++)
    {
        for(int coluna=0;coluna<quantidadeDeColunas;coluna++)
        {
            saida+= QString::number(getElemento(linha,coluna));
            saida+= "   ";
        }
        saida+="\n";
    }
    return saida;
}

Matriz* Matriz::operator +(Matriz const * const objeto) const
{
    if(quantidadeDeLinhas != objeto->getQuantidadeDeLinhas() || quantidadeDeColunas != objeto->getQuantidadeDeColunas())
        throw QString("Não podem ser adicionadas matrizes de tamanho difente.");

    try {
        Matriz *aux = new Matriz(quantidadeDeLinhas,quantidadeDeColunas);
        for(int linha=0;linha<quantidadeDeLinhas;linha++){
            for(int coluna=0;coluna<quantidadeDeColunas;coluna++){
                int valor = this->getElemento(linha,coluna) +
                        objeto->getElemento(linha,coluna);
                aux->setElemento(linha,coluna,valor);
            }
        }
        return aux;
    } catch (std::bad_alloc&) {
        throw QString("Problema na alocação de memória.");
    } catch(QString &erro){
        throw QString(erro);
    }
}

Matriz* Matriz::operator -(Matriz const * const objeto) const
{
    if(quantidadeDeLinhas != objeto->getQuantidadeDeLinhas() || quantidadeDeColunas != objeto->getQuantidadeDeColunas())
        throw QString("Não podem ser subtraídas matrizes de tamanho difente.");

    try {
        Matriz *aux = new Matriz(quantidadeDeLinhas,quantidadeDeColunas);
        for(int linha=0;linha<quantidadeDeLinhas;linha++){
            for(int coluna=0;coluna<quantidadeDeColunas;coluna++){
                int valor = this->getElemento(linha,coluna) -
                        objeto->getElemento(linha,coluna);
                aux->setElemento(linha,coluna,valor);
            }
        }
        return aux;
    } catch (std::bad_alloc&) {
        throw QString("Problema na alocação de memória.");
    } catch(QString &erro){
        throw QString(erro);
    }
}

Matriz* Matriz::operator *(Matriz const * const objeto)const{
    if(quantidadeDeColunas != objeto->getQuantidadeDeLinhas()) throw QString("Quantidade de colunas da Matriz A deve ser\nigual à quantidade de linhas da Matriz B.");

    try {
        Matriz *aux = new Matriz(quantidadeDeLinhas,objeto->getQuantidadeDeColunas());
        int elemento = 0;
        for(int linha=0;linha<quantidadeDeLinhas;linha++){
            for(int coluna=0;coluna<objeto->getQuantidadeDeColunas();coluna++){
                for(int propriedadeComum=0;propriedadeComum<quantidadeDeColunas;propriedadeComum++){
                    elemento += this->getElemento(linha,propriedadeComum) * objeto->getElemento(propriedadeComum,coluna);
                }
                aux->setElemento(linha, coluna, elemento);
                elemento = 0;
            }
        }
        return aux;
    } catch (std::bad_alloc&) {
        throw QString("Problema na alocação de memória.");
    } catch(QString &erro){
        throw QString(erro);
    }
}

Matriz* Matriz::gerarTransposta() const
{
    try {
        if(!ptMatriz) throw QString("Matriz não existe.");
        Matriz *aux = new Matriz(quantidadeDeColunas,quantidadeDeLinhas);
        for(int linha=0;linha<quantidadeDeColunas;linha++){
            for(int coluna=0;coluna<quantidadeDeLinhas;coluna++){
                aux->setElemento(linha,coluna,getElemento(coluna,linha));
            }
        }
        return aux;
    } catch (std::bad_alloc&) {
        throw QString("Problema na alocação de memória.");
    } catch(QString &erro){
        throw QString(erro);
    }

}

Matriz* Matriz::multiplicarPorK(int k) const
{
    try {
        if(!ptMatriz) throw QString("Matriz não existe.");
        Matriz *aux = new Matriz(quantidadeDeLinhas,quantidadeDeColunas);
        for(int linha=0;linha<quantidadeDeLinhas;linha++){
            for(int coluna=0;coluna<quantidadeDeColunas;coluna++){
                int valor = this->getElemento(linha,coluna) * k;
                aux->setElemento(linha,coluna,valor);
            }
        }
        return aux;
    } catch (std::bad_alloc&) {
        throw QString("Problema na alocação de memória.");
    } catch(QString &erro){
        throw QString(erro);
    }
}

bool Matriz::operator ==(Matriz const * const objeto) const
{
    if(this->quantidadeDeColunas == objeto->quantidadeDeColunas && this->quantidadeDeLinhas == objeto->quantidadeDeLinhas){
        for(int linha=0;linha<quantidadeDeLinhas;linha++){
            for(int coluna=0;coluna<quantidadeDeColunas;coluna++){
                if(this->getElemento(linha,coluna) != objeto->getElemento(linha,coluna)) return false;
            }
        }

        return true;
    }else return false;
}

bool Matriz::operator !=(Matriz const * const objeto) const
{
    if(this->quantidadeDeColunas != objeto->quantidadeDeColunas || this->quantidadeDeLinhas != objeto->quantidadeDeLinhas){
        return true;
    }else{
        for(int linha=0;linha<quantidadeDeLinhas;linha++){
            for(int coluna=0;coluna<quantidadeDeColunas;coluna++){
                if(this->getElemento(linha,coluna) != objeto->getElemento(linha,coluna)) return true;
            }
        }

        return false;
    }
}

bool Matriz::ehTriangularSuperior() const
{
    if(!ptMatriz) throw QString("Matriz não existe.");

    if(quantidadeDeColunas!=quantidadeDeLinhas) return false;
    for(int linha=0;linha<quantidadeDeLinhas;linha++){
        for(int coluna=0;coluna<quantidadeDeColunas;coluna++){
            if(linha>coluna){
                if(getElemento(linha,coluna)!=0) return false;
            }
        }
    }

    return true;
}

bool Matriz::ehTriangularInferior() const
{
    if(!ptMatriz) throw QString("Matriz não existe.");
    if(quantidadeDeColunas!=quantidadeDeLinhas) return false;
    for(int linha=0;linha<quantidadeDeLinhas;linha++){
        for(int coluna=0;coluna<quantidadeDeColunas;coluna++){
            if(linha<coluna){
                if(getElemento(linha,coluna)!=0) return false;
            }
        }
    }

    return true;
}

bool Matriz::ehSimetrica() const
{
    try {
        if(!ptMatriz) throw QString("Matriz não existe.");

        if(quantidadeDeColunas!=quantidadeDeLinhas){
            return false;
        }else{
            for(int linha=0;linha<quantidadeDeLinhas;linha++){
                for(int coluna=0;coluna<quantidadeDeColunas;coluna++){
                        if(getElemento(linha,coluna)!=getElemento(coluna,linha)){
                            return false;
                        }
                }
            }
        }

        return true;
    }catch (std::bad_alloc&) {
        throw QString("Problema na alocação de memória.");
    } catch(QString &erro){
        throw QString(erro);
    }
}

bool Matriz::ehIdentidade() const
{
    if(!ptMatriz) throw QString("Matriz não existe.");
    if(quantidadeDeColunas!=quantidadeDeLinhas) return false;
    for(int linha=0;linha<quantidadeDeLinhas;linha++){
        for(int coluna=0;coluna<quantidadeDeColunas;coluna++){
            if(linha==coluna){
                if(getElemento(linha,coluna)!=1) return false;
            }
        }
    }

    return true;
}

bool Matriz::ehOrtogonal() const
{
    if(!ptMatriz) throw QString("Matriz não existe.");
    Matriz *transposta = this->gerarTransposta();
    Matriz *resultado = (*this)*transposta;

    if(resultado->ehIdentidade()){
        delete transposta;
        delete resultado;
        return true;
    }

    delete transposta;
    delete resultado;
    return false;
}

bool Matriz::ehDePermutacao() const
{
    if(!ptMatriz) throw QString("Matriz não existe.");
    if(this->getQuantidadeDeColunas()==1 && this->getQuantidadeDeLinhas()==1 && this->getElemento(0,0)!=1) return false;

    int soma = 0;
    for(int coluna=0;coluna<quantidadeDeColunas;coluna++){
        for(int linha=0;linha<quantidadeDeLinhas;linha++){
            if(getElemento(linha,coluna)==1) soma+=getElemento(linha,coluna);
            else if(getElemento(linha,coluna)!=0) return false;
        }
        if(soma!=1) return false;
        soma = 0;
    }

    return true;
}

Matriz* Matriz::potenciacao(int potencia) const
{
    if(!ptMatriz) throw QString("Matriz não existe.");
    if(quantidadeDeColunas!=quantidadeDeLinhas) throw QString("Matriz deve ser quadrada.");
    if(potencia<0) throw QString("Potencia não pode ser menor que 0.");
    try {
        Matriz *aux = new Matriz(quantidadeDeLinhas,quantidadeDeColunas);
        Matriz *aux2;

        if(potencia==0){
            for(int linha=0;linha<quantidadeDeLinhas;linha++){
                for(int coluna=0;coluna<quantidadeDeColunas;coluna++){
                    if(linha==coluna){
                        aux->setElemento(linha,coluna,1);
                    }else{
                        aux->setElemento(linha,coluna,0);
                    }
                }
            }
            return aux;
        }

        for(int linha=0;linha<quantidadeDeLinhas;linha++){
            for(int coluna=0;coluna<quantidadeDeColunas;coluna++){
                aux->setElemento(linha,coluna,getElemento(linha,coluna));
            }
        }

        if(potencia==1) return aux;

        for(int i=0;i<potencia-1;i++){
            aux2 = aux;
            aux = (*this) * aux;
            delete aux2;
        }

        return aux;
    } catch (std::bad_alloc&) {
        throw QString("Problema na alocação de memória.");
    } catch (QString &e) {
        throw QString(e);
    }
}

}

