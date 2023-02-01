#include "basicalgs.cpp"

#define KOLVO_KART 2
#define KOLVO_KART_ON_THE_TABLE 5

const std::vector<std::string> masti{"♠", "♥", "♦", "♣"};
const std::vector<std::string> karti{
        "2",
        "3",
        "4",
        "5",
        "6",
        "7",
        "8",
        "9",
        "10",
        "valet",
        "dama",
        "korol",
        "tuz"};

class Player {
public:
    std::vector<long> card_ids;
    long c, d;
};

int main()
{
    std::map<std::string, bool> deck;
    std::vector<std::string> bob;
    std::vector<std::string> alice;
    std::map<std::string, long> cards_;
    std::vector<long> u;
    std::vector<long> table;

    srand(time(NULL));
    long p = rand() % RAND_MAX + 1;
    while (!isPrime(p)) {
        p = rand() % RAND_MAX + 1;
    }

    // filling map mast':karta
    for (auto& kart : karti) {
        for (auto& mast : masti) {
            long tmp;
            do {
                tmp = rand() % (p - 2) + 1;
            } while (find_key_by_value(cards_, tmp).size());
            cards_[mast + ' ' + kart] = tmp;
            u.push_back(tmp);
        }
    }

    int players_num;

    std::cout << "number of players = ";
    std::cin >> players_num;

    if (((masti.size() * karti.size() - (players_num * KOLVO_KART))
         < KOLVO_KART_ON_THE_TABLE)
        || players_num < 2) {
        std::cout << "Invalid number of players!\n";
        exit(0);
    }

    Player players[players_num];

    for (int i = 0; i < players_num; i++) {
        generate_prime_numbers_v2(players[i].c, players[i].d, p - 1);
    }

    for (int i = 0; i < players_num; i++) {
        for (auto& item : u) {
            item = fexp(item, players[i].c, p);
        }
    }

    for (int j = 0; j < KOLVO_KART; j++) {
        for (int i = 0; i < players_num; i++) {
            std::random_shuffle(u.begin(), u.end());
            int idx = rand() % (u.size() - 1);
            players[i].card_ids.push_back(u[idx]);
            u.erase(u.begin() + idx);
        }
    }

    for (int i = 0; i < KOLVO_KART; i++) {
        for (int j = 0; j < players_num; j++) {
            for (int k = 0; k < players_num; k++) {
                if (k != j) {
                    players[j].card_ids[i]
                            = fexp(players[j].card_ids[i], players[k].d, p);
                }
            }
        }
    }

    for (int i = 0; i < players_num; i++) {
        std::cout << "player[" << i << "]:\n";
        for (int j = 0; j < KOLVO_KART; j++) {
            std::cout << "\t" << j + 1 << ". "
                      << find_key_by_value(
                                 cards_,
                                 fexp(players[i].card_ids[j], players[i].d, p))
                      << "\n";
        }
    }

    for (int i = 0; i < KOLVO_KART_ON_THE_TABLE; i++) {
        int idx = rand() % (u.size() - 1);
        table.push_back(u[idx]);
        u.erase(u.begin() + idx);
        for (int j = 0; j < players_num; j++) {
            table[i] = fexp(table[i], players[j].d, p);
        }
    }

    std::cout << "table:\n";
    for (int i = 0; i < KOLVO_KART_ON_THE_TABLE; i++) {
        std::cout << "\t" << i + 1 << ". "
                  << find_key_by_value(cards_, table[i]) << "\n";
    }

    return 0;
}