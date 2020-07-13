namespace detail {
template<class...>
struct make_void {
    using type = void;
};

template<class... Ts>
using void_t = typename make_void<Ts...>::type;

template<class Def, class Void, template<class...> class, class...>
struct detector {
    using type = Def;
};

template<class Def, template<class...> class Tp, class... Ts>
struct detector<Def, void_t<Tp<Ts...>>, Tp, Ts...> {
    using type = Tp<Ts...>;
};

template<class T, template<class...> class Tp, class... Ts>
using detect_t = typename detail::detector<T, void, Tp, Ts...>::type;

template<class F, class... Ts>
struct curry {
    template<class... Us>
    using apply = detect_t<
        curry<F, Ts..., Us...>, F::template apply, Ts..., Us...
    >;
};

template<bool, class, class>
struct cond;

template<class T, class U>
struct cond<true, T, U> {
    using type = T;
};

template<class T, class U>
struct cond<false, T, U> {
    using type = U;
};

template<bool B, class T, class U>
using cond_t = typename cond<B, T, U>::type;
}

template<class F, class... Ts>
using apply = typename detail::curry<F>::template apply<Ts...>;

template<class F, class... Ts>
struct eta {
    template<class... Us>
    using apply = apply<apply<F, Ts...>, Us...>;
};

struct True {
    template<class A, class B>
    using apply = A;
};

struct False {
    template<class A, class B>
    using apply = B;
};

struct If {
    template<class P, class A, class B>
    using apply = apply<P, A, B>;
};

template<bool B>
using pred = detail::cond_t<B, True, False>;

struct Y {
    template<class F>
    struct _ {
        template<class X>
        using apply = apply<F, eta<X, X>>;
    };
    template<class F>
    using apply = apply<_<F>, _<F>>;
};

