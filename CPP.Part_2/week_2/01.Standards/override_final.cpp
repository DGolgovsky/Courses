struct Base
{
    virtual void update();
    virtual void foo(int);
    virtual void bar() const;
};

struct Derived: Base
{
    void updata() override;               // error: used data instead date
    void foo(int) override;               // OK
    virtual void foo(long) override;      // error: argument
    virtual void foo(int) const override; // error: const
    virtual int  foo(int) override;       // error: ret type
    virtual void bar(long);               // OK
    virtual void bar() const final;       // OK
};

struct Derived2 final : Derived
{
    virtual void bar() const;             // error: used 'final'
};

struct Derived3 : Derived2 {};            // error: Derived2 -> final

