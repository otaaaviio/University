#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

void waitEnter() {
    cout << "Pressione Enter para continuar...";
    for(int i = 0; i < 2; i++)
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

class Player {
public:
    string name;
    string position;
    int age;
    int number;
    int goals;
    int yellowCards;
    int redCards;
    int fouls;

    Player(const string& _name, const string& _position, int _age, int _number) 
    : name(_name), position(_position), age(_age), number(_number),
          goals(0), yellowCards(0), redCards(0), fouls(0) {}

    Player* next;
};

class PlayerList {
public:
    Player* firstPlayer;

    PlayerList() : firstPlayer(nullptr) {}

    void addPlayer(Player* player) {
    Player* newPlayer = new Player(*player);
    newPlayer->next = nullptr;  
    if (firstPlayer == nullptr) {
        firstPlayer = newPlayer;  
    } else {
        Player* current = firstPlayer;
        while (current->next != nullptr) {
            current = current->next; 
        }
        current->next = newPlayer; 
    }
    delete player;
    cout << "Jogador adicionado com sucesso!" << endl;
    waitEnter();
    }
 
    void removePlayer(const string& playerName) {
        Player* current = firstPlayer;
        Player* previous = nullptr;

        while (current != nullptr && current->name != playerName) {
            previous = current;
            current = current->next;
        }

        if (current != nullptr) {
            if (previous != nullptr) {
                previous->next = current->next;
            } else {
                firstPlayer = current->next;
            }
            delete current;
            cout << "Jogador removido com sucesso!" << endl;
        } else {
            cout << "Jogador não encontrado." << endl;
        }
        waitEnter();
    }

    Player* findPlayer(const string& playerName) {
        Player* current = firstPlayer;
        while (current != nullptr) {
            if (current->name == playerName) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void sortedReportByGoalsOfPlayers() {
    if (firstPlayer == nullptr || firstPlayer->next == nullptr) {
        cout << "Sem jogadores cadastrados." << endl;
        waitEnter();
        return;
    }

    Player* current = firstPlayer;
    while (current != nullptr) {
        Player* minPlayer = current;
        Player* runner = current->next;
        while (runner != nullptr) {
            if (runner->goals < minPlayer->goals) {
                minPlayer = runner;
            }
            runner = runner->next;
        }

        Player temp = *current;
        *current = *minPlayer;
        *minPlayer = temp;

        current = current->next;
    }

    cout << "Relatório de artilharia:" << endl;
    current = firstPlayer;
    while(current != nullptr) {
        cout << "Jogador: " << current->name << endl;
        cout << "Número de gols no campeonato: " << current->goals << endl;
        cout << endl;

        current = current->next;
        }
    waitEnter();
    }

    void reportPlayers() {
        Player* current = firstPlayer;
        if(current == nullptr)
            cout << "Sem jogadores cadastrados." << endl;
        else
            cout << "Relatório de estatísticas (por jogador)." << endl;
        while(current != nullptr) {
            cout << "Jogador: " << current->name << endl;
            cout << "Gols feitos: " << current->goals << endl;
            cout << "Cartões amarelos: " << current->yellowCards << endl;
            cout << "Cartões vermelhos: " << current->redCards << endl;
            cout << "Faltas: " << current->fouls << endl;
            cout << endl;

            current = current->next;
        }
        waitEnter();
    }

    void removeAllPlayers() {
        Player* current = firstPlayer;
        while (current != nullptr) {
            Player* temp = current;
            current = current->next;
            delete temp;
        }
        firstPlayer = nullptr;  
    }
};

class Trainer {
    public:
    string name;

    Trainer(const string& _name) : name(_name) {}

    Trainer *next;
};

class TrainerList {
    public:
    Trainer *firstTrainer;

    TrainerList() : firstTrainer(nullptr) {}

    void addTrainer(Trainer* trainer) {
    Trainer* newTrainer = new Trainer(*trainer);
    newTrainer->next = nullptr;
    if (firstTrainer == nullptr) {
        firstTrainer = newTrainer;  
    } else {
        Trainer* current = firstTrainer;
        while (current->next != nullptr) {
            current = current->next; 
        }
        current->next = newTrainer; 
    }
    delete trainer;
    cout << "Treinador adicionado com sucesso!" << endl;
    waitEnter();
    }

    void removeTrainer(const string& trainerName) {
        Trainer* current = firstTrainer;
        Trainer* previous = nullptr;

        while (current != nullptr && current->name != trainerName) {
            previous = current;
            current = current->next;
        }

        if (current != nullptr) {
            if (previous != nullptr) {
                previous->next = current->next;
            } else {
                firstTrainer = current->next;
            }
            delete current;
            cout << "Treinador removido com sucesso!" << endl;
        } else {
            cout << "Treinador não encontrado." << endl;
        }
        waitEnter();
    }
    
    Trainer* searchTrainer(const string& trainerName) {
        Trainer* current = firstTrainer;
        bool found = false;
        while (current != nullptr) {
            if (current->name == trainerName) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
        }
 
    void removeAllTrainers() {
        Trainer* current = firstTrainer;
        while (current != nullptr) {
            Trainer* temp = current;
            current = current->next;
            delete temp;
        }
        firstTrainer = nullptr;  
    }
};

class Team {
public:
    string name;
    string stadium;
    string city;
    Trainer* firstTrainer;
    Player* firstPlayer;
    int goalsScored;
    int goalsConceded;
    int yellowCards;
    int redCards;
    int fouls;
    int wins;
    int defeats;
    int draws;

    Team(const string& _name, const string& _stadium, const string& _city, Trainer* _firstTrainer = nullptr)
        : name(_name), stadium(_stadium), city(_city), firstTrainer(_firstTrainer), firstPlayer(nullptr), goalsScored(0), goalsConceded(0), yellowCards(0), redCards(0), fouls(0), wins(0), defeats(0), draws(0) {}

    Team *next;

    int countPlayers() {
        int count = 0;
        Player* current = firstPlayer;
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }

    void addPlayerOnTeam(Player* player) {
        if (countPlayers() < 25) {
            Player* newPlayer = new Player(*player);
            newPlayer->next = firstPlayer;
            firstPlayer = newPlayer;
            cout << "Jogador adicionado ao time com sucesso!" << endl;
        } else {
            cout << "O time já possui o número máximo de jogadores (25)." << endl;
        }
        waitEnter();
    }

    void addTrainer(Trainer* trainer) {
        Trainer* newTrainer = new Trainer(*trainer);
        if(firstTrainer == nullptr){
            newTrainer->next = firstTrainer;
            firstTrainer = newTrainer;  
            cout << "Treinador adicionado ao time com sucesso!" << endl;
        } else {
            cout << "Equipe ja possui treinador" << endl;
        }
        waitEnter();
    }
};

class TeamList {
    public:
    Team *firstTeam;

    TeamList() : firstTeam(nullptr) {}

    void addTeam(Team* team) {
        Team* newTeam = new Team(*team);
        newTeam->next = nullptr;
        if(firstTeam == nullptr) {
            firstTeam = newTeam;
        } else {
            Team* current = firstTeam;
            while (current->next != nullptr) {
                current = current->next; 
            }
            current->next = newTeam; 
        }
        delete team;
        cout << "Time adicionado com sucesso!" << endl;
        waitEnter();
    }

    void removeTeam(const string& teamName) {
        Team* current = firstTeam;
        Team* previous = nullptr;

        while (current != nullptr && current->name != teamName) {
            previous = current;
            current = current->next;
        }

        if (current != nullptr) {
            if (previous != nullptr) {
                previous->next = current->next;
            } else {
                firstTeam = current->next;
            }
            delete current;
            cout << "Time removido com sucesso!" << endl;
        } else {
            cout << "Time não encontrado." << endl;
        }
        waitEnter();
    }
    
    Team* searchTeam(const string& teamName) {
        Team* current = firstTeam;
        while (current != nullptr) {
            if (current->name == teamName) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void reportSortedTeams() {
        if (firstTeam == nullptr || firstTeam->next == nullptr) {
            cout << "Sem times cadastrados." << endl;
            waitEnter();
            return;
        }

        Team* current = firstTeam;
        while (current != nullptr) {
            Team* minTeam = current;
            Team* runner = current->next;
            while (runner != nullptr) {
                int teamPoints = runner->wins * 3 + runner->draws;
                int minTeamPoints = minTeam->wins * 3 + minTeam->draws;
                if (teamPoints < minTeamPoints) {
                    minTeam = runner;
                }
                runner = runner->next;
            }

            Team temp = *current;
            *current = *minTeam;
            *minTeam = temp;

            current = current->next;
        }

        cout << "Classificação dos times:" << endl;
        cout << left << setw(20) << "Time";
        cout << setw(5) << "Pts";
        cout << setw(5) << "VIT";
        cout << setw(5) << "E";
        cout << setw(5) << "DER" << endl;
        current = firstTeam;
        while(current != nullptr) {
            int pts = current->wins * 3 + current->draws;
            cout << left << setw(20) << current->name;
            cout << setw(5) << pts;
            cout << setw(5) << current->wins;
            cout << setw(5) << current->draws;
            cout << setw(5) << current->defeats << endl;

            current = current->next;
            }
        waitEnter();
    }

    void reportTeams() {
        Team* current = firstTeam;
        if(current == nullptr)
            cout << "Sem times cadastrados." << endl;
        else
            cout << "Relatório de estatísticas (por time)." << endl;
        while(current != nullptr) {
            cout << "Time: " << current->name << endl;
            cout << "Gols feitos: " << current->goalsScored << endl;
            cout << "Gols sofridos: " << current->goalsConceded << endl;
            cout << "Cartões amarelos: " << current->yellowCards << endl;
            cout << "Cartões vermelhos: " << current->redCards << endl;
            cout << "Faltas cometidas: " << current->fouls << endl;
            cout << endl;

            current = current->next;
        }
        waitEnter();
    }
 
    void removeAllTeams() {
        Team* current = firstTeam;
        while (current != nullptr) {
            Team* temp = current;
            current = current->next;
            delete temp;
        }
        firstTeam = nullptr;  
    }
};

class Match {
    public:
    Team* homeTeam;
    Team* visitingTeam;

    Match(Team* _homeTeam, Team* _visitingTeam) : homeTeam(_homeTeam), visitingTeam(_visitingTeam) {}

    Match* next;
};

class MatchList {
    public:
    Match *firstMatch;
    MatchList* next;

    MatchList() : firstMatch(nullptr) {}

    void addMatch(Match* match) {
        Match* newMatch = new Match(*match);
        newMatch->next = nullptr;
        if(firstMatch == nullptr) {
            firstMatch = newMatch;
        } else {
            Match* current = firstMatch;
            while (current->next != nullptr) {
                current = current->next; 
            }
            current->next = newMatch; 
        }
        delete match;
        cout << "Partida adicionado com sucesso!" << endl;
        waitEnter();
    }

    void removeMatch(const string& homeTeamName, const string& visitingTeamName) {
        Match* current = firstMatch;
        Match* previous = nullptr;

        while (current != nullptr && (current->homeTeam->name != homeTeamName || current->visitingTeam->name != visitingTeamName)) {
            previous = current;
            current = current->next;
        }

        if (current != nullptr) {
            if (previous != nullptr) {
                previous->next = current->next;
            } else {
                firstMatch = current->next;
            }
            delete current;
            cout << "Partida removida com sucesso!" << endl;
        } else {
            cout << "Partida não encontrada." << endl;
        }
        waitEnter();
    }
    
    Match* searchMatch(const string& homeTeamName, const string& visitingTeamName) {
        Match* current = firstMatch;
        while (current != nullptr) {
            if (current->homeTeam->name == homeTeamName && current->visitingTeam->name == visitingTeamName) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void removeAllMatches() {
        Match* current = firstMatch;
        while (current != nullptr) {
            Match* temp = current;
            current = current->next;
            delete temp;
        }
        firstMatch = nullptr;  
    }
};

class RoundList {
    public:
    MatchList* firstMatchList;

    RoundList() : firstMatchList(nullptr) {}

    void addMatchList(MatchList* matchList) {
        MatchList* newMatchList = new MatchList(*matchList);
        newMatchList->next = nullptr;
        if (firstMatchList == nullptr) {
            firstMatchList = newMatchList;
        } else {
            MatchList* current = firstMatchList;
            while (current->next != nullptr) {
                current = current->next;
                cout << "Rodada cadastrada com sucesso.";
            }
            current->next = newMatchList;
        }
        delete matchList;
        waitEnter();
    }

    void removeAllMatchLists() {
        MatchList* current = firstMatchList;
        while (current != nullptr) {
            MatchList* temp = current;
            current = current->next;
            delete temp;
        }
        firstMatchList = nullptr;  
    }
};

void clear_screen() {
    cout << "\033[2J\033[1;1H";
}

void menu_players(PlayerList* playerList) {
    int select;
    Player* player;
    while(select != 6){
        clear_screen();
        cout << "Gerenciamento de jogadores" << endl;
        cout << "(1) Cadastrar novo jogador" << endl;
        cout << "(2) Remover jogador" << endl;
        cout << "(3) Procurar jogador" << endl;
        cout << "(4) Gerar relatório de estatísticas" << endl;
        cout << "(5) Gerar relatório de artilharia" << endl;
        cout << "(6) Voltar pro menu principal." << endl;
        cout << "Selecione uma opção: ";
        cin >> select;

        string name, position;
        int age, number;

        clear_screen();
        switch (select)
        {
        case 1:
            cout << "Digite o nome: "; cin >> name;
            cout << "Digite a posição: "; cin >> position;
            cout << "Digite a idade: "; cin >> age;
            cout << "Digite o numero da camisa: "; cin >> number;
            player = new Player(name, position, age, number);
            playerList->addPlayer(player);
            break;
        case 2:
            cout << "Digite o nome do jogador a ser removido: "; cin >> name;
            playerList->removePlayer(name);
            break;
        case 3:
            cout << "Digite o nome do jogador a ser procurado: "; cin >> name;
            player = playerList->findPlayer(name);
            cout << "Nome: " << player->name << endl;
            cout << "Posição: " << player->position << endl;
            cout << "Idade: " << player->age << endl;
            cout << "Número da camisa: " << player->number << endl;
            waitEnter();
            delete player;
            break;
        case 4:
            playerList->reportPlayers();
            break;
        case 5:
            playerList->sortedReportByGoalsOfPlayers();
            break;
        }
    }
}

void menu_trainers(TrainerList* trainerList) {
    int select;
    Trainer* trainer;
    while(select != 4){
        clear_screen();
        cout << "Gerenciamento de treinadores" << endl;
        cout << "(1) Cadastrar novo treinador" << endl;
        cout << "(2) Remover treinador" << endl;
        cout << "(3) Procurar treinador" << endl;
        cout << "(4) Voltar pro menu principal." << endl;
        cout << "Selecione uma opção: ";
        cin >> select;

        string name;
        clear_screen();
        switch (select)
        {
        case 1:
            cout << "Digite o nome: "; cin >> name;
            trainer = new Trainer(name);
            trainerList->addTrainer(trainer);
            break;
        case 2:
            cout << "Digite o nome do treinador a ser removido: "; cin >> name;
            trainerList->removeTrainer(name);
            break;
        case 3:
            cout << "Digite o nome do treinador a ser procurado: "; cin >> name;
            trainer = trainerList->searchTrainer(name);
            cout << "Nome: " << trainer->name << endl;
            waitEnter();
            delete trainer;
            break;
        }
    }
}

void manage_team(TeamList* teamList, PlayerList* playerList, TrainerList* trainerList) {
    clear_screen();
    string name;
    int select;
    Team* team;
    Player* player;
    Trainer* trainer;
    cout << "Digite o nome do time a ser gerenciado: "; cin >> name;
    team = teamList->searchTeam(name);

    if(team != nullptr)
        while(select != 3) {
            clear_screen();
            cout << "(1) Adicionar jogador já existente" << endl;
            cout << "(2) Adicionar Treinador já existente" << endl;
            cout << "(3) Voltar." << endl;
            cout << "Selecione uma opção: "; cin >> select;

            clear_screen();
            switch (select)
            {
            case 1:
                cout << "Digite o nome do jogador: "; cin >> name;
                player = playerList->findPlayer(name);
                if(player != nullptr)
                    team->addPlayerOnTeam(player);
                break;
            case 2:
                cout << "Digite o nome do treinador: "; cin >> name;
                trainer = trainerList->searchTrainer(name);
                if(trainer != nullptr)
                    team->addTrainer(trainer);
                break;
            }
        }
}

void menu_teams(TeamList* teamList, PlayerList* playerList, TrainerList* trainerList) {
    int select;
    Team* team;
    while(select != 7){
        clear_screen();
        cout << "Gerenciamento de times" << endl;
        cout << "(1) Cadastrar novo time" << endl;
        cout << "(2) Remover time" << endl;
        cout << "(3) Procurar time" << endl;
        cout << "(4) Vizualizar classificação geral dos times" << endl;
        cout << "(5) Gerar relatório de estatísticas" << endl;
        cout << "(6) Gerenciar time especifico" << endl;
        cout << "(7) Voltar pro menu principal." << endl;
        cout << "Selecione uma opção: ";
        cin >> select;

        string name, stadium, city;
        clear_screen();
        switch (select)
        {
        case 1:
            cout << "Digite o nome: "; cin >> name;
            cout << "Digite o nome do estádio: "; cin >> stadium;
            cout << "Digite o nome da cidade: "; cin >> city;
            team = new Team(name, stadium, city);
            teamList->addTeam(team);
            break;
        case 2:
            cout << "Digite o nome do time a ser removido: "; cin >> name;
            teamList->removeTeam(name);
            break;
        case 3:
            cout << "Digite o nome do time a ser procurado: "; cin >> name;
            team = teamList->searchTeam(name);
            cout << "Nome: " << team->name << endl;
            cout << "Estádio: " << team->stadium << endl;
            cout << "Cidade: " << team->city << endl;
            waitEnter();
            delete team;
            break;
        case 4:
            teamList->reportSortedTeams();
            break;
        case 5:
            teamList->reportTeams();
            break;
        case 6:
            manage_team(teamList, playerList, trainerList);
            break;
        }
    }
}

void new_match(MatchList* matchList, TeamList* teamList, PlayerList* playerList) {
    clear_screen();
    Team* homeTeam = nullptr;
    Team* visitingTeam = nullptr;
    Player* player;
    Match* match;
    vector<string> playersHome(11);
    vector<string> playersVisiting(11);
    string homeTeamName, visitingTeamName;

    cout << "Digite o nome do time da casa: ";
    cin >> homeTeamName;
    homeTeam = teamList->searchTeam(homeTeamName);

    cout << "Digite o nome do time visitante: ";
    cin >> visitingTeamName;
    visitingTeam = teamList->searchTeam(visitingTeamName);

    clear_screen();

    if (homeTeam != nullptr && visitingTeam != nullptr) {
        cout << "Escalação time da casa: " << homeTeamName << endl;
        for (int i = 0; i < 11; i++) {
            cout << "Digite o nome do jogador cadastrado no time: ";
            cin >> playersHome[i];
        }

        clear_screen();

        cout << "Escalação time visitante: " << visitingTeamName << endl;
        for (int i = 0; i < 11; i++) {
            cout << "Digite o nome do jogador cadastrado no time: ";
            cin >> playersVisiting[i];
        }

        int minute, select = 0, goalsHome = 0, goalsVisiting = 0;
        string team, playerName;
        while (select != 5) {
            clear_screen();
            cout << "Narrar partida" << endl;
            cout << "(1) Gol" << endl;
            cout << "(2) Cartao amarelo" << endl;
            cout << "(3) Cartao vermelho" << endl;
            cout << "(4) Falta" << endl;
            cout << "(5) Encerrar partida" << endl;
            cin >> select;

            clear_screen();
            if(select != 5) {
            cout << "Minuto: "; cin >> minute;
            cout << "Time: "; cin >> team;
            cout << "Jogador: "; cin >> playerName;
            player = playerList->findPlayer(playerName);
            }
            waitEnter();

            switch (select) {
                case 1: {
                    if (team == homeTeamName) {
                        homeTeam->goalsScored++;
                        visitingTeam->goalsConceded++;
                        goalsHome++;
                    } else {
                        homeTeam->goalsConceded++;
                        visitingTeam->goalsScored++;
                        goalsVisiting++;
                    }
                    player->goals++;
                    break;
                }
                case 2:
                    if (team == homeTeamName) {
                        homeTeam->yellowCards++;
                    } else {
                        visitingTeam->yellowCards++;
                    }
                    player->yellowCards++;
                    break;
                case 3:
                    if (team == homeTeamName) {
                        homeTeam->redCards++;
                    } else {
                        visitingTeam->redCards++;
                    }
                    player->redCards++;
                    break;
                case 4:
                    if (team == homeTeamName) {
                        homeTeam->fouls++;
                    } else {
                        visitingTeam->fouls++;
                    }
                    player->fouls++;
                    break;
                case 5:
                    if(goalsHome > goalsVisiting)
                        homeTeam->wins++;
                    else if(goalsHome < goalsVisiting)
                        visitingTeam->wins++;
                    else{
                        visitingTeam->draws++;
                        homeTeam->draws++;
                    }
                    match = new Match(homeTeam, visitingTeam);
                    matchList->addMatch(match);
                    delete match;
                    break;
                default:
                    cout << "Opção inválida. Tente novamente." << endl;
                    break;
            }
        }
    } else {
        cout << "Erro, tente novamente." << endl;
        waitEnter();
    }
}

void menu_matches(MatchList* matchList, TeamList* teamList, PlayerList* playerList) {
    int select;
    string homeTeam, visitingTeam;
    clear_screen();
    while(select != 4) {
        cout << "Gerenciamento de partidas." << endl;
        cout << "(1) Cadastrar nova partida" << endl;
        cout << "(2) Remover partida" << endl;
        cout << "(3) Pesquisar partida" << endl;
        cout << "(4) Voltar pro menu principal." << endl;
        cout << "Selecione uma opção: ";
        cin >> select;

        switch (select)
        {
        case 1:
            new_match(matchList, teamList, playerList);
            break;
        case 2:
            cout << "Digite o time da casa: "; cin >> homeTeam;
            cout << "Digite o time visitante: "; cin >> visitingTeam;
            matchList->removeMatch(homeTeam, visitingTeam);
            break;
        case 3:
            cout << "Digite o time da casa: "; cin >> homeTeam;
            cout << "Digite o time visitante: "; cin >> visitingTeam;
            matchList->searchMatch(homeTeam, visitingTeam);
            break;
        }
    }
}

void menu_rounds(RoundList* roundList, MatchList* matchList) {
    int select = 1;
    while(select != 2){
        clear_screen();
        cout << "Gerenciamento de rodadas" << endl;
        cout << "(1) Cadastrar rodadas" << endl;
        cout << "(2) Voltar" << endl;
        cout << "Selecione uma opção: ";
        cin >> select;

        switch (select)
        {
        case 1:
            roundList->addMatchList(matchList);
            break;
        }
    }
}

void main_menu(PlayerList* playerList, TrainerList* trainerList, TeamList* teamList, MatchList* matchList, RoundList* roundList) {
    int select = 1;
    while(select != 0){
        clear_screen();
        cout << "Programa para controle de um campeonato de futebol" << endl;
        cout << "(1) Gerenciar jogadores" << endl;
        cout << "(2) Gerenciar treinadores" << endl;
        cout << "(3) Gerenciar times" << endl;
        cout << "(4) Gerenciar partidas" << endl;
        cout << "(5) Gerenciar rodadas" << endl;
        cout << "(6) Sair" << endl;
        cout << "Selecione uma opção: ";
        cin >> select;

        switch (select)
        {
        case 1:
            menu_players(playerList);
            break;
        case 2:
            menu_trainers(trainerList);
            break;
        case 3:
            menu_teams(teamList, playerList, trainerList);
            break;
        case 4:
            menu_matches(matchList, teamList, playerList);
            break;
        case 5:
            menu_rounds(roundList, matchList);
            break;
        case 6:
            return;
        }
    }
}

int main(){
    PlayerList* playerList = new PlayerList();
    TrainerList* trainerList = new TrainerList();
    TeamList* teamList = new TeamList();
    MatchList* matchList = new MatchList();
    RoundList* roundList = new RoundList();

    main_menu(playerList, trainerList, teamList, matchList, roundList);

    playerList->removeAllPlayers();
    trainerList->removeAllTrainers();
    teamList->removeAllTeams();
    matchList->removeAllMatches();
    roundList->removeAllMatchLists();

    return 0;
}