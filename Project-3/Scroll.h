#ifndef SCROLL_INCLUDED
#define SCROLL_INCLUDED

#include "GameObject.h"

class Scroll : public GameObject {
    public:
        Scroll(int y, int x, string nm, Level* lvl);
        virtual ~Scroll();
        
        char getSymbol();
        virtual void read() = 0;
        virtual string extraMessage() = 0;
    private:
};

class ScrollOfTeleportation : public Scroll {
    public:
        ScrollOfTeleportation(int y, int x, Level* lvl);
        virtual void read();
        virtual string extraMessage();
    private:
};

class ScrollOfImproveArmor : public Scroll {
    public:
        ScrollOfImproveArmor(int y, int x, Level* lvl);
        virtual void read();
        virtual string extraMessage();
    private:
};

class ScrollOfRaiseStrength : public Scroll {
    public:
        ScrollOfRaiseStrength(int y, int x, Level* lvl);
        virtual void read();
        virtual string extraMessage();
    private:
};

class ScrollOfEnhanceHealth : public Scroll {
    public:
        ScrollOfEnhanceHealth(int y, int x, Level* lvl);
        virtual void read();
        virtual string extraMessage();
    private:
};

class ScrollOfEnhanceDexterity : public Scroll {
    public:
        ScrollOfEnhanceDexterity(int y, int x, Level* lvl);
        virtual void read();
        virtual string extraMessage();
    private:
};

#endif