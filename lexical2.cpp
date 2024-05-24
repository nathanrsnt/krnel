#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <unordered_map>
#include <vector>

// Enumeração para representar os tokens
enum class Token {
    IGUAL,
    DIFERENTE,
    MAIOR,
    MAIOR_IGUAL,
    MENOR,
    MENOR_IGUAL,
    OU,
    MULTIPLICAR,
    SOMAR,
    INCREMENTAR,
    DECREMENTAR,
    SUBTRAIR,
    DIVIDIR,
    INICIO_PROGRAMA,
    FIM_PROGRAMA,
    INICIO_BLOCO,
    FIM_BLOCO,
    FIM_COMANDO,
    ATRIBUIR,
    CONDICIONAL_SE,
    CONDICIONAL_SENAO,
    CONDICIONAL_SENAOSE,
    LACO_ENQUANTO,
    LACO_PARA,
    ENTRADA_DADOS,
    SAIDA_DADOS,
    PALAVRA_RESERVADA,
    IDENTIFICADOR,
    NUMERO,
    COMENTARIO,
    TIPAGEM,
    DESCONHECIDO
};

// Função para converter um enum para string
std::string enumToString(Token token) {
    switch (token) {
        case Token::IGUAL: return "IGUAL";
        case Token::DIFERENTE: return "DIFERENTE";
        case Token::MAIOR: return "MAIOR";
        case Token::MAIOR_IGUAL: return "MAIOR_IGUAL";
        case Token::MENOR: return "MENOR";
        case Token::MENOR_IGUAL: return "MENOR_IGUAL";
        case Token::OU: return "OU";
        case Token::MULTIPLICAR: return "MULTIPLICAR";
        case Token::SOMAR: return "SOMAR";
        case Token::INCREMENTAR: return "INCREMENTAR";
        case Token::DECREMENTAR: return "DECREMENTAR";
        case Token::SUBTRAIR: return "SUBTRAIR";
        case Token::DIVIDIR: return "DIVIDIR";
        case Token::INICIO_PROGRAMA: return "INICIO_PROGRAMA";
        case Token::FIM_PROGRAMA: return "FIM_PROGRAMA";
        case Token::INICIO_BLOCO: return "INICIO_BLOCO";
        case Token::FIM_BLOCO: return "FIM_BLOCO";
        case Token::FIM_COMANDO: return "FIM_COMANDO";
        case Token::ATRIBUIR: return "ATRIBUIR";
        case Token::CONDICIONAL_SE: return "CONDICIONAL_SE";
        case Token::CONDICIONAL_SENAO: return "CONDICIONAL_SENAO";
        case Token::CONDICIONAL_SENAOSE: return "CONDICIONAL_SENAOSE";
        case Token::LACO_ENQUANTO: return "LACO_ENQUANTO";
        case Token::LACO_PARA: return "LACO_PARA";
        case Token::ENTRADA_DADOS: return "ENTRADA_DADOS";
        case Token::SAIDA_DADOS: return "SAIDA_DADOS";
        case Token::PALAVRA_RESERVADA: return "PALAVRA_RESERVADA";
        case Token::IDENTIFICADOR: return "IDENTIFICADOR";
        case Token::NUMERO: return "NUMERO";
        case Token::COMENTARIO: return "COMENTARIO";
        case Token::TIPAGEM: return "TIPAGEM";
        case Token::DESCONHECIDO: return "DESCONHECIDO";
    }
    return "DESCONHECIDO";
}

// Mapeamento de strings para tokens
std::unordered_map<std::string, Token> keywords = {
    {"=-=", Token::IGUAL},
    {"=!=", Token::DIFERENTE},
    {">=", Token::MAIOR_IGUAL},
    {"=<<=", Token::MENOR_IGUAL},
    {"=||=", Token::OU},
    {"*.*", Token::MULTIPLICAR},
    {"*+*", Token::SOMAR},
    {"*++*", Token::INCREMENTAR},
    {"*--*", Token::DECREMENTAR},
    {"*-*", Token::SUBTRAIR},
    {"*/*", Token::DIVIDIR},
    {"@:!", Token::INICIO_PROGRAMA},
    {"%:!", Token::FIM_PROGRAMA},
    {"{", Token::INICIO_BLOCO},
    {"}", Token::FIM_BLOCO},
    {";", Token::FIM_COMANDO},
    {"*>>*", Token::ATRIBUIR},
    {"def:", Token::PALAVRA_RESERVADA},
    {"super:def", Token::PALAVRA_RESERVADA},
    {"yeet", Token::PALAVRA_RESERVADA},
    {"i:", Token::PALAVRA_RESERVADA},
    {"e:", Token::PALAVRA_RESERVADA},
    {"ie:", Token::PALAVRA_RESERVADA},
    {"w:", Token::PALAVRA_RESERVADA},
    {"f:", Token::PALAVRA_RESERVADA},
    {"read:", Token::PALAVRA_RESERVADA},
    {"put::", Token::PALAVRA_RESERVADA},
    {"int", Token::TIPAGEM},
    {"float", Token::TIPAGEM},
    {"boolean", Token::TIPAGEM},
    {"string", Token::TIPAGEM},
    {"char", Token::TIPAGEM}
};

// Função para verificar se uma string é um identificador válido
bool isIdentifier(const std::string& str) {
    if (!std::isalpha(str[0]))
        return false;
    for (char c : str) {
        if (!std::isalnum(c) && c != '_')
            return false;
    }
    return true;
}

// Função para verificar se uma string é um número válido
bool isNumber(const std::string& str) {
    for (char c : str) {
        if (!std::isdigit(c))
            return false;
    }
    return true;
}

// Função para analisar uma linha de entrada
void analyzeLine(const std::string& line) {
    int errors = 0;
    std::stringstream ss(line);
    std::string token;
    char prevChar = ' ';

    while (ss >> token) {
        // Verificar se o token é uma palavra reservada
        auto it = keywords.find(token);
        if (it != keywords.end()) {
            Token tokenType = it->second;
            std::cout << "Palavra reservada: " << token << " [" << enumToString(tokenType) << "]" << std::endl;
            continue;
        }

        // Verificar se o token é um número
        if (isNumber(token)) {
            std::cout << "Número: " << token << std::endl;
            continue;
        }

        // Verificar se o token é um identificador
        if (isIdentifier(token)) {
            std::cout << "Identificador: " << token << std::endl;
            continue;
        }

        // Verificar se o token é um símbolo
        if (token.size() == 1 && !std::isalnum(token[0])) {
            std::cout << "Símbolo: " << token << std::endl;
            continue;
        }

        // Verificar se o token é um comentário
        if (token == "#") {
            std::cout << "Comentário: ";
            std::string comment;
            std::getline(ss, comment);
            std::cout << comment << std::endl;
            break; // Comentário engole o resto da linha
        }

        // Se chegou aqui, o token é desconhecido
        std::cerr << "Erro léxico: token desconhecido -> " << token << std::endl;
        break;
    }
}

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de entrada.\n";
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        analyzeLine(line);
    }

    inputFile.close();
    return 0;
}
