# TESTE_CPP_LAB
Sistema de gerenciamento escolar desenvolvido em C++ para demonstrar os conceitos fundamentais de Programação Orientada a Objetos (POO). O sistema permite o cadastro, listagem, pesquisa, remoção e persistência de dados de estudantes e professores. 


# 🎓 Sistema Escolar em C++

![C++](https://img.shields.io/badge/C++-17-blue.svg)
![POO](https://img.shields.io/badge/POO-Completo-green.svg)
![License](https://img.shields.io/badge/License-MIT-orange.svg)

## 👥 Integrantes do Grupo

| Nome | Função |
|------|--------|
| **Denilson Sansao Uate** | Desenvolvedor |
| **Joao Armando Mussepe** | Desenvolvedor |
| **Kelven Jossamo** | Desenvolvedor |
| **Sabura Sorte** | Desenvolvedor |

---

## 📋 Descrição do Projeto

Sistema de gerenciamento escolar desenvolvido em C++ para demonstrar os conceitos fundamentais de **Programação Orientada a Objetos (POO)**. O sistema permite o cadastro, listagem, pesquisa, remoção e persistência de dados de **estudantes** e **professores**.

Este projeto foi desenvolvido como parte de um teste prático com duração de 120 minutos, abordando todos os pilares da POO.

---

## 🚀 Funcionalidades

| Opção | Funcionalidade | Descrição |
|-------|----------------|-----------|
| 1 | Cadastrar estudante | Insere novo estudante com validação de notas (0-20) |
| 2 | Cadastrar professor | Insere novo professor no sistema |
| 3 | Mostrar estudantes | Lista todos os estudantes cadastrados |
| 4 | Mostrar professores | Lista todos os professores cadastrados |
| 5 | Pesquisar por nome | Busca linear por nome (estudantes e professores) |
| 6 | Remover pessoa | Remove por número do estudante ou código do professor |
| 7 | Verificar aprovação | Mostra média e situação do estudante |
| 8 | Aumentar salário | Reajusta salário do professor por percentual |
| 9 | Salvar em arquivo | Persiste todos os dados em arquivo `.txt` |
| 10 | Ler do arquivo | Recupera dados de arquivo `.txt` |
| 11 | Sair | Encerra o programa |

---

## 🧠 Conceitos de POO Demonstrados

| Conceito | Onde foi aplicado | Explicação |
|----------|-------------------|-------------|
| **Classe** | `Pessoa`, `Estudante`, `Professor`, `SistemaGerenciador` | Modelos para criação de objetos |
| **Objeto** | `new Estudante(...)` | Instância concreta de uma classe |
| **Encapsulamento** | Atributos `protected` + getters/setters | Proteção e acesso controlado aos dados |
| **Herança** | `class Estudante : public Pessoa` | Reaproveitamento de código da classe base |
| **Polimorfismo** | `mostrarDados()` | Mesmo método com comportamentos diferentes |
| **Late Binding** | Ponteiro `Pessoa*` chamando `mostrarDados()` | Decisão em tempo de execução |
| **Classe Abstrata** | `virtual void mostrarDados() = 0` | Classe que não pode ser instanciada |
| **Construtor** | `Pessoa(string n, int i, char s)` | Inicializa objetos automaticamente |
| **Destrutor** | `~SistemaGerenciador()` | Limpa memória automaticamente |
| **Ponteiros** | `Estudante* estudantes[10]` | Armazena endereços de memória |
| **Alocação Dinâmica** | `new Estudante(...)` | Memória alocada em tempo de execução |

---

## 📁 Estrutura do Projeto
