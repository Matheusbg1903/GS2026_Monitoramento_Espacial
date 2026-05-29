# GS2026_Monitoramento_Espacial
Sistema de monitoramento energético para missão espacial experimental - Global Soluction 2026.1

# SERS - Sistema de Monitoramento Energético Espacial

Sistema desenvolvido em C para monitorar os módulos energéticos de uma missão espacial experimental, aplicando conceitos de energias renováveis e sustentabilidade.

Trabalho desenvolvido para o Global Solution 2026.1 - FIAP.

---

## Como rodar

1. Compile o código:
```
gcc src/monitoramento.c -o monitoramento
```

2. Execute:
```
./monitoramento
```
---

## O que o sistema faz

O programa monitora 6 módulos da nave: temperatura, bateria, painéis solares, turbinas, consumo energético e comunicação com a Terra.

Você pode inserir os dados manualmente ou deixar o sistema simular automaticamente. Com base nos valores, o sistema emite alertas automáticos e indica ações corretivas quando necessário.

---

## Menu

- **1** - Inserir dados manualmente
- **2** - Simular dados dos sensores automaticamente
- **3** - Ver status atual com barras de progresso
- **4** - Executar análise completa com alertas
- **5** - Ver histórico das últimas 10 leituras
- **6** - Encerrar

---

## Integrantes

- Matheus Borges - RM: 574085
- Ryan Luther - RM
- Murilo Ignacio - RM