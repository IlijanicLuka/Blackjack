# Blackjack Game
This is a simple console-based Blackjack game implemented in C++. The player competes against the dealer, with the goal of reaching a card sum as close to 21 as possible without exceeding it.

## Features
- Card Deck Simulation: The game uses a standard 52-card deck, with each card having its respective point value.
- Dealer and Player: The player competes against the dealer. Both are dealt two cards at the start, and the player can choose to "Hit" (take another card) or "Stand" (keep the current hand).
- Blackjack Check: The game checks for a natural blackjack (21 points with the first two cards) for both the player and the dealer.
- Dealer Logic: The dealer must keep drawing cards until the sum is at least 17.
- Betting System: Player place a bet at the beginning of the game. Depending on the outcome (win, lose, draw), the payout is calculated.
- Game Outcomes: The game handles different outcomes, such as:
  - Blackjack: Player or dealer wins automatically with a blackjack.
  - Bust: If the player's or dealer's card sum exceeds 21, they lose.
  - Regular Win or Draw: If no one busts, the sums are compared to determine the winner.

## How to Play
1. The player starts by placing a bet.
2. Both the player and the dealer are dealt two cards, with the player's cards fully visible while the dealer's second card remains hidden.
3. The player decides to either:
   - Hit: Take another card.
   - Stand: End their turn and keep the current hand.
4. After the player stands, the dealer automatically draws cards according to the game rules.
5. The winner is determined based on the card sums:
   - Closer to 21 without exceeding it wins.
   - A tie results in a draw.
