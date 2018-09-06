typedef struct { //Ficha;
    char nome_jogador[31];
    char nome_personagem[31];
    char raca[31];
    char classe[31];
    char habilidades[20][30]; ///no max 20 habilidades, com 30 caracteres para cada
    char equipamentos[30][30]; ///no max 30 equips, com 30 caracteres para cada
    int nivel;
    int forca, agilidade, inteligencia, vontade;
    int vida_maxima, mana_maxima;
    int bloqueio, esquiva, determinacao;
    int carga_basica, carga_pesada, carga_maxima;
    int deslocamento, corrida;
    int dinheiro;
    int lvl_points; ///Pontos de Evolução, para gastar em vida, mana ou aprendiz de classe.
    int nmr_habs; ///Pra controlar quantas habilidades o pj pode ter de acordo com o nivel dele.
    int indice_equip; ///Variavel pra controlar os equipamentos e nao deixar serem sobrescritos.
                          ///Assim que gastar um indice, a variavel é incrementada.
} Ficha;

void atribuicoesIniciais(Ficha *F);

void detalhesPJ(Ficha *F, int *indice_hab);

void escolherRaca(Ficha *F);

void escolherClasse(Ficha *F);

void comprarArmaCorporal(Ficha *F);

void comprarArmaDistancia(Ficha *F);

void comprarArmadura(Ficha *F, int *comprou_armadura, int *armadura_observacao);

void comprarEscudo(Ficha *F, int *comprou_escudo);

void comprarItemConjuracao(Ficha *F);

void atribuicoesFinais(Ficha *F, int armadura_observacao);

void escreverTxt(Ficha F, int indice_hab);
