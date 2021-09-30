//
// Created by Tessa Power on 30/09/21.
//

#ifndef PIXEL_H
#define PIXEL_H

#include <cstdlib>
#include <iostream>

class Pixel {
public:
    Pixel();
    Pixel(int r, int g, int b, bool was_seen);

    /**
     * @return The Red intensity of this pixel [0, 255]
     */
    inline int red() const { return R; }

    /**
     * @return The Green intensity of this pixel [0, 255]
     */
    inline int green() const { return G; }

    /**
     * @return The Blue intensity of this pixel [0, 255]
     */
    inline int blue() const { return B; }

    /**
     * Sets whether the pixel has been seen.
     *
     * @param val True for seen, or false for not seen.
     */
    inline void set_seen(bool val) { was_seen = val; }

    /**
     * @return Whether this pixel has been seen.
     */
    inline bool seen() const { return was_seen; }

    /**
     * Sets the intensity of the Red, Green, and Blue values for a Pixel.
     * Must sit in the range [0, 255].
     *
     * @param r Value from 0 to 255 representing intensity for Red
     * @param g Value from 0 to 255 representing intensity for Green
     * @param b Value from 0 to 255 representing intensity for Blue
     */
    void set_rgb_values(int r, int g, int b);

    friend std::ostream& operator<<(std::ostream& os, const Pixel& p);
    friend bool operator==(const Pixel& lhs, const Pixel& rhs);
    friend bool operator!=(const Pixel& lhs, const Pixel& rhs);

private:
    int R, G, B;
    bool was_seen;
};

#endif //PIXEL_H
