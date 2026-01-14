#include "lca.hpp"
#include "tree_node.hpp"

#include <cstdint>

enum class State : std::uint8_t
{
    None = 0,
    P = 1u << 0,
    Q = 1u << 1,
    Both = P | Q,
};

constexpr auto operator|(State lhs, State rhs) noexcept -> State
{
    return static_cast<State>(static_cast<std::uint8_t>(lhs) | static_cast<std::uint8_t>(rhs));
}

constexpr auto operator&(State lhs, State rhs) noexcept -> State
{
    return static_cast<State>(static_cast<std::uint8_t>(lhs) & static_cast<std::uint8_t>(rhs));
}

constexpr auto operator|=(State& lhs, State rhs) noexcept -> State&
{
    lhs = lhs | rhs;
    return lhs;
}

constexpr auto operator&=(State& lhs, State rhs) noexcept -> State&
{
    lhs = lhs & rhs;
    return lhs;
}

auto lowest_common_ancestor(TreeNode* root, TreeNode* p, TreeNode* q, State& state) -> TreeNode*
{
    if (root == p)
    {
        state |= State::P;
    }
    if (root == q)
    {
        state |= State::Q;
    }
    if (state == State::Both)
    {
        return root;
    }
    if (state == State::None)
    {
        if (root->left)
        {
            auto node = lowest_common_ancestor(root->left, p, q, state);
            if (state == State::Both)
            {
                return node;
            }
        }
        if (!root->right)
        {
            return nullptr;
        }
        if (state == State::None)
        {
            return lowest_common_ancestor(root->right, p, q, state);
        }
        lowest_common_ancestor(root->right, p, q, state);
        if (state == State::Both)
        {
            return root;
        }
        return nullptr;
    }
    if (root->left)
    {
        lowest_common_ancestor(root->left, p, q, state);
    }
    if (state == State::Both)
    {
        return root;
    }
    if (!root->right)
    {
        return nullptr;
    }
    lowest_common_ancestor(root->right, p, q, state);
    if (state == State::Both)
    {
        return root;
    }
    return nullptr;
}

auto lowest_common_ancestor(TreeNode* root, TreeNode* p, TreeNode* q) -> TreeNode*
{
    if (!root || !p || !q)
    {
        return nullptr;
    }
    State state = State::None;
    return lowest_common_ancestor(root, p, q, state);
}
