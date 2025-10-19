#pragma once
#include <functional>
#include <memory>
#include <string>
#include <typeinfo>
#include <unordered_map>

namespace utils {

// A minimal, type-safe Factory that supports registering zero-argument
// creators for concrete types and creating instances later by type.
// This keeps the implementation simple and is sufficient for the
// example/tests added here. If you need constructors with arguments,
// we can extend the design (e.g. using std::any/std::vector<std::any>).
class Factory {
public:
    // Register a zero-argument creator for type T.
    template<class T>
    void register_creator(std::function<std::shared_ptr<T>()> creator) {
        // Wrap the typed creator into a type-erased creator returning shared_ptr<void>
        creators_[typeid(T).name()] = [creator]() -> std::shared_ptr<void> {
            return std::static_pointer_cast<void>(creator());
        };
    }

    // Create an instance of T using the previously registered creator.
    // Returns nullptr if no creator was registered for T.
    template<class T>
    std::shared_ptr<T> create() {
        auto it = creators_.find(typeid(T).name());
        if (it != creators_.end()) {
            std::shared_ptr<void> p = it->second();
            return std::static_pointer_cast<T>(p);
        }
        return nullptr;
    }

private:
    std::unordered_map<std::string, std::function<std::shared_ptr<void>()>> creators_;
};

} // namespace utils
