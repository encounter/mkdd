#ifndef KARTDAMAGE_H
#define KARTDAMAGE_H

class KartDamage
{ // Autogenerated
public:
    KartDamage() {}
    void Init(int);                 // 0x80306cb0
    void ClrSetDamage();            // 0x80306d00
    void ClrAllDamage();            // 0x80306d14
    void TstSetDamage();            // 0x80306d24
    void SetDamager();              // 0x80306d3c
    void SetSetDamage();            // 0x80306dac
    void SetSetBurn();              // 0x80306e4c
    void SetSetBigDamage();         // 0x80306f34
    void SetDriverDamageAnime();    // 0x80306fd0
    void SetDriverEndDamageAnime(); // 0x80307064
    void SetDamageAnime();          // 0x803070c8
    void SetBurnAnime();            // 0x80307264
    void SetBigDamageAnime();       // 0x80307424
    void MakeHalfDamage();          // 0x803074e4
    void MakeDamage();              // 0x80307674
    void MakeBigDamage();           // 0x803076c4
    void MakeBurnDamage();          // 0x80307728
    void DoDamageCrl();             // 0x80307778
    // Inline/Unused
    // void SetThunderDamageAnime();
    // void DoAfterDamageCrl();
private:
    // TODO
};
#endif // KARTDAMAGE_H