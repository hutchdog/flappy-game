#pragma once

namespace common {
    //Player horizontal speed
    const float PlayerSpeed = 8.f;

    //Player gravity
    const float PlayerGravity = 0.5f;

    //Player vertical speed boost
    const float PlayerBoostOnTouch = 0.35f;

    //Player start position
    const core::Vec2 PlayerStartPos = {-40.f, 0.f};

    //Player avatar size
    const float PlayerSize = 8.f;

    /*
     * Screen virtual vertical size, game Y coords will be in [-50, 50] bounds
     * Horizontal size will be calculated by system provided viewport aspect ratio
     */
    const float ScreenDesignHeight = 100.f;

    //Level blocks horizontal space
    const float BlockOffset = 50.f;

    //Level blocks width
    const float BlockWidth = 15.f;

    //Level block generation heights
    const float BlockBaseHeight = 20.f;
    const float BlockDeltaLow = 10.f;
    const float BlockDeltaHigh = 40.f;
}
