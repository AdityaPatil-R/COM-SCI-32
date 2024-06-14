class Investment {
    public:
        Investment(string name, int purchasePrice) {
            m_name = name;
            m_purchasePrice = purchasePrice;
        }

        virtual ~Investment() {
            
        }

        string name() const {
            return m_name;
        }

        int purchasePrice() const {
            return m_purchasePrice;
        }

        virtual string description() const {
            return "investment";
        }

        virtual bool fungible() const {
            return false;
        }
    private:
        string m_name;
        int m_purchasePrice;
};

class Painting : public Investment {
    public:
        Painting(string name, int purchasePrice) : Investment(name, purchasePrice) {

        }

        ~Painting() {
            cout << "Destroying " << name() << ", a painting" << endl;
        }

        virtual string description() const {
            return "painting";
        }

        virtual bool fungible() const {
            return false;
        }
};

class Stock : public Investment {
    public:
        Stock(string name, int purchasePrice, string tickerSymbol) : Investment(name, purchasePrice) {
            m_tickerSymbol = tickerSymbol;
        }

        ~Stock() {
            cout << "Destroying " << name() << ", a stock holding" << endl;
        }

        virtual string description() const {
            return "stock trading as " + m_tickerSymbol;
        }

        virtual bool fungible() const {
            return true;
        }
    private:
        string m_tickerSymbol;
};

class House : public Investment {
    public:
        House(string name, int purchasePrice) : Investment(name, purchasePrice) {

        }

        ~House() {
            cout << "Destroying the house " << name() << endl;
        }

        virtual string description() const {
            return "house";
        }

        virtual bool fungible() const {
            return false;
        }
};