#include <stdio.h>
#include <string.h>
#include "RPG.h"

int main()
{

    Ficha Nova_Ficha;
    int i, opcao;
    int armadura_observacao = 0; ///1 = Pesada. 2 = Rigida. Variavel pra calcular a corrida na funcao atribuicoesFinais().

    int comprou_armadura = 0; /// Variaveis pra controlar a compra de armadura/escudo (só pode comprar um de cada).
    int comprou_escudo = 0;   /// 0 significa que não comprou e 1 significa que já comprou.

    int indice_hab = 2; ///Variavel pra controlar as habilidades e nao deixar serem sobrescritas.
                        ///Começa com 2 pois ja tem as habilidades automaticas de raca e classe.

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    atribuicoesIniciais(&Nova_Ficha);

    do{
        printf("O que vai querer fazer agora?\n\n"
               "[1] Editar Detalhes do Personagem\n\n"
               "[2] Editar Raca\n\n"
               "[3] Editar Classe\n\n"
               "[4] Comprar Armas Corporais\n\n"
               "[5] Comprar Armas de Distancia\n\n"
               "[6] Comprar Armadura\n\n"
               "[7] Comprar Escudo\n\n"
               "[8] Comprar Itens de Conjuracao\n\n"
               "[9] SAIR\n\n");
        scanf("%i", &opcao);
        fflush(stdin);
        while((opcao < 1) || (opcao > 9)){
            printf("Codigo Invalido, escolha um numero de 1 a 9: \n");
            scanf("%i", &opcao);
            fflush(stdin);
        }
        system("cls");
        switch(opcao){
        case 1:
            detalhesPJ(&Nova_Ficha, &indice_hab);
            system("cls");
            break;
        case 2:
            escolherRaca(&Nova_Ficha);
            system("cls");
            break;
        case 3:
            escolherClasse(&Nova_Ficha);
            system("cls");
            break;
        case 4:
            if (Nova_Ficha.dinheiro <= 0) {
                printf("Voce nao tem mais dinheiro.\n\n");
            }else{
                comprarArmaCorporal(&Nova_Ficha);
                system("cls");
            }
            break;
        case 5:
            if (Nova_Ficha.dinheiro <= 0) {
                printf("Voce nao tem mais dinheiro.\n\n");
            }else{
                comprarArmaDistancia(&Nova_Ficha);
                system("cls");
            }
            break;
        case 6:
            if (comprou_armadura == 1){
                printf("Voce ja comprou armadura!\n\n");
                system("pause");
                break;
            }
            if (Nova_Ficha.dinheiro <= 0) {
                printf("Voce nao tem mais dinheiro.\n\n");
            }else{
                comprarArmadura(&Nova_Ficha, &comprou_armadura, &armadura_observacao);
                system("cls");
            }
            break;
        case 7:
            if (comprou_escudo == 1){
                printf("Voce ja comprou escudo!\n\n");
                system("pause");
                break;
            }
            if (Nova_Ficha.dinheiro <= 0) {
                printf("Voce nao tem mais dinheiro.\n\n");
            }else{
                comprarEscudo(&Nova_Ficha, &comprou_escudo);
                system("cls");
            }
            break;
        case 8:
            if (Nova_Ficha.dinheiro <= 0) {
                printf("Voce nao tem mais dinheiro.\n\n");
            }else{
                comprarItemConjuracao(&Nova_Ficha);
                system("cls");
            }
            break;
        default:
            printf("Saindo...\n");
        }
    }while(opcao != 9);

    atribuicoesFinais(&Nova_Ficha, armadura_observacao); ///Funcao pra atribuir deslocamento, carga e defesa.

    escreverTxt(Nova_Ficha, indice_hab); ///Funcao que cria o arquivo txt.

    return 0;
}
