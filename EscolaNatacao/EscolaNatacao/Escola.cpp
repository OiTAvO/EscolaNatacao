// Programa Escola de Natação - Prova B1 - 08/04/2015 - Turma da Noite
//
#include "Escola.h"
//	Entry point do programa
//
void main(void)
{
	int nPeriodo,								// periodo da aula de natação
		nRaia,									// raia da piscina
		iIndRaia,								// indice da raia calculada
		nQtdeParentes,							// quantidade de parentes para desconto
		nQtdeRaiasPiscina,						// para receber a quantidade de raias que a piscina tem
		nQtdeTotalDeRaias,						// qtde total de raias nos três períodos
		i, j;									// índices genéricos
	double dValorMensalidade;					// para calcular a mensalidade
	char cOpcao,								// opcao do operador
		cNomeAluno[] = "OTAVIO AUGUSTO MARINHO PORTO",
		cRA_Aluno[] = "1840481623024",
		cSobrenome[TAMANHO_SOBRENOME + 1],		// para receber o sobrenome
		cWork[200];								// para sprintf
	SYSTEMTIME stTime;							// para data e hora do sistema
	char vetNomesPeriodos[QTDE_PERIODOS][7] =
	{ "Manhã", "Tarde", "Noite" };
	// vetores dos periodos e raias das piscinas
	// vetor que indica se raia livre ou ocupada - true - indica ocupada, false - indica que a raia está livre
	bool vetRaiaLivreOcupada[QTDE_PERIODOS * QTDE_MAXIMA_RAIAS_PISCINA];
	// vetor de sobrenomes dos alunos matriculados
	char vetSobrenomesAlunos[QTDE_PERIODOS * QTDE_MAXIMA_RAIAS_PISCINA][TAMANHO_SOBRENOME + 1];
	double vetMensalidades[QTDE_PERIODOS * QTDE_MAXIMA_RAIAS_PISCINA];
	// para duas casas decimais nos valores
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
	setlocale(LC_ALL, "portuguese_brazil");		// para acentuação brasileira
												// <<<1>>> - Preencher as variáveis com seu nome e RA
												// <<<2>>> - ficar em loop pedindo a quantidade de raias que tem a piscina
												//				esta quantidade tem que ser entre a quantidade mínima e máxima ou
												//				zeros para cancelar a execução do programa
												//				nQtdeRaiasPiscina é a variável que receberá a quantidade de raias que tem a piscina
												//				Se nQtdeRaiasPiscina for zero -->> cancelar a execução do programa
												//	<<<3>>> - Em nQtdeTotalDeRaias calcular total de alunos que a escola de natação considerando a
												//				quantidade de períodos e de raias que a piscina tem.
												//
												// <<<4>>> - Fazer um loop indicando que todas as raias de todos os períodos 
												//			 estão desocupadas
												//
												// Codificar o loop que indica que todas as raias de todos os períodos estão livres
												//  ????????????????????????????


												//
	do
	{
		cout << "Informe a QTDE de raias (valores entre " << QTDE_MINIMA_RAIAS_PISCINA << " e "
			<< QTDE_MAXIMA_RAIAS_PISCINA << ") ou ZERO para cancelar o prog: ";
		cin >> nQtdeRaiasPiscina;
		if (nQtdeRaiasPiscina == 0)
			return;
	} while (nQtdeRaiasPiscina<QTDE_MINIMA_RAIAS_PISCINA || nQtdeRaiasPiscina>QTDE_MAXIMA_RAIAS_PISCINA);

	for (i = 0, nQtdeTotalDeRaias = nQtdeRaiasPiscina * QTDE_PERIODOS; i < nQtdeTotalDeRaias; i++)
		vetRaiaLivreOcupada[i] = false;
	//



	//	Loop Infinito
	while (true)
	{
		LIMPAR_TELA;
		GetLocalTime(&stTime);						// data e hora do sistema
		sprintf_s(cWork, sizeof(cWork),
			"\tFATEC-Escola de Natação %02d/%02d/%04d às %02d:%02d:%02d\n\tOperador: %s Matrícula: %s",
			stTime.wDay, stTime.wMonth, stTime.wYear,
			stTime.wHour, stTime.wMinute, stTime.wSecond,
			cNomeAluno, cRA_Aluno);
		cout << cWork << endl;
		// exibir o menu
		cout << MATRICULAR_ALUNO << " - Matricular aluno em um período desejado" << endl
			<< CANCELAR_MATRICULA << " - Cancelar a matrícula de um aluno" << endl
			<< LISTAR_PERIODO << " - Listar os alunos de um dado período" << endl
			<< SAIR_DO_PROGRAMA << " - Sair do programa" << endl
			<< "\tSelecione: ";
		cin >> cOpcao;
		cOpcao = toupper(cOpcao);					// converte para maiúscula
		switch (cOpcao)								// avalia a opção escolhida
		{
		case MATRICULAR_ALUNO:
			// <<<5>>> - pedir um período válido (desejado pelo aluno)
			// <<<6>>> - chamar a função que verifica se tem uma raia livre no
			//			 período desejado e se não houver uma livre, esta função, devolve zero e
			//			 caso contrário, devolve o número da raia livre no período desejado
			//			 Se não houver uma raia livre cancelar esta ação de matricular aluno
			//				(volta ao menu principal)
			// <<<7>>> - pedir o sobrenome do aluno sendo matriculado.
			//			 verificar se existe o mesmo sobrenome nas raias ocupadas. Para
			//			 cada parente encontrado será dado um desconto de 5% limitado ao
			//			 máximo de 20%.
			//			 Assim: Se houver um só ou o primeiro aluno a mensalidade é cheia (100%); 
			//			  se houver mais um 10% de desconto, se houver
			//				mais um 20%; mais um 30% e apartir quarto todos terão 40% de desconto
			// <<<8>>>	Associar este aluno ao período e à raia desejada (ocupar a raia com a bool true
			//			no vetor de livre/ocupada, sobrenome que está nesta raia, valor da mensalidade 
			//			Voltar ao menu 

			nPeriodo = PedirPeriodo(QTDE_PERIODOS, "Matricular Aluno");
			if (nPeriodo == 0)					// cancelou a ação?
				break;							// cai fora do switch
												// chamar a função que vê se tem raia livre neste periodo
			nRaia = BuscarRaiaLivreNoPeriodo(&vetRaiaLivreOcupada[0], nPeriodo, nQtdeRaiasPiscina);

			// verificar se não tem raia livre neste periodo
			if (nRaia == 0)						// não tem raia livre?
			{	// não tem raia livre neste período
				cout << "Não tem vaga no periodo da " << vetNomesPeriodos[nPeriodo - 1] << endl;
				PAUSA;
				break;
			}
			// calcular o indice desta raia para saber a posição dentro dos vetores
			//iIndRaia = ????????????????????????????????????;
			iIndRaia = (nPeriodo - 1) * nQtdeRaiasPiscina + (nRaia - 1);


			// Pedir o sobrenome que pode ter mais de uma palavra
			cout << "Digite o Sobrenome do aluno: ";
			cin.ignore(1, EOF);
			cin.getline(cSobrenome, 15, '\n');
			for (i = 0; i < TAMANHO_SOBRENOME; i++)
				cSobrenome[i] = toupper(cSobrenome[i]);
			//cout << vetSobrenomesAlunos[iIndRaia] << endl;
			// loop para cálculo da mensalidade do aluno
			for (i = 0, nQtdeParentes = 0; i < nQtdeTotalDeRaias; i++)
			{
				if (strcmp(cSobrenome, vetSobrenomesAlunos[i]) == 0)
					nQtdeParentes++;
			}
			//strcpy_s(vetSobrenomesAlunos[iIndRaia], sizeof(vetSobrenomesAlunos[iIndRaia]), cSobrenome);
			// sabemos quantos parentes tem
			//  Calcular o valor da mensalidade e armazenar no valor da
			//		mensalidade dentro do vetor de mensalidades
			// ???????????????????????????????
			if (nQtdeParentes > 4)
				nQtdeParentes = 4;
			cout << nQtdeParentes << endl;
			dValorMensalidade = ((100-(nQtdeParentes*VALOR_DESCONTO_POR_PARENTE))*VALOR_MENSALIDADE)/100;
			vetMensalidades[iIndRaia] = dValorMensalidade;
			//
			vetRaiaLivreOcupada[iIndRaia] = true;						// indica raia ocupada
			strcpy_s(&vetSobrenomesAlunos[iIndRaia][0], TAMANHO_SOBRENOME, cSobrenome);
			//cout << vetSobrenomesAlunos[iIndRaia] << " e " << vetMensalidades[iIndRaia] << endl;
			cout << "O aluno está matriculado no período " << vetNomesPeriodos[nPeriodo - 1] <<
				" Raia: " << nRaia << endl;
			PAUSA;
			break;								// cai fora do switch
		case CANCELAR_MATRICULA:
			// <<<9>>>  Chamar a função que pede o periodo e a raia indicando que a ação é
			//			Cancelamento de Matrícula
			// <<<10>>> Verificar se a raia está ocupada e se estiver livre avisar ao operador e
			//			cancelar está ação voltando ao menu
			//			Se a raia estiver ocupada exibir o sobrenome, valor da matrícula
			// <<<11>>> Pedir a confirmação do cancelamento da matrícula e havendo a confirmação
			//			apenas indicar que está raia deste periodo está livre. Caso contrário
			//			voltar ao menu principal
			break;								// cai fora do switch



		case LISTAR_PERIODO:
			//dddd
			// <<<15>>> Pedir um período válido ou zero para cancelar a ação de listar
			//			Se foi informado um período válido listar todos as raias ocupadas
			//			no seguinte formato:
			//				Listagem das raias do periodo: ppppppp
			//			Raia Sobrenome  Mensalidade 
			//			 RR  SSSSSSSSS  MMMMMM,MM	
			//			.....
			//			.....
			//					       Total das Mensalidades: TTTTTT,TT
			//			Onde: PPPPPPP - periodo: "Manhã", "Tarde" ou "Noite"
			//				  RR - raia ocupada ( 1 a Qtde de Raias da Piscina)
			//				  SSSSSSSSS - sobrenome do aluno
			//				  MMMMM - valor da mensalidade
			//				  TTTTTTT = somatória das mensalidades dos alunos matriculados
			//	<<<16>>> Pausa para visualização e voltar ao menu
			//sprintf(cWork, "%2d %-15s %8.2f", int(referente a raia), char (referente sobrenome), double
			//	(referente ao valor da mensalidade);
			PAUSA;
			break;								// cai fora do switch
		case SAIR_DO_PROGRAMA:
			cout << "Vai sair realmente? (S ou N): ";
			cin >> cOpcao;
			if (cOpcao == 's' || cOpcao == 'S')	// sair realmente?
				return;
			break;								// cai fora do switch
		default:
			cout << "Opção inválida!" << endl;
			PAUSA;
		} // switch
	} // while
} // main
  // 
  // Funções do Programa
  //
  // Função que pede um período válido e uma raia da piscina válida
  // Parâmetros:
  //	Entrada: int *ptrPeriodo - ponteiro para receber o período desejado
  //			 int *ptrRaia - ponteiro para receber a raia da piscina desejada
  //			 int nQtdePeriodos - quantidade de períodos da Escola de Natação
  //			 int nQtRaiasPiscina - quantidade de raias que tem a piscina da Escola de Natação
  //			 char *ptrAcao - ponteiro de um string que contém a ação que está sendo executada
  //	Retorno: bool - true - indica que foi informado um período e uma raia válidos
  //					false - indica que o operador desistiu da ação que iria executar:
bool PedirPeriodoRaia(int *ptrPeriodo, int *ptrRaia,
	int nQtdePeriodos, int nQtRaiasPiscina, char *ptrAcao)
{
	do
	{
		cout << "\n\t" << ptrAcao << endl;
		cout << "Informe o período desejado " << endl <<
			"\t1 - Manhã" << endl << "\t2 - Tarde" << endl << "\t3 - Noite" << endl
			<< "Ou zero para cancelar está ação: ";
		cin >> *(ptrPeriodo);
		if (*(ptrPeriodo) == 0)				// cancelou a ação
			return false;					// indica que cancelou
	} while (*(ptrPeriodo) < PERIODO_MANHA ||
		*(ptrPeriodo) > nQtdePeriodos);
	do
	{
		cout << "Informe a raia entre 1 e " << nQtRaiasPiscina << endl
			<< "Ou zero para cancelar a execução desta ação: ";
		cin >> *(ptrRaia);
		if (*(ptrRaia) == 0)					// cancelou a ação?
			return false;
	} while (*(ptrRaia) < 1 ||
		*(ptrRaia) > nQtRaiasPiscina);
	return true;							// indica que foi digitado um período e uma raia
}
//
// Função que verifica se tem uma raia livre no período desejado
//	Parâmetros:
//		Entrada: bool *ptrVetLivreOcup - ponteiro do vetor de bool que indica se a raia está 
//										 livre ou ocupada
//				 int nPeriodo - período desejado
//				 int nQtRaiasPiscina - quantidade de raia que a piscina tem
//		Retorno: int - Número da raia que está livre ou zero se não existir nenhuma
//						raia livre no período desejado
int BuscarRaiaLivreNoPeriodo(bool *ptrVetLivreOcup, int nPeriodo, int nQtRaiasPiscina)
{
	int i, j;							// indices genéricos
	for (i = (nPeriodo - 1) * nQtRaiasPiscina, j = 0; j < nQtRaiasPiscina; j++, i++)
	{
		if (!*(ptrVetLivreOcup + i))		// raia livre?
			return (j + 1);				// retornar a raia livre
	}
	return 0;							// não tem raia livre no período
}

// Função que pede um período válido ou zero para cancelar a ação
//	Parâmetros:
//		Entrada: int nQtdePeriodos - quantidade de períodos da escola de natação
//				 char *ptrAcao - ponteiro para uma string que contem a ação sendo executada
//		Retorno: int - o período desejado ou zero para cancelar a ação
int PedirPeriodo(int nQtdePeriodos, char *ptrAcao)
{
	int nPeriodo;									// para receber o periodo
	do
	{
		cout << "\n\t" << ptrAcao << endl;
		cout << "Informe o período desejado " << endl <<
			"\t1 - Manhã" << endl << "\t2 - Tarde" << endl << "\t3 - Noite" << endl
			<< "Ou zero para cancelar está ação: ";
		cin >> nPeriodo;
	} while (nPeriodo < 0 || nPeriodo > nQtdePeriodos);
	// devolver o que foi válido digitado
	return nPeriodo;								// devolve o digitado
}
