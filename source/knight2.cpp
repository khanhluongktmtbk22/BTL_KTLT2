#include "knight2.h"

/* * * BEGIN implementation of class BaseBag * * */
BaseItem::BaseItem() {
    next = nullptr;
    itemType = Antidote;
}
BaseItem* BaseBag::get(ItemType itemType) {
    if (head == nullptr) return nullptr; 
    BaseItem* htemp = nullptr; 
    if (head->itemType == itemType) {
        htemp = head;
        head=head->next;
        count--;
        return htemp;
    }
    else if(head->next!=nullptr){
        if (head->next->itemType == itemType) {
            htemp = head->next;
            head->next = htemp->next;
            count--;
            return htemp;
        }
        else return nullptr;
    }
    for (BaseItem* temp = head->next; temp != nullptr && temp->next!=nullptr;) {
        if (temp->next->itemType == itemType) {
            htemp = temp->next;
            temp->next = head;
            head = head->next;
            temp->next->next = htemp->next;
            count--;
            return htemp;
        }
        temp = temp->next;
    }
    return htemp;
}
BaseItem* BaseBag::gethead() { return head; }
int  BaseBag::getcount() { return count; }
void BaseBag::sethead(BaseItem* head) { this->head = head; }
void  BaseBag::setcount(int count) { this->count = count; }
string BaseBag::toString() const {
    int c = count;
    string temp1 = "", temp2 = "";
    string out = ""; 
    BaseItem* htemp = head; 
    while (htemp != nullptr) {
        if (htemp->itemType == Antidote)
            temp2 = temp2 + "Antidote";
        else if (htemp->itemType == PhoenixI)
            temp2 = temp2 + "PhoenixI";
        else if (htemp->itemType == PhoenixII)
            temp2 = temp2 + "PhoenixII";
        else if (htemp->itemType == PhoenixIII)
            temp2 = temp2 + "PhoenixIII";
        else if (htemp->itemType == PhoenixIV)
            temp2 = temp2 + "PhoenixIV";
        if (htemp->next != nullptr)
            temp2 = temp2 + ",";
        htemp = htemp->next;
    }
    delete htemp;
    temp2 = temp2 + "]";
    stringstream fin;
    fin << c;
    getline(fin, temp1);
    out = "Bag[count=" + temp1 + ";" + temp2;
    return out;
}
bool BaseBag::insertFirst(BaseItem* item) {
    return false;
}
void BaseBag::xoaTop() {
    if (head != nullptr) {
        BaseItem* tempH = head;
        head = head->next;
        delete tempH;
        count--;
    }
}
BaseBag::~BaseBag() {
    for (int i = 0; i < count; i++) {
        xoaTop();
    }
}
/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */
string BaseKnight::toString() const {
    string typeString[4] = { "PALADIN", "LANCELOT", "DRAGON", "NORMAL" };
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id)
        + ",hp:" + to_string(hp)
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}
BaseKnight::~BaseKnight() {
    delete bag;
}
BaseBag* BaseKnight::getbag() { return bag; }
void BaseKnight::setbag(BaseBag* bag) { this->bag = bag; }
void BaseKnight::setgil(int gil) {
    this->gil = gil;
}
int BaseKnight::getgil() {
    return gil;
}
KnightType BaseKnight::gettype() {
    return knightType;
}
int BaseKnight::getlevel() {
    return level;
}
void BaseKnight::setlevel(int level) {
    this->level = level;
}
int BaseKnight::getHp() {
    return hp;
}
void BaseKnight::setHp(int hp) {
    this->hp = hp;
}
int BaseKnight::getMaxhp() {
    return maxhp;
}
int BaseKnight::getAntidote() {
    return antidote;
}
void BaseKnight::setAntidote(int antidote) {
    this->antidote = antidote;
}
bool BaseKnight::get_gomega() { return gomega; }
void BaseKnight::set_gomega(bool gomega) { this->gomega = gomega; }
/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight* lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}
ArmyKnights::ArmyKnights(const string& file_armyknights) {
    PaladinShield = 0;
    LancelotSpear = 0;
    GuinevereHair = 0;
    ExcaliburSword = 0;
    ifstream fknight;
    fknight.open(file_armyknights);
    int n, id, maxhp, level, gil, antidote, phoenixdownI;
    fknight >> n;
    soluongbd = n;
    soluong = n;
    mang_knight = new BaseKnight * [n];
    for (int i = 0; i < n; i++) {
        id = i + 1;
        fknight >> maxhp >> level >> phoenixdownI >> gil >> antidote;
        mang_knight[i] = BaseKnight::create(id, maxhp, level, gil, antidote, phoenixdownI);
    }
    fknight.close();
}
ArmyKnights::~ArmyKnights() {
   for (int i = 0; i < soluong; i++) {
        delete mang_knight[i];
    }
    delete[] mang_knight;
}
bool ArmyKnights::fight(BaseOpponent* opponent) {
    if (opponent->roido(lastKnight())) {
        if (opponent->gettype() == OMEGAWEAPON) {
            for (int i = 0; i < count(); i++) {
                mang_knight[i]->set_gomega(true);
            }
        }
        if (opponent->gettype() == HADES) {
            for (int i = 0; i < count(); i++) {
                mang_knight[i]->ghades = true;
            }
            PaladinShield = 1;
        } 
        return true;
    }
    else
    {
        if (lastKnight()->getgil() > 999) {
            if (count() == 1) {
                lastKnight()->setgil(999);
                return true;
            }
            int gildu = lastKnight()->getgil() - 999;
            lastKnight()->setgil(999);
            BaseKnight* knightT;
            for (int i = count()-2; i >=0; i--) {
                knightT = mang_knight[i];
                knightT->setgil(knightT->getgil() + gildu);
                if (knightT->getgil() > 999) {
                    gildu = knightT->getgil() - 999;
                    knightT->setgil(999);
                }
                else return true;
            }
            return true;
        }
        int i = 0; 
        ItemType tempItem = Antidote; 
        BaseItem* headt = (lastKnight()->getbag()->gethead());
        for (; i < lastKnight()->getbag()->getcount(); i++) {
            if (headt->canUse(lastKnight())) {
                tempItem = headt->itemType;
                headt = nullptr;
                break;
            }
            else headt = headt->next;
        }
        if (i < lastKnight()->getbag()->getcount()) {
            BaseItem* ptrt = lastKnight()->getbag()->get(tempItem);
            ptrt->use(lastKnight());
            delete ptrt;
            return true;
        }
        else if (lastKnight()->getgil() >= 100&&lastKnight()->getHp()==0) {
            lastKnight()->setHp(lastKnight()->getMaxhp() / 2);
            lastKnight()->setgil(lastKnight()->getgil() - 100);
            return true;
        }
        else {
            if (lastKnight()->getHp() <=0 )
                return false;
            else return true;
        }
    }
}
bool ArmyKnights::adventure(Events* events) {
    BaseOpponent* oppon = nullptr;
    for (int i = 1; i <= events->count(); i++) {
        if (events->get(i) == 1)
            oppon = new MadBear(i-1);
        else if (events->get(i) == 2)
            oppon = new Bandit(i-1);
        else if (events->get(i) == 3)
            oppon = new LordLupin(i-1);
        else if (events->get(i) == 4)
            oppon = new Elf(i-1);
        else if (events->get(i) == 5)
            oppon = new Troll(i-1);
        else if (events->get(i) == 6)
            oppon = new Tornbery(i-1);
        else if (events->get(i) == 7)
            oppon = new QueenOfCards(i-1);
        else if (events->get(i) == 8)
            oppon = new NinaDeRings();
        else if (events->get(i) == 9)
            oppon = new DurianGarden();
        else if (events->get(i) == 10)
            oppon = new OmegaWeapon();
        else if (events->get(i) == 11)
            oppon = new Hades();
        if (events->get(i)<12 && events->get(i)>0) {
            while (!fight(oppon)) {
                soluong--;
                break;
            }
            delete oppon;
        }
        if (events->get(i) == 99) {
            if (hasExcaliburSword()){
                printInfo();
                break;
            }
            else {
                if (hasGuinevereHair() && hasLancelotSpear() && hasPaladinShield()) {
                    int HPboss = 5000;
                    int slt = count();
                    int damage = 0;
                    for (int i = slt-1; i>=0; i--) {
                        if (mang_knight[i]->gettype() == NORMAL) {
                            continue;
                        }
                        else if (mang_knight[i]->gettype() == DRAGON) {
                            damage= 0.075 * (mang_knight[i]->getHp()) * (mang_knight[i]->getlevel());
                        }
                        else if (mang_knight[i]->gettype() == PALADIN) {
                            damage = 0.06 * (mang_knight[i]->getHp()) * (mang_knight[i]->getlevel());
                        }
                        else if (mang_knight[i]->gettype() == LANCELOT) {
                            damage = 0.05 * (mang_knight[i]->getHp()) * (mang_knight[i]->getlevel());
                        }
                        HPboss -= damage;
                        if (HPboss > 0) {
                            mang_knight[i]->setHp(0);
                            soluong--;
                        }
                        else break; 
                    }
                    if (HPboss > 0) soluong = 0;
                }
                else soluong = 0;
            }
        } 
        else if (events->get(i) == 112 or events->get(i) == 113 or events->get(i) == 114) {
            BaseItem* itemTemp = nullptr;
            BaseKnight* temp = nullptr;
            if (events->get(i) == 112) {
                itemTemp= new PhoenixDownII;
            }
            else if(events->get(i) == 113){
                itemTemp = new PhoenixDownIII;
            }
            else if(events->get(i) == 114){
                itemTemp = new PhoenixDownIV;
            }
            for (int i = count()-1; i >=0; i--) {
                temp = mang_knight[i];
                if (temp->getbag()->insertFirst(itemTemp)) {
                    break;
                }
            }
            itemTemp = nullptr;
            temp = nullptr;
            delete itemTemp;
            delete temp;
        }
        else if (events->get(i) == 95) {
            PaladinShield = 1;
        }
        else if (events->get(i) == 96) {
            LancelotSpear = 1;
        }
        else if (events->get(i) == 97) {
            GuinevereHair = 1;
        }
        else if (events->get(i) == 98) {
            if (hasGuinevereHair() && hasLancelotSpear() && hasPaladinShield()) {
                ExcaliburSword = 1;
            }
        }
        printInfo();
        if (count()==0) return false;
    }
    return true;
}
int ArmyKnights::count() const {
    return soluong;
}
BaseKnight* ArmyKnights::lastKnight() const {
    if (soluong == 0) return nullptr;
    int hpd = 0;
    for (int i = soluongbd - 1; i >= 0; i--) {
        if (mang_knight[i]->getHp() > 0) {
            hpd++;
        }
    }
    if (hpd < soluong) return mang_knight[soluong - 1];
    else {
        for (int i = soluongbd - 1; i >= 0; i--) {
            if (mang_knight[i]->getHp() > 0) {
                return mang_knight[i];
            }
        }
    }
}
bool ArmyKnights::hasPaladinShield() const {
    if (PaladinShield) return true;
    else return false;
}
bool ArmyKnights::hasLancelotSpear() const {
    if (LancelotSpear) return true;
    else return false;
}
bool ArmyKnights::hasGuinevereHair() const {
    if (GuinevereHair) return true;
    else return false;
}
bool ArmyKnights::hasExcaliburSword() const {
    if (ExcaliburSword) return true;
    else return false;
}
/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}
KnightAdventure::~KnightAdventure() {
    delete armyKnights;
    delete events;
    armyKnights = nullptr;
    events = nullptr;
}
void KnightAdventure::loadArmyKnights(const string& file_armyknights) {
    armyKnights = new  ArmyKnights(file_armyknights);
}
void KnightAdventure::loadEvents(const string& file_events) {
    events = new Events(file_events);
}
void KnightAdventure::run() {
    armyKnights->printResult(armyKnights->adventure(events));
}

/* * * END implementation of class KnightAdventure * * */
Events::Events(const string& file_events) {
    int n, skt;
    ifstream fevent;
    fevent.open(file_events);
    fevent >> n;
    numevent = n;
    events_arr = new int[n];
    for (int i = 0; i < n; i++) {
        fevent >> skt;
        events_arr[i] = skt;
    }
    fevent.close();
}
int Events::get(int i) const {
    return events_arr[i - 1];
}
int Events::count() const {
    return numevent;
}
Events::~Events() {
    delete[] events_arr;
}
BaseKnight::BaseKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) {
    this->id = id;
    this->maxhp = maxhp;
    this->level = level;
    this->gil = gil;
    this->antidote = antidote;
    this->gomega = false;
    this->hp = maxhp;
    this->bag = nullptr;
    this->knightType = NORMAL;
    this->gomega = false;
    this->ghades = false;
}
BaseKnight* BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) {
    int kt = 0;
    int a=0, b=0, c=0;
    for (int i = 1; i <= maxhp; i++) {
        if (maxhp % i == 0) kt++;
    }
    if (maxhp >= 100 && maxhp <= 999) {
         c = maxhp % 10;
         b = (maxhp / 10) % 10;
         a = (maxhp / 100) % 10;
    }
    if (kt == 2) { 
        return new  PaladinKnight(id, maxhp, level, gil, antidote, phoenixdownI); 
    }
    else if (maxhp == 888) {
        return new LancelotKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    }
    else if (a != 0 && b!=0 && c!=0 && (a * a == c * c + b * b or b * b == a * a + c * c or c * c == b * b + a * a)) {
            return new DragonKnight(id, maxhp, level, gil, antidote, phoenixdownI);
        }
    else {
        return new NormalKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    }
}
DragonKnight::DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
    :BaseKnight(id, maxhp, level, gil, antidote, phoenixdownI) {
    this->knightType = DRAGON;
    bag = new Dragon_bag(this, antidote, phoenixdownI);
}
NormalKnight::NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
    :BaseKnight(id, maxhp, level, gil, antidote, phoenixdownI) {
    this->knightType = NORMAL;
    bag = new Normal_bag(this, antidote, phoenixdownI);
}
LancelotKnight::LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
    :BaseKnight(id, maxhp, level, gil, antidote, phoenixdownI) {
    this->knightType = LANCELOT;
    bag = new Lancelot_bag(this, antidote, phoenixdownI);
}
PaladinKnight::PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
    :BaseKnight(id, maxhp, level, gil, antidote, phoenixdownI) {
    this->knightType = PALADIN;
    bag = new Paladin_bag(this, antidote, phoenixdownI);
}
Dragon_bag::Dragon_bag(BaseKnight* knight, int antidote, int phoenixI) {
    head = nullptr;
    count = 0;
    this->knight = knight;
    if (phoenixI > 0) {
        for (int i = 0; i < phoenixI; i++) {
            BaseItem* chen = new PhoenixDownI;
            insertFirst(chen);
            chen = nullptr;
        }
        for (int i = 0; i < antidote; i++) {
            BaseItem* chen = new Antidotec;
            insertFirst(chen);
            chen = nullptr;
        }
    }
    else {
        for (int i = 0; i < antidote; i++) {
            BaseItem* chen = new Antidotec;
            insertFirst(chen);
            chen = nullptr;
        }
    }
}
bool Dragon_bag::insertFirst(BaseItem* item) {
    if (count <= 14 && item->itemType != Antidote) {
        item->next = head;
        head = item;
        count++;
        return true;
    }
    else {
        return false;
    }
}
Paladin_bag::Paladin_bag(BaseKnight* knight, int antidote, int phoenixI) {
    head = nullptr;
    count = 0;
    this->knight = knight;
    if (phoenixI > 0) {
        for (int i = 0; i < phoenixI; i++) {
            BaseItem* chen = new PhoenixDownI;
            insertFirst(chen);
            chen = nullptr;
        }
        for (int i = 0; i < antidote; i++) {
            BaseItem* chen = new Antidotec;
            insertFirst(chen);
            chen = nullptr;
        }
    }
    else {
        for (int i = 0; i < antidote; i++) {
            BaseItem* chen = new Antidotec;
            insertFirst(chen);
            chen = nullptr;
        }
    }
}
bool Paladin_bag::insertFirst(BaseItem* item) {
    item->next = head;
    head = item;
    count++;
    return true;
}
Lancelot_bag::Lancelot_bag(BaseKnight* knight, int antidote, int phoenixI)  {
    head = nullptr;
    count = 0;
    this->knight = knight;
    if (phoenixI > 0) {
        for (int i = 0; i < phoenixI; i++) {
            BaseItem* chen = new PhoenixDownI;
            insertFirst(chen);
            chen = nullptr;
        }
        for (int i = 0; i < antidote; i++) {
            BaseItem* chen = new Antidotec;
            insertFirst(chen);
            chen = nullptr;
        }
    }
    else {
        for (int i = 0; i < antidote; i++) {
            BaseItem* chen = new Antidotec;
            insertFirst(chen);
            chen = nullptr;
        }
    }
}
bool Lancelot_bag::insertFirst(BaseItem* item) {
    if (count <= 16) {
        item->next = head;
        head = item;
        count++;
        return true;
    }
    else {
        return false;
    }
}
Normal_bag::Normal_bag(BaseKnight* knight, int antidote, int phoenixI) {
    head = nullptr;
    count = 0;
    this->knight = knight;
    if (phoenixI > 0) {
        for (int i = 0; i < phoenixI; i++) {
            BaseItem* chen1 = new PhoenixDownI;
            insertFirst(chen1);
            chen1 = nullptr;
        }
        for (int i = 0; i < antidote; i++) {
            BaseItem* chen2 = new Antidotec;
            insertFirst(chen2);
            chen2 = nullptr;
        }
    }
    else {
        for (int i = 0; i < antidote; i++) {
            BaseItem* chen3 = new Antidotec;
            insertFirst(chen3);
            chen3 = nullptr;
        }
    }
}
bool Normal_bag::insertFirst(BaseItem* item) {
    if (count <= 19) {
        item->next = head;
        head = item; 
        count++; 
        return true;
    }
    else {

        return false;
    }
}
Antidotec::Antidotec() {
    next = nullptr;
    itemType = Antidote;
}
PhoenixDownI::PhoenixDownI() {
    next = nullptr;
    itemType = PhoenixI;
}
PhoenixDownII::PhoenixDownII() {
    next = nullptr;
    itemType = PhoenixII;
}
PhoenixDownIII::PhoenixDownIII() {
    next = nullptr;
    itemType = PhoenixIII;
}
PhoenixDownIV::PhoenixDownIV() {
    next = nullptr;
    itemType = PhoenixIV;
}
bool Antidotec::canUse(BaseKnight* knight) {
    return false;
}
void Antidotec::use(BaseKnight* knight) {
    return;
}
bool PhoenixDownI::canUse(BaseKnight* knight) {
    if (knight->getHp() <= 0) return true;
    else return false;
}
void PhoenixDownI::use(BaseKnight* knight) {
    knight->setHp(knight->getMaxhp());
}
bool PhoenixDownII::canUse(BaseKnight* knight) {
    if (knight->getHp() < knight->getMaxhp() / 4) return true;
    else return false;
}
void PhoenixDownII::use(BaseKnight* knight) {
    knight->setHp(knight->getMaxhp());
}
bool PhoenixDownIII::canUse(BaseKnight* knight) {
    if (knight->getHp() < knight->getMaxhp() / 3) return true;
    else return false;
}
void PhoenixDownIII::use(BaseKnight* knight) {
    if (knight->getHp() <= 0) knight->setHp(knight->getMaxhp() / 3);
    else knight->setHp(knight->getHp() + knight->getMaxhp() / 4);
}
bool PhoenixDownIV::canUse(BaseKnight* knight) {
    if (knight->getHp() < knight->getMaxhp() / 2) return true;
    else return false;
}
void PhoenixDownIV::use(BaseKnight* knight) {
    if (knight->getHp() <= 0) knight->setHp(knight->getMaxhp() / 2);
    else knight->setHp(knight->getHp() + knight->getMaxhp() / 5);
}
bool BaseOpponent::roido(BaseKnight* knight) {
    if (knight->getlevel() >= levelO or knight->gettype() == LANCELOT
        or knight->gettype() == PALADIN) {
        knight->setgil(knight->getgil() + gil);
        if (knight->getgil() > 999)
            knight->setgil(999);
        return true;
    }
    else {
        knight->setHp(knight->getHp() - damagebase * (levelO - knight->getlevel()));
        if (knight->getHp() < 0) knight->setHp(0);
        return false;
    }
}
OpponentType BaseOpponent::gettype() {
    return opponentType;
}
MadBear::MadBear(int ski){
    levelO = (ski + 1) % 10 + 1;
    gil = 100;
    damagebase = 10;
    opponentType = MADBEAR;
    }
Bandit::Bandit(int ski) {
    levelO = (ski + 2) % 10 + 1;
    gil = 150;
    damagebase = 15;
    opponentType = BANDIT;
}
LordLupin::LordLupin(int ski) {
    levelO = (ski + 3) % 10 + 1;
    gil = 450;
    damagebase = 45;
    opponentType = LORDLUPIN;
}
Elf::Elf(int ski) {
    levelO = (ski + 4) % 10 + 1;
    gil = 750;
    damagebase = 75;
    opponentType = ELF;
}
Troll::Troll(int ski) {
    levelO = (ski + 5) % 10 + 1;
    gil = 800;
    damagebase = 95;
    opponentType = TROLL;
}
Tornbery::Tornbery(int ski) {
    levelO = (ski + 6) % 10 + 1;
    opponentType = TORNBERY;
}
QueenOfCards::QueenOfCards(int ski) {
    levelO = (ski + 7) % 10 + 1;
    opponentType = QUEENOFCARDS;
}
NinaDeRings::NinaDeRings() {
    opponentType = NINADERINGS;
}
DurianGarden::DurianGarden() {
    opponentType = DURIANGARDEN;
}
OmegaWeapon::OmegaWeapon() {
    opponentType = OMEGAWEAPON;
}
Hades::Hades() {
    opponentType = HADES;
}
bool Tornbery::roido(BaseKnight* knight) {
    if (knight->getlevel() >= levelO) {
        knight->setlevel(knight->getlevel() + 1);
        if (knight->getlevel() > 10) {
            knight->setlevel(10);
        }
        return true;
    }
    else 
    {
        if (knight->gettype() == DRAGON) return true;
        BaseItem* itemT = knight->getbag()->get(Antidote);
        if (itemT != nullptr) {
            itemT->use(knight);
            delete itemT;
            return true;
        }
        else {
            for (int i = 0; i < 3; i++) {
                knight->getbag()->xoaTop();
            }
            knight->setHp(knight->getHp() - 10);
            if (knight->getHp() < 0) knight->setHp(0);
            return false;
        }
    }
}
bool QueenOfCards::roido(BaseKnight* knight) {
    if (knight->getlevel() >= levelO) {
        knight->setgil((knight->getgil())* 2);
            return false;
    }
    else {
        if (knight->gettype() == PALADIN) return true;
        knight->setgil(knight->getgil() / 2);
        return true;
    }
}
bool  NinaDeRings::roido(BaseKnight* knight) {
    if(knight->getHp()<knight->getMaxhp()/3){
        knight->setgil(knight->getgil() - 50);
        knight->setHp(knight->getHp() + knight->getMaxhp() / 5);
        if(knight->gettype()==PALADIN){
            knight->setgil(knight->getgil() + 50); }
    }
    return true;
}
bool DurianGarden::roido(BaseKnight* knight) {
    knight->setHp(knight->getMaxhp());
    return true;
}
bool OmegaWeapon::roido(BaseKnight* knight) {
    if (knight->get_gomega()) return true;
    if (((knight->getHp() == knight->getMaxhp()) && knight->getlevel() == 10) || knight->gettype() == DRAGON) {
        knight->setlevel(10);
        knight->setgil(999);
        knight->set_gomega(true);
        return true;
        
    }
    else {
        knight->setHp(0);
        return false;
    }
}
bool Hades::roido(BaseKnight* knight) {
    if (knight->ghades) return true;
    else if (knight->getlevel() == 10 || (knight->gettype() == PALADIN && knight->getlevel() >= 8)) {
        return true;
    }
    else {
        knight->setHp(0);
        return false;
    }
}


