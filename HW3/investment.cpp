

//======================================================
// Investment class

class Investment
{
public:
    Investment(string n, int p);
    virtual ~Investment(){}
    string name()const;
    virtual bool fungible()const
    {
        return false;
    }
    virtual string description() const = 0;
    int purchasePrice() const;
private:
    string m_name;
    int m_price;

};

Investment::Investment(string n, int p)
    :m_name(n), m_price(p)
{}

string Investment::name()const
{
    return m_name;
}
int Investment::purchasePrice() const
{
    return m_price;
}
//=========================================================

class Stock : public Investment
{
public:
    Stock(string n, int value, string ticker)
        :Investment(n, value), m_ticker(ticker)
    {}
    virtual ~Stock()
    {
        cout << "Destroying " << name() << ", a stock holding" << endl;

    }

    virtual bool fungible() const
    {
        return true;
    }

    virtual string description() const
    {
        string s;
        s = "stock trading as " + m_ticker;
        return s;
    }

private:
    string m_ticker;

};

class House : public Investment
{
public:
    House(string n, int p)
        :Investment(n, p)
    {}

    virtual ~House()
    {
        cout << "Destroying the house " << name() << endl;

    }

    virtual string description() const
    {
        string s;
        s = "house";
        return s;
    }

};

class Painting : public Investment
{
public:
    Painting(string n, int p)
        :Investment(n, p)
    {}

    virtual ~Painting()
    {
        cout << "Destroying " << name() << ", a painting" << endl;

    }

    virtual string description() const
    {
        string s;
        s = "painting";
        return s;
    }
};

void display(const Investment* inv)
{
    cout << inv->name();
    if (inv->fungible())
        cout << " (fungible)";
    cout << ": " << inv->description() << " bought for $" << inv->purchasePrice() << endl;
}

