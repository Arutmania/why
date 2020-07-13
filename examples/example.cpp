#include <cstdio>
#include "../include/Y.hpp"

template<auto V>
struct Value {
    static constexpr auto value = V;
};

struct FacGen {
    struct Base {
        template<class, class>
        using apply = Value<1>;
    };

    struct Rec {
        struct Mult {
            template<class X, class Y>
            using apply = Value<X::value * Y::value>;
        };

        struct Sub1 {
            template<class X>
            using apply = Value<X::value - 1>;
        };

        template<class F, class N>
        using apply = apply<Mult, N, apply<F, apply<Sub1, N>>>;
    };

    template<class F, class N>
    using apply = apply<
        apply<
            If, pred<N::value <= 1>,
                Base,
                Rec
        >, F, N
    >;
};

struct FibGen {
    struct Base {
        template<class, class N>
        using apply = N;
    };

    struct Rec {
        struct Add {
            template<class X, class Y>
            using apply = Value<X::value + Y::value>;
        };

        struct Sub1 {
            template<class X>
            using apply = Value<X::value - 1>;
        };

        struct Sub2 {
            template<class X>
            using apply = Value<X::value - 2>;
        };

        template<class F, class N>
        using apply = apply<
            Add, apply<F, apply<Sub1, N>>,
                 apply<F, apply<Sub2, N>>
        >;
    };

    template<class F, class N>
    using apply = apply<
        apply<
            If, pred<N::value <= 1>,
                Base,
                Rec
        >, F, N
    >;
};


int main() {
    std::printf(
        "factorial 20 = %llu\n",
        apply<apply<Y, FacGen>, Value<20ULL>>::value
    );

    std::printf(
        "fibonacci 20 = %d\n",
        apply<apply<Y, FibGen>, Value<20>>::value
    );
}
