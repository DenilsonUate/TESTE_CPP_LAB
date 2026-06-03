/**
 * ============================================================================
 * SISTEMA ESCOLAR - PROGRAMACAO ORIENTADA A OBJETOS EM C++
 * ============================================================================
 * 
 * DISCIPLINA: Programacao Orientada a Objetos
 * DATA: 03/06/2026
 * DURACAO: 120 minutos
 * 
 * DESCRICAO: Sistema para gerenciamento de estudantes e professores
 * 
 * REGRAS: As notas dos estudantes variam de 0 a 20 (VALIDACAO OBRIGATORIA)
 * 
 * ============================================================================
 */

#include <iostream>   // Para entrada e saida (cout, cin)
#include <string>     // Para uso da classe string
#include <fstream>    // Para manipulacao de arquivos (salvar/ler dados)
#include <cstdlib>    // Para system("pause") no Windows

using namespace std;

// ============================================================================
// FUNCAO AUXILIAR PARA VALIDAR NOTAS (0 a 20)
// ============================================================================
/**
 * @brief Valida se uma nota esta dentro do intervalo permitido (0 a 20)
 * @param nota A nota a ser validada
 * @return true se a nota for valida, false caso contrario
 */
bool notaValida(double nota) 
{
    return (nota >= 0.0 && nota <= 20.0);
}

// ============================================================================
// EXERCICIO 1: CLASSE ABSTRATA PESSOA
// ============================================================================
/**
 * @class Pessoa
 * @brief Classe base abstrata para todas as pessoas do sistema
 * 
 * CONCEITO DE CLASSE ABSTRATA:
 * - E uma classe que NAO PODE ser instanciada diretamente
 * - Serve como modelo para outras classes (Estudante e Professor)
 * - Possui pelo menos um metodo puramente virtual (mostrarDados)
 * - O metodo puramente virtual e declarado com "= 0"
 * 
 * CONCEITO DE ENCAPSULAMENTO:
 * - Atributos sao PROTECTED (acessiveis pela classe e suas filhas)
 * - Acesso aos dados e feito atraves de GETTERS e SETTERS
 * - Isso protege os dados de modificacoes indevidas
 * 
 * CONCEITO DE HERANCA:
 * - As classes Estudante e Professor vao herdar (reaproveitar)
 *   todos os atributos e metodos desta classe
 */
class Pessoa 
{
protected:
    // ATRIBUTOS PROTEGIDOS
    // O "protected" permite que as classes filhas acessem diretamente
    string nome;      // Nome completo da pessoa
    int    idade;     // Idade em anos
    char   sexo;      // Sexo: 'M' (Masculino) ou 'F' (Feminino)

public:
    // ------------------------------------------------------------------------
    // CONSTRUTOR PARAMETRIZADO
    // ------------------------------------------------------------------------
    /**
     * @brief Construtor que inicializa todos os atributos da pessoa
     * 
     * CONCEITO DE CONSTRUTOR:
     * - Metodo especial chamado AUTOMATICAMENTE ao criar um objeto
     * - Tem o MESMO NOME da classe
     * - NAO tem tipo de retorno (nem void)
     * - Pode ser sobrecarregado (vários construtores)
     * 
     * @param n Nome da pessoa
     * @param i Idade da pessoa
     * @param s Sexo da pessoa ('M' ou 'F')
     */
    Pessoa(string n, int i, char s) : nome(n), idade(i), sexo(s) {}
    
    // ------------------------------------------------------------------------
    // DESTRUTOR VIRTUAL
    // ------------------------------------------------------------------------
    /**
     * @brief Destrutor virtual
     * 
     * CONCEITO DE DESTRUTOR:
     * - Metodo especial chamado AUTOMATICAMENTE ao destruir um objeto
     * - Tem o mesmo nome da classe com "~" na frente
     * - NAO recebe parametros
     * - NAO tem tipo de retorno
     * 
     * CONCEITO DE DESTRUTOR VIRTUAL:
     * - O "virtual" garante que o destrutor da classe filha seja chamado
     * - Isso evita vazamento de memoria em hierarquias polimorficas
     */
    virtual ~Pessoa() {}
    
    // ------------------------------------------------------------------------
    // GETTERS (METODOS DE ACESSO)
    // ------------------------------------------------------------------------
    /**
     * CONCEITO DE GETTER:
     * - Metodo PUBLICO que permite LER o valor de um atributo
     * - O "const" no final indica que o metodo NAO MODIFICA o objeto
     * - Nomenclatura padrao: get + NomeDoAtributo
     */
    string getNome()  const { return nome;  }
    int    getIdade() const { return idade; }
    char   getSexo()  const { return sexo;  }
    
    // ------------------------------------------------------------------------
    // SETTERS (METODOS DE MODIFICACAO)
    // ------------------------------------------------------------------------
    /**
     * CONCEITO DE SETTER:
     * - Metodo PUBLICO que permite MODIFICAR o valor de um atributo
     * - Permite validar os dados antes de modificar
     * - Nomenclatura padrao: set + NomeDoAtributo
     */
    void setNome(string n)  { nome  = n; }
    void setIdade(int i)    { idade = i; }
    void setSexo(char s)    { sexo  = s; }
    
    // ------------------------------------------------------------------------
    // METODO PURAMENTE VIRTUAL
    // ------------------------------------------------------------------------
    /**
     * CONCEITO DE METODO PURAMENTE VIRTUAL:
     * - Declarado com "= 0" no final
     * - NAO tem implementacao na classe base
     * - OBRIGA as classes filhas a implementarem este metodo
     * - Torna a classe ABSTRATA (nao pode ser instanciada)
     */
    virtual void mostrarDados() const = 0;
};

// ============================================================================
// EXERCICIO 2.1: CLASE ESTUDANTE (HERDA DE PESSOA)
// ============================================================================
/**
 * @class Estudante
 * @brief Representa um estudante do sistema educacional
 * 
 * CONCEITO DE HERANCA:
 * - "class Estudante : public Pessoa" significa:
 *   Estudante herda TUDO que Pessoa tem (nome, idade, sexo)
 * - "public" indica o tipo de heranca (mantem os niveis de acesso)
 * - Estudante e um tipo ESPECIFICO de Pessoa
 * - Relacao "E UM" (Estudante E UMA Pessoa)
 * 
 * CONCEITO DE SOBRESCRITA (OVERRIDE):
 * - Estudante vai IMPLEMENTAR o metodo mostrarDados()
 * - O metodo tem o MESMO NOME e MESMOS PARAMETROS da classe base
 * - O COMPORTAMENTO e diferente (especifico para estudante)
 */
class Estudante : public Pessoa 
{
private:
    // ATRIBUTOS ESPECIFICOS DA CLASSE ESTUDANTE
    int     numeroEstudante;   // Numero de matricula do estudante
    string  curso;             // Nome do curso que o estudante faz
    double  notas[3];          // Vetor com 3 notas: [0]=TesteI, [1]=TesteII, [2]=Trabalho

public:
    // ------------------------------------------------------------------------
    // CONSTRUTOR
    // ------------------------------------------------------------------------
    /**
     * @brief Construtor da classe Estudante
     * 
     * CONCEITO DE CONSTRUTOR DA CLASSE DERIVADA:
     * - Chama primeiro o construtor da classe base (: Pessoa(n, i, s))
     * - Depois inicializa seus proprios atributos
     * - Garante que TODOS os atributos sejam inicializados corretamente
     * 
     * @param n   Nome do estudante
     * @param i   Idade do estudante
     * @param s   Sexo do estudante
     * @param num Numero de matricula
     * @param c   Curso do estudante
     * @param n1  Nota do Teste I (0 a 20)
     * @param n2  Nota do Teste II (0 a 20)
     * @param n3  Nota do Trabalho (0 a 20)
     */
    Estudante(string n, int i, char s, int num, string c, 
              double n1, double n2, double n3)
        : Pessoa(n, i, s)           // Chama o construtor da classe base
        , numeroEstudante(num)      // Inicializa numero do estudante
        , curso(c)                  // Inicializa curso
    {
        // Inicializa o vetor de notas com VALIDACAO
        notas[0] = (notaValida(n1) ? n1 : 0.0);
        notas[1] = (notaValida(n2) ? n2 : 0.0);
        notas[2] = (notaValida(n3) ? n3 : 0.0);
    }
    
    // ------------------------------------------------------------------------
    // GETTERS ESPECIFICOS
    // ------------------------------------------------------------------------
    int    getNumeroEstudante() const { return numeroEstudante; }
    string getCurso()           const { return curso; }
    double getNota(int idx)     const { return notas[idx]; }
    
    // ------------------------------------------------------------------------
    // METODOS ESPECIFICOS DA CLASSE ESTUDANTE
    // ------------------------------------------------------------------------
    /**
     * @brief Calcula a media aritmetica das 3 notas
     * @return Media das notas (soma / 3)
     */
    double calcularMedia() const 
    {
        return (notas[0] + notas[1] + notas[2]) / 3.0;
    }
    
    /**
     * @brief Verifica a situacao do estudante baseado na media
     * @return String com a situacao
     * 
     * CRITERIOS DE APROVACAO (notas de 0 a 20):
     * - Media >= 14.0  -> DISPENSADO (aprovado direto, sem exame)
     * - Media >= 9.5   -> ADMITIDO A EXAME (recuperacao)
     * - Media < 9.5    -> REPROVADO
     */
    string verificarAprovacao() const 
    {
        double media = calcularMedia();
        
        if (media >= 14.0)
            return "DISPENSADO (Aprovado)";
        else if (media >= 9.5)
            return "ADMITIDO A EXAME";
        else
            return "REPROVADO";
    }
    
    // ------------------------------------------------------------------------
    // SOBRESCRITA DO METODO MOSTRAR DADOS (POLIMORFISMO)
    // ------------------------------------------------------------------------
    /**
     * @brief Exibe todos os dados do estudante na tela
     * 
     * CONCEITO DE SOBRESCRITA:
     * - Este metodo tem o MESMO NOME que o metodo da classe base
     * - A implementacao e DIFERENTE (especifica para estudante)
     * - Quando chamado via ponteiro da classe base, o comportamento
     *   correto e decidido em TEMPO DE EXECUCAO (polimorfismo)
     */
    void mostrarDados() const 
    {
        cout << "\n";
        cout << "+----------------------------------------------------------+\n";
        cout << "¦                    DADOS DO ESTUDANTE                    ¦\n";
        cout << "¦----------------------------------------------------------¦\n";
        cout << "¦ Nome:              " << nome << "\n";
        cout << "¦ Idade:             " << idade << "\n";
        cout << "¦ Sexo:              " << (sexo == 'M' ? "Masculino" : "Feminino") << "\n";
        cout << "¦ Numero Estudante:  " << numeroEstudante << "\n";
        cout << "¦ Curso:             " << curso << "\n";
        cout << "¦ Notas:             " << notas[0] << " | " << notas[1] << " | " << notas[2] << "\n";
        cout << "¦ Media:             " << calcularMedia() << "\n";
        cout << "¦ Situacao:          " << verificarAprovacao() << "\n";
        cout << "+----------------------------------------------------------+\n";
    }
};

// ============================================================================
// EXERCICIO 2.2: CLASE PROFESSOR (HERDA DE PESSOA)
// ============================================================================
/**
 * @class Professor
 * @brief Representa um professor do sistema educacional
 * 
 * Herda todos os atributos e metodos da classe Pessoa e adiciona
 * atributos especificos como codigo, disciplina e salario.
 */
class Professor : public Pessoa 
{
private:
    // ATRIBUTOS ESPECIFICOS DA CLASSE PROFESSOR
    int     codigoProfessor;   // Codigo unico de identificacao do professor
    string  disciplina;        // Disciplina que o professor leciona
    double  salario;           // Salario do professor

public:
    // ------------------------------------------------------------------------
    // CONSTRUTOR
    // ------------------------------------------------------------------------
    Professor(string n, int i, char s, int cod, string disc, double sal)
        : Pessoa(n, i, s)       // Chama o construtor da classe base
        , codigoProfessor(cod)  // Inicializa codigo do professor
        , disciplina(disc)      // Inicializa disciplina
        , salario(sal)          // Inicializa salario
    {}
    
    // ------------------------------------------------------------------------
    // GETTERS ESPECIFICOS
    // ------------------------------------------------------------------------
    int    getCodigoProfessor() const { return codigoProfessor; }
    string getDisciplina()      const { return disciplina; }
    double getSalario()         const { return salario; }
    
    // ------------------------------------------------------------------------
    // METODOS ESPECIFICOS DA CLASSE PROFESSOR
    // ------------------------------------------------------------------------
    /**
     * @brief Aumenta o salario do professor baseado em um percentual
     * @param percentual Percentual de aumento (ex: 10 para 10%)
     */
    void aumentarSalario(double percentual) 
    {
        if (percentual > 0) 
        {
            salario += salario * (percentual / 100.0);
            cout << "\n[*] Salario de " << nome 
                 << " reajustado para R$ " << salario << endl;
        }
        else 
        {
            cout << "\n[!] Percentual invalido!\n";
        }
    }
    
    // ------------------------------------------------------------------------
    // SOBRESCRITA DO METODO MOSTRAR DADOS (POLIMORFISMO)
    // ------------------------------------------------------------------------
    void mostrarDados() const 
    {
        cout << "\n";
        cout << "+----------------------------------------------------------+\n";
        cout << "¦                    DADOS DO PROFESSOR                    ¦\n";
        cout << "¦----------------------------------------------------------¦\n";
        cout << "¦ Nome:              " << nome << "\n";
        cout << "¦ Idade:             " << idade << "\n";
        cout << "¦ Sexo:              " << (sexo == 'M' ? "Masculino" : "Feminino") << "\n";
        cout << "¦ Codigo:            " << codigoProfessor << "\n";
        cout << "¦ Disciplina:        " << disciplina << "\n";
        cout << "¦ Salario:           R$ " << salario << "\n";
        cout << "+----------------------------------------------------------+\n";
    }
};

// ============================================================================
// EXERCICIO 3: CLASE GERENCIADORA DO SISTEMA
// ============================================================================
/**
 * @class SistemaGerenciador
 * @brief Gerencia todas as operacoes do sistema (CRUD + Persistencia)
 * 
 * Responsabilidades:
 * - Cadastrar estudantes e professores (com validacao)
 * - Listar todos os registros
 * - Pesquisar por nome (busca linear)
 * - Remover por identificador
 * - Salvar e carregar dados de arquivo
 * - Demonstrar polimorfismo
 * 
 * CONCEITO DE CLASSE GERENCIADORA:
 * - Classe que centraliza TODAS as operacoes do sistema
 * - Mantem os dados (vetores de ponteiros)
 * - Fornece uma interface clara para o usuario (via menu)
 * - Separa a logica de negocio da interface (main)
 */
class SistemaGerenciador 
{
private:
    // CONSTANTES DE CAPACIDADE MAXIMA
    static const int MAX_ESTUDANTES = 10;   // Maximo de 10 estudantes
    static const int MAX_PROFESSORES = 5;   // Maximo de 5 professores
    
    // VETORES DE PONTEIROS
    /**
     * CONCEITO DE VETOR DE PONTEIROS:
     * - Armazena ENDERECOS de memoria, nao os objetos diretamente
     * - Permite ALOCACAO DINAMICA (criar objetos sob demanda)
     * - Permite POLIMORFISMO (ponteiros da classe base)
     * - Cada posicao pode apontar para NULL (nenhum objeto)
     */
    Estudante* estudantes[MAX_ESTUDANTES];
    Professor* professores[MAX_PROFESSORES];
    
    // CONTADORES
    int qtdEstudantes;   // Quantos estudantes estao cadastrados
    int qtdProfessores;  // Quantos professores estao cadastrados

    // ------------------------------------------------------------------------
    // METODO PRIVADO PARA VALIDAR NOTAS INDIVIDUALMENTE
    // ------------------------------------------------------------------------
    /**
     * @brief Valida se as tres notas estao no intervalo 0-20
     * @param n1 Nota 1
     * @param n2 Nota 2
     * @param n3 Nota 3
     * @return true se todas as notas sao validas
     */
    bool todasNotasValidas(double n1, double n2, double n3) const 
    {
        return (notaValida(n1) && notaValida(n2) && notaValida(n3));
    }

public:
    // ------------------------------------------------------------------------
    // CONSTRUTOR
    // ------------------------------------------------------------------------
    SistemaGerenciador() : qtdEstudantes(0), qtdProfessores(0) 
    {
        // Inicializa todos os ponteiros como NULL
        // NULL = 0 (nenhum endereco valido)
        for (int i = 0; i < MAX_ESTUDANTES; i++) 
            estudantes[i] = NULL;
        
        for (int i = 0; i < MAX_PROFESSORES; i++) 
            professores[i] = NULL;
    }
    
    // ------------------------------------------------------------------------
    // DESTRUTOR
    // ------------------------------------------------------------------------
    /**
     * @brief Libera toda a memoria alocada dinamicamente
     * 
     * CONCEITO DE DESTRUTOR:
     * - Chamado AUTOMATICAMENTE quando o objeto e destruido
     * - Libera a memoria que foi alocada com "new"
     * - Evita VAZAMENTO DE MEMORIA (memory leak)
     */
    ~SistemaGerenciador() 
    {
        for (int i = 0; i < qtdEstudantes; i++) 
            delete estudantes[i];
        
        for (int i = 0; i < qtdProfessores; i++) 
            delete professores[i];
    }
    
    // ========================================================================
    // OPERACOES DE CADASTRO
    // ========================================================================
    
    /**
     * @brief Cadastra um novo estudante no sistema
     * 
     * CONCEITO DE ALOCACAO DINAMICA:
     * - "new Estudante(...)" aloca memoria no HEAP
     * - Retorna um PONTEIRO para o objeto criado
     * - O objeto continua existindo ate ser deletado
     * 
     * @return true se cadastrado com sucesso, false se limite atingido ou nota invalida
     */
    bool cadastrarEstudante(string nome, int idade, char sexo, int num, 
                            string curso, double n1, double n2, double n3) 
    {
        // VALIDACAO DAS NOTAS (0 a 20)
        if (!todasNotasValidas(n1, n2, n3)) 
        {
            cout << "\n[?] ERRO: As notas devem estar entre 0 e 20!\n";
            cout << "    Notas inseridas: " << n1 << ", " << n2 << ", " << n3 << "\n";
            return false;
        }
        
        // Verifica se ainda ha espaco disponivel
        if (qtdEstudantes < MAX_ESTUDANTES) 
        {
            // ALOCACAO DINAMICA: cria o objeto no heap
            estudantes[qtdEstudantes++] = new Estudante(nome, idade, sexo, 
                                                         num, curso, n1, n2, n3);
            cout << "\n[?] Estudante cadastrado com sucesso!\n";
            return true;
        }
        
        cout << "\n[?] Limite maximo de " << MAX_ESTUDANTES 
             << " estudantes atingido!\n";
        return false;
    }
    
    /**
     * @brief Cadastra um novo professor no sistema
     * @return true se cadastrado com sucesso, false se limite atingido
     */
    bool cadastrarProfessor(string nome, int idade, char sexo, int cod, 
                            string disc, double sal) 
    {
        if (qtdProfessores < MAX_PROFESSORES) 
        {
            professores[qtdProfessores++] = new Professor(nome, idade, sexo, 
                                                            cod, disc, sal);
            cout << "\n[?] Professor cadastrado com sucesso!\n";
            return true;
        }
        
        cout << "\n[?] Limite maximo de " << MAX_PROFESSORES 
             << " professores atingido!\n";
        return false;
    }
    
    // ========================================================================
    // OPERACOES DE LISTAGEM
    // ========================================================================
    
    void listarEstudantes() 
    {
        if (qtdEstudantes == 0) 
        {
            cout << "\n[!] Nenhum estudante cadastrado.\n";
            return;
        }
        
        cout << "\n";
        cout << "+----------------------------------------------------------+\n";
        cout << "¦              LISTA DE ESTUDANTES CADASTRADOS             ¦\n";
        cout << "+----------------------------------------------------------+\n";
        
        for (int i = 0; i < qtdEstudantes; i++)
            estudantes[i]->mostrarDados();
    }
    
    void listarProfessores() 
    {
        if (qtdProfessores == 0) 
        {
            cout << "\n[!] Nenhum professor cadastrado.\n";
            return;
        }
        
        cout << "\n";
        cout << "+----------------------------------------------------------+\n";
        cout << "¦             LISTA DE PROFESSORES CADASTRADOS             ¦\n";
        cout << "+----------------------------------------------------------+\n";
        
        for (int i = 0; i < qtdProfessores; i++)
            professores[i]->mostrarDados();
    }
    
    // ========================================================================
    // OPERACOES DE PESQUISA E REMOCAO
    // ========================================================================
    
    /**
     * @brief Pesquisa uma pessoa pelo nome (BUSCA LINEAR)
     * 
     * CONCEITO DE BUSCA LINEAR:
     * - Percorre o vetor ELEMENTO por ELEMENTO
     * - Compara o nome digitado com cada nome armazenado
     * - Complexidade: O(n) (pior caso, percorre tudo)
     */
    void pesquisarPorNome(string nomeBusca) 
    {
        bool encontrado = false;
        
        // Busca entre os estudantes
        for (int i = 0; i < qtdEstudantes; i++) 
        {
            if (estudantes[i]->getNome() == nomeBusca) 
            {
                estudantes[i]->mostrarDados();
                encontrado = true;
            }
        }
        
        // Busca entre os professores
        for (int i = 0; i < qtdProfessores; i++) 
        {
            if (professores[i]->getNome() == nomeBusca) 
            {
                professores[i]->mostrarDados();
                encontrado = true;
            }
        }
        
        if (!encontrado)
            cout << "\n[!] Pessoa com nome \"" << nomeBusca 
                 << "\" nao encontrada.\n";
    }
    
    /**
     * @brief Remove uma pessoa pelo identificador
     * @param id Identificador (numero do estudante ou codigo do professor)
     * @return true se removido com sucesso
     */
    bool removerPorIdentificador(int id) 
    {
        // Tenta remover um estudante
        for (int i = 0; i < qtdEstudantes; i++) 
        {
            if (estudantes[i]->getNumeroEstudante() == id) 
            {
                delete estudantes[i];  // Libera memoria
                
                // DESLOCA OS ELEMENTOS para preencher a vaga
                for (int j = i; j < qtdEstudantes - 1; j++)
                    estudantes[j] = estudantes[j + 1];
                
                estudantes[--qtdEstudantes] = NULL;
                cout << "\n[?] Estudante removido com sucesso!\n";
                return true;
            }
        }
        
        // Tenta remover um professor
        for (int i = 0; i < qtdProfessores; i++) 
        {
            if (professores[i]->getCodigoProfessor() == id) 
            {
                delete professores[i];
                
                for (int j = i; j < qtdProfessores - 1; j++)
                    professores[j] = professores[j + 1];
                
                professores[--qtdProfessores] = NULL;
                cout << "\n[?] Professor removido com sucesso!\n";
                return true;
            }
        }
        
        cout << "\n[?] Identificador " << id << " nao encontrado.\n";
        return false;
    }
    
    // ========================================================================
    // OPERACOES ESPECIFICAS
    // ========================================================================
    
    void verificarAprovacaoEstudante(int numero) 
    {
        for (int i = 0; i < qtdEstudantes; i++) 
        {
            if (estudantes[i]->getNumeroEstudante() == numero) 
            {
                cout << "\n+-------- VERIFICACAO DE APROVACAO --------+\n";
                cout << "¦ Estudante: " << estudantes[i]->getNome() << "\n";
                cout << "¦ Curso:     " << estudantes[i]->getCurso() << "\n";
                cout << "¦ Notas:     " << estudantes[i]->getNota(0) << " | "
                                      << estudantes[i]->getNota(1) << " | "
                                      << estudantes[i]->getNota(2) << "\n";
                cout << "¦ Media:     " << estudantes[i]->calcularMedia() << "\n";
                cout << "¦ Situacao:  " << estudantes[i]->verificarAprovacao() << "\n";
                cout << "+------------------------------------------+\n";
                return;
            }
        }
        cout << "\n[!] Estudante com numero " << numero << " nao encontrado.\n";
    }
    
    void aumentarSalarioProfessor(int codigo, double percentual) 
    {
        for (int i = 0; i < qtdProfessores; i++) 
        {
            if (professores[i]->getCodigoProfessor() == codigo) 
            {
                professores[i]->aumentarSalario(percentual);
                return;
            }
        }
        cout << "\n[!] Professor com codigo " << codigo << " nao encontrado.\n";
    }
    
    // ========================================================================
    // OPERACOES DE PERSISTENCIA (ARQUIVOS)
    // ========================================================================
    
    void salvarEmArquivo(string nomeArquivo) 
    {
        ofstream arquivo(nomeArquivo.c_str());
        
        if (!arquivo) 
        {
            cout << "\n[!] Erro ao abrir arquivo para escrita!\n";
            return;
        }
        
        // SALVA ESTUDANTES
        arquivo << qtdEstudantes << endl;
        for (int i = 0; i < qtdEstudantes; i++) 
        {
            arquivo << "E" << endl;
            arquivo << estudantes[i]->getNome() << endl;
            arquivo << estudantes[i]->getIdade() << endl;
            arquivo << estudantes[i]->getSexo() << endl;
            arquivo << estudantes[i]->getNumeroEstudante() << endl;
            arquivo << estudantes[i]->getCurso() << endl;
            arquivo << estudantes[i]->getNota(0) << endl;
            arquivo << estudantes[i]->getNota(1) << endl;
            arquivo << estudantes[i]->getNota(2) << endl;
        }
        
        // SALVA PROFESSORES
        arquivo << qtdProfessores << endl;
        for (int i = 0; i < qtdProfessores; i++) 
        {
            arquivo << "P" << endl;
            arquivo << professores[i]->getNome() << endl;
            arquivo << professores[i]->getIdade() << endl;
            arquivo << professores[i]->getSexo() << endl;
            arquivo << professores[i]->getCodigoProfessor() << endl;
            arquivo << professores[i]->getDisciplina() << endl;
            arquivo << professores[i]->getSalario() << endl;
        }
        
        arquivo.close();
        cout << "\n[?] Dados salvos em \"" << nomeArquivo << "\" com sucesso!\n";
    }
    
    void lerDoArquivo(string nomeArquivo) 
    {
        ifstream arquivo(nomeArquivo.c_str());
        
        if (!arquivo) 
        {
            cout << "\n[!] Arquivo nao encontrado!\n";
            return;
        }
        
        // LIMPA OS DADOS ATUAIS
        for (int i = 0; i < qtdEstudantes; i++) 
            delete estudantes[i];
        for (int i = 0; i < qtdProfessores; i++) 
            delete professores[i];
        
        qtdEstudantes = 0;
        qtdProfessores = 0;
        
        string tipo;
        int nEst, nProf;
        
        // CARREGA ESTUDANTES
        arquivo >> nEst;
        for (int i = 0; i < nEst; i++) 
        {
            arquivo >> tipo;
            string nome, curso;
            int idade, numero;
            char sexo;
            double n1, n2, n3;
            
            arquivo.ignore();
            getline(arquivo, nome);
            arquivo >> idade;
            arquivo >> sexo;
            arquivo >> numero;
            arquivo.ignore();
            getline(arquivo, curso);
            arquivo >> n1 >> n2 >> n3;
            
            cadastrarEstudante(nome, idade, sexo, numero, curso, n1, n2, n3);
        }
        
        // CARREGA PROFESSORES
        arquivo >> nProf;
        for (int i = 0; i < nProf; i++) 
        {
            arquivo >> tipo;
            string nome, disciplina;
            int idade, codigo;
            char sexo;
            double salario;
            
            arquivo.ignore();
            getline(arquivo, nome);
            arquivo >> idade;
            arquivo >> sexo;
            arquivo >> codigo;
            arquivo.ignore();
            getline(arquivo, disciplina);
            arquivo >> salario;
            
            cadastrarProfessor(nome, idade, sexo, codigo, disciplina, salario);
        }
        
        arquivo.close();
        cout << "\n[?] Dados carregados de \"" << nomeArquivo 
             << "\" com sucesso!\n";
    }
    
    // ========================================================================
    // EXERCICIO 4: DEMONSTRACAO DE POLIMORFISMO (LATE BINDING)
    // ========================================================================
    /**
     * @brief Demonstra o polimorfismo em tempo de execucao (late binding)
     * 
     * CONCEITO DE POLIMORFISMO:
     * - "Poli" = muitos, "Morfismo" = formas
     * - Um mesmo metodo (mostrarDados) tem COMPORTAMENTOS DIFERENTES
     * - Depende do tipo REAL do objeto (Estudante ou Professor)
     * 
     * CONCEITO DE LATE BINDING (LIGACAO TARDIA):
     * - A decisao de QUAL metodo chamar acontece em TEMPO DE EXECUCAO
     * - NAO e decidida na compilacao
     * - O programa verifica o tipo real do objeto e chama o metodo correto
     * 
     * CONCEITO DE PONTEIRO DA CLASSE BASE:
     * - Um ponteiro do tipo "Pessoa*" pode apontar para:
     *   - Objeto do tipo Pessoa (se nao fosse abstrata)
     *   - Objeto do tipo Estudante
     *   - Objeto do tipo Professor
     * - Isso e possivel devido a HERANCA (Estudante E UMA Pessoa)
     */
    void demonstrarPolimorfismo() 
    {
        int total = qtdEstudantes + qtdProfessores;
        
        if (total == 0) 
        {
            cout << "\n[!] Nenhuma pessoa cadastrada para demonstrar polimorfismo.\n";
            return;
        }
        
        // VETOR DE PONTEIROS DA CLASSE BASE
        // Isto e o CORACAO do polimorfismo!
        Pessoa* listaPessoas[20];  // Capacidade maxima (10 + 5 = 15)
        int indice = 0;
        
        // ARMAZENA PONTEIROS DE DIFERENTES TIPOS NO MESMO VETOR
        // Isto so e possivel porque Estudante e Professor HERDAM de Pessoa
        for (int i = 0; i < qtdEstudantes; i++)
            listaPessoas[indice++] = estudantes[i];
        
        for (int i = 0; i < qtdProfessores; i++)
            listaPessoas[indice++] = professores[i];
        
        // DEMONSTRACAO DO POLIMORFISMO
        cout << "\n";
        cout << "+--------------------------------------------------------------+\n";
        cout << "¦           DEMONSTRACAO DE POLIMORFISMO (LATE BINDING)        ¦\n";
        cout << "¦--------------------------------------------------------------¦\n";
        cout << "¦                                                                ¦\n";
        cout << "¦  O QUE E POLIMORFISMO?                                        ¦\n";
        cout << "¦  - Um mesmo metodo (mostrarDados) tem comportamentos diferentes ¦\n";
        cout << "¦  - Depende do tipo REAL do objeto (Estudante ou Professor)    ¦\n";
        cout << "¦                                                                ¦\n";
        cout << "¦  O QUE E LATE BINDING?                                        ¦\n";
        cout << "¦  - A decisao de qual metodo chamar ocorre em TEMPO DE EXECUCAO ¦\n";
        cout << "¦  - NAO e decidida na compilacao                               ¦\n";
        cout << "¦                                                                ¦\n";
        cout << "¦  Veja o exemplo abaixo:                                       ¦\n";
        cout << "¦  Um mesmo ponteiro (Pessoa*) chama mostrarDados()             ¦\n";
        cout << "¦  O programa decide em tempo real qual versao executar         ¦\n";
        cout << "¦                                                                ¦\n";
        cout << "+--------------------------------------------------------------+\n";
        
        // LIGACAO TARDIA (LATE BINDING)
        // O programa decide em TEMPO DE EXECUCAO qual versao do metodo chamar
        for (int i = 0; i < total; i++) 
        {
            listaPessoas[i]->mostrarDados();  // CHAMADA POLIMORFICA!
        }
    }
};

// ============================================================================
// EXERCICIO 5: FUNCAO MAIN COM MENU INTERATIVO
// ============================================================================
/**
 * @brief Funcao principal do programa
 * 
 * CONCEITO DE MENU INTERATIVO:
 * - Loop do-while (executa pelo menos uma vez)
 * - Switch-case para tratar cada opcao
 * - Opcao 11 sai do loop
 * 
 * @return 0 - Execucao bem sucedida
 */
int main() 
{
    SistemaGerenciador sistema;
    
    int    opcao;
    string nome, curso, disciplina, nomeArquivo;
    int    idade, numero, codigo;
    char   sexo;
    double nota1, nota2, nota3, salario, percentual;
    
    do 
    {
        cout << "\n";
        cout << "+--------------------------------------------------------------+\n";
        cout << "¦                                                              ¦\n";
        cout << "¦                 SISTEMA ESCOLAR - MENU PRINCIPAL             ¦\n";
        cout << "¦                                                              ¦\n";
        cout << "¦--------------------------------------------------------------¦\n";
        cout << "¦                                                              ¦\n";
        cout << "¦   1. Cadastrar estudante                                     ¦\n";
        cout << "¦   2. Cadastrar professor                                     ¦\n";
        cout << "¦   3. Mostrar estudantes                                      ¦\n";
        cout << "¦   4. Mostrar professores                                     ¦\n";
        cout << "¦   5. Pesquisar pessoa (por nome)                             ¦\n";
        cout << "¦   6. Remover pessoa                                          ¦\n";
        cout << "¦   7. Verificar aprovacao de estudante                        ¦\n";
        cout << "¦   8. Aumentar salario de professor                           ¦\n";
        cout << "¦   9. Salvar dados em arquivo (.txt)                          ¦\n";
        cout << "¦  10. Ler dados do arquivo (.txt)                             ¦\n";
        cout << "¦  11. Sair                                                    ¦\n";
        cout << "¦                                                              ¦\n";
        cout << "¦  OBS: As notas dos estudantes devem estar entre 0 e 20       ¦\n";
        cout << "¦                                                              ¦\n";
        cout << "+--------------------------------------------------------------+\n";
        cout << "\nDigite sua opcao: ";
        cin >> opcao;
        cin.ignore();
        
        switch(opcao) 
        {
            case 1:  // CADASTRAR ESTUDANTE
                cout << "\n--- CADASTRO DE ESTUDANTE ---\n";
                cout << "Nome: ";                 getline(cin, nome);
                cout << "Idade: ";                cin >> idade;
                cout << "Sexo (M/F): ";           cin >> sexo;
                cout << "Numero do estudante: ";  cin >> numero;
                cin.ignore();
                cout << "Curso: ";                getline(cin, curso);
                
                cout << "\n[ATENCAO] As notas devem ser entre 0 e 20!\n";
                cout << "Nota do Teste I: ";      cin >> nota1;
                cout << "Nota do Teste II: ";     cin >> nota2;
                cout << "Nota do Trabalho: ";     cin >> nota3;
                
                sistema.cadastrarEstudante(nome, idade, sexo, numero, 
                                           curso, nota1, nota2, nota3);
                break;
                
            case 2:  // CADASTRAR PROFESSOR
                cout << "\n--- CADASTRO DE PROFESSOR ---\n";
                cout << "Nome: ";                 getline(cin, nome);
                cout << "Idade: ";                cin >> idade;
                cout << "Sexo (M/F): ";           cin >> sexo;
                cout << "Codigo do professor: ";  cin >> codigo;
                cin.ignore();
                cout << "Disciplina: ";           getline(cin, disciplina);
                cout << "Salario: R$ ";           cin >> salario;
                sistema.cadastrarProfessor(nome, idade, sexo, codigo, 
                                           disciplina, salario);
                break;
                
            case 3:
                sistema.listarEstudantes();
                break;
                
            case 4:
                sistema.listarProfessores();
                break;
                
            case 5:
                cout << "\nDigite o nome para pesquisa: ";
                getline(cin, nome);
                sistema.pesquisarPorNome(nome);
                break;
                
            case 6:
                cout << "\nDigite o numero do estudante ou codigo do professor: ";
                cin >> codigo;
                sistema.removerPorIdentificador(codigo);
                break;
                
            case 7:
                cout << "\nDigite o numero do estudante: ";
                cin >> numero;
                sistema.verificarAprovacaoEstudante(numero);
                break;
                
            case 8:
                cout << "\nDigite o codigo do professor: ";
                cin >> codigo;
                cout << "Digite o percentual de aumento (%): ";
                cin >> percentual;
                sistema.aumentarSalarioProfessor(codigo, percentual);
                break;
                
            case 9:
                cout << "\nDigite o nome do arquivo (ex: dados.txt): ";
                getline(cin, nomeArquivo);
                sistema.salvarEmArquivo(nomeArquivo);
                break;
                
            case 10:
                cout << "\nDigite o nome do arquivo (ex: dados.txt): ";
                getline(cin, nomeArquivo);
                sistema.lerDoArquivo(nomeArquivo);
                break;
                
            case 11:
                cout << "\n[?] Encerrando o sistema...\n";
                break;
                
            default:
                cout << "\n[!] Opcao invalida! Tente novamente.\n";
                break;
        }
        
    } while (opcao != 11);
    
    // DEMONSTRACAO DO POLIMORFISMO (EXERCICIO 4)
    sistema.demonstrarPolimorfismo();
    
    cout << "\n[?] Programa finalizado com sucesso!\n";
    system("pause");
    
    return 0;
}
