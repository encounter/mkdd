#ifndef _STD_PAIR_H
#define _STD_PAIR_H

namespace std {
    template <typename T1, typename T2> struct pair {
        T1 first;
        T2 second;
    };

    template <> struct pair<float, float> {
        pair()
            : first(0.0f)
            , second(0.0f) {};
        float first;
        float second;
    };
} // namespace std

#endif