#include <stdlib.h>
#include <stdio.h>

void GAME_DEBUG();
void GAME_EXECUTE();

enum type_cards
{
	Dragon = 1,
	Mage = 2,
	Warrior = 3,
	Barbarian = 4,
	Knight = 5,
	Demon = 6,
	NONE = 7
};

/*enum scenes
{
	Menu = 1,
	DeckSelector = 2,
	Game = 2
};*/

struct Cards
{
	char name[32];
	type_cards type;
	int health;
	int attack;
	int defense;
};

Cards null_card = { "NONE",type_cards::NONE,10,NULL };

Cards cards_game[4] = {
	Cards{
		"Dragon Blue Eyes",
		type_cards::Dragon,
		10,
		0
	},
	Cards{
		"Diablo",
		type_cards::Demon,
		12,
		0
	},
	Cards{
		"Barbarian Elite",
		type_cards::Barbarian,
		20,
		0
	},
	Cards {
		"Dragon Fire Elite",
		type_cards::Dragon,
		25,
		0
	}

};

struct Player
{
	Cards deck[sizeof(cards_game) / sizeof(cards_game[0])] = {	};
	int player_scene;
	int health;

};


int main()
{
	GAME_DEBUG();

	system("pause");
	return 0;
}


void GAME_EXECUTE()
{
	Player jogador;
	for (int i = 0; i < sizeof(cards_game) / sizeof(cards_game[0]); i++) {
		jogador.deck[i] = null_card;
	}

	jogador.player_scene = 0;
	jogador.health = 100;
	int cpuhealth = 100;
	//P C
	int Vez[] = { 0,1 };
	int ArvoreDecisao[] = { 0,0,0,0 };

	int SelectedMenu = 1;
	char InputPlayer;
	system("cls");
	while (true) {

		if (jogador.player_scene == 0) {
			system("cls");
			if (SelectedMenu == 1) {
				printf("\t\t\t\tMenu\n\n\t\t\t\tPress \'g\' for select option.\n\t\t\t\tPress \'s\' or \'w\' to navigate in options.\n\n\n\n\n");
				printf("\t\t\t\t---> Play With IA\n");
				printf("\t\t\t\tDeck Editor\n");
				printf("\t\t\t\t----------------\n");
			}
			else if (SelectedMenu == 2) {
				printf("\t\t\t\tMenu\n\n\t\t\t\tPress \'g\' for select option.\n\t\t\t\tPress \'s\' or \'w\' to navigate in options.\n\n\n\n\n");
				printf("\t\t\t\tPlay With IA\n");
				printf("\t\t\t\t---> Deck Editor\n");
				printf("\t\t\t\t----------------\n");
			}
			InputPlayer = getchar();
			if (InputPlayer == 's' || InputPlayer == 'S') {
				if (SelectedMenu == 1) {
					system("cls");
					SelectedMenu = 2;
				}
				else if (SelectedMenu == 2) {
					system("cls");
					SelectedMenu = 1;
				}
			}
			if (InputPlayer == 'w' || InputPlayer == 'W') {
				if (SelectedMenu == 2) {
					system("cls");
					SelectedMenu = 1;
				}
				else if (SelectedMenu == 1) {
					system("cls");
					SelectedMenu = 2;
				}
			}

			if (InputPlayer == 'g' || InputPlayer == 'p') {
				if (SelectedMenu == 1) {
					system("cls");
					jogador.player_scene = 2;
					SelectedMenu = 1;
				}
				if (SelectedMenu == 2) {
					system("cls");
					jogador.player_scene = 1;
					SelectedMenu = 1;
				}
			}
		}
		if (jogador.player_scene == 1) {
			system("cls");
			printf("\t\t\t\tDeckSelector\n\n");
			printf("\t\t\t\twrite \'r\' to random deck\n\t\t\t\tPress \'<\' to back.\n");

			printf("\t\tAll Cards\n\n\n");
			for (int i = 0; i < sizeof(cards_game) / sizeof(cards_game[0]); i++) {
				printf("\t\t------------------------\n");
				printf("\t\t(%i) %s\n", i, cards_game[i].name);
			}
			printf("\n\n\n\t\t\t\tYou Deck\n\n");
			for (int i = 0; i < sizeof(jogador.deck) / sizeof(jogador.deck[0]); i++) {
				printf("\t\t\t\t------------------------\n");
				printf("\t\t\t\t(%i) %s\n", i, jogador.deck[i].name);
			}
			printf("\t\t\t\t------------------------\n");




			InputPlayer = getchar();

			if (InputPlayer == 'r') {
				for (int i = 0; i < sizeof(jogador.deck) / sizeof(jogador.deck[0]); i++) {
					int r = rand() % sizeof(jogador.deck) / sizeof(jogador.deck[0]);
					jogador.deck[i] = cards_game[r];
				}

			}


			if (InputPlayer == '<')
				jogador.player_scene = 0;
		}
		if (jogador.player_scene == 2) {
			//printf("\t\t\t\tGame\n\n");
			//printf("\t\t\t\t----------------\n");

			if (jogador.health > 0 && cpuhealth > 0) {
				if (Vez[0] == 1) {
					InputPlayer = getchar();
					if (InputPlayer != NULL) {
						for (int i = 0; i < 5; i++) {
							ArvoreDecisao[i] = rand() % 10 + 1;
							//	printf("%i \n", ArvoreDecisao[i]);
						}
						if (ArvoreDecisao[0] > ArvoreDecisao[1] && ArvoreDecisao[0] > ArvoreDecisao[2] && ArvoreDecisao[0] > ArvoreDecisao[3]) {
							system("cls");
							int atk = rand() % 10 + jogador.deck[0].attack;
							cpuhealth = cpuhealth - atk;
							printf("Player Card [%s] Attack...\nDMG: %i\n", jogador.deck[0].name, atk);
							Vez[1] = 1;
							Vez[0] = 0;

						}
						if (ArvoreDecisao[1] > ArvoreDecisao[2] && ArvoreDecisao[1] > ArvoreDecisao[3]) {
							system("cls");
							int atk = rand() % 10 + jogador.deck[1].attack;
							cpuhealth = cpuhealth - atk;
							printf("Player Card [%s] Attack...\nDMG: %i\n", jogador.deck[1].name, atk);
							Vez[1] = 1;
							Vez[0] = 0;
						}
						if (ArvoreDecisao[2] > ArvoreDecisao[1] && ArvoreDecisao[2] > ArvoreDecisao[3]) {
							system("cls");
							int atk = rand() % 10 + jogador.deck[2].attack;
							cpuhealth = cpuhealth - atk;
							printf("Player Card [%s] Attack...\nDMG: %i\n", jogador.deck[2].name, atk);
							Vez[1] = 1;
							Vez[0] = 0;
						}
						if (ArvoreDecisao[3] > ArvoreDecisao[1] && ArvoreDecisao[3] > ArvoreDecisao[2]) {
							system("cls");
							int atk = rand() % 10 + jogador.deck[1].attack;
							cpuhealth = cpuhealth - atk;
							printf("Player Card [%s] Attack...\nDMG: %i\n", jogador.deck[3].name, atk);
							Vez[1] = 1;
							Vez[0] = 0;
						}
					}
				}


				if (Vez[1] == 1) {
					printf("CPU Playing...\n");
					for (int i = 0; i < 5; i++) {
						ArvoreDecisao[i] = rand() % 10 + 1;
						//	printf("%i \n", ArvoreDecisao[i]);
					}
					if (ArvoreDecisao[0] > ArvoreDecisao[1] && ArvoreDecisao[0] > ArvoreDecisao[2] && ArvoreDecisao[0] > ArvoreDecisao[3]) {
						system("cls");
						int atk = rand() % 10 + 1;
						jogador.health = jogador.health - atk;
						printf("CPU Attack...\nDMG: %i\n", atk);
						Vez[0] = 1;
						Vez[1] = 0;
					}
					if (ArvoreDecisao[1] > ArvoreDecisao[2] && ArvoreDecisao[1] > ArvoreDecisao[3]) {
						system("cls");
						int atk = rand() % 10 + 1;
						jogador.health = jogador.health - atk;
						printf("CPU Attack...\nDMG: %i\n", atk);
						Vez[0] = 1;
						Vez[1] = 0;
					}
					if (ArvoreDecisao[2] > ArvoreDecisao[1] && ArvoreDecisao[2] > ArvoreDecisao[3]) {
						system("cls");
						int atk = rand() % 10 + 1;
						jogador.health = jogador.health - atk;
						printf("CPU Attack...\nDMG: %i\n", atk);
						Vez[0] = 1;
						Vez[1] = 0;
					}
					if (ArvoreDecisao[3] > ArvoreDecisao[1] && ArvoreDecisao[3] > ArvoreDecisao[2]) {
						system("cls");
						int atk = rand() % 10 + 1;
						jogador.health = jogador.health - atk;
						printf("CPU Attack...\nDMG: %i\n", atk);
						Vez[0] = 1;
						Vez[1] = 0;
					}
				}


				printf("\n\n\n\n\n\t\t\t CPU: %i\n\t\t\tPLAYER: %i\n", cpuhealth, jogador.health);
			}


			if (jogador.health <= 0) {
				system("cls");
				printf("You Lose, say < for exit. \n\n\n");
			}
			if(cpuhealth <= 0){
				system("cls");
				printf("You Win, say < for exit. \n\n\n");
			}

			InputPlayer = getchar();


			if (InputPlayer == '<' && jogador.health <=0 || InputPlayer == '<' && cpuhealth <= 0)
			{
				jogador.health = 0;
				cpuhealth = 0;
				jogador.health = 100;
				cpuhealth = 100;
				jogador.player_scene = 0;
			}

		}

	}
}

void GAME_DEBUG()
{
	system("COLOR F0");
	char b;
	int i;
	printf("\t\t\t\t RampgeCards RPG Game\n\t\t\t\t %i Cards Loaded.\n\n", sizeof(cards_game) / sizeof(cards_game[0]));
	for (i = 0; i < sizeof(cards_game) / sizeof(cards_game[0]); i++) {
		printf("\t\t\t\t----------------\n");
		printf("\t\t\t\t(%i) %s\n", i, cards_game[i].name);
	}
	printf("\n\n\n\n");
	printf("Press one input to enter in game...");
	b = getchar();
	if (b >= 0) {
		GAME_EXECUTE();
	}
}