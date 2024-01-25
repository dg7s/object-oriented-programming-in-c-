#ifndef SQUARE_H
#define SQUARE_H

#include "player.h"

// Names of all classes which can be used in the game.
enum class square_name {start_square, end_square, empty_square, regeneration_square, move_to_square, waiting_square};


class Square {
    public:
        // Constructors.
        Square() = default;

        // Destructor.
        ~Square() = default;

        // Copy constructor and Assigment operator is deleted.
        Square(const Square& s) = delete;
        Square& operator=(const Square&) = delete;
/*
        // Getters to next, and prev;
        Square* getNext() const;
        Square* getPrev() const;
*/
        // Methods:
        virtual void action(Player* player, int &square_index) const = 0; // Make action on player.
        virtual void name() const = 0; // Print out a name.

        virtual bool hypotheticalAction(Player* player, int &square_index) const = 0; // Return if an action for player was taken.
        virtual bool hypotheticalEnd(int &square_index) const = 0; // Return if an action for player was taken.


};
class NotEnd : public Square{
    public:
        bool hypotheticalEnd(int &square_index) const override;
};

class HypotheticalActionIsNull : public NotEnd{
    public:
        bool hypotheticalAction(Player* player, int &square_index) const override;
};

class ActionIsNull : public HypotheticalActionIsNull{
    public:
        void action(Player* player, int &square_index) const override;
};

// Square from where players start game. Only one per board. During game does nothing.
class Start : public ActionIsNull {
    public:
        void name() const override;
};

// Nothing happens.
class Empty : public ActionIsNull {
    public:
        void name() const override;
};

// Square where players end a game.
class End : public Square {
    public:
        void name() const override;
        bool hypotheticalAction(Player* player, int &square_index) const override;
        void action(Player* player, int &square_index) const override;
        bool hypotheticalEnd(int &square_index) const override;

};

// DokTOr attribute increase.
class Regeneration : public NotEnd {
    public:
        void name() const override;
        void action(Player* player, int &square_index) const override;
        bool hypotheticalAction(Player *player, int &square_index) const override;
};

// Player need to wait a few queues.
class Waiting : public HypotheticalActionIsNull {
    public:
        void name() const override;
        void action(Player* player, int &square_index) const override;
};

// Move player to proper square.
class MoveTo : public HypotheticalActionIsNull {
    private:
        int square_number;
    public:
        MoveTo() = delete;
        MoveTo(int k);

        void name() const override;
        void action(Player* player, int &square_index) const override;
};

#endif // SQUARE_H