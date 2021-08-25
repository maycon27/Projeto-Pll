#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <string.h>
#include <windows.h>
#include <conio2.h>
#include <locale.h>

#define MAX 50

using namespace std;


namespace princ{

typedef struct
{
    char nome[MAX],cpf[MAX],telefone[MAX],endereco[MAX];
    int num_conta, senha, rf;
    double saldo, emprestimo = 0;
} conta;
conta cliente[MAX];

void tela();
void menu_Principal();
void clientes();
void adm();
void cadastrar();
void mostrar();
void mostrar(int num_conta, int indent);
void saqueDeposito(int num_conta);
void transferencia(int num_conta);
void verificar (int num_conta, int& cont);
void login (int& num_conta, int senha, int& cont);
double movimentar (double saldo, int op, int saque, double deposito);
void emprestimo (int num_conta);
void solicitarEmp (double& emprestimo, int& opc);
void calcularEmp (double& valor, int opc, double& parc);
void pagarEmp (double& valorEmp);


// FUNÇÃO PARA TELA INCIAL
void menu_Principal()
{
    char menu;

    do
    {
        system("cls");

        tela();

        gotoxy(5,13);
        printf("1 - Administrador");
        gotoxy(5,14);
        printf("2 - Cliente");
        gotoxy(5,15);
        printf("3 - Sair");

        gotoxy(45,28);
        printf ("PRECIONE A TECLA CORRESPONDENTE ");
        fflush(stdin);
        menu = getch();

        switch(menu)
        {
        case 49:
            system("cls");
            adm();
            break;

        case 50:
            system("cls");
            clientes();
            break;

        case 51:
            system ("cls");
            exit(0);

        default:
            gotoxy(5,21);
            printf ("Opção inválida. ");
            system("pause");
            break;
        }
    }
    while(menu!=51);
}

// FUNÇÃO PARA ACESSAR SUBMENU ADMINISTRADOR
void adm()
{
    char menu;
    int conta, indentificador = 0;
    do
    {
        system("cls");
        gotoxy(5,2);
        printf("ADMINISTRADOR");
        gotoxy(5,4);
        printf("1 - Cadastrar Cliente");
        gotoxy(5,5);
        printf("2 - Consultar Cliente");
        gotoxy(5,6);
        printf("3 - Listar Clientes");
        gotoxy(5,7);
        printf("4 - Voltar");
        gotoxy(45,28);
        printf ("PRECIONE A TECLA CORRESPONDENTE ");

        menu = getch();

        switch(menu)
        {
        case 49:
            system("cls");
            cadastrar();
            break;

        case 50:
            system("cls");
            gotoxy(5,2);
            printf("Informe o número da conta: ");
            cin >> conta;
            mostrar(conta,indentificador);
            break;

        case 51:
            system("cls");
            mostrar();

            break;

        case 52:
            system("cls");
            menu_Principal();
            break;

        default:
            gotoxy(5,21);
            printf ("Opção inválida. ");
            system("pause");
            break;

        }
    }
    while(menu != 4);
}

// FUNÇÃO PARA ACESSAR SUBMENU CLIENTE
void clientes()
{

    char menu;
    int conta, senha, indentificador = 0;

    login (conta, senha, indentificador);
    if (indentificador == 1)
    {
        do
        {
            system("cls");
            gotoxy(5,2);
            printf("CLIENTE");
            gotoxy(5,4);
            printf("1 - Consultar Conta");
            gotoxy(5,5);
            printf("2 - Saque/Depósito");
            gotoxy(5,6);
            printf("3 - Transferência");
            gotoxy(5,7);
            printf("4 - Emprestimo");
            gotoxy(5,8);
            printf("5 - Voltar");
            gotoxy(45,28);
            printf ("PRECIONE A TECLA CORRESPONDENTE ");

            menu = getch();


            switch(menu)
            {
            case 49:

                system("cls");
                mostrar(conta,indentificador);
                break;

            case 50:
                system("cls");
                saqueDeposito(conta);
                break;

            case 51:
                system("cls");
                transferencia(conta);
                break;

            case 52:
                system("cls");
                emprestimo(conta);
                break;

            case 53:
                system("cls");
                menu_Principal();
                break;

            default:
                gotoxy(10,21);
                printf ("Opção inválida. ");
                system("pause");
                break;
            }

        } while(menu !=53);

        return;
    }

    gotoxy(5,21);
    printf("Login incorreto. ");
    system ("pause");
}

// FUNÇÃO PARA O CADASTRO DO CLIENTE
void cadastrar()
{
    // VARIAVEIS LOCAIS
    char res, nome[MAX],cpf[MAX],endereco[MAX],telefone[MAX];
    int num_conta, senha, cont = 0;
    double saldo;

    // INFORMAÇÕES NECESSARIAS PARA O CADASTRO
    do
    {
        fflush(stdin);
        system("cls");
        gotoxy(5,2);
        printf("Informe os dados do cliente");

        gotoxy(5,4);
        printf("Número da conta: ");
        cin >> num_conta;
        verificar(num_conta, cont);
        if (cont != 0)
        {
            gotoxy(5,21);
            printf ("Inválido, número de conta existente. ");
            system ("pause");
            return;
        }
        fflush(stdin);
        gotoxy(5,5);
        printf("Nome: ");
        gotoxy(5,5);
        printf("Nome: ");
        fgets(nome,sizeof(nome),stdin);
        fflush(stdin);
        gotoxy(5,6);
        printf("CPF: ");
        fgets(cpf,sizeof(cpf),stdin);
        gotoxy(5,7);
        printf("Endereço: ");
        fgets(endereco,sizeof(endereco),stdin);
        gotoxy(5,8);
        printf("Telefone: ");
        fgets(telefone,sizeof(telefone),stdin);
        gotoxy(5,9);
        printf("Senha: ");
        cin >> senha;
        gotoxy(5,11);
        printf("Saldo inicial: ");
        cin >> saldo;
        fflush(stdin);
        system("cls");

        if(cliente[num_conta].rf==0)
        {
            strcpy(cliente[num_conta].nome, nome);
            cliente[num_conta].num_conta = num_conta;
            strcpy(cliente[num_conta].cpf, cpf);
            strcpy(cliente[num_conta].endereco, endereco);
            strcpy(cliente[num_conta].telefone, telefone);
            cliente[num_conta].senha = senha;
            cliente[num_conta].saldo = saldo;
            cliente[num_conta].rf=1;

        }

        gotoxy(40,15);
        printf("Deseja cadastrar outro cliente?");
        gotoxy(40,25);
        printf ("PRECIONE A TECLA CORRESPONDENTE (S/N): ");
        res = getch();

    }
    while(res == 's' || res =='S');

}

// FUNÇÃO PARA LISTAR TODOS CADASTROS
void mostrar()
{
    system("cls");
    gotoxy(5,2);
    printf("LISTA DE CLIENTES");

    for(int i=0; i<MAX; i++)
    {
        if(cliente[i].rf==1)
        {
            cout << endl << endl;
            cout << "    Número da Conta: " << cliente[i].num_conta;
            cout << endl;
            cout << "    Nome: " << cliente[i].nome;
            cout << "    CPF: " << cliente[i].cpf;
            cout << "    Endereço: " << cliente[i].endereco;
            cout << "    Telefone: " << cliente[i].telefone;
            cout << "    Saldo: " << cliente[i].saldo << endl;
            printf("    Debito de Emprestimo:R$ %.2f",cliente[i].emprestimo);


        }
    }

    printf("\n\n    ");
    system("pause");

}

// FUNÇÃO PARA PESQUISAR O CADASTRO DO CLIENTE
void mostrar(int num_conta, int ident)
{
    switch(ident)
    {
    case 0:
        cout << endl
             << "    Número da Conta: " << cliente[num_conta].num_conta;
        cout << endl
             <<"    Nome: " << cliente[num_conta].nome;
        cout << "    CPF: " << cliente[num_conta].cpf;
        cout << "    Endereço: " << cliente[num_conta].endereco;
        cout << "    Telefone: " << cliente[num_conta].telefone;
        cout << "    Saldo: " << cliente[num_conta].saldo << endl;
        printf("    Debito de Emprestimo:R$ %.2f",cliente[num_conta].emprestimo);
        gotoxy(5,21);
        printf("precione qualquer tecla para retornar");
        getch();
        break;

    case 1:
        cout << endl
             << "    Número da Conta: " << cliente[num_conta].num_conta << endl;
        cout << "    Nome: " << cliente[num_conta].nome;
        cout << "    Saldo: " << cliente[num_conta].saldo << endl;
        printf("    Debito de Emprestimo:R$ %.2f",cliente[num_conta].emprestimo);

        gotoxy(5,21);
        printf("precione qualquer tecla para retornar");
        getch();
        break;

    case 2:
        cout << endl
             << "    Número da Conta: " << cliente[num_conta].num_conta << endl;
        cout << "    Nome: " << cliente[num_conta].nome;
        break;
    }
}

// FUNÇÃO PARA SAQUE OU DEPOSITO
void saqueDeposito(int num_conta)
{
    // VARIAVEIS LOCAIS
    int retirada, deposito, indentificador = 2;
    char opcao;

    system("cls");
    gotoxy(5,2);
    printf ("1 - Saque");
    gotoxy(5,3);
    printf ("2 - Deposito");

    gotoxy(45,25);
    printf ("PRECIONE A TECLA CORRESPONDENTE ");
    opcao = getch();

    system("cls");

    switch (opcao)
    {
    case 49:
        mostrar(num_conta, indentificador);
        gotoxy(5,6);
        printf ("Valor do saque: ");
        cin >> retirada;
        if(retirada <= cliente[num_conta].saldo)
        {
            cliente[num_conta].saldo = movimentar(cliente[num_conta].saldo, opcao, retirada, deposito);
            gotoxy(5,21);
            printf("saque concluído, precione qualquer tecla para retornar");
            getch();
            break;
        }

        else
        {
            gotoxy(5,21);
            printf ("Saldo não suficiente. ");
            system("pause");
            break;
        }

    case 50:
        mostrar(num_conta,indentificador);
        gotoxy(5,6);
        printf ("Valor do depósito: ");
        cin >> deposito;

        cliente[num_conta].saldo = movimentar(cliente[num_conta].saldo, opcao, retirada, deposito);
        gotoxy(5,21);
        printf("depósito concluído, precione qualquer tecla para retornar");
        getch();
        break;


    default:
        gotoxy(5,21);
        printf ("Opção inválida. ");
        system("pause");
        break;
    }
}

// FUNÇÃO PARA TRANSFERIR DINHEIRO PARA OUTRA CONTA
void transferencia(int num_conta)
{
    // VARIAVEIS LOCAIS
    int num_conta2, cont = 0, identificador = 2;
    double trans;

    gotoxy(5,2);
    printf ("Conta debitada:\n");
    mostrar(num_conta,identificador);

    gotoxy(5,8);
    printf ("Conta creditada: ");
    cin >> num_conta2;
    verificar(num_conta2, cont);
    if (cont == 0)
    {
        gotoxy(5,21);
        printf ("Incorreto, conta não existente. ");
        system("pause");
        return;
    }
    gotoxy(5,8);
    printf ("Conta creditada:        \n");

    mostrar(num_conta2,identificador);

    gotoxy(5,14);
    printf ("Valor a ser transferido: ");
    cin >> trans;

    if(trans <= cliente[num_conta].saldo)
        cliente[num_conta].saldo -= trans;

    else
    {
        gotoxy(5,21);
        printf ("Saldo insuficiente. ");
        system("pause");
        return;
    }
    if(trans <= cliente[num_conta2].saldo)
        cliente[num_conta2].saldo += trans;
    else
    {
        gotoxy(5,21);
        printf ("Saldo insuficiente. ");
        system("pause");
        return;
    }

    gotoxy(5,21);
    printf("tranferência concluída, precione qualquer tecla para retornar");
    getch();
}

// FUNÇÃO PARA VERIFICAR A EXISTENCIA DA CONTA
void verificar (int num_conta, int& cont)
{
    for(int i=0; i<MAX; i++)
    {
        if(num_conta==cliente[i].num_conta || num_conta >= MAX || num_conta <= 0)
        {
            cont ++;
            break;
        }
    }
}

// FUNÇÃO PARA RESTRIGIR O ACESSO AO PUBLICO
void login (int& num_conta, int senha, int& cont)
{
    system("cls");
    gotoxy(45,10);
    printf("LOGIN ");
    gotoxy(45,11);
    printf("Conta: ");
    cin >> num_conta;
    gotoxy(45,12);
    printf("Senha: ");
    cin >> senha;

    for(int i=0; i<MAX; i++)
    {
        if(num_conta==cliente[i].num_conta && senha==cliente[i].senha)
        {
            cont ++;
            return;
        }
    }
}

// FUNÇÃO PARA EFETUAR A OPERACAO DO SAQUE OU DEPOSITO
double movimentar(double saldo, int op, int saque, double deposito)
    {

        if(op == 49)
            saldo -= saque;
        else
            saldo += deposito;

        return saldo;
    }
// FUNÇÃO PARA PEGAR OU PAGAR EMPRÉSIIMO
void emprestimo (int num_conta)
{
    char opc;
    int opc2;
    double emprestimo,parcelas;

    cout << "Emprestimo\n\n";
    cout << "1 - Solicitar\n";
    cout << "2 - Pagar\n";
    opc = getch();

    switch (opc)
    {
        case 49:

        system("cls");

        cout << "Forneca o valor do emprestimo: ";
        cin >> emprestimo;

        cout << "Escolha a quantidade de parcelas" << endl;
        cout << "1 - 6 parcelas " << endl;
        cout << "2 - 12 parcelas " << endl;
        cin >> opc2;

        switch (opc2)
        {
           case 1:
            calcularEmp (emprestimo, opc2, parcelas);
            cliente[num_conta].emprestimo = emprestimo;
            printf("Valor das pacelas: R$ %.2f", parcelas);
            getch();
            break;

          case 2:
            calcularEmp (emprestimo, opc2, parcelas);
            cliente[num_conta].emprestimo = emprestimo;
            printf("Valor das pacelas: R$ %.2f", parcelas);
            getch();
            break;

          default:
            cout << "Escolha invalida";
            getch();
            break;
        }
      break;

    case 50:

    system("cls");
    pagarEmp(cliente[num_conta].emprestimo);
    break;

    default:
    gotoxy(5,21);
    printf ("Opção inválida. ");
    system("pause");
    break;
    }

}
// FUNÇÃO PARA CALCULAR O EMPRESTIMO
void calcularEmp (double& valor, int opc, double& parc)
{
    if (opc == 1)
    {
        valor = valor * pow((1+(4.9/100)), 6);
        parc = valor/6;
    }

    else
    {
        valor = valor * pow((1+(6/100)), 12);
        parc = valor/12;
    }

}
// FUNÇÃO PARA PAGAR O EMPRESTIMO
void pagarEmp (double& valorEmp)
{
    int opc2;
    cout << "Escolha a opcao de pagamento" << endl;
    cout << "1 - Uma parcela" << endl;
    cout << "2 - Quitar divida" << endl;
    cin >> opc2;

    if (opc2 == 1)
    {
        valorEmp = valorEmp -(valorEmp/6);
    gotoxy(5,21);
    printf("Parcela paga com sucesso, precione qualquer tecla para retornar");
    getch();

    }
    else
    {
    valorEmp = 0;
    printf("Emprestimo pago com sucesso, precione qualquer tecla para retornar");
    getch();
    }
}

// FUNÇÃO PARA IMPRIMIR O LAYOUT
void tela()
{
        textcolor(WHITE);
        textbackground(BLUE);
        clrscr();
        gotoxy(15,4);
        cprintf("     __  _     _                        _____                             _        ");
        gotoxy(15,5);
        cprintf("    / _\\(_)___| |_ ___ _ __ ___   __ _  \\  _  \\ __ _ _ __   ___ __ _ _ __(_) ___   ");
        gotoxy(15,6);
        cprintf("    \\ \\ | / __| __/ _ \\ '_ ` _ \\ / _` | |     /  _` | '_ \\ / __/ _` | '__| |/ _ \\  ");
        gotoxy(15,7);
        cprintf("    _\\ \\| \\__ \\ ||  __/ | | | | | (_| | |  _  \\ (_| | | | | (_| (_| | |  | | (_) | ");
        gotoxy(15,8);
        cprintf("    \\__/|_|___/\\__\\___|_| |_| |_|\\__,_| |_____/\\__,_|_| |_|\\___\\__,_|_|  |_|\\___/  ");
}
}
