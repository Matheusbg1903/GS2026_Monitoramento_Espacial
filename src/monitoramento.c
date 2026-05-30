/*
 * ================================================================
 *
 *  MODULOS MONITORADOS:
 *    - Paineis solares (geracao de energia renovavel)
 *    - Baterias        (armazenamento energetico)
 *    - Turbinas        (geracao auxiliar)
 *    - Consumo         (demanda dos modulos da nave)
 *    - Temperatura     (estabilidade termica)
 *    - Comunicacao     (status do link com a Terra)
 *
 * ================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define RESET    "\033[0m"
#define VERM     "\033[1;31m"
#define VERDE    "\033[1;32m"
#define AMAR     "\033[1;33m"
#define CIANO    "\033[1;36m"
#define BRANCO   "\033[1;37m"
#define AZUL     "\033[1;34m"
#define MAGENTA  "\033[1;35m"

#define TEMP_MAX          85.0   
#define TEMP_ALERTA       70.0   
#define BATERIA_MIN       15.0   
#define BATERIA_ALERTA    30.0   
#define PAINEL_MIN        20.0   
#define TURBINA_MIN       10.0   
#define CONSUMO_MAX       90.0   
#define MAX_HISTORICO     10     

typedef struct {
    float temperatura;      
    float bateria;          
    float painel_solar;     
    float turbina;          
    float consumo;          
    int   comunicacao;      
    int   valida;           
} Leitura;

Leitura leituraAtual;
Leitura historico[MAX_HISTORICO];
int totalLeituras = 0;


void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void imprimirCabecalho() {
    printf("\n");
    printf(CIANO "  ================================================\n" RESET);
    printf(CIANO "   " BRANCO "SERS - SISTEMA DE MONITORAMENTO ENERGETICO" CIANO "\n" RESET);
    printf(CIANO "   " AZUL "Missao Espacial Experimental 2026.1" CIANO "\n" RESET);
    printf(CIANO "  ================================================\n\n" RESET);
}

void barraProgresso(float valor, float limite_alerta, float limite_critico, int invertido) {
    int total = 20;
    int preenchido = (int)(valor / 100.0 * total);
    const char *cor;

    if (invertido) {
        
        if (valor >= limite_critico)      cor = VERM;
        else if (valor >= limite_alerta)  cor = AMAR;
        else                              cor = VERDE;
    } else {
        
        if (valor <= limite_critico)      cor = VERM;
        else if (valor <= limite_alerta)  cor = AMAR;
        else                              cor = VERDE;
    }

    printf("%s[", cor);
    for (int i = 0; i < total; i++) {
        printf(i < preenchido ? "#" : "-");
    }
    printf("] %.1f%%" RESET, valor);
}

void inserirDados() {
    limparTela();
    imprimirCabecalho();
    printf(BRANCO "  [ INSERCAO DE DADOS DA MISSAO ]\n\n" RESET);

    printf("  Temperatura da nave (oC)          : ");
    scanf("%f", &leituraAtual.temperatura);

    printf("  Nivel da bateria (0-100%%)         : ");
    scanf("%f", &leituraAtual.bateria);
    if (leituraAtual.bateria < 0)   leituraAtual.bateria = 0;
    if (leituraAtual.bateria > 100) leituraAtual.bateria = 100;

    printf("  Eficiencia dos paineis solares (%%) : ");
    scanf("%f", &leituraAtual.painel_solar);
    if (leituraAtual.painel_solar < 0)   leituraAtual.painel_solar = 0;
    if (leituraAtual.painel_solar > 100) leituraAtual.painel_solar = 100;

    printf("  Potencia das turbinas (%%)          : ");
    scanf("%f", &leituraAtual.turbina);
    if (leituraAtual.turbina < 0)   leituraAtual.turbina = 0;
    if (leituraAtual.turbina > 100) leituraAtual.turbina = 100;

    printf("  Consumo energetico dos modulos (%%) : ");
    scanf("%f", &leituraAtual.consumo);
    if (leituraAtual.consumo < 0)   leituraAtual.consumo = 0;
    if (leituraAtual.consumo > 100) leituraAtual.consumo = 100;

    printf("  Comunicacao com a Terra (1=Ativa / 0=Falha): ");
    scanf("%d", &leituraAtual.comunicacao);

    leituraAtual.valida = 1;

    int pos = totalLeituras % MAX_HISTORICO;
    historico[pos] = leituraAtual;
    totalLeituras++;

    printf(VERDE "\n  Dados inseridos com sucesso! Leitura #%d registrada.\n" RESET, totalLeituras);
}

void simularDados() {
    limparTela();
    imprimirCabecalho();
    printf(BRANCO "  [ SIMULACAO AUTOMATICA DE SENSORES ]\n\n" RESET);
    printf(AZUL "  Gerando dados simulados da missao...\n\n" RESET);

    srand((unsigned int)time(NULL) + totalLeituras);

    leituraAtual.temperatura  = 40.0 + (rand() % 600) / 10.0;  /* 40 a 100oC  */
    leituraAtual.bateria      = 10.0 + (rand() % 900) / 10.0;  /* 10 a 100%   */
    leituraAtual.painel_solar = 15.0 + (rand() % 860) / 10.0;  /* 15 a 100%   */
    leituraAtual.turbina      = 5.0  + (rand() % 960) / 10.0;  /* 5  a 100%   */
    leituraAtual.consumo      = 20.0 + (rand() % 800) / 10.0;  /* 20 a 100%   */
    leituraAtual.comunicacao  = (rand() % 10) > 1 ? 1 : 0;     /* 80% ativa   */
    leituraAtual.valida       = 1;

    printf("  Temperatura   : %.1foC\n", leituraAtual.temperatura);
    printf("  Bateria       : %.1f%%\n",  leituraAtual.bateria);
    printf("  Painel Solar  : %.1f%%\n",  leituraAtual.painel_solar);
    printf("  Turbinas      : %.1f%%\n",  leituraAtual.turbina);
    printf("  Consumo       : %.1f%%\n",  leituraAtual.consumo);
    printf("  Comunicacao   : %s\n",      leituraAtual.comunicacao ? "ATIVA" : "FALHA");

    int pos = totalLeituras % MAX_HISTORICO;
    historico[pos] = leituraAtual;
    totalLeituras++;

    printf(VERDE "\n  Simulacao concluida! Leitura #%d registrada.\n" RESET, totalLeituras);
}

void visualizarStatus() {
    limparTela();
    imprimirCabecalho();
    printf(BRANCO "  [ STATUS ATUAL DA MISSAO ]\n\n" RESET);

    if (!leituraAtual.valida) {
        printf(AMAR "  Nenhum dado disponivel.\n"
                    "  Use a opcao 1 (inserir) ou 2 (simular) primeiro.\n" RESET);
        return;
    }

    printf("  -------------------------------------------------\n");
    printf("  |  MODULO              VALOR        STATUS         |\n");
    printf("  |-------------------------------------------------|\n");

    printf("  |  Temperatura         ");
    barraProgresso(leituraAtual.temperatura, TEMP_ALERTA, TEMP_MAX, 1);
    printf("\n");

    printf("  |  Bateria             ");
    barraProgresso(leituraAtual.bateria, BATERIA_ALERTA, BATERIA_MIN, 0);
    printf("\n");

    printf("  |  Painel Solar        ");
    barraProgresso(leituraAtual.painel_solar, 40.0, PAINEL_MIN, 0);
    printf("\n");

    printf("  |  Turbinas            ");
    barraProgresso(leituraAtual.turbina, 30.0, TURBINA_MIN, 0);
    printf("\n");

    printf("  |  Consumo             ");
    barraProgresso(leituraAtual.consumo, 70.0, CONSUMO_MAX, 1);
    printf("\n");

    printf("  |  Comunicacao         ");
    if (leituraAtual.comunicacao)
        printf(VERDE "LINK ESTABELECIDO" RESET);
    else
        printf(VERM "FALHA NO LINK" RESET);
    printf("\n");

    printf("  -------------------------------------------------\n");

    float geracao = (leituraAtual.painel_solar + leituraAtual.turbina) / 2.0;
    float balanco = geracao - leituraAtual.consumo;
    printf("\n  Geracao media (paineis + turbinas): %.1f%%\n", geracao);
    if (balanco >= 0)
        printf(VERDE "  Balanco energetico: +%.1f%% (superavit)\n" RESET, balanco);
    else
        printf(VERM "  Balanco energetico: %.1f%% (deficit)\n" RESET, balanco);
}


void executarAnalise() {
    limparTela();
    imprimirCabecalho();
    printf(BRANCO "  [ ANALISE COMPLETA DO SISTEMA ]\n\n" RESET);

    if (!leituraAtual.valida) {
        printf(AMAR "  Nenhum dado disponivel para analise.\n" RESET);
        return;
    }

    int alertas   = 0;
    int criticos  = 0;

    if (leituraAtual.temperatura >= TEMP_MAX) {
        printf(VERM "  [CRITICO] SUPERAQUECIMENTO DETECTADO!\n"
                    "            Temp: %.1foC (limite: %.1foC)\n"
                    "            > Ativar sistema de resfriamento imediatamente.\n\n" RESET,
               leituraAtual.temperatura, TEMP_MAX);
        criticos++;
    } else if (leituraAtual.temperatura >= TEMP_ALERTA) {
        printf(AMAR "  [ALERTA]  Temperatura elevada: %.1foC\n"
                    "            > Monitorar e reduzir carga termica.\n\n" RESET,
               leituraAtual.temperatura);
        alertas++;
    } else {
        printf(VERDE "  [OK]      Temperatura normal: %.1foC\n\n" RESET,
               leituraAtual.temperatura);
    }

    if (leituraAtual.bateria <= BATERIA_MIN) {
        printf(VERM "  [CRITICO] BATERIA EM NIVEL CRITICO!\n"
                    "            Carga: %.1f%% (minimo: %.1f%%)\n"
                    "            > Ativar modo de emergencia energetica.\n\n" RESET,
               leituraAtual.bateria, BATERIA_MIN);
        criticos++;
    } else if (leituraAtual.bateria <= BATERIA_ALERTA) {
        printf(AMAR "  [ALERTA]  Bateria baixa: %.1f%%\n"
                    "            > Reduzir consumo e aumentar geracao.\n\n" RESET,
               leituraAtual.bateria);
        alertas++;
    } else {
        printf(VERDE "  [OK]      Bateria: %.1f%%\n\n" RESET, leituraAtual.bateria);
    }

    if (leituraAtual.painel_solar <= PAINEL_MIN) {
        printf(VERM "  [CRITICO] PAINEIS SOLARES COM FALHA!\n"
                    "            Eficiencia: %.1f%% (minimo: %.1f%%)\n"
                    "            > Verificar orientacao e limpeza dos paineis.\n\n" RESET,
               leituraAtual.painel_solar, PAINEL_MIN);
        criticos++;
    } else if (leituraAtual.painel_solar <= 40.0) {
        printf(AMAR "  [ALERTA]  Paineis com eficiencia reduzida: %.1f%%\n"
                    "            > Ajustar angulo de captacao solar.\n\n" RESET,
               leituraAtual.painel_solar);
        alertas++;
    } else {
        printf(VERDE "  [OK]      Paineis solares: %.1f%%\n\n" RESET,
               leituraAtual.painel_solar);
    }

    if (leituraAtual.turbina <= TURBINA_MIN) {
        printf(VERM "  [CRITICO] TURBINAS COM FALHA OPERACIONAL!\n"
                    "            Potencia: %.1f%% (minimo: %.1f%%)\n"
                    "            > Verificar sistema de turbinas auxiliares.\n\n" RESET,
               leituraAtual.turbina, TURBINA_MIN);
        criticos++;
    } else if (leituraAtual.turbina <= 30.0) {
        printf(AMAR "  [ALERTA]  Turbinas com baixa potencia: %.1f%%\n"
                    "            > Verificar integridade das pas.\n\n" RESET,
               leituraAtual.turbina);
        alertas++;
    } else {
        printf(VERDE "  [OK]      Turbinas: %.1f%%\n\n" RESET, leituraAtual.turbina);
    }

    /* -- Consumo -- */
    if (leituraAtual.consumo >= CONSUMO_MAX) {
        printf(VERM "  [CRITICO] CONSUMO EXCESSIVO DOS MODULOS!\n"
                    "            Consumo: %.1f%% (maximo: %.1f%%)\n"
                    "            > Desligar modulos nao essenciais.\n\n" RESET,
               leituraAtual.consumo, CONSUMO_MAX);
        criticos++;
    } else if (leituraAtual.consumo >= 70.0) {
        printf(AMAR "  [ALERTA]  Consumo elevado: %.1f%%\n"
                    "            > Otimizar uso dos modulos.\n\n" RESET,
               leituraAtual.consumo);
        alertas++;
    } else {
        printf(VERDE "  [OK]      Consumo: %.1f%%\n\n" RESET, leituraAtual.consumo);
    }

    if (!leituraAtual.comunicacao) {
        printf(VERM "  [CRITICO] FALHA DE COMUNICACAO COM A TERRA!\n"
                    "            > Reiniciar modulo de comunicacao.\n"
                    "            > Verificar antenas e transmissores.\n\n" RESET);
        criticos++;
    } else {
        printf(VERDE "  [OK]      Comunicacao estabelecida.\n\n" RESET);
    }

    printf("  ==================================================\n");
    if (criticos == 0 && alertas == 0) {
        printf(VERDE "  MISSAO: OPERANDO NORMALMENTE\n"
                     "  Todos os sistemas dentro dos parametros.\n" RESET);
    } else if (criticos > 0) {
        printf(VERM "  MISSAO: SITUACAO CRITICA - %d CRITICO(S), %d ALERTA(S)\n"
                    "  Intervencao imediata necessaria!\n" RESET, criticos, alertas);
    } else {
        printf(AMAR "  MISSAO: ATENCAO - %d ALERTA(S) DETECTADO(S)\n"
                    "  Monitorar e tomar acoes preventivas.\n" RESET, alertas);
    }
    printf("  ==================================================\n");
}


void verHistorico() {
    limparTela();
    imprimirCabecalho();
    printf(BRANCO "  [ HISTORICO DE LEITURAS ]\n\n" RESET);

    if (totalLeituras == 0) {
        printf(AMAR "  Nenhuma leitura registrada ainda.\n" RESET);
        return;
    }

    int qtd = totalLeituras < MAX_HISTORICO ? totalLeituras : MAX_HISTORICO;

    printf("  %-5s %-8s %-8s %-8s %-8s %-8s %-6s\n",
           "Leit.", "TempoC", "Bater%", "Solar%", "Turb%", "Cons%", "Comun.");
    printf("  ----------------------------------------------------\n");

    for (int i = 0; i < qtd; i++) {
        int pos = totalLeituras <= MAX_HISTORICO ? i : (totalLeituras + i) % MAX_HISTORICO;
        Leitura l = historico[pos];
        int num   = totalLeituras > MAX_HISTORICO ? (totalLeituras - qtd + i + 1) : (i + 1);

        const char *cor_t = l.temperatura >= TEMP_MAX    ? VERM : (l.temperatura >= TEMP_ALERTA ? AMAR : VERDE);
        const char *cor_b = l.bateria     <= BATERIA_MIN ? VERM : (l.bateria <= BATERIA_ALERTA  ? AMAR : VERDE);
        const char *cor_p = l.painel_solar <= PAINEL_MIN ? VERM : VERDE;
        const char *cor_u = l.turbina      <= TURBINA_MIN ? VERM : VERDE;
        const char *cor_c = l.consumo      >= CONSUMO_MAX ? VERM : VERDE;
        const char *cor_k = l.comunicacao ? VERDE : VERM;

        printf("  %-5d %s%-7.1f%s %s%-7.1f%s %s%-7.1f%s %s%-7.1f%s %s%-7.1f%s %s%-6s%s\n",
               num,
               cor_t, l.temperatura,  RESET,
               cor_b, l.bateria,       RESET,
               cor_p, l.painel_solar,  RESET,
               cor_u, l.turbina,       RESET,
               cor_c, l.consumo,       RESET,
               cor_k, l.comunicacao ? "ATIVA" : "FALHA", RESET);
    }

    printf("\n  Total de leituras realizadas: %d\n", totalLeituras);
}


int main() {
    int opcao;

    leituraAtual.valida = 0;
    for (int i = 0; i < MAX_HISTORICO; i++)
        historico[i].valida = 0;

    do {
        limparTela();
        imprimirCabecalho();

        printf(BRANCO "  MENU PRINCIPAL\n\n" RESET);
        printf(CIANO  "  [1]" RESET " Inserir dados manualmente\n");
        printf(AZUL   "  [2]" RESET " Simular dados dos sensores\n");
        printf(CIANO  "  [3]" RESET " Visualizar status atual\n");
        printf(CIANO  "  [4]" RESET " Executar analise completa\n");
        printf(CIANO  "  [5]" RESET " Ver historico de leituras\n");
        printf(VERM   "  [6]" RESET " Encerrar sistema\n");
        printf("\n  Escolha uma opcao: ");

        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserirDados();    break;
            case 2: simularDados();    break;
            case 3: visualizarStatus(); break;
            case 4: executarAnalise(); break;
            case 5: verHistorico();    break;
            case 6:
                limparTela();
                imprimirCabecalho();
                printf(AMAR "  Sistema encerrado.\n"
                            "  Total de leituras realizadas: %d\n\n" RESET, totalLeituras);
                break;
            default:
                printf(VERM "\n  Opcao invalida. Tente novamente.\n" RESET);
        }

        if (opcao != 6) {
            printf("\n  Pressione ENTER para continuar...");
            getchar();
            getchar();
        }

    } while (opcao != 6);

    return 0;
}