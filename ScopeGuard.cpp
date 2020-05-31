// This is purely derived from, although I found it so interestig that I to run it and so it makes it wouthwhile to upload to the repo as well
//  https://github.com/CppCon/CppCon2019/blob/master/Presentations/design_patterns/design_patterns__fedor_pikus__cppcon_2019.pdf
//


#include <iostream>
#include <exception>

// Classes for demonstration
class Record
{
    char data[128];
};

class Storage
{
    public:
        void insert(Record const& r) {}
        void undo() { std::cout << __FUNCTION__  << " called\n";}
        void finalize() { std::cout << __FUNCTION__  << " called\n";}
};

class Memory
{
    public:
        void insert(Record const& r) {
            throw std::runtime_error("It happens");
        }
};

// C++03 Implementation

#ifdef CXX03
void undo(Storage& S) { S.undo(); }
void finalize(Storage& S) { S.finalize(); }

class ScopeGuardImplBase {
    public:
        ScopeGuardImplBase() : commit_(false) {}
        void commit() const throw() { commit_ = true; }
    protected:
        ScopeGuardImplBase(const ScopeGuardImplBase& other)
            : commit_(other.commit_) { other.commit(); }
        ~ScopeGuardImplBase() {}
        mutable bool commit_;
    private:
        ScopeGuardImplBase& operator=(const ScopeGuardImplBase&);
};

template <typename Func, typename Arg>
class ScopeGuardImpl : public ScopeGuardImplBase {
    public:
        ScopeGuardImpl(const Func& f, Arg& arg) : func_(f), arg_(arg) {}
        ~ScopeGuardImpl() { if (!commit_) func_(arg_); }
    private:
        const Func& func_;
        Arg& arg_;
};

template <typename Func, typename Arg>
ScopeGuardImpl<Func, Arg> MakeGuard(const Func& f, Arg& arg) {
    return ScopeGuardImpl<Func, Arg>(f, arg);
}
#endif

// C++11 Implementation
class ScopeGuardBase {
    public:
        ScopeGuardBase() : commit_(false) {}
        void commit() noexcept { commit_ = true; }
    protected:
        ScopeGuardBase(ScopeGuardBase&& other)
            : commit_(other.commit_) { other.commit(); }
        ~ScopeGuardBase() {}
        bool commit_;
    private:
        ScopeGuardBase& operator=(const ScopeGuardBase&) = delete;
};

template <typename Func>
class ScopeGuard : public ScopeGuardBase {
    public:
        ScopeGuard(Func&& f) : func_(f) {}
        ScopeGuard(const Func& f) : func_(f) {}
        ~ScopeGuard() { if (!commit_) func_(); }
        ScopeGuard(ScopeGuard&& other) : ScopeGuardBase{std::move(other)}, func_{other.func_} {}
    private:
        Func func_;
};

template <typename Func>
ScopeGuard<Func> MakeGuard(Func&& f) {
    return ScopeGuard<Func>(std::forward<Func>(f));
}

void test(Record const& r, Storage& S, Memory& M)
{
    S.insert(r);
    auto SF = MakeGuard([&](){S.finalize();});
    auto SG = MakeGuard([&](){S.undo();});
    M.insert(r);
    SG.commit();
}
// C++1z
/*
void test(Record const& r, Storage& S, Memory& M)
{
    S.insert(r);
    auto SF = ScopeGuard([&](){S.finalize();});
    auto SG = ScopeGuard([&](){S.undo();});
    M.insert(r);
    SG.commit();
}*/
// C++1z implementation

int main()
{
    Record r;
    Storage s;
    Memory m;
    try {
        test(r, s, m);
    } catch (...) {}
    return 0;
}
