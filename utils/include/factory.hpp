#pragma once
#include <functional>
#include <memory>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <any>
#include <vector>
#include <tuple>
#include <utility>
#include <type_traits>

namespace utils {

// A minimal, type-safe Factory that supports registering zero-argument
// creators for concrete types and creating instances later by type.
// This keeps the implementation simple and is sufficient for the
// example/tests added here. If you need constructors with arguments,
// we can extend the design (e.g. using std::any/std::vector<std::any>).
class Factory {
public:
    // Register a creator for type T. The creator can be any callable that returns
    // std::shared_ptr<T> and accepts any number of arguments. The argument types
    // are deduced from the callable; when creating an instance you must supply
    // matching arguments which will be packed into std::any and forwarded.
    // Register a creator for type T by passing a callable (lambda, function, std::function).
    // The callable must return std::shared_ptr<T> (or compatible) and may accept any arguments.
    template <class T, typename Creator>
    void register_creator(Creator creator) {
        using traits = function_traits<Creator>;
        using args_tuple = typename traits::args;
        tuple_to_pack<args_tuple>::template call<T, Creator>(this, creator);
    }

    // Overload that deduces T from the callable's return type (must be std::shared_ptr<T>)
    template <typename Creator>
    void register_creator(Creator creator) {
        using traits = function_traits<Creator>;
        using return_t = typename traits::return_type;
        using args_tuple = typename traits::args;
        // extract_shared_ptr is defined at class scope below
        static_assert(extract_shared_ptr<return_t>::value, "creator must return std::shared_ptr<T>");
        using T = typename extract_shared_ptr<return_t>::type;
        tuple_to_pack<args_tuple>::template call<T, Creator>(this, creator);
    }

    // Create an instance of T by forwarding the provided args to the previously
    // registered creator. Returns nullptr on failure (no registration or bad any cast).
    template <class T, typename... Args>
    std::shared_ptr<T> create(Args&&... args) {
        auto it = creators_.find(typeid(T).name());
        if (it == creators_.end()) return nullptr;

        std::vector<std::any> packed;
        packed.reserve(sizeof...(Args));
        (packed.emplace_back(std::forward<Args>(args)), ...);

        try {
            auto& creator = it->second;
            std::shared_ptr<void> p = creator(packed);
            return std::static_pointer_cast<T>(p);
        } catch (...) {
            return nullptr;
        }
    }

private:
    // function_traits: minimal traits to extract argument types from a callable
    template <typename T>
    struct function_traits : function_traits<decltype(&T::operator())> {};

    template <typename R, typename... Args>
    struct function_traits<R(*)(Args...)> {
        using return_type = R;
        using args = std::tuple<Args...>;
    };

    template <typename C, typename R, typename... Args>
    struct function_traits<R(C::*)(Args...) const> {
        using return_type = R;
        using args = std::tuple<Args...>;
    };

    // Helper to convert a tuple type to a pack and call register_creator_impl
    template <typename Tuple>
    struct tuple_to_pack;

    template <typename... Args>
    struct tuple_to_pack<std::tuple<Args...>> {
        template <class T, class Creator>
        static void call(Factory* f, Creator creator) {
            f->template register_creator_impl<T, Creator, Args...>(creator);
        }
    };

    // helper to extract T from std::shared_ptr<T>
    template <typename R>
    struct extract_shared_ptr { static constexpr bool value = false; };
    template <typename U>
    struct extract_shared_ptr<std::shared_ptr<U>> { using type = U; static constexpr bool value = true; };

    // Invoke a Creator with args extracted from std::any vector
    template <typename Creator, typename T, typename... Args, size_t... I>
    static std::shared_ptr<T> invoke_with_any_impl(const Creator& c, const std::vector<std::any>& v, std::index_sequence<I...>) {
        try {
            return c(std::any_cast<std::decay_t<Args>>(v[I])...);
        } catch (const std::bad_any_cast&) {
            return nullptr;
        }
    }

    template <typename Creator, typename T, typename... Args>
    static std::shared_ptr<T> invoke_with_any(const Creator& c, const std::vector<std::any>& v) {
        return invoke_with_any_impl<Creator, T, Args...>(c, v, std::index_sequence_for<Args...>{});
    }

    // register_creator implementation that knows the argument types Args...
    template <class T, typename Creator, typename... Args>
    void register_creator_impl(Creator creator) {
        creators_[typeid(T).name()] = [creator](const std::vector<std::any>& v) -> std::shared_ptr<void> {
            if (v.size() != sizeof...(Args)) return nullptr;
            auto p = invoke_with_any<Creator, T, Args...>(creator, v);
            return std::static_pointer_cast<void>(p);
        };
    }

    std::unordered_map<std::string, std::function<std::shared_ptr<void>(const std::vector<std::any>&)>> creators_;
};

} // namespace utils
