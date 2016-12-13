#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>

class Card {
	friend std::ostream& operator<<(std::ostream& os,const Card& aCard);
public:
	enum eRank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
						JACK, QUEEN, KING };
	enum eSuit { HEARTS, SPADES, DIAMONDS, CLUBS };

	Card(const eRank rank = ACE, const eSuit suit = HEARTS, const bool isUp = true);
	int GetValue() const;
	void Flip();
private:
	eRank m_Rank;
	eSuit m_Suit;
	bool m_IsFaceUp;
};

class Hand {
public:
	Hand();
	virtual ~Hand();
	void Add(Card* pCard);
	void Clear();
	int GetTotal() const;
protected:
	std::vector<Card*> m_Cards;
};

class GenericPlayer : public Hand{
	friend std::ostream& operator<<(std::ostream& os, const GenericPlayer& aGenericPlayer);
public:
	GenericPlayer(const std::string& name = "");
	virtual bool IsHitting() const = 0;
	bool IsBusted() const;
	void Bust() const;
protected:
	std::string m_Name;
};

class Player : public GenericPlayer{
public:
	Player(const std::string& name);
	virtual bool IsHitting() const;
	void Win() const;
	void Lose() const;
	void Push() const;
};

class Dealer : public GenericPlayer{
public:
	Dealer(const std::string& name = "Dealer");
	virtual bool IsHitting() const;
	void FlipFirstCard();
};

class Deck : public Hand{
public:
	Deck();
	~Deck();
	void AskCard(GenericPlayer& asker);
	void Deal(Hand& asker);
	void Shuffle();
	void Populate();
};

class Game {
public:
	Game(const std::vector<std::string>& names);
	void Play();
private:
	Deck m_Deck;
	Dealer m_Dealer;
	std::vector<Player> m_Players;
};

int main() {
	std::cout << "\t\tWelcome to Blackjack!\n\n";
	int numPlayers = 0;
	while ((numPlayers < 1) || (numPlayers > 7)) {
	std::cout << "With how many players do you play? (1/7)\n"
		<< "With a total of ";
	std::cin >> numPlayers;
	}
	std::vector<std::string> names;
	std::string name;
	for (int i = 0; i < numPlayers; ++i) {
		std::cout << "Player name: ";
		std::cin >> name;
		names.push_back(name);
	}
	Game aGame(names);
	char again = 'y';
	while ((again == 'y') || (again == 'Y')) {
		aGame.Play();
		std::cout << "Do you want to play again? (Y/N): ";
		std::cin >> again;
	}

	return 0;
}

std::ostream & operator<<(std::ostream & os, const Card & aCard)
{
	const std::string RANKS[]{ "0", "A", "2", "3", "4", "5", "6", "7", "8", "9",
		"10" , "J", "Q", "K" };
	const std::string SUITS[]{ "h", "s", "d", "c" };
	if (aCard.m_IsFaceUp)
		os << RANKS[aCard.m_Rank] << SUITS[aCard.m_Suit];
	else
		os << "XX";
	return os;
}

Card::Card(const eRank rank, const eSuit suit, const bool isUp) :
	m_Rank(rank),
	m_Suit(suit),
	m_IsFaceUp(isUp)
{}

int Card::GetValue() const
{
	int value = 0;
	if (m_IsFaceUp) {
		value = m_Rank;
		if (value > 10)
			value = 10;
	}
	return value;
}

inline void Card::Flip()
{
	m_IsFaceUp = !(m_IsFaceUp);
}

Deck::Deck()
{
	m_Cards.reserve(52);
	Populate();
}

Deck::~Deck()
{
}

Hand::Hand()
{
	m_Cards.reserve(7);
}

Hand::~Hand()
{
	Clear();
}

void Hand::Add(Card * pCard)
{
	m_Cards.push_back(pCard);
}

void Hand::Clear()
{
	for (std::vector<Card*>::iterator iter = m_Cards.begin(); iter != m_Cards.end(); ++iter) {
		delete *iter;
		*iter = 0;
	}
	m_Cards.clear();
}

int Hand::GetTotal() const
{
	if (m_Cards.empty())
		return 0;
	else if (m_Cards[0]->GetValue() == 0)
		return 0;

	int total = 0;
	bool containsAce = false;
	for (std::vector<Card*>::const_iterator iter = m_Cards.begin(); iter != m_Cards.end(); ++iter) {
		total += (*iter)->GetValue();
		if ((*iter)->GetValue() == Card::ACE)
			containsAce = true;
	}

	if ((containsAce) && total <= 11)
		total += 10;

	return total;
}

std::ostream & operator<<(std::ostream & os, const GenericPlayer & aGenericPlayer)
{
	os << aGenericPlayer.m_Name << ":\t";
	if (!(aGenericPlayer.m_Cards.empty())) {
		for (std::vector<Card*>::const_iterator iter = aGenericPlayer.m_Cards.begin(); iter != aGenericPlayer.m_Cards.end(); ++iter)
			os << *(*iter) << '\t';
		if (aGenericPlayer.GetTotal() != 0)
			os << '(' << aGenericPlayer.GetTotal() << ')';
	}
	else
		os << "<empty>";
	return os;
}

GenericPlayer::GenericPlayer(const std::string & name) :
	m_Name(name)
{}

bool GenericPlayer::IsBusted() const
{
	return (GetTotal() > 21);
}

void GenericPlayer::Bust() const
{
	std::cout << m_Name << " busts.\n";
}

Player::Player(const std::string & name) :
	GenericPlayer(name)
{}

bool Player::IsHitting() const
{
	std::cout << "Does " << m_Name << " wants to hit? (Y/N): ";
	char input;
	std::cin >> input;
	return ((input == 'y') || (input == 'Y'));
}

inline void Player::Win() const
{
	std::cout << m_Name << " wins!\n";
}

inline void Player::Lose() const
{
	std::cout << m_Name << " loses.\n";
}

inline void Player::Push() const
{
	std::cout << m_Name << " pushes.\n";
}

Dealer::Dealer(const std::string& name):
	GenericPlayer(name)
{}

inline bool Dealer::IsHitting() const
{
	return(GetTotal() <= 16);

}

inline void Dealer::FlipFirstCard()
{
	m_Cards[0]->Flip();
}

void Deck::AskCard(GenericPlayer & asker)
{
	std::cout << '\n';
	while (!(asker.IsBusted()) && (asker.IsHitting())) {
		Deal(asker);
		std::cout << asker << '\n';
		if (asker.IsBusted())
			asker.Bust();
	}

}

void Deck::Deal(Hand & asker)
{
	if (!(m_Cards.empty())) {
		asker.Add(m_Cards.back());
		m_Cards.pop_back();
	}
	else
		std::cout << "No cards left to deal.\n";
}

inline void Deck::Shuffle()
{
	std::random_shuffle(m_Cards.begin(), m_Cards.end());
}

void Deck::Populate()
{
	Clear();
	for (int s = Card::ACE; s <= Card::KING; ++s)
		for (int r = Card::HEARTS; r <= Card::CLUBS; ++r)
			Add(new Card(static_cast<Card::eRank>(s), static_cast<Card::eSuit>(r)));
}

Game::Game(const std::vector<std::string>& names)
{
	for (std::vector<std::string>::const_iterator iter = names.begin(); iter != names.end(); ++iter)
		m_Players.push_back(*iter);
	srand(static_cast<unsigned int>(time(NULL)));
	m_Deck.Populate();
	m_Deck.Shuffle();
}

void Game::Play()
{
	// Deals cards
	for (int i = 0; i < 2; ++i) {
		for (std::vector<Player>::iterator iter = m_Players.begin(); iter != m_Players.end(); ++iter)
			m_Deck.Deal(*iter);
	m_Deck.Deal(m_Dealer);
	}

	m_Dealer.FlipFirstCard();
	std::cout << '\n';

	// Displays cards
	for (std::vector<Player>::iterator iter = m_Players.begin(); iter != m_Players.end(); ++iter)
		std::cout << *iter << '\n';

	std::cout << m_Dealer << '\n';

	// Asks to draw card
	for (std::vector<Player>::iterator iter = m_Players.begin(); iter != m_Players.end(); ++iter)
		m_Deck.AskCard(*iter);

	m_Dealer.FlipFirstCard();
	std::cout << '\n' << m_Dealer << '\n';

	m_Deck.AskCard(m_Dealer);
	if (m_Dealer.IsBusted())
		for (std::vector<Player>::const_iterator iter = m_Players.begin(); iter != m_Players.end(); ++iter) {
			if (!(*iter).IsBusted())
				(*iter).Win();
			else
				(*iter).Lose();
		}
	else {
		for (std::vector<Player>::const_iterator iter = m_Players.begin(); iter != m_Players.end(); ++iter) {
			if (!(*iter).IsBusted()) {
				if ((*iter).GetTotal() > m_Dealer.GetTotal())
					(*iter).Win();
				else if ((*iter).GetTotal() == m_Dealer.GetTotal())
					(*iter).Push();
				else
					(*iter).Lose();
			}
		}
	}
		for (std::vector<Player>::iterator iter = m_Players.begin(); iter != m_Players.end(); ++iter) {
			iter->Clear();
		}
		m_Dealer.Clear();
}