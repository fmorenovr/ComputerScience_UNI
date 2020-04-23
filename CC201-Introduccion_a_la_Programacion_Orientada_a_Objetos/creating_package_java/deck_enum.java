
import java.util.*;

enum Suit { // enum se comporta como una clase
   DIAMONDS, 
   CLUBS, 
   HEARTS, 
   SPADES 
}

enum Rank { 
   DEUCE, THREE, FOUR, FIVE, SIX, SEVEN,
   EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE 
}

class Card {
    private final Rank rank;
    private final Suit suit;

    public Card(Rank rank, Suit suit) {
        this.rank = rank;
        this.suit = suit;
    }

    public Suit getSuit() {
        return suit;
    }

    public Rank getRank() {
        return rank;
    }

    public String toString() {
        return rank + " of " + suit;
    }
}

class Deck {
    private static Card[] cards = new Card[52];
    public Deck() {
        int i = 0;
        for (Suit suit : Suit.values()) {
            for (Rank rank : Rank.values()) {
                cards[i++] = new Card(rank, suit);
            }
        }
    }
    public Card getcard(int i)
    {
      return cards[i];
    }
}

class Mostrar
{
  public static void main(String[] args)
  {
    Deck deck = new Deck();
    int i = 0;
    for (;i<52;i++) {
        System.out.println(deck.getcard(i).toString());
    }
  }
}
