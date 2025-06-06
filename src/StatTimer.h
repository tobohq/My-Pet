#ifndef STATTIMER_H
#define STATTIMER_H

#include <SFML/Graphics.hpp>

class StatTimer : public sf::Clock {
    private:
    Clock clock;
    bool update = 0;
    float interval;

    public:
    // 30 Seconds Constructor
    StatTimer() : StatTimer(30.f) {}
    StatTimer(float interval)
    : interval(interval), update(false) {
    }

    bool shouldUpdate() {
        if (clock.getElapsedTime().asSeconds() >= interval) {
            update = true;
        } else {
            update = false;
        }
        return update;
    }

    float getInterval() {
        return interval;
    }
};

#endif //STATTIMER_H
