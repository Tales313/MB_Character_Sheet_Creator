#include <stdio.h>
#include <string.h>
#include "RPG.h"

void atribuicoesIniciais(Ficha *F)
{
    strcpy(F->nome_jogador, "...");
    strcpy(F->nome_personagem, "...");
    strcpy(F->raca, "...");
    strcpy(F->classe, "...");
    F->nivel = 1;

    F->vida_maxima = 60;
    F->mana_maxima = 60;
    F->forca = 1;
    F->agilidade = 1;
    F->inteligencia = 1;
    F->vontade = 1;

    F->bloqueio = 5;  ///Bloqueio, Esquiva e Determinacao ja começam com seus valores automaticos atribuidos!
    F->esquiva = 5;
    F->determinacao = 8;
    F->deslocamento = (F->agilidade/2) + 5;
    F->corrida = F->deslocamento*4;

    F->carga_basica = F->forca*7;
    F->carga_pesada = F->carga_basica*5;
    F->carga_maxima = F->carga_basica*10;

    F->lvl_points = 0;
    F->nmr_habs = 0;
    F->indice_equip = 0;

    strcpy(F->habilidades[0], "Raca nao escolhida");
    strcpy(F->habilidades[1], "Classe nao escolhida");

    printf("Nome do Jogador: "); ///Lendo o nome do jogador.
    scanf("%30[^\n]s", F->nome_jogador);
    fflush(stdin);
    system("cls");

    printf("Dinheiro Inicial: "); ///Lendo a quantidade de dinheiro inicial do personagem.
    scanf("%i", &F->dinheiro);
    fflush(stdin);
    system("cls");
}

void detalhesPJ(Ficha *F, int *indice_hab)
{
    int opcao;
    int escolheu_nivel = 0; ///O usuario so pode escolher o nivel uma vez durante a execucao do programa.

    do{
        printf("Digite o numero e pressione Enter: \n"
               "(Voce tem %i pontos de evolucao para gastar)\n"
               "(Pontos de evolucao = Nivel -1)\n\n\n"
               "[1] Nivel (apos escolhido uma vez, nao sera possivel mudar)\n\n"
               "[2] Nome do Personagem\n\n"
               "[3] Habilidades\n\n"
               "[4] +10 na Vida (-1 ponto de evolucao)\n\n"
               "[5] +10 na Mana (-1 ponto de evolucao)\n\n"
               "[6] +5 na vida e +5 na mana (-1 ponto de evolucao)\n\n"
               "[7] VOLTAR\n\n", F->lvl_points);
        scanf("%i", &opcao);
        fflush(stdin);
        while((opcao < 1) || (opcao > 7)){
            printf("Codigo Invalido, escolha um numero de 1 a 7: ");
            scanf("%i", &opcao);
            fflush(stdin);
        }
        puts("\n");
        switch(opcao){
        case 1:
            if(escolheu_nivel == 1){
                printf("Voce ja escolheu o nivel do personagem!\n\n");
                system("pause");
                break;
            }
            printf("Digite o nivel do personagem: ");
            scanf("%i", &F->nivel);
            escolheu_nivel = 1; ///Significa que o usuario nao vai poder mudar o nivel do pj.
            F->lvl_points = F->nivel-1;
            F->nmr_habs = F->nivel+2;
            break;
        case 2:
            printf("Digite o nome do personagem: ");
            scanf("%30[^\n]s", F->nome_personagem);
            break;
        case 3:
            if(F->nmr_habs == 0){
                printf("Voce nao pode mais escolher habilidades!\n\n");
                system("pause");
                break;
            }
            printf("Digite o nome da habilidade: ");
            scanf("%30[^\n]s", F->habilidades[*indice_hab]);
            *indice_hab += 1;
            F->nmr_habs -= 1;
            break;
        case 4:
            if(F->lvl_points == 0){
                printf("Voce nao tem mais pontos de evolucao para gastar!\n\n");
                system("pause");
                break;
            }
            F->vida_maxima += 10;
            F->lvl_points--;
            printf("Voce agora tem %i de vida maxima!\n\n", F->vida_maxima);
            system("pause");
            break;
        case 5:
            if(F->lvl_points == 0){
                printf("Voce nao tem mais pontos de evolucao para gastar!\n\n");
                system("pause");
                break;
            }
            F->mana_maxima += 10;
            F->lvl_points--;
            printf("Voce agora tem %i de mana maxima!\n\n", F->mana_maxima);
            system("pause");
            break;
        case 6:
            if(F->lvl_points == 0){
                printf("Voce nao tem mais pontos de evolucao para gastar!\n\n");
                system("pause");
                break;
            }
            F->mana_maxima += 5;
            F->vida_maxima += 5;
            F->lvl_points--;
            printf("Voce agora tem %i de vida maxima e %i de mana maxima!\n\n", F->vida_maxima, F->mana_maxima);
            system("pause");
            break;
        default:
            system("exit");
        }
        system("cls");
    }while(opcao != 7);
}

void escolherRaca(Ficha *F)
{
    ///são 14 raças, 11 do guia basico +3 do guia do heroi.
    int opcao, codigo_asterio, codigo_humano;

    printf("Digite o numero e pressione Enter: \n\n"
           "[1] Aesir\n\n"
           "[2] Anao\n\n"
           "[3] Asterio\n\n" ///guia do heroi
           "[4] Centauro\n\n" ///guia do heroi
           "[5] Elfo\n\n"
           "[6] Faen\n\n"
           "[7] Fauno\n\n"
           "[8] Fira\n\n"
           "[9] Humano\n\n"
           "[10] Juban\n\n"
           "[11] Levent\n\n"
           "[12] Mahok\n\n"
           "[13] Metadilio\n\n" ///guia do heroi
           "[14] Tailox\n\n"
           "[15] VOLTAR\n\n");
    scanf("%i", &opcao);
    fflush(stdin);
    while((opcao < 1) || (opcao > 15)){
        printf("Codigo Invalido, escolha um numero de 1 a 15: ");
        scanf("%i", &opcao);
        fflush(stdin);
    }

    switch(opcao){
    case 1:
        F->forca = 4; F->agilidade = 2; F->inteligencia = 3; F->vontade = 3;
        strcpy(F->raca, "Aesir");
        strcpy(F->habilidades[0], "Vigor Nordico");
        break;
    case 2:
        F->forca = 4; F->agilidade = 2; F->inteligencia = 3; F->vontade = 3;
        strcpy(F->raca, "Anao");
        strcpy(F->habilidades[0], "Coracao da Montanha");
        break;
    case 3:
        strcpy(F->raca, "Asterio");
        printf("Macho ou femea? (digite 1 ou 2): ");
        scanf("%i", &codigo_asterio);
        fflush(stdin);
        while((codigo_asterio != 1) && (codigo_asterio != 2)){
            printf("Codigo Invalido, digite 1 para macho ou 2 para femea: ");
            scanf("%i", &codigo_asterio);
            fflush(stdin);
        }
        if(codigo_asterio == 1){
            F->forca = 5; F->agilidade = 2; F->inteligencia = 2; F->vontade = 3;
            strcpy(F->habilidades[0], "Chifres Poderosos");
        }else{
            F->forca = 3; F->agilidade = 2; F->inteligencia = 3; F->vontade = 2;
            strcpy(F->habilidades[0], "Faro");
        }
        break;
    case 4:
        F->forca = 4; F->agilidade = 2; F->inteligencia = 3; F->vontade = 3;
        strcpy(F->raca, "Centauro");
        strcpy(F->habilidades[0], "Corpo Equino");
        break;
    case 5:
        F->forca = 2; F->agilidade = 4; F->inteligencia = 3; F->vontade = 3;
        strcpy(F->raca, "Elfo");
        strcpy(F->habilidades[0], "Bencao de Lathellanis");
        break;
    case 6:
        F->forca = 2; F->agilidade = 4; F->inteligencia = 3; F->vontade = 2;
        strcpy(F->raca, "Faen");
        strcpy(F->habilidades[0], "Constituicao Feerica");
        break;
    case 7:
        F->forca = 3; F->agilidade = 3; F->inteligencia = 3; F->vontade = 3;
        strcpy(F->raca, "Fauno");
        strcpy(F->habilidades[0], "Patas com Cascos");
        break;
    case 8:
        F->forca = 3; F->agilidade = 3; F->inteligencia = 3; F->vontade = 3;
        strcpy(F->raca, "Fira");
        strcpy(F->habilidades[0], "Habitante do Deserto");
        break;
    case 9:
        F->forca = 3; F->agilidade = 3; F->inteligencia = 3; F->vontade = 3;
        strcpy(F->raca, "Humano");
        strcpy(F->habilidades[0], "Adaptabilidade");
        printf("O Humano pode escolher um atributo para aumentar, digite o codigo: \n\n"
               "[1] Forca\n"
               "[2] Agilidade\n"
               "[3] Inteligencia\n"
               "[4] Vontade\n\n");
        scanf("%i", &codigo_humano);
        fflush(stdin);
        while((codigo_humano < 1) || (codigo_humano > 4)){
            printf("Codigo Invalido, escolha um numero de 1 a 4: ");
            scanf("%i", &codigo_humano);
            fflush(stdin);
        }
        switch(codigo_humano){
        case 1:
            F->forca += 1;
            break;
        case 2:
            F->agilidade += 1;
            break;
        case 3:
            F->inteligencia += 1;
            break;
        case 4:
            F->vontade += 1;
        }
        break;
    case 10:
        F->forca = 4; F->agilidade = 2; F->inteligencia = 3; F->vontade = 4;
        strcpy(F->raca, "Juban");
        strcpy(F->habilidades[0], "Corpo Pesado");
        break;
    case 11:
        F->forca = 2; F->agilidade = 3; F->inteligencia = 3; F->vontade = 3;
        strcpy(F->raca, "Levent");
        strcpy(F->habilidades[0], "Asas Pesadas");
        break;
    case 12:
        F->forca = 5; F->agilidade = 2; F->inteligencia = 2; F->vontade = 3;
        strcpy(F->raca, "Mahok");
        strcpy(F->habilidades[0], "Pele de Pedra");
        break;
    case 13:
        F->forca = 2; F->agilidade = 4; F->inteligencia = 3; F->vontade = 3;
        strcpy(F->raca, "Metadilio");
        strcpy(F->habilidades[0], "Tamanho Pequeno");
        break;
    case 14:
        F->forca = 2; F->agilidade = 4; F->inteligencia = 3; F->vontade = 3;
        strcpy(F->raca, "Tailox");
        strcpy(F->habilidades[0], "Pernas Vulpinas");
        break;
    default:
        system("exit");
    }
}

void escolherClasse(Ficha *F)
{
    ///são 11 classes, todas do guia basico.
    int opcao;

    printf("Digite o numero e pressione Enter: \n\n"
           "[1] Bardo\n\n"
           "[2] Druida\n\n"
           "[3] Espadachim\n\n"
           "[4] Feiticeiro\n\n"
           "[5] Guerreiro\n\n"
           "[6] Ladino\n\n"
           "[7] Paladino\n\n"
           "[8] Patrulheiro\n\n"
           "[9] Runico\n\n"
           "[10] Sacerdote\n\n"
           "[11] Xama\n\n"
           "[12] VOLTAR\n\n");
    scanf("%i", &opcao);
    fflush(stdin);
    puts("");
    while((opcao < 1) || (opcao > 12)){
            printf("Codigo Invalido, escolha um numero de 1 a 12: ");
            scanf("%i", &opcao);
            fflush(stdin);
          }

    switch(opcao){
    case 1:
        F->agilidade += 1; F->vontade += 1;
        strcpy(F->classe, "Bardo");
        strcpy(F->habilidades[1], "Poesia dos Bardos");
        break;
    case 2:
        F->inteligencia += 1; F->vontade += 1;
        strcpy(F->classe, "Druida");
        strcpy(F->habilidades[1], "Conhecimento Mistico");
        break;
    case 3:
        F->forca += 1; F->agilidade += 1;
        strcpy(F->classe, "Espadachim");
        strcpy(F->habilidades[1], "Mestre de Armas 1");
        break;
    case 4:
        F->inteligencia += 1; F->vontade += 1;
        strcpy(F->classe, "Feiticeiro");
        strcpy(F->habilidades[1], "Conhecimento Arcano");
        break;
    case 5:
        F->forca += 1; F->agilidade += 1;
        strcpy(F->classe, "Guerreiro");
        strcpy(F->habilidades[1], "Mestre de Armas 1");
        break;
    case 6:
        F->agilidade += 1; F->inteligencia += 1;
        strcpy(F->classe, "Ladino");
        strcpy(F->habilidades[1], "Gatuno");
        break;
    case 7:
        F->forca += 1; F->vontade += 1;
        strcpy(F->classe, "Paladino");
        strcpy(F->habilidades[1], "Mestre de Armas 1");
        break;
    case 8:
        F->agilidade += 1; F->inteligencia += 1;
        strcpy(F->classe, "Patrulheiro");
        strcpy(F->habilidades[1], "Arqueria");
        break;
    case 9:
        F->forca += 1; F->inteligencia += 1;
        strcpy(F->classe, "Runico");
        strcpy(F->habilidades[1], "Conhecimento Arcano");
        break;
    case 10:
        F->inteligencia += 1; F->vontade += 1;
        strcpy(F->classe, "Sacerdote");
        strcpy(F->habilidades[1], "Conhecimento Mistico");
        break;
    case 11:
        F->forca += 1; F->vontade += 1;
        strcpy(F->classe, "Xama");
        strcpy(F->habilidades[1], "Guia Espiritual");
        break;
    default:
        system("exit");
    }
}

void comprarArmaCorporal(Ficha *F)
{
    int opcao;

    printf("Qual arma voce quer comprar?\n(Voce ainda tem %i de Gold)\n\n"
           "[1] Adaga\n[2] Alabarda\n"
           "[3] Azagaia\n[4] Bico-de-Corvo\n"
           "[5] Bordao\n[6] Cimitarra\n"
           "[7] Clava\n[8] Claymore\n"
           "[9] Espada Curta\n[10] Espada Longa\n"
           "[11] Glaive\n[12] Lanca\n"
           "[13] Maca Leve\n[14] Maca Pesada\n"
           "[15] Maca Estrela\n[16] Machadinha\n"
           "[17] Machado de Batalha\n[18] Machado Pesado\n"
           "[19] Mangual\n[20] Marreta\n"
           "[21] Martelo Lucerno\n[22] Martelo de Guerra\n"
           "[23] Rapieira\n[24] Sabre\n"
           "[25] Soqueira/Manopla\n[26] Tridente\n\n"
           "[27] VOLTAR\n\n", F->dinheiro);
    scanf("%i", &opcao);
    fflush(stdin);
    puts("");
    while((opcao < 1) || (opcao > 27)){
        printf("Codigo Invalido, escolha um numero de 1 a 27: ");
        scanf("%i", &opcao);
        fflush(stdin);
    }
    system("cls");

    switch(opcao){
    case 1:
        if((F->dinheiro - 50) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 50;
            strcpy(F->equipamentos[F->indice_equip], "Adaga");
            (F->indice_equip)++;
        }
        break;
    case 2:
        if((F->dinheiro - 250) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 250;
            strcpy(F->equipamentos[F->indice_equip], "Alabarda");
            (F->indice_equip)++;
        }
        break;
    case 3:
        if((F->dinheiro - 50) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 50;
            strcpy(F->equipamentos[F->indice_equip], "Azagaia");
            (F->indice_equip)++;
        }
        break;
    case 4:
        if((F->dinheiro - 125) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 125;
            strcpy(F->equipamentos[F->indice_equip], "Bico-de-Corvo");
            (F->indice_equip)++;
        }
        break;
    case 5:
        if((F->dinheiro - 50) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 50;
            strcpy(F->equipamentos[F->indice_equip], "Bordao");
            (F->indice_equip)++;
        }
        break;
    case 6:
        if((F->dinheiro - 225) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 225;
            strcpy(F->equipamentos[F->indice_equip], "Cimitarra");
            (F->indice_equip)++;
        }
        break;
    case 7:
        if((F->dinheiro - 75) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n", F->dinheiro);
        }else{
            F->dinheiro -= 75;
            strcpy(F->equipamentos[F->indice_equip], "Clava");
            (F->indice_equip)++;
        }
        break;
    case 8:
        if((F->dinheiro - 250) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 250;
            strcpy(F->equipamentos[F->indice_equip], "Claymore");
            (F->indice_equip)++;
        }
        break;
    case 9:
        if((F->dinheiro - 100) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 100;
            strcpy(F->equipamentos[F->indice_equip], "Espada Curta");
            (F->indice_equip)++;
        }
        break;
    case 10:
        if((F->dinheiro - 175) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 175;
            strcpy(F->equipamentos[F->indice_equip], "Espada Longa");
            (F->indice_equip)++;
        }
        break;
    case 11:
        if((F->dinheiro - 225) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 225;
            strcpy(F->equipamentos[F->indice_equip], "Glaive");
            (F->indice_equip)++;
        }
        break;
    case 12:
        if((F->dinheiro - 100) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 100;
            strcpy(F->equipamentos[F->indice_equip], "Lanca");
            (F->indice_equip)++;
        }
        break;
    case 13:
        if((F->dinheiro - 25) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 25;
            strcpy(F->equipamentos[F->indice_equip], "Maca Leve");
            (F->indice_equip)++;
        }
        break;
    case 14:
        if((F->dinheiro - 150) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 150;
            strcpy(F->equipamentos[F->indice_equip], "Maca Pesada");
            (F->indice_equip)++;
        }
        break;
    case 15:
        if((F->dinheiro - 100) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 100;
            strcpy(F->equipamentos[F->indice_equip], "Maca Estrela");
            (F->indice_equip)++;
        }
        break;
    case 16:
        if((F->dinheiro - 100) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 100;
            strcpy(F->equipamentos[F->indice_equip], "Machadinha");
            (F->indice_equip)++;
        }
        break;
    case 17:
        if((F->dinheiro - 150) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 150;
            strcpy(F->equipamentos[F->indice_equip], "Machado de Batalha");
            (F->indice_equip)++;
        }
        break;
    case 18:
        if((F->dinheiro - 175) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 175;
            strcpy(F->equipamentos[F->indice_equip], "Machado Pesado");
            (F->indice_equip)++;
        }
        break;
    case 19:
        if((F->dinheiro - 200) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 200;
            strcpy(F->equipamentos[F->indice_equip], "Mangual");
            (F->indice_equip)++;
        }
        break;
    case 20:
        if((F->dinheiro - 175) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 175;
            strcpy(F->equipamentos[F->indice_equip], "Marreta");
            (F->indice_equip)++;
        }
        break;
    case 21:
        if((F->dinheiro - 275) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 275;
            strcpy(F->equipamentos[F->indice_equip], "Martelo Lucerno");
            (F->indice_equip)++;
        }
        break;
    case 22:
        if((F->dinheiro - 175) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 175;
            strcpy(F->equipamentos[F->indice_equip], "Martelo de Guerra");
            (F->indice_equip)++;
        }
        break;
    case 23:
        if((F->dinheiro - 125) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 125;
            strcpy(F->equipamentos[F->indice_equip], "Rapieira");
            (F->indice_equip)++;
        }
        break;
    case 24:
        if((F->dinheiro - 100) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 100;
            strcpy(F->equipamentos[F->indice_equip], "Sabre");
            (F->indice_equip)++;
        }
        break;
    case 25:
        if((F->dinheiro - 25) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 25;
            strcpy(F->equipamentos[F->indice_equip], "Soqueira/Manopla");
            (F->indice_equip)++;
        }
        break;
    case 26:
        if((F->dinheiro - 175) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 175;
            strcpy(F->equipamentos[F->indice_equip], "Tridente");
            (F->indice_equip)++;
        }
        break;
    default:
        system("exit");
    }
}

void comprarArmaDistancia(Ficha *F)
{
    int opcao;

    printf("Qual arma voce quer comprar?\n(Voce ainda tem %i de Gold)\n\n"
           "[1] Arco Simples\n\n"
           "[2] Arco Composto\n\n"
           "[3] Arco de Guerra\n\n"
           "[4] Arco Recurvo\n\n"
           "[5] Besta Leve\n\n"
           "[6] Besta Pesada\n\n"
           "[7] Funda/Estilingue\n\n"
           "[8] Fustibalo\n\n"
           "[9] Plumbata\n\n"
           "[10] Prodd\n\n"
           "[11] Zarabatana\n\n"
           "[12] VOLTAR\n\n", F->dinheiro);
    scanf("%i", &opcao);
    fflush(stdin);
    puts("");
    while((opcao < 1) || (opcao > 12)){
        printf("Codigo Invalido, escolha um numero de 1 a 12: ");
        scanf("%i", &opcao);
        fflush(stdin);
    }
    system("cls");

    switch(opcao){
    case 1:
        if((F->dinheiro - 75) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 75;
            strcpy(F->equipamentos[F->indice_equip], "Arco Simples");
            (F->indice_equip)++;
        }
        break;
    case 2:
        if((F->dinheiro - 175) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 175;
            strcpy(F->equipamentos[F->indice_equip], "Arco Composto");
            (F->indice_equip)++;
        }
        break;
    case 3:
        if((F->dinheiro - 250) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 250;
            strcpy(F->equipamentos[F->indice_equip], "Arco de Guerra");
            (F->indice_equip)++;
        }
        break;
    case 4:
        if((F->dinheiro - 250) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 250;
            strcpy(F->equipamentos[F->indice_equip], "Arco Recurvo");
            (F->indice_equip)++;
        }
        break;
    case 5:
        if((F->dinheiro - 175) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 175;
            strcpy(F->equipamentos[F->indice_equip], "Besta Leve");
            (F->indice_equip)++;
        }
        break;
    case 6:
        if((F->dinheiro - 225) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 225;
            strcpy(F->equipamentos[F->indice_equip], "Besta Pesada");
            (F->indice_equip)++;
        }
        break;
    case 7:
        if((F->dinheiro - 50) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n", F->dinheiro);
        }else{
            F->dinheiro -= 50;
            strcpy(F->equipamentos[F->indice_equip], "Funda/Estilingue");
            (F->indice_equip)++;
        }
        break;
    case 8:
        if((F->dinheiro - 200) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 200;
            strcpy(F->equipamentos[F->indice_equip], "Fustibalo");
            (F->indice_equip)++;
        }
        break;
    case 9:
        if((F->dinheiro - 100) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 100;
            strcpy(F->equipamentos[F->indice_equip], "Plumbata");
            (F->indice_equip)++;
        }
        break;
    case 10:
        if((F->dinheiro - 175) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 175;
            strcpy(F->equipamentos[F->indice_equip], "Prodd");
            (F->indice_equip)++;
        }
        break;
    case 11:
        if((F->dinheiro - 25) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 25;
            strcpy(F->equipamentos[F->indice_equip], "Zarabatana");
            (F->indice_equip)++;
        }
        break;
    default:
        system("exit");
    }
}

void comprarArmadura(Ficha *F, int *comprou_armadura, int *armadura_observacao)
{
    int opcao;

    printf("Qual armadura voce quer comprar? (Voce ainda tem %i de Gold)\n"
           "WARNING: So eh possivel comprar uma armadura!\n\n"
           "[1] Tunica Pesada\n\n"
           "[2] Armadura de Couro\n\n"
           "[3] Armadura Simples\n\n"
           "[4] Armadura de Batalha\n\n"
           "[5] Armadura Completa\n\n"
           "[6] VOLTAR\n\n", F->dinheiro);
    scanf("%i", &opcao);
    fflush(stdin);
    puts("");
    while((opcao < 1) || (opcao > 6)){
        printf("Codigo Invalido, escolha um numero de 1 a 6: ");
        scanf("%i", &opcao);
        fflush(stdin);
    }
    system("cls");

    switch(opcao){
    case 1:
        if (*comprou_armadura == 1){
            printf("Voce ja comprou armadura!\n\n");
            system("pause");
            break;
        }
        if((F->dinheiro - 50) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 50;
            strcpy(F->equipamentos[F->indice_equip], "Tunica Pesada");
            F->bloqueio += 1;
            F->esquiva += 1;
            (F->indice_equip)++;
            *comprou_armadura = 1;
        }
        break;
    case 2:
        if (*comprou_armadura == 1){
            printf("Voce ja comprou armadura!\n\n");
            system("pause");
            break;
        }
        if((F->dinheiro - 100) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 100;
            strcpy(F->equipamentos[F->indice_equip], "Armadura de Couro");
            F->bloqueio += 2;
            F->esquiva += 1;
            (F->indice_equip)++;
            *comprou_armadura = 1;
        }
        break;
    case 3:
        if (*comprou_armadura == 1){
            printf("Voce ja comprou armadura!\n\n");
            system("pause");
            break;
        }
        if((F->dinheiro - 200) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 200;
            strcpy(F->equipamentos[F->indice_equip], "Armadura Simples");
            F->bloqueio += 3;
            F->esquiva += 1;
            (F->indice_equip)++;
            *comprou_armadura = 1;
            *armadura_observacao = 1;
        }
        break;
    case 4:
        if (*comprou_armadura == 1){
            printf("Voce ja comprou armadura!\n\n");
            system("pause");
            break;
        }
        if((F->dinheiro - 600) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 600;
            strcpy(F->equipamentos[F->indice_equip], "Armadura de Batalha");
            F->bloqueio += 4;
            F->esquiva += 1;
            (F->indice_equip)++;
            *comprou_armadura = 1;
            *armadura_observacao = 1;
        }
        break;
    case 5:
        if (*comprou_armadura == 1){
            printf("Voce ja comprou armadura!\n\n");
            system("pause");
            break;
        }
        if((F->dinheiro - 2000) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 2000;
            strcpy(F->equipamentos[F->indice_equip], "Armadura Completa");
            F->bloqueio += 5;
            F->esquiva += 1;
            (F->indice_equip)++;
            *comprou_armadura = 1;
            *armadura_observacao = 2;
        }
        break;
    default:
        system("exit");
    }
}

void comprarEscudo(Ficha *F, int *comprou_escudo)
{
    int opcao;

    printf("Qual escudo voce quer comprar? (Voce ainda tem %i de Gold)\n"
           "WARNING: So eh possivel comprar um escudo!\n\n"
           "[1] Escudo Pequeno\n\n"
           "[2] Escudo Medio\n\n"
           "[3] Escudo de Corpo\n\n"
           "[4] VOLTAR\n\n", F->dinheiro);
    scanf("%i", &opcao);
    fflush(stdin);
    puts("");
    while((opcao < 1) || (opcao > 4)){
        printf("Codigo Invalido, escolha um numero de 1 a 4: ");
        scanf("%i", &opcao);
        fflush(stdin);
    }
    system("cls");
    switch(opcao){
    case 1:
        if (*comprou_escudo == 1){
            printf("Voce ja comprou escudo!\n\n");
            system("pause");
            break;
        }
        if((F->dinheiro - 50) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 50;
            strcpy(F->equipamentos[F->indice_equip], "Escudo Pequeno");
            F->bloqueio += 1;
            F->esquiva += 1;
            (F->indice_equip)++;
            *comprou_escudo = 1;
        }
        break;
    case 2:
        if (*comprou_escudo == 1){
            printf("Voce ja comprou escudo!\n\n");
            system("pause");
            break;
        }
        if((F->dinheiro - 100) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n", F->dinheiro);
        }else{
            F->dinheiro -= 100;
            strcpy(F->equipamentos[F->indice_equip], "Escudo Medio");
            F->bloqueio += 2;
            F->esquiva += 1;
            (F->indice_equip)++;
            *comprou_escudo = 1;
        }
        break;
    case 3:
        if (*comprou_escudo == 1){
            printf("Voce ja comprou escudo!\n\n");
            system("pause");
            break;
        }
        if((F->dinheiro - 200) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 200;
            strcpy(F->equipamentos[F->indice_equip], "Escudo de Corpo");
            F->bloqueio += 3;
            F->esquiva += 1;
            (F->indice_equip)++;
            *comprou_escudo = 1;
        }
        break;
    default:
        system("exit");
    }
}

void comprarItemConjuracao(Ficha *F)
{
    int opcao;

    printf("Qual item voce quer comprar?\n(Voce ainda tem %i de Gold)\n\n"
           "[1] Cajado\n\n"
           "[2] Cetro\n\n"
           "[3] Grimorio\n\n"
           "[4] Missal\n\n"
           "[5] Orbe de Cristal\n\n"
           "[6] Punhal\n\n"
           "[7] Simbolo Sagrado\n\n"
           "[8] Varinha\n\n"
           "[9] VOLTAR\n\n", F->dinheiro);
    scanf("%i", &opcao);
    fflush(stdin);
    puts("");
    while((opcao < 1) || (opcao > 9)){
        printf("Codigo Invalido, escolha um numero de 1 a 9: ");
        scanf("%i", &opcao);
        fflush(stdin);
    }
    system("cls");

    switch(opcao){
    case 1:
        if((F->dinheiro - 50) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 50;
            strcpy(F->equipamentos[F->indice_equip], "Cajado");
            (F->indice_equip)++;
        }
        break;
    case 2:
        if((F->dinheiro - 75) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 75;
            strcpy(F->equipamentos[F->indice_equip], "Cetro");
            (F->indice_equip)++;
        }
        break;
    case 3:
        if((F->dinheiro - 50) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 50;
            strcpy(F->equipamentos[F->indice_equip], "Grimorio");
            (F->indice_equip)++;
        }
        break;
    case 4:
        if((F->dinheiro - 50) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 50;
            strcpy(F->equipamentos[F->indice_equip], "Missal");
            (F->indice_equip)++;
        }
        break;
    case 5:
        if((F->dinheiro - 25) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 25;
            strcpy(F->equipamentos[F->indice_equip], "Orbe de Cristal");
            (F->indice_equip)++;
        }
        break;
    case 6:
        if((F->dinheiro - 50) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 50;
            strcpy(F->equipamentos[F->indice_equip], "Punhal");
            (F->indice_equip)++;
        }
        break;
    case 7:
        if((F->dinheiro - 25) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n", F->dinheiro);
        }else{
            F->dinheiro -= 25;
            strcpy(F->equipamentos[F->indice_equip], "Simbolo Sagrado");
            (F->indice_equip)++;
        }
        break;
    case 8:
        if((F->dinheiro - 25) <= 0){
            printf("Dinheiro Insuficiente, voce tem %i de Gold.\n\n", F->dinheiro);
            system("pause");
        }else{
            F->dinheiro -= 25;
            strcpy(F->equipamentos[F->indice_equip], "Varinha");
            (F->indice_equip)++;
        }
        break;
    default:
        system("exit");
    }
}

void atribuicoesFinais(Ficha *F, int armadura_observacao)
{
    F->bloqueio += F->forca;
    F->esquiva += F->agilidade;
    if(F->inteligencia > F->vontade) F->determinacao += F->inteligencia;
    else F->determinacao += F->vontade;

    F->deslocamento = (F->agilidade/2) + 5;
    if(armadura_observacao == 1) F->corrida = F->deslocamento*3;
    else if(armadura_observacao == 2) F->corrida = F->deslocamento*2;
    else F->corrida = F->deslocamento*4;

    F->carga_basica = F->forca*7;
    F->carga_pesada = F->carga_basica*5;
    F->carga_maxima = F->carga_basica*10;
}

void escreverTxt(Ficha F, int indice_hab)
{
    FILE *arquivo;
    int i;

    arquivo = fopen("Ficha.txt", "w");
        fprintf(arquivo, "Jogador: ");
        fprintf(arquivo, F.nome_jogador);
        fprintf(arquivo, "\nPersonagem: ");
        fprintf(arquivo, F.nome_personagem);
        fprintf(arquivo, "\nRaça: ");
        fprintf(arquivo, F.raca);
        fprintf(arquivo, "\nClasse: ");
        fprintf(arquivo, F.classe);
        fprintf(arquivo, "\nNível: ");
        fprintf(arquivo, "%i\n\n", F.nivel);

        fprintf(arquivo, "Vida Maxima: ");
        fprintf(arquivo, "%i\n", F.vida_maxima);
        fprintf(arquivo, "Mana Maxima: ");
        fprintf(arquivo, "%i\n", F.mana_maxima);

        fprintf(arquivo, "\nForça: ");
        fprintf(arquivo, "%i\n", F.forca);
        fprintf(arquivo, "Agilidade: ");
        fprintf(arquivo, "%i\n", F.agilidade);
        fprintf(arquivo, "Inteligência: ");
        fprintf(arquivo, "%i\n", F.inteligencia);
        fprintf(arquivo, "Vontade: ");
        fprintf(arquivo, "%i\n\n", F.vontade);

        fprintf(arquivo, "Bloqueio: ");
        fprintf(arquivo, "%i\n", F.bloqueio);
        fprintf(arquivo, "Esquiva: ");
        fprintf(arquivo, "%i\n", F.esquiva);
        fprintf(arquivo, "Determinação: ");
        fprintf(arquivo, "%i\n\n", F.determinacao);

        fprintf(arquivo, "Deslocamento: ");
        fprintf(arquivo, "%i\n", F.deslocamento);
        fprintf(arquivo, "Corrida: ");
        fprintf(arquivo, "%i\n\n", F.corrida);

        fprintf(arquivo, "Carga Básica: ");
        fprintf(arquivo, "%i\n", F.carga_basica);
        fprintf(arquivo, "Carga Pesada: ");
        fprintf(arquivo, "%i\n", F.carga_pesada);
        fprintf(arquivo, "Carga Maxima: ");
        fprintf(arquivo, "%i\n\n", F.carga_maxima);

        fprintf(arquivo, "Equipamentos: \n");
        fprintf(arquivo, "Gold: %i\n", F.dinheiro);
        for(i=0; i<F.indice_equip; i++) fprintf(arquivo, "%s\n", F.equipamentos[i]);

        fprintf(arquivo, "\nHabilidades: \n");
        for(i=0; i<indice_hab; i++) fprintf(arquivo, "%s\n", F.habilidades[i]);

    fclose(arquivo);
}



