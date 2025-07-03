#pragma once
#include <vector>
class Observer;
enum class GAME_EVENT {
    COIN_CHANGE,
    LIVES_CHANGE,
    SCORE_CHANGE
};
class Subject {
public:
    virtual ~Subject() = default;

    // Attach an observer to the subject
    virtual void addObserver(class Observer* observer);

    // Detach an observer from the subject
    virtual void removeObserver(class Observer *observer);

protected:
    // Notify all observers about an event
    virtual void notify(GAME_EVENT, int value);
private:
    std::vector<Observer*> observers;
};