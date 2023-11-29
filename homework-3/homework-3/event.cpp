/**
 * CS 32, Homework 3, event.cpp
 * Name: Niklas Leet
 * UID: 405795083
 * Date: 5/8/2023
*/

// Your declarations and implementations would go here
/*
    Need classes:
    - Event class
    - Concert class
    - HockeyGame class
    - BasketballGame
    Functions:
    - name
    - need
    - isSport
*/

class Event {
    public:
        Event(string name) { m_name = name; }
        string name() const { return m_name; }
        virtual string need() const = 0;
        virtual bool isSport() const { return true; }
    private:
        string m_name;
};

class Concert : public Event {
    public:
        Concert(string name, string genre) : Event(name) { m_genre = genre; }
        string need() const { return "a stage"; }
        bool isSport() const { return false; }
    private:
        string m_genre;
};

class HockeyGame : public Event {
    public:
        HockeyGame(string name) : Event(name) {};
        string need() const { return "ice"; }
};

class BasketballGame : public Event {
    public:
        BasketballGame(string name) : Event(name) {};
        string need() const { return "hoops"; }
};


// void display(const Event* e)
// {
//     cout << e->name() << ": ";
//     if (e->isSport())
//         cout << "(sport) ";
//     cout << "needs " << e->need() << endl;
// }
// 
// int main()
// {
//     Event* events[4];
//     events[0] = new BasketballGame("Lakers vs. Warriors");
//     // Concerts have a name and a genre.
//     events[1] = new Concert("Ricardo Arjona", "Latin pop");
//     events[2] = new Concert("Erykah Badu", "neo soul");
//     events[3] = new HockeyGame("Kings vs. Oilers");
// 
//     cout << "Here are the events." << endl;
//     for (int k = 0; k < 4; k++)
//         display(events[k]);
// 
//     // Clean up the events before exiting
//     cout << "Cleaning up." << endl;
//     for (int k = 0; k < 4; k++)
//         delete events[k];
// }