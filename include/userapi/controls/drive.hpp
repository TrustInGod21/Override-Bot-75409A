#pragma once

namespace keybindActions::drive {
    inline bool arcade = true;

    inline void toggle_arcade() {
        arcade = !arcade;
    }

    inline bool is_arcade() {
        return arcade;
    }
}