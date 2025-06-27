#pragma once
#include "Subject.h"
class Observer {
    public:
        virtual ~Observer() = default;
        virtual void onNotify(GAME_EVENT event, int newValue) = 0;
};