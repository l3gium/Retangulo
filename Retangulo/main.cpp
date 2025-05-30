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
	int max = 5;

	std::string query = 
		"SELECT base, altura "
		"FROM ( "
		"  SELECT base, altura, ROW_NUMBER() OVER (ORDER BY id ASC) AS linha "
		"  FROM Retangulo "
		") AS t "
		"WHERE linha <= " + std::to_string(max) + ";";

	std::vector<int> valores = db.executeSelectQuery(query);

	for (size_t i = 0; i < valores.size(); i += 2) 
	{
		Retangulo retangulo(valores[i], valores[i + 1]);
		std::cout << "Retangulo " << (i / 2) + 1 << ": Base = " << retangulo.getBase() 
				  << ", Altura = " << retangulo.getAltura() << ", Area = " << retangulo.getArea() << std::endl;
	}
}

void exibeRetangulos(const std::vector<Retangulo>& retangulos)
{
	std::cout << "Exibindo retangulos:" << std::endl;
	int i = 0;
	for (const auto& retangulo : retangulos)
	{
		std::cout << i << ": " <<"Base: " << retangulo.getBase() << ", Altura: " << retangulo.getAltura() 
				  << ", Area: " << retangulo.getArea() << std::endl;
	}
}

int main()
{
	Testes();
	
	/*Database db;
	std::vector<Retangulo>retangulos;

	db.connect(connectionString);

	int linhas = db.executeCountQuery("SELECT COUNT(*) FROM [ATV_RETANGULO].[dbo].[Retangulo]");

	for (int i = 0; i < linhas; i++)
	{
		std::string query =
			"SELECT base, altura "
			"FROM ( "
			"  SELECT base, altura, ROW_NUMBER() OVER (ORDER BY id ASC) AS linha "
			"  FROM Retangulo "
			") AS t "
			"WHERE linha = " + std::to_string(i + 1) + ";";

		std::vector<int> valores = db.executeSelectQuery(query);

		if (valores.size() == 2) 
		{
			Retangulo retangulo(valores[0], valores[1]);
			retangulos.push_back(retangulo);
		}
		else 
		{
			std::cerr << "Erro ao obter dados do retangulo na linha " << i + 1 << std::endl;
		}
	}

	exibeRetangulos(retangulos);*/

	return 0;
}