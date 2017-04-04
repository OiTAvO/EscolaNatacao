// Programa Escola de Nata��o - Prova B1 - 08/04/2015 - Turma da Noite
//
#include "Escola.h"
//	Entry point do programa
//
void main(void)
{
	int nPeriodo,								// periodo da aula de nata��o
		nRaia,									// raia da piscina
		iIndRaia,								// indice da raia calculada
		nQtdeParentes,							// quantidade de parentes para desconto
		nQtdeRaiasPiscina,						// para receber a quantidade de raias que a piscina tem
		nQtdeTotalDeRaias,						// qtde total de raias nos tr�s per�odos
		i, j;									// �ndices gen�ricos
	double dValorMensalidade;					// para calcular a mensalidade
	char cOpcao,								// opcao do operador
		cNomeAluno[] = "OTAVIO AUGUSTO MARINHO PORTO",
		cRA_Aluno[] = "1840481623024",
		cSobrenome[TAMANHO_SOBRENOME + 1],		// para receber o sobrenome
		cWork[200];								// para sprintf
	SYSTEMTIME stTime;							// para data e hora do sistema
	char vetNomesPeriodos[QTDE_PERIODOS][7] =
	{ "Manh�", "Tarde", "Noite" };
	// vetores dos periodos e raias das piscinas
	// vetor que indica se raia livre ou ocupada - true - indica ocupada, false - indica que a raia est� livre
	bool vetRaiaLivreOcupada[QTDE_PERIODOS * QTDE_MAXIMA_RAIAS_PISCINA];
	// vetor de sobrenomes dos alunos matriculados
	char vetSobrenomesAlunos[QTDE_PERIODOS * QTDE_MAXIMA_RAIAS_PISCINA][TAMANHO_SOBRENOME + 1];
	double vetMensalidades[QTDE_PERIODOS * QTDE_MAXIMA_RAIAS_PISCINA];
	// para duas casas decimais nos valores
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
	setlocale(LC_ALL, "portuguese_brazil");		// para acentua��o brasileira
												// <<<1>>> - Preencher as vari�veis com seu nome e RA
												// <<<2>>> - ficar em loop pedindo a quantidade de raias que tem a piscina
												//				esta quantidade tem que ser entre a quantidade m�nima e m�xima ou
												//				zeros para cancelar a execu��o do programa
												//				nQtdeRaiasPiscina � a vari�vel que receber� a quantidade de raias que tem a piscina
												//				Se nQtdeRaiasPiscina for zero -->> cancelar a execu��o do programa
												//	<<<3>>> - Em nQtdeTotalDeRaias calcular total de alunos que a escola de nata��o considerando a
												//				quantidade de per�odos e de raias que a piscina tem.
												//
												// <<<4>>> - Fazer um loop indicando que todas as raias de todos os per�odos 
												//			 est�o desocupadas
												//
												// Codificar o loop que indica que todas as raias de todos os per�odos est�o livres
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
			"\tFATEC-Escola de Nata��o %02d/%02d/%04d �s %02d:%02d:%02d\n\tOperador: %s Matr�cula: %s",
			stTime.wDay, stTime.wMonth, stTime.wYear,
			stTime.wHour, stTime.wMinute, stTime.wSecond,
			cNomeAluno, cRA_Aluno);
		cout << cWork << endl;
		// exibir o menu
		cout << MATRICULAR_ALUNO << " - Matricular aluno em um per�odo desejado" << endl
			<< CANCELAR_MATRICULA << " - Cancelar a matr�cula de um aluno" << endl
			<< LISTAR_PERIODO << " - Listar os alunos de um dado per�odo" << endl
			<< SAIR_DO_PROGRAMA << " - Sair do programa" << endl
			<< "\tSelecione: ";
		cin >> cOpcao;
		cOpcao = toupper(cOpcao);					// converte para mai�scula
		switch (cOpcao)								// avalia a op��o escolhida
		{
		case MATRICULAR_ALUNO:
			// <<<5>>> - pedir um per�odo v�lido (desejado pelo aluno)
			// <<<6>>> - chamar a fun��o que verifica se tem uma raia livre no
			//			 per�odo desejado e se n�o houver uma livre, esta fun��o, devolve zero e
			//			 caso contr�rio, devolve o n�mero da raia livre no per�odo desejado
			//			 Se n�o houver uma raia livre cancelar esta a��o de matricular aluno
			//				(volta ao menu principal)
			// <<<7>>> - pedir o sobrenome do aluno sendo matriculado.
			//			 verificar se existe o mesmo sobrenome nas raias ocupadas. Para
			//			 cada parente encontrado ser� dado um desconto de 5% limitado ao
			//			 m�ximo de 20%.
			//			 Assim: Se houver um s� ou o primeiro aluno a mensalidade � cheia (100%); 
			//			  se houver mais um 10% de desconto, se houver
			//				mais um 20%; mais um 30% e apartir quarto todos ter�o 40% de desconto
			// <<<8>>>	Associar este aluno ao per�odo e � raia desejada (ocupar a raia com a bool true
			//			no vetor de livre/ocupada, sobrenome que est� nesta raia, valor da mensalidade 
			//			Voltar ao menu 

			nPeriodo = PedirPeriodo(QTDE_PERIODOS, "Matricular Aluno");
			if (nPeriodo == 0)					// cancelou a a��o?
				break;							// cai fora do switch
												// chamar a fun��o que v� se tem raia livre neste periodo
			nRaia = BuscarRaiaLivreNoPeriodo(&vetRaiaLivreOcupada[0], nPeriodo, nQtdeRaiasPiscina);

			// verificar se n�o tem raia livre neste periodo
			if (nRaia == 0)						// n�o tem raia livre?
			{	// n�o tem raia livre neste per�odo
				cout << "N�o tem vaga no periodo da " << vetNomesPeriodos[nPeriodo - 1] << endl;
				PAUSA;
				break;
			}
			// calcular o indice desta raia para saber a posi��o dentro dos vetores
			//iIndRaia = ????????????????????????????????????;
			iIndRaia = (nPeriodo - 1) * nQtdeRaiasPiscina + (nRaia - 1);


			// Pedir o sobrenome que pode ter mais de uma palavra
			cout << "Digite o Sobrenome do aluno: ";
			cin.ignore(1, EOF);
			cin.getline(cSobrenome, 15, '\n');
			for (i = 0; i < TAMANHO_SOBRENOME; i++)
				cSobrenome[i] = toupper(cSobrenome[i]);
			//cout << vetSobrenomesAlunos[iIndRaia] << endl;
			// loop para c�lculo da mensalidade do aluno
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
			cout << "O aluno est� matriculado no per�odo " << vetNomesPeriodos[nPeriodo - 1] <<
				" Raia: " << nRaia << endl;
			PAUSA;
			break;								// cai fora do switch
		case CANCELAR_MATRICULA:
			// <<<9>>>  Chamar a fun��o que pede o periodo e a raia indicando que a a��o �
			//			Cancelamento de Matr�cula
			// <<<10>>> Verificar se a raia est� ocupada e se estiver livre avisar ao operador e
			//			cancelar est� a��o voltando ao menu
			//			Se a raia estiver ocupada exibir o sobrenome, valor da matr�cula
			// <<<11>>> Pedir a confirma��o do cancelamento da matr�cula e havendo a confirma��o
			//			apenas indicar que est� raia deste periodo est� livre. Caso contr�rio
			//			voltar ao menu principal
			break;								// cai fora do switch



		case LISTAR_PERIODO:
			//dddd
			// <<<15>>> Pedir um per�odo v�lido ou zero para cancelar a a��o de listar
			//			Se foi informado um per�odo v�lido listar todos as raias ocupadas
			//			no seguinte formato:
			//				Listagem das raias do periodo: ppppppp
			//			Raia Sobrenome  Mensalidade 
			//			 RR  SSSSSSSSS  MMMMMM,MM	
			//			.....
			//			.....
			//					       Total das Mensalidades: TTTTTT,TT
			//			Onde: PPPPPPP - periodo: "Manh�", "Tarde" ou "Noite"
			//				  RR - raia ocupada ( 1 a Qtde de Raias da Piscina)
			//				  SSSSSSSSS - sobrenome do aluno
			//				  MMMMM - valor da mensalidade
			//				  TTTTTTT = somat�ria das mensalidades dos alunos matriculados
			//	<<<16>>> Pausa para visualiza��o e voltar ao menu
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
			cout << "Op��o inv�lida!" << endl;
			PAUSA;
		} // switch
	} // while
} // main
  // 
  // Fun��es do Programa
  //
  // Fun��o que pede um per�odo v�lido e uma raia da piscina v�lida
  // Par�metros:
  //	Entrada: int *ptrPeriodo - ponteiro para receber o per�odo desejado
  //			 int *ptrRaia - ponteiro para receber a raia da piscina desejada
  //			 int nQtdePeriodos - quantidade de per�odos da Escola de Nata��o
  //			 int nQtRaiasPiscina - quantidade de raias que tem a piscina da Escola de Nata��o
  //			 char *ptrAcao - ponteiro de um string que cont�m a a��o que est� sendo executada
  //	Retorno: bool - true - indica que foi informado um per�odo e uma raia v�lidos
  //					false - indica que o operador desistiu da a��o que iria executar:
bool PedirPeriodoRaia(int *ptrPeriodo, int *ptrRaia,
	int nQtdePeriodos, int nQtRaiasPiscina, char *ptrAcao)
{
	do
	{
		cout << "\n\t" << ptrAcao << endl;
		cout << "Informe o per�odo desejado " << endl <<
			"\t1 - Manh�" << endl << "\t2 - Tarde" << endl << "\t3 - Noite" << endl
			<< "Ou zero para cancelar est� a��o: ";
		cin >> *(ptrPeriodo);
		if (*(ptrPeriodo) == 0)				// cancelou a a��o
			return false;					// indica que cancelou
	} while (*(ptrPeriodo) < PERIODO_MANHA ||
		*(ptrPeriodo) > nQtdePeriodos);
	do
	{
		cout << "Informe a raia entre 1 e " << nQtRaiasPiscina << endl
			<< "Ou zero para cancelar a execu��o desta a��o: ";
		cin >> *(ptrRaia);
		if (*(ptrRaia) == 0)					// cancelou a a��o?
			return false;
	} while (*(ptrRaia) < 1 ||
		*(ptrRaia) > nQtRaiasPiscina);
	return true;							// indica que foi digitado um per�odo e uma raia
}
//
// Fun��o que verifica se tem uma raia livre no per�odo desejado
//	Par�metros:
//		Entrada: bool *ptrVetLivreOcup - ponteiro do vetor de bool que indica se a raia est� 
//										 livre ou ocupada
//				 int nPeriodo - per�odo desejado
//				 int nQtRaiasPiscina - quantidade de raia que a piscina tem
//		Retorno: int - N�mero da raia que est� livre ou zero se n�o existir nenhuma
//						raia livre no per�odo desejado
int BuscarRaiaLivreNoPeriodo(bool *ptrVetLivreOcup, int nPeriodo, int nQtRaiasPiscina)
{
	int i, j;							// indices gen�ricos
	for (i = (nPeriodo - 1) * nQtRaiasPiscina, j = 0; j < nQtRaiasPiscina; j++, i++)
	{
		if (!*(ptrVetLivreOcup + i))		// raia livre?
			return (j + 1);				// retornar a raia livre
	}
	return 0;							// n�o tem raia livre no per�odo
}

// Fun��o que pede um per�odo v�lido ou zero para cancelar a a��o
//	Par�metros:
//		Entrada: int nQtdePeriodos - quantidade de per�odos da escola de nata��o
//				 char *ptrAcao - ponteiro para uma string que contem a a��o sendo executada
//		Retorno: int - o per�odo desejado ou zero para cancelar a a��o
int PedirPeriodo(int nQtdePeriodos, char *ptrAcao)
{
	int nPeriodo;									// para receber o periodo
	do
	{
		cout << "\n\t" << ptrAcao << endl;
		cout << "Informe o per�odo desejado " << endl <<
			"\t1 - Manh�" << endl << "\t2 - Tarde" << endl << "\t3 - Noite" << endl
			<< "Ou zero para cancelar est� a��o: ";
		cin >> nPeriodo;
	} while (nPeriodo < 0 || nPeriodo > nQtdePeriodos);
	// devolver o que foi v�lido digitado
	return nPeriodo;								// devolve o digitado
}
