#include <iostream>
#include "Retangulo.h"
#include "Database.h"

int main()
{
	//Teste Classe Retangulo
	// Cria��o de objetos da classe Retangulo
	Retangulo r1;

	Retangulo r2(12);

	Retangulo r3(15, 10);

	// Exibindo as �reas dos ret�ngulos
	std::cout << "Area do retangulo r1: " << r1.getArea() << std::endl;
	std::cout << "Area do retangulo r2: " << r2.getArea() << std::endl;
	std::cout << "Area do retangulo r3: " << r3.getArea() << std::endl;

	//Teste conex�o com Banco
	Database db;

	std::string connectionString =
		"Driver={ODBC Driver 17 for SQL Server};"
		"Server=DESKTOP-A7BJJV6\\SQLEXPRESS;"
		"Database=ATV_RETANGULO;"
		"Trusted_Connection=Yes;"
		"Encrypt=Yes;"
		"TrustServerCertificate=Yes;";

	
	if (db.connect(connectionString)) 
		std::cout << "Conexao com o banco de dados estabelecida com sucesso!" << std::endl;
	else
		std::cout << "Falha ao conectar ao banco de dados." << std::endl;

	return 0;
}