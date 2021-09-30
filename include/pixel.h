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
    Pixel(uint8_t r, uint8_t g, uint8_t b, bool seen);

    /**
     *
     * @return
     */
    inline uint8_t R() const { return R; }
    /**
     *
     * @return
     */
    inline uint8_t G() const { return G; }
    /**
     *
     * @return
     */
    inline uint8_t B() const { return B; }
    /**
     *
     * @param val
     */
    inline void set_seen(bool val) { seen = val; }
    /**
     *
     * @return
     */
    inline bool seen() const { return seen; }

    /**
     *
     * @param r
     * @param g
     * @param b
     */
    void set_rgb_value(uint8_t r, uint8_t g, uint8_t b);

    friend std::ostream& operator<<(std::ostream& os, const Pixel& p);
    friend bool operator==(const Pixel& lhs, const Pixel& rhs) const;
    friend bool operator!=(const Pixel& lhs, const Pixel& rhs) const;

private:
    uint8_t R, G, B;
    bool seen;
};

#endif //PIXEL_H
