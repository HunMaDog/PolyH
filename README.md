# PolyH
PolyH - Polymorphic Helpers

# VirtualBase
Curiously recurring template pattern solution with multilevel and multiple inheritance.

```cpp

    #include "detail/polyh/crtp_macro.hpp"
    #include "detail/polyh/virtual_base.hpp"

    #include <iostream>

    constexpr int forty_and_two{42};

    template<typename Derived>
    class Question : public marklar::detail::polyh::VirtualBase<Derived, Question> {
    public:
        void print_answer() const noexcept
        {
            std::cout << CRTP_UNDERLYING.answer() << " - The Answer to the Ultimate Question of Life, The Universe, and Everything.\n";
        }
    };

    class Answer : public Question<Answer> {
        CRTP_FRIEND(Question<Answer>)

    protected:
        constexpr int answer() const noexcept
        {
            return forty_and_two;
        }
    };

    int main()
    {
        Answer answare;

        answare.print_answer();
    
        return 0;
    }

```

# VirtualAssign
Work in progress

# VirtualCompare
Work in progress
