#include <iostream>
#include <vector>
#include "Retangulo.h"
#include "Database.h"

const std::string connectionString =
"Driver={ODBC Driver 17 for SQL Server};"
"Server=DESKTOP-A7BJJV6\\SQLEXPRESS;"
"Database=ATV_RETANGULO;"
"Trusted_Connection=Yes;"
"Encrypt=Yes;"
"TrustServerCertificate=Yes;";

void Testes()
{
	//Teste Classe Retangulo
	// Criação de objetos da classe Retangulo
	Retangulo r1;

	Retangulo r2(12);

	Retangulo r3(15, 10);

	// Exibindo as áreas dos retângulos
	std::cout << "Area do retangulo r1: " << r1.getArea() << std::endl;
	std::cout << "Area do retangulo r2: " << r2.getArea() << std::endl;
	std::cout << "Area do retangulo r3: " << r3.getArea() << std::endl;

	//Teste conexão com Banco
	Database db;

	if (db.connect(connectionString))
		std::cout << "Conexao com o banco de dados estabelecida com sucesso!" << std::endl;
	else
		std::cout << "Falha ao conectar ao banco de dados." << std::endl;

	//Teste captura de dados de UMA linha do banc
	std::cout << "Total de linhas na tabela Retangulo: " << 
					db.executeCountQuery("SELECT COUNT(*) FROM [ATV_RETANGULO].[dbo].[Retangulo]")
					<< std::endl;

	//Teste captura de dados de VÁRIAS linhas do banco
	///*std::vector<std::vector<std::string>> linhas = db.executeQuery("SELECT * FROM [ATV_RETANGULO].[dbo].[Retangulo]");
	//for (const auto& linha : linhas) {
	//	for (const auto& valor : linha) {
	//		std::cout << valor << " ";
	//	}
	//	std::cout << std::endl;
	//}*/
}

int main()
{
	Testes();
	
	Database db;

	db.connect(connectionString);

	int linhas = db.executeCountQuery("SELECT COUNT(*) FROM [ATV_RETANGULO].[dbo].[Retangulo]");

	return 0;
}