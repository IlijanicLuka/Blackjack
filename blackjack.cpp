#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>
#include <limits>
#include <algorithm>
#include <random>

using namespace std;


map<string, int> card_points = { {"2_clubs", 2}, {"3_clubs", 3}, {"4_clubs", 4}, {"5_clubs", 5}, {"6_clubs", 6}, {"7_clubs", 7}, {"8_clubs", 8},
                                 {"9_clubs", 9},{"10_clubs", 10}, {"J_clubs", 10}, {"Q_clubs", 10}, {"K_clubs", 10},
                                 {"2_diamonds", 2}, {"3_diamonds", 3}, {"4_diamonds", 4}, {"5_diamonds", 5}, {"6_diamonds", 6}, {"7_diamonds", 7}, {"8_diamonds", 8},
                                 {"9_diamonds", 9}, {"10_diamonds", 10}, {"J_diamonds", 10}, {"Q_diamonds", 10}, {"K_diamonds", 10},
                                 {"2_hearts", 2}, {"3_hearts", 3}, {"4_hearts", 4}, {"5_hearts", 5}, {"6_hearts", 6}, {"7_hearts", 7}, {"8_hearts", 8},
                                 {"9_hearts", 9}, {"10_hearts", 10}, {"J_hearts", 10}, {"Q_hearts", 10}, {"K_hearts", 10},
                                 {"2_spades", 2}, {"3_spades", 3}, {"4_spades", 4}, {"5_spades", 5}, {"6_spades", 6}, {"7_spades", 7}, {"8_spades", 8},
                                 {"9_spades", 9}, {"10_spades", 10}, {"J_spades", 10}, {"Q_spades", 10}, {"K_spades", 10}
                            };


void show_cards(vector<string> cards, bool dealer_2nd_deal = false){
    for(int i = 0; i < cards.size(); i++){
        if(dealer_2nd_deal == true && i > 0){
            cout << "?" << " ";
        }
        else{
            cout << cards[i] << " ";
        }
    }
}


int sum(vector<string> cards){
    int sum = 0;
    int aces = 0;
    for(string i : cards){
        if(i.substr(0, 3) != "ACE"){
            sum += card_points[i];
        }
        else{
            aces++;
        }
    }
    while (aces > 0) {
        if (sum + 11 <= 21){
            sum += 11;
        }
        else {
            sum += 1;
        }
        aces--;
    }

    return sum;
}

class Dealer{
    public:
    vector<string> deck = {"ACE_clubs", "2_clubs", "3_clubs", "4_clubs", "5_clubs", "6_clubs", "7_clubs", "8_clubs",
                           "9_clubs", "10_clubs", "J_clubs", "Q_clubs", "K_clubs",
                           "ACE_diamonds", "2_diamonds", "3_diamonds", "4_diamonds", "5_diamonds", "6_diamonds", "7_diamonds", "8_diamonds",
                           "9_diamonds", "10_diamonds", "J_diamonds", "Q_diamonds", "K_diamonds",
                           "ACE_hearts", "2_hearts", "3_hearts", "4_hearts", "5_hearts", "6_hearts", "7_hearts", "8_hearts",
                           "9_hearts", "10_hearts", "J_hearts", "Q_hearts", "K_hearts",
                           "ACE_spades", "2_spades", "3_spades", "4_spades", "5_spades", "6_spades", "7_spades", "8_spades",
                           "9_spades", "10_spades", "J_spades", "Q_spades", "K_spades"
    };
    vector<string> cards;

    string deal(){
        int card_num = rand() % deck.size();
        string card = deck[card_num];
        deck.erase(deck.begin() + card_num);

        return card;
    }

    void action(){
        if(sum(cards) >= 17){
            cout << "Dealer cards: ";
            show_cards(cards);
            cout <<  "\n";
            cout << "Dealer sum: " << sum(cards) << endl;
            return;
        }
        while(sum(cards) < 17){
            cards.push_back(deal());
            cout << "Dealer took a card...\nDealer cards: ";
            show_cards(cards);
            cout <<  "\n";
            cout << "Dealer sum: " << sum(cards) << endl;
        }

        return;
    }
};


class Player{
    public:
    vector<string> cards;
    double bet;
    double payout = 0;

    Player(int x){
        bet = x;
    }

    void action(Dealer& dealer){
        string choose;

        while(true){
            cout << "\n--> Press 'h' for Hit or 's' for Stand: ";
            cin >> choose;
            cout << "\n";
            if(choose != "h" && choose != "s"){
                cout << "Wrong input!\n";
                cin.clear();
                continue;
            }
            else if(choose == "s"){
                break;
            }
            else{
                cards.push_back(dealer.deal());
                cout << "You took a card...\nYour cards: ";
                show_cards(cards);
                cout <<  "\n";
                cout << "Your sum: " << sum(cards) << endl;
                if(sum(cards) > 21){
                    return;
                }
            }
        }
        return;

    }
};


void shuffle_deck(Dealer& dealer) {
    random_device rd;
    mt19937 g(rd());
    shuffle(dealer.deck.begin(), dealer.deck.end(), g);
}


bool more_than_21(vector<string> cards){
    if(sum(cards) > 21){
        return true;
    }
    else{
        return false;
    }
}


bool check_blackjack(Player& player, Dealer& dealer){
    if(sum(player.cards) == 21 && sum(dealer.cards) == 21){
        cout << "\n---------- Both you and the dealer have blackjack. Draw! ----------\n";
        cout << "\nYour cards: ";
        show_cards(player.cards);
        cout << "\nDealer cards: ";
        show_cards(dealer.cards);
        player.payout = player.bet;
        cout << "\n >>> Your payout is " << player.payout << " dollars <<<" << endl;
        return true;
    }
    else if(sum(player.cards) == 21){
        cout << "\n---------- You have blackjack! ----------\n";
        player.payout = player.bet + player.bet * 1.5;
        cout << "\n >>> Your payout is " << player.payout << " dollars <<<" << endl;
        return true;
    }
    else if(sum(dealer.cards) == 21){
        cout << "\n---------- Dealer has blackjack! ----------\n";
        cout << "\nDealer cards: ";
        show_cards(dealer.cards);
        player.payout = 0;
        cout << "\n >>> Your payout is " << player.payout << " dollars <<<" << endl;
        return true;
    }
    else{
        return false;
    }
}

void win_check(Player& player, Dealer& dealer){
    if(sum(player.cards) > sum(dealer.cards)){
        cout << "\n---------- You won! ----------\n";
        player.payout = player.bet * 2;
        cout << "\n >>> Your payout is " << player.payout << " dollars <<<" << endl;
    }
    else if(sum(player.cards) < sum(dealer.cards)){
        cout << "\n---------- Dealer won! ----------\n";
        player.payout = 0;
        cout << "\n >>> Your payout is " << player.payout << " dollars <<<" << endl;
    }
    else{
        cout << "\n---------- Draw! ----------\n";
        player.payout = player.bet;
        cout << "\n >>> Your payout is " << player.payout << " dollars <<<" << endl;
    }
}


int main() {

    srand(time(0));

    double bet, payout;
    while(true){
        cout << "Enter your bet in dollars: ";
        cin >> bet;
        if(cin.good() && bet > 0){
            break;
        }
        else{
            cout << "\nWrong input!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
    }

    Player player1(bet);
    Dealer dealer1;

    shuffle_deck(dealer1);

    cout << "\n---------- Initial deal ----------\n";

    player1.cards.push_back(dealer1.deal());
    player1.cards.push_back(dealer1.deal());
    cout << "\nYour cards: ";
    show_cards(player1.cards);
    cout << "\nYour sum: " << sum(player1.cards) << endl;

    dealer1.cards.push_back(dealer1.deal());
    dealer1.cards.push_back(dealer1.deal());
    cout << "\nDealer cards: ";
    show_cards(dealer1.cards, true);
    cout << "\nDealer sum: " << "?" << endl;

    if(check_blackjack(player1, dealer1)){
        exit(0);
    }

    cout << "\n---------- Game start ----------" << endl;

    player1.action(dealer1);

    if(more_than_21(player1.cards)){
        cout << "\nYou have too many points.\n---------- Dealer won! ----------\n";
        player1.payout = 0;
        cout << "\n >>> Your payout is " << player1.payout << " dollars <<<" << endl;
        exit(0);
    }
    if(check_blackjack(player1, dealer1)){
        exit(0);
    }

    dealer1.action();

    if(more_than_21(dealer1.cards)){
        cout << "\nDealer has too many points.\n---------- You won! ----------\n";
        player1.payout = player1.bet * 2;
        cout << "\n >>> Your payout is " << player1.payout << " dollars <<<" << endl;
        exit(0);
    }
    if(check_blackjack(player1, dealer1)){
        exit(0);
    }

    win_check(player1, dealer1);

    return 0;
}
