#include "banco.h"
#include <iostream>
#include "constantes.h"

using namespace std;

Banco::Banco() 
{
    this->contas[0] = Conta(); // Conta default/admin
    this->contas[1] = {1234, 1, "Joao", "Corrente", 300};
    this->contas[2] = {4567, 2, "Jose", "Poupanca", 800};
    this->contas[3] = {7890, 3, "Maria", "Corrente", 1000};
    this->contas[4] = {8956, 4, "Madalena", "Poupanca", 2000};
    
    
    this->qtd_contas = 5; // Inicializa a variável que controla a quantidade de contas cadastradas
    this->senha_mestra = 0000; // criei uma senha mestra como foi pedido
}

Banco::~Banco()
{
}

// Plota as mensagens de erro/sucesso do sistema
void Banco::exibeStatus(int status) {
    switch (status) {
        case SUCESSO:
            cout << "Operacao realizada com sucesso!" << endl;
            break;
        case SALDO_INSUFICIENTE:
            cout << "Erro: Saldo insuficiente." << endl;
            break;
        case SENHA_INVALIDA:
            cout << "Erro: Senha incorreta." << endl;
            break;
        case VALOR_INVALIDO:
            cout << "Erro: Valor invalido (deve ser maior que zero)." << endl;
            break;
        case BANCO_CHEIO:
            cout << "Erro: O banco atingiu o limite maximo de contas." << endl;
            break;
        default:
            cout << "Erro desconhecido. Codigo: " << status << endl;
            break;
    }
}

Conta *Banco::buscaConta(int numero)
{
    
    for (int i = 0; i < NUMCONTAS; i++)
    {
        if (numero == this->contas[i].numero)
        {
            return &this->contas[i];
        }
    }
    return nullptr;
}

// funcao de transferencia
int Banco::transferencia(Conta *origem, Conta *destino, double valor, int senha) {
    // Tenta sacar da conta de origem primeiro
    int status_saque = origem->saque(senha, valor);
    
    if (status_saque == SUCESSO) {
        destino->deposito(valor);
        return SUCESSO;
    }
    return status_saque; 
}

// Usando a variável de qtd_contas
int Banco::cadastro(int senha, string titular, string tipo, double saldo){
    
    if (this->qtd_contas < NUMCONTAS) {
        int novo_numero_conta = this->qtd_contas + NUMCONTAS; 
        
        // Adiciona a conta no primeiro espaço vazio do vetor
        this->contas[this->qtd_contas] = Conta(senha, novo_numero_conta, titular, tipo, saldo);
        
        cout << "\nConta criada com sucesso! O NUMERO DA CONTA E: " << novo_numero_conta << endl;
        
        this->qtd_contas++;
        return SUCESSO;
    }
    
    return BANCO_CHEIO;
}

int Banco::atendimento_cliente() 
{
    Conta *contaCliente;
    int numC = 0;
    int senhain;

    cout << "\n--- ATENDIMENTO AO CLIENTE ---" << endl;
    cout << "Digite o numero da sua conta: ";
    cin >> numC;

    contaCliente = this->buscaConta(numC); 

    if (contaCliente == nullptr) {
        this->exibeStatus(CONTA_INEXISTENTE);
        return CONTA_INEXISTENTE;
    }
    
    cout << "Digite a sua senha: ";
    cin >> senhain;

    if (contaCliente->validaSenha(senhain)) {
        cout << "\nOla, " << contaCliente->titular << "! Acesso liberado." << endl;
        
        bool atendimento = true;
        while (atendimento) 
        {
            int senha;
            int status;
            int op;
            double valor;
            
            cout << "\nQual operacao deseja fazer?" << endl;
            cout << "1 - Saque | 2 - Deposito | 3 - Ver Saldo | 4 - Transferencia | 5 - Sair: ";
            cin >> op; 
            
            switch (op)
            {
                case 1:
                    cout << "Digite o valor do saque: R$ ";
                    cin >> valor;
                    cout << "Confirme sua senha: ";
                    cin >> senha;
                    
                    status = contaCliente->saque(senha, valor);
                    this->exibeStatus(status);
                    break;
                    
                case 2:
                    cout << "Digite o valor do deposito: R$ ";
                    cin >> valor;
                    
                    status = contaCliente->deposito(valor);
                    this->exibeStatus(status);
                    break;
                    
                case 3:
                {
                    double saldoSaida = 0;
                    cout << "Confirme sua senha: ";
                    cin >> senha;
                    
                    status = contaCliente->getSaldo(senha, saldoSaida);
                    if (status == SUCESSO) {
                        cout << "Saldo atual: R$ " << saldoSaida << endl;
                    } else {
                        this->exibeStatus(status);
                    }
                    break;
                }
                case 4:
                {
                    int contaDestinoNum;
                    Conta *contaDestino;

                    cout << "Digite o numero da conta de destino: ";
                    cin >> contaDestinoNum;
                    
            
                    contaDestino = this->buscaConta(contaDestinoNum); 
                    
                    if (contaDestino == nullptr) {
                        cout << "Erro: Conta de destino nao encontrada." << endl;
                        break;
                    }

                    cout << "Digite o valor da transferencia: R$ ";
                    cin >> valor;
                    cout << "Confirme sua senha: ";
                    cin >> senha;
                    
                    status = this->transferencia(contaCliente, contaDestino, valor, senha);
                    this->exibeStatus(status);
                    break;
                }
                case 5:
                    cout << "Saindo da conta..." << endl;
                    atendimento = false;
                    break;
                    
                default:
                    cout << "Opcao Invalida!" << endl;
                    break;
            }
        }
    }
    else {
        this->exibeStatus(SENHA_INVALIDA);
    }
    
    return 0;
}

int Banco::atendimento_funcionario() {
    int senhaFuncionario;
    
    cout << "\n--- ACESSO RESTRITO FUNCIONARIO ---" << endl;
    cout << "Digite a senha mestra de funcionario: ";
    cin >> senhaFuncionario;
    
    bool validacao = this->senha_mestra;
    
    if (validacao) {
        int opcao;
        cout << "\n1 - Cadastrar nova conta" << endl;
        cout << "2 - Voltar" << endl;
        cout << "Opcao: ";
        cin >> opcao;
        
        if (opcao == 1) {
            string nome, tipo; 
            int senha;
            double saldo;
            
            cout << "Nome do titular: ";
            cin >> nome;
            
            cout << "Tipo da conta (Corrente/Poupanca): ";
            cin >> tipo;
            
            cout << "Defina a senha da conta: ";
            cin >> senha;
            
            cout << "Deposito inicial obrigatorio: R$ ";
            cin >> saldo;
            
            int status = this->cadastro(senha, nome, tipo, saldo);
            this->exibeStatus(status);
        }
    } else {
        this->exibeStatus(SENHA_INVALIDA);
    }
    
    return 0;
}