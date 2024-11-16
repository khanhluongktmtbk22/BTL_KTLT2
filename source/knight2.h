#pragma once
#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"
// #define DEBUG
class BaseKnight;
class Events;
class Antidotec;
class PhoenixDownI;
class PhoenixDownII;
class PhoenixDownIII;
class PhoenixDownIV;
class BaseItem;
class BaseBag;
enum ItemType {
    Antidote = 0, PhoenixI,
    PhoenixII, PhoenixIII, PhoenixIV
};
class BaseItem {
public:
    BaseItem();
    virtual bool canUse(BaseKnight* knight) = 0;
    virtual void use(BaseKnight* knight) = 0;
    BaseItem* next;
    ItemType itemType;
};
class Antidotec :public BaseItem {
public:
    Antidotec();
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};
class PhoenixDownI :public BaseItem {
public:
    PhoenixDownI();
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};
class PhoenixDownII : public BaseItem {
public:
    PhoenixDownII();
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};
class PhoenixDownIII :public BaseItem {
public:
    PhoenixDownIII();
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};
class PhoenixDownIV :public BaseItem {
public:
    PhoenixDownIV();
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};
class BaseBag {
public:
    virtual bool insertFirst(BaseItem* item);
    virtual BaseItem* get(ItemType itemType);
    virtual string toString() const;
    BaseItem* gethead();
    int getcount();
    void sethead(BaseItem* head);
    void setcount(int count);
    void xoaTop();
    ~BaseBag();
protected:
    BaseItem* head=nullptr;
    int count=0;
    BaseKnight* knight=nullptr;
};
class Dragon_bag : public BaseBag {
public:
    Dragon_bag(BaseKnight* knight, int antidote, int phoenixI);
    bool insertFirst(BaseItem* item);

};
class Paladin_bag : public BaseBag {
public:
    Paladin_bag(BaseKnight* knight, int antidote, int phoenixI);
    bool insertFirst(BaseItem* item);

};
class Lancelot_bag : public BaseBag {
public:
    Lancelot_bag(BaseKnight* knight, int antidote, int phoenixI);
    bool insertFirst(BaseItem* item);

};
class Normal_bag : public BaseBag {
public:
    bool insertFirst(BaseItem* item);
    Normal_bag(BaseKnight* knight, int antidote, int phoenixI);
};
enum OpponentType {
    MADBEAR = 0, BANDIT, LORDLUPIN, ELF, TROLL, TORNBERY, QUEENOFCARDS,
    NINADERINGS, DURIANGARDEN, OMEGAWEAPON, HADES
};
class BaseOpponent {
public:
    virtual bool roido(BaseKnight* knight);
    OpponentType gettype();
protected:
    int levelO = 0;
    int gil = 0;
    int damagebase = 0;
    OpponentType opponentType= HADES;
};
class MadBear : public BaseOpponent {
public:
    MadBear(int ski);
};
class Bandit : public BaseOpponent {
public:
    Bandit(int ski);
};
class LordLupin : public BaseOpponent {
public:
    LordLupin(int ski);
};
class Elf : public BaseOpponent {
public:
    Elf(int ski);
};
class Troll : public BaseOpponent {
public:
    Troll(int ski);
};
class Tornbery : public BaseOpponent {
public:
    Tornbery(int ski);
    bool roido(BaseKnight* knight);
};
class QueenOfCards : public BaseOpponent {
public:
    QueenOfCards(int ski);
    bool roido(BaseKnight* knight);
};
class NinaDeRings : public BaseOpponent {
public:
    NinaDeRings();
    bool roido(BaseKnight* knight);
};
class DurianGarden : public BaseOpponent {
public:
    DurianGarden();
    bool roido(BaseKnight* knight);
};
class OmegaWeapon : public BaseOpponent {
public:
    OmegaWeapon();
    bool roido(BaseKnight* knight);
};
class Hades : public BaseOpponent {
public:
    Hades();
    bool roido(BaseKnight* knight);
};
enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    BaseBag* bag;
    KnightType knightType;
    bool gomega;
public:
    ~BaseKnight();
    BaseKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    static BaseKnight* create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
    int getHp();
    void setHp(int hp);
    int getMaxhp();
    int getAntidote();
    void setAntidote(int antidote);
    bool get_gomega();
    void set_gomega(bool gomega);
    int getlevel();
    void setlevel(int level);
    KnightType gettype();
    void setgil(int gil);
    int getgil();
    BaseBag* getbag();
    void setbag(BaseBag* bag);
    bool ghades;
};
class PaladinKnight : public BaseKnight {
public:
    PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
};
class LancelotKnight : public BaseKnight {
public:
    LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
};
class DragonKnight :public BaseKnight {
public:
    DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
};
class NormalKnight : public BaseKnight {
public:
    NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
};

class ArmyKnights {
public:
    ArmyKnights(const string& file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent* opponent);
    bool adventure(Events* events);
    int count() const;
    BaseKnight* lastKnight() const;

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;
private:
    BaseKnight** mang_knight;
    int soluong, soluongbd;
    int PaladinShield, LancelotSpear, GuinevereHair, ExcaliburSword;
};
class Events {
public:
    Events(const string& file_events);
    int count() const;
    int get(int i) const;
    ~Events();
private:
    int* events_arr;
    int numevent;
};

class KnightAdventure {
private:
    ArmyKnights* armyKnights;
    Events* events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string& file_armyknights);
    void loadEvents(const string& file_events);
    void run();
};

#endif // __KNIGHT2_H__